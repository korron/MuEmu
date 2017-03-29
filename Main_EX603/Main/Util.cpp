#include "stdafx.h"
#include "Util.h"

BYTE NewAddressData1[240];
BYTE NewAddressData2[240];
BYTE NewAddressData3[6000];

void SetByte(DWORD offset,BYTE value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,1,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(BYTE*)(offset) = value;

	VirtualProtect((void*)offset,1,OldProtect,&OldProtect);
}

void SetWord(DWORD offset,WORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,2,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(WORD*)(offset) = value;

	VirtualProtect((void*)offset,2,OldProtect,&OldProtect);
}

void SetDword(DWORD offset,DWORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetFloat(DWORD offset,float value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(float*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetDouble(DWORD offset,double value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,8,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(double*)(offset) = value;

	VirtualProtect((void*)offset,8,OldProtect,&OldProtect);
}

void SetCompleteHook(BYTE head,DWORD offset,...) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,5,PAGE_EXECUTE_READWRITE,&OldProtect);

	if(head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset+1;

	*(DWORD*)(offset+1) = (*function)-(offset+5);

	VirtualProtect((void*)offset,5,OldProtect,&OldProtect);
}

void MemoryCpy(DWORD offset,void* value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memcpy((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void MemorySet(DWORD offset,DWORD value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memset((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void VirtualizeOffset(DWORD offset,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	DWORD HookAddr = (DWORD)malloc(size+5);

	memcpy((void*)HookAddr,(void*)offset,size);

	*(BYTE*)(HookAddr+size) = 0xE9;

	*(DWORD*)(HookAddr+size+1) = (offset+size)-((HookAddr+size)+5);

	*(BYTE*)(offset) = 0xE9;

	*(DWORD*)(offset+1) = HookAddr-(offset+5);

	memset((void*)(offset+5),0x90,(size-5));

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size) // OK
{
	BYTE XorTable[3] = {0xFC,0xCF,0xAB};

	for(int n=0;n < size;n++)
	{
		out_buff[n] = in_buff[n]^XorTable[n%3];
	}
}

char* ConvertModuleFileName(char* name) // OK
{
	static char buff[MAX_PATH] = {0};

	for(int n=strlen(name);n > 0;n--)
	{
		if(name[n] == '\\')
		{
			strcpy_s(buff,sizeof(buff),&name[(n+1)]);
			break;
		}
	}

	return buff;
}

void LoadReferenceAddressTable(HMODULE mod,char* name,DWORD address) // OK
{
	if(IS_INTRESOURCE(name) == 0)
	{
		return;
	}

	HRSRC resource = FindResource(mod,name,"BIN");

	if(resource == 0)
	{
		return;
	}

	if(SizeofResource(mod,resource) < sizeof(REFERENCE_INFO))
	{
		return;
	}

	HGLOBAL data = LoadResource(mod,resource);

	if(data == 0)
	{
		return;
	}

	REFERENCE_INFO* ReferenceInfo = (REFERENCE_INFO*)LockResource(data);

	if(ReferenceInfo == 0)
	{
		FreeResource(data);
		return;
	}

	if(ReferenceInfo->start == ReferenceInfo->end)
	{
		if(SizeofResource(mod,resource) < (sizeof(REFERENCE_INFO)+(ReferenceInfo->count*sizeof(REFERENCE_BASE))))
		{
			return;
		}

		REFERENCE_BASE* ReferenceBase = (REFERENCE_BASE*)((DWORD)ReferenceInfo+sizeof(REFERENCE_INFO));

		for(DWORD n=0;n < ReferenceInfo->count;n++)
		{
			SetDword(ReferenceBase[n].address,address);
		}
	}
	else
	{
		if(SizeofResource(mod,resource) < (sizeof(REFERENCE_INFO)+(ReferenceInfo->count*sizeof(REFERENCE_DATA))))
		{
			return;
		}

		REFERENCE_DATA* ReferenceData = (REFERENCE_DATA*)((DWORD)ReferenceInfo+sizeof(REFERENCE_INFO));

		for(DWORD n=0;n < ReferenceInfo->count;n++)
		{
			SetDword(ReferenceData[n].address,(address+ReferenceData[n].value));
		}
	}

	FreeResource(data);
}
