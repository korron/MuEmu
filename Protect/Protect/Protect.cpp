#include "stdafx.h"

BYTE* executable_data = 0;
DWORD executable_size = 0;
DWORD executable_info = 0;
static const BYTE gProtectTable[16] = {0xC8,0x9D,0x24,0xC2,0x10,0xDD,0xE1,0x66,0xF3,0x5D,0x35,0xD2,0xA8,0x96,0xC5,0x48};
static const BYTE gProtectInsertStart[16] = {0x74,0x91,0x8B,0xB7,0x52,0x44,0xCF,0xFC,0x30,0xBD,0xEA,0x71,0x2A,0x47,0xDC,0xED}; //{0xEB,0x0E,0x14,0x28,0xCD,0xDB,0x50,0x63,0xAF,0x22,0x75,0xEE,0xB5,0xD8,0x43,0x72}
static const BYTE gProtectInsertFinal[16] = {0x74,0x91,0xA8,0x6D,0x52,0x44,0xCF,0xFC,0x30,0xBD,0xEA,0x71,0x2A,0x47,0x1A,0xFE}; //{0xEB,0x0E,0x37,0xF2,0xCD,0xDB,0x50,0x63,0xAF,0x22,0x75,0xEE,0xB5,0xD8,0x85,0x61}
static const BYTE gProtectRemoveStart[16] = {0x5C,0x74,0x92,0xB7,0x52,0x44,0xCF,0xFC,0x30,0xBD,0xEA,0x71,0x2A,0x47,0xDC,0xED}; //{0xC3,0xEB,0x0D,0x28,0xCD,0xDB,0x50,0x63,0xAF,0x22,0x75,0xEE,0xB5,0xD8,0x43,0x72}
static const BYTE gProtectRemoveFinal[16] = {0x5C,0x74,0x92,0x6D,0x52,0x44,0xCF,0xFC,0x30,0xBD,0xEA,0x71,0x2A,0x47,0x1A,0xFE}; //{0xC3,0xEB,0x0D,0xF2,0xCD,0xDB,0x50,0x63,0xAF,0x22,0x75,0xEE,0xB5,0xD8,0x85,0x61}

void ProtectBlock(DWORD type);
void EncryptBlock(BYTE* data,int size);
void InsertMemoryMacro(BYTE* data,BYTE* info,int size);
bool VerifyMemoryMacro(BYTE* data,BYTE* info,int size);
bool GetInsertStartBlock(DWORD start_offset,DWORD final_offset,DWORD* start_block);
bool GetInsertFinalBlock(DWORD start_offset,DWORD final_offset,DWORD* start_block);
bool LoadExecutable(char* name);
bool SaveExecutable(char* name);
void ProtectExecutable(char* name);

void ProtectBlock(DWORD type) // OK
{
	DWORD start_offset = (DWORD)executable_data;

	DWORD final_offset = (DWORD)executable_data+executable_size;

	DWORD start_block,final_block;

	executable_info = 0;

	while(GetInsertStartBlock(start_offset,final_offset,&start_block) != 0 && GetInsertFinalBlock(start_block,final_offset,&final_block) != 0)
	{
		InsertMemoryMacro((BYTE*)start_block,(BYTE*)&gProtectRemoveStart[0],sizeof(gProtectRemoveStart));

		InsertMemoryMacro((BYTE*)final_block,(BYTE*)&gProtectRemoveFinal[0],sizeof(gProtectRemoveFinal));

		EncryptBlock((BYTE*)(start_block+sizeof(gProtectInsertStart)),(final_block-(start_block+sizeof(gProtectInsertStart))));

		start_offset = final_block+sizeof(gProtectInsertFinal);

		executable_info++;
	}
}

void EncryptBlock(BYTE* data,int size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)data,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	for(int n=0;n < size;n++)
	{
		data[n] = (data[n]+0xAF)^gProtectTable[(n%sizeof(gProtectTable))];
	}

	VirtualProtect((void*)data,size,OldProtect,&OldProtect);
}

void InsertMemoryMacro(BYTE* data,BYTE* info,int size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)data,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	for(int n=0;n < size;n++)
	{
		data[n] = info[n]^0x9F;
	}

	VirtualProtect((void*)data,size,OldProtect,&OldProtect);
}

bool VerifyMemoryMacro(BYTE* data,BYTE* info,int size) // OK
{
	for(int n=0;n < size;n++)
	{
		if(data[n] != (info[n]^0x9F))
		{
			return 0;
		}
	}

	return 1;
}

bool GetInsertStartBlock(DWORD start_offset,DWORD final_offset,DWORD* start_block) // OK
{
	for(DWORD offset=start_offset;offset < final_offset;offset++)
	{
		if((final_offset-offset) >= sizeof(gProtectInsertStart))
		{
			if(VerifyMemoryMacro((BYTE*)offset,(BYTE*)&gProtectInsertStart[0],sizeof(gProtectInsertStart)) != 0)
			{
				(*start_block) = offset;
				return 1;
			}
		}
	}

	return 0;
}

bool GetInsertFinalBlock(DWORD start_offset,DWORD final_offset,DWORD* final_block) // OK
{
	for(DWORD offset=start_offset;offset < final_offset;offset++)
	{
		if((final_offset-offset) >= sizeof(gProtectInsertFinal))
		{
			if(VerifyMemoryMacro((BYTE*)offset,(BYTE*)&gProtectInsertFinal[0],sizeof(gProtectInsertFinal)) != 0)
			{
				(*final_block) = offset;
				return 1;
			}
		}
	}

	return 0;
}

bool LoadExecutable(char* name) // OK
{
	HANDLE file = CreateFile(name,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	executable_size = GetFileSize(file,0);

	executable_data = new BYTE[executable_size];

	DWORD OutSize = 0;

	if(ReadFile(file,executable_data,executable_size,&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);
	return 1;
}

bool SaveExecutable(char* name) // OK
{
	HANDLE file = CreateFile(name,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if(WriteFile(file,executable_data,executable_size,&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	delete[] executable_data;

	executable_size = 0;

	CloseHandle(file);
	return 1;
}

void ProtectExecutable(char* name) // OK
{
	if(LoadExecutable(name) == 0)
	{
		printf("[LoadExecutable][%s] FAILED!\n",name);
		return;
	}

	ProtectBlock(0);

	if(executable_info > 0 && SaveExecutable(name) == 0)
	{
		printf("[SaveExecutable][%s] FAILED!\n",name);
		return;
	}

	printf("[SaveExecutable][%s] SUCCESS! (Macro count: %d)\n",name,executable_info);
}

int _tmain(int argc,_TCHAR* argv[]) // OK
{
	char CSName[MAX_PATH];
	char DSName[MAX_PATH];
	char GSName[MAX_PATH];
	char GCName[MAX_PATH];
	char JSName[MAX_PATH];

	GetPrivateProfileString("ProtectInfo","CSName","",CSName,sizeof(CSName),".\\Protect.ini");

	GetPrivateProfileString("ProtectInfo","DSName","",DSName,sizeof(DSName),".\\Protect.ini");

	GetPrivateProfileString("ProtectInfo","GSName","",GSName,sizeof(GSName),".\\Protect.ini");

	GetPrivateProfileString("ProtectInfo","GCName","",GCName,sizeof(GCName),".\\Protect.ini");

	GetPrivateProfileString("ProtectInfo","JSName","",JSName,sizeof(JSName),".\\Protect.ini");

	ProtectExecutable(CSName);

	ProtectExecutable(DSName);

	ProtectExecutable(GSName);

	ProtectExecutable(GCName);

	ProtectExecutable(JSName);

	Sleep(10000);

	return 0;
}
