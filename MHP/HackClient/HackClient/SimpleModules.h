#pragma once

#define MIN_HACK_VERIFY_SIZE 0
#define MAX_HACK_VERIFY_SIZE 256
#define MAX_HANDLE_PROTECTION_COUNT 5

#define CHECK_API_REDIRECT(x) (((x)==0)?0:((*(BYTE*)((x))==0xE9)?0:(x)))

struct HACK_VERIFY_FILE
{
	DWORD time;
	DWORD spid;
	DWORD tpid;
};

struct HACK_VERIFY_FILE_MAPPING
{
	void Clear() // OK
	{
		this->ReadVirtualMemoryCount = MIN_HACK_VERIFY_SIZE;
		this->ReadVirtualMemoryIndex = MIN_HACK_VERIFY_SIZE;
		this->WriteVirtualMemoryCount = MIN_HACK_VERIFY_SIZE;
		this->WriteVirtualMemoryIndex = MIN_HACK_VERIFY_SIZE;
	}

	DWORD ReadVirtualMemoryCount;
	DWORD ReadVirtualMemoryIndex;
	HACK_VERIFY_FILE ReadVirtualMemoryTable[MAX_HACK_VERIFY_SIZE];
	DWORD WriteVirtualMemoryCount;
	DWORD WriteVirtualMemoryIndex;
	HACK_VERIFY_FILE WriteVirtualMemoryTable[MAX_HACK_VERIFY_SIZE];
};

struct MEMORY_CHECK_SOURCE
{
	DWORD VirtualAddress;
	DWORD VirtualSize;
	DWORD VirtualChecksum;
};

void CheckSystemInformation();
bool GetPhysicalDriveSerialNumber(int PhysicalDriveNumber,char* PhysicalDriveSerial,int PhysicalDriveSerialSize);
bool API_INIT();
bool API_SCAN();
bool DEBUGGER_SCAN();
bool MEMORY_PROTECTION_INIT();
bool MEMORY_PROTECTION_SCAN();
bool HANDLE_PROTECTION_INIT();
bool HANDLE_PROTECTION_SCAN();
bool LIBRARY_LOAD_ATTACH();
bool LIBRARY_LOAD_DETACH();
bool MEMORY_CHECK_ATTACH();
bool MEMORY_CHECK_DETACH();
