#include "StdAfx.h"
#include "Utils.h"

struct FAIL_FILE_DATA_BLOCK
{
	DWORD off;
	BYTE size;
};

std::map<int,FAIL_FILE_DATA_BLOCK> gFailFileDataBlock;

void CreateFailFile(char* name)
{
	HANDLE file = CreateFile(name,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return;
	}

	DWORD OutSize = 0;

	DWORD count = gFailFileDataBlock.size();

	WriteFile(file,&count,sizeof(count),&OutSize,0);

	if(count > 0)
	{
		FAIL_FILE_DATA_BLOCK* dblock = new FAIL_FILE_DATA_BLOCK[count];

		int ID = 0;

		for(std::map<int,FAIL_FILE_DATA_BLOCK>::iterator it=gFailFileDataBlock.begin();it != gFailFileDataBlock.end();it++)
		{
			memcpy(&dblock[ID],&it->second,sizeof(FAIL_FILE_DATA_BLOCK));

			ID++;
		}

		WriteFile(file,dblock,sizeof(FAIL_FILE_DATA_BLOCK)*count,&OutSize,0);

		delete[] dblock;
	}

	CloseHandle(file);
}

void ReadFailFile(char* name)
{
	HANDLE file = CreateFile(name,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return;
	}

	DWORD OutSize = 0;

	DWORD count = 0;

	ReadFile(file,&count,sizeof(count),&OutSize,0);

	if(count > 0)
	{
		FAIL_FILE_DATA_BLOCK* dblock = new FAIL_FILE_DATA_BLOCK[count];

		ReadFile(file,dblock,sizeof(FAIL_FILE_DATA_BLOCK)*count,&OutSize,0);

		for(DWORD n=0;n < count;n++)
		{
			if(dblock[n].off > 0x09000000)
			{
				gFailFileDataBlock.insert(std::pair<int,FAIL_FILE_DATA_BLOCK>(dblock[n].off,dblock[n]));
			}
		}

		delete[] dblock;
	}

	CloseHandle(file);
}

int GetOpcodeSize(BYTE opcode,BYTE spcode)
{
	int size = 0;

	switch(opcode)
	{
	case 0x83:
		switch(spcode)
		{
		case 0x7C:
			size = 5;
			break;
		default:
			break;
		}
		break;
	case 0x88:
		switch(spcode)
		{
		case 0x01:
			size = 2;
			break;
		case 0x08:
			size = 2;
			break;
		case 0x10:
			size = 2;
			break;
		default:
			break;
		}
		break;
	case 0x89:
		switch(spcode)
		{
		case 0x02:
			size = 2;
			break;
		case 0x07:
			size = 2;
			break;
		case 0x08:
			size = 2;
			break;
		case 0x0D:
			size = 6;
			break;
		case 0x11:
			size = 2;
			break;
		case 0x14:
			size = 7;
			break;
		case 0x15:
			size = 6;
			break;
		case 0x17:
			size = 2;
			break;
		case 0x18:
			size = 2;
			break;
		case 0x47:
			size = 3;
			break;
		case 0x48:
			size = 3;
			break;
		case 0x4F:
			size = 3;
			break;
		default:
			break;
		}
		break;
	case 0x8A:
		switch(spcode)
		{
		case 0x44:
			size = 4;
			break;
		default:
			break;
		}
		break;
	case 0xA3:
		size = 5;
		break;
	case 0xF3:
		switch(spcode)
		{
		case 0xA4:
			size = 2;
			break;
		case 0xA5:
			size = 2;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return size;
}

void AutoFixStart()
{
	ReadFailFile("FailFile.txt");
	ReadFailFile("FailFileExtra.txt");

	int FixCount = 0;

	for(std::map<int,FAIL_FILE_DATA_BLOCK>::iterator it=gFailFileDataBlock.begin();it != gFailFileDataBlock.end();it++)
	{
		HookSET((LPVOID)it->second.off,0x90,it->second.size);
		FixCount++;
	}

#if(_DEBUG_CONSOLE == TRUE)
	cLog.ConsoleOutput("FIX COUNT = %d",FixCount);
#endif
}