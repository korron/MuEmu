#include "stdafx.h"
#include "SimpleModules.h"
#include "CCRC32.h"
#include "HackServerProtocol.h"
#include "Log.h"
#include "ProcessQuery.h"
#include "Util.h"

DWORD API_Address_Count = 0;
DWORD API_Address_Table[64] = {0};
HANDLE FileMappingHandle;
HACK_VERIFY_FILE_MAPPING* lpHackVerifyFileMapping;
DWORD MemoryProtectionTime;
DWORD HandleProtectionNumber;
DWORD HandleProtectionObject;
BYTE LibraryLoadSource[6];
std::map<DWORD,MEMORY_CHECK_SOURCE> MemoryCheckSource;

void CheckSystemInformation() // OK
{
	gLog.Output(LOG_DEBUG,"----------------------------------------------------------------------------------------------------");

	OSVERSIONINFO osvi;

	ZeroMemory(&osvi,sizeof(OSVERSIONINFO));

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osvi);

	MEMORYSTATUSEX mstx;

	mstx.dwLength = sizeof(mstx);

	GlobalMemoryStatusEx(&mstx);

	gLog.Output(LOG_DEBUG,GetEncryptedString(0),HACKCLIENT_VERSION,osvi.dwMajorVersion,osvi.dwMinorVersion,osvi.dwBuildNumber,(int)(((mstx.ullTotalPhys-mstx.ullAvailPhys)/1024)/1024),(int)((mstx.ullTotalPhys/1024)/1024));
}

bool GetPhysicalDriveSerialNumber(int PhysicalDriveNumber,char* PhysicalDriveSerial,int PhysicalDriveSerialSize) // OK
{
	char PhysicalDrivePath[MAX_PATH];

	wsprintf(PhysicalDrivePath,"\\\\.\\PhysicalDrive%d",PhysicalDriveNumber);

	HANDLE PhysicalDriveHandle = CreateFile(PhysicalDrivePath,0,FILE_SHARE_READ | FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);

	if(PhysicalDriveHandle == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD BytesReturned;

	STORAGE_PROPERTY_QUERY StoragePropertyQuery;

	STORAGE_DESCRIPTOR_HEADER StorageDescriptorHeader;

	memset(&StoragePropertyQuery,0,sizeof(StoragePropertyQuery));

	memset(&StorageDescriptorHeader,0,sizeof(StorageDescriptorHeader));

	StoragePropertyQuery.PropertyId = StorageDeviceProperty;

	StoragePropertyQuery.QueryType = PropertyStandardQuery;

	if(DeviceIoControl(PhysicalDriveHandle,IOCTL_STORAGE_QUERY_PROPERTY,&StoragePropertyQuery,sizeof(StoragePropertyQuery),&StorageDescriptorHeader,sizeof(StorageDescriptorHeader),&BytesReturned,0) == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		return 0;
	}

	BYTE* PhysicalDriveBuff = new BYTE[StorageDescriptorHeader.Size];

	memset(PhysicalDriveBuff,0,StorageDescriptorHeader.Size);

	if(DeviceIoControl(PhysicalDriveHandle,IOCTL_STORAGE_QUERY_PROPERTY,&StoragePropertyQuery,sizeof(StoragePropertyQuery),PhysicalDriveBuff,StorageDescriptorHeader.Size,&BytesReturned,0) == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}

	if(((STORAGE_DEVICE_DESCRIPTOR*)PhysicalDriveBuff)->SerialNumberOffset == 0)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}

	__try
	{
		strcpy_s(PhysicalDriveSerial,PhysicalDriveSerialSize,(char*)(PhysicalDriveBuff+((STORAGE_DEVICE_DESCRIPTOR*)PhysicalDriveBuff)->SerialNumberOffset));
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 1;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		CloseHandle(PhysicalDriveHandle);
		delete[] PhysicalDriveBuff;
		return 0;
	}
}

bool API_INIT() // OK
{
	CProcessQuery::m_NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle("Ntdll.dll"),"NtQuerySystemInformation");

	API_Address_Table[API_Address_Count++] = (DWORD)GetProcAddress(GetModuleHandle("Kernel32.dll"),"OpenProcess");

	API_Address_Table[API_Address_Count++] = (DWORD)GetProcAddress(GetModuleHandle("Kernel32.dll"),"ExitProcess");

	API_Address_Table[API_Address_Count++] = (DWORD)GetProcAddress(GetModuleHandle("Kernel32.dll"),"TerminateProcess");

	API_Address_Table[API_Address_Count++] = (DWORD)GetProcAddress(GetModuleHandle("Kernel32.dll"),"CreateThread");

	API_Address_Table[API_Address_Count++] = (DWORD)GetProcAddress(GetModuleHandle("Kernel32.dll"),"QueryPerformanceCounter");

	API_Address_Table[API_Address_Count++] = (DWORD)GetProcAddress(GetModuleHandle("Kernel32.dll"),"QueryPerformanceFrequency");

	API_Address_Table[API_Address_Count++] = CHECK_API_REDIRECT((DWORD)GetProcAddress(GetModuleHandle("Kernel32.dll"),"GetTickCount"));

	API_Address_Table[API_Address_Count++] = CHECK_API_REDIRECT((DWORD)GetProcAddress(GetModuleHandle("Ntdll.dll"),"ZwOpenProcess"));

	API_Address_Table[API_Address_Count++] = CHECK_API_REDIRECT((DWORD)GetProcAddress(GetModuleHandle("Ntdll.dll"),"ZwTerminateProcess"));

	API_Address_Table[API_Address_Count++] = CHECK_API_REDIRECT((DWORD)GetProcAddress(GetModuleHandle("Ntdll.dll"),"ZwSuspendProcess"));

	API_Address_Table[API_Address_Count++] = CHECK_API_REDIRECT((DWORD)GetProcAddress(GetModuleHandle("Ntdll.dll"),"ZwSuspendThread"));

	return API_SCAN();
}

bool API_SCAN() // OK
{
	for(DWORD n=0;n < API_Address_Count;n++)
	{
		if(API_Address_Table[n] == 0)
		{
			continue;
		}

		BYTE opcode = *(BYTE*)(API_Address_Table[n]);

		switch(opcode)
		{
			case 0x68:
			case 0xC2:
			case 0xC3:
			case 0xE8:
			case 0xE9:
			case 0xFF:
				CHClientDisconnectSend(CLIENT_DISCONNECT_MEMORY_DETECTION,0,0);
				return 0;
		}
	}

	return 1;
}

bool DEBUGGER_SCAN() // OK
{
	BOOL IsDebuggerPresent = 0;

	_asm
	{
		Mov Eax,Dword Ptr Fs:[0x30]
		Movzx Ecx,Byte Ptr Ds:[Eax+0x02]
		Mov IsDebuggerPresent,Ecx
	}

	if(IsDebuggerPresent != 0)
	{
		CHClientDisconnectSend(CLIENT_DISCONNECT_DEBUGGER_DETECTION,0,0);
		return 0;
	}

	CProcessQuery ProcessQuery;

	if(ProcessQuery.Fetch(SystemKernelDebuggerInformation,sizeof(SYSTEM_KERNEL_DEBUGGER_INFO)) != 0)
	{
		SYSTEM_KERNEL_DEBUGGER_INFO* lpSystemKernelDebuggerInfo = ProcessQuery.GetKernelDebuggerInfo();

		if(lpSystemKernelDebuggerInfo != 0)
		{
			if(lpSystemKernelDebuggerInfo->DebuggerEnabled != 0 && lpSystemKernelDebuggerInfo->DebuggerNotPresent == 0)
			{
				CHClientDisconnectSend(CLIENT_DISCONNECT_DEBUGGER_DETECTION,0,0);
				return 0;
			}
		}
	}

	ProcessQuery.Close();

	return 1;
}

bool MEMORY_PROTECTION_INIT() // OK
{
	bool ClearFileMapping = 0;

	if((FileMappingHandle=CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,sizeof(HACK_VERIFY_FILE_MAPPING),"Local\\HACK_VERIFY_FILE_MAPPING")) == 0)
	{
		return 0;
	}

	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		ClearFileMapping = 0;
	}
	else
	{
		ClearFileMapping = 1;
	}

	if((lpHackVerifyFileMapping=(HACK_VERIFY_FILE_MAPPING*)MapViewOfFile(FileMappingHandle,FILE_MAP_ALL_ACCESS,0,0,sizeof(HACK_VERIFY_FILE_MAPPING))) == 0)
	{
		return 0;
	}

	if(ClearFileMapping != 0)
	{
		lpHackVerifyFileMapping->Clear();
	}

	MemoryProtectionTime = GetTickCount();

	return 1;
}

bool MEMORY_PROTECTION_SCAN() // OK
{
	if(gMemoryGuardSwitch == 0 || (gMemoryGuardNumber & MEMORY_GUARD_NUMBER_INJECT) == 0)
	{
		return 1;
	}

	for(DWORD n=0;n < lpHackVerifyFileMapping->WriteVirtualMemoryCount;n++)
	{
		HACK_VERIFY_FILE* lpHackVerifyFile = &lpHackVerifyFileMapping->WriteVirtualMemoryTable[n];

		if(lpHackVerifyFile->time >= MemoryProtectionTime)
		{
			if(lpHackVerifyFile->spid != GetCurrentProcessId())
			{
				if(lpHackVerifyFile->tpid == GetCurrentProcessId())
				{
					CHClientDisconnectSend(CLIENT_DISCONNECT_MEMORY_DETECTION,0,lpHackVerifyFile->spid);
					return 1;
				}
			}
		}
	}

	return 1;
}

bool HANDLE_PROTECTION_INIT() // OK
{
	CProcessQuery ProcessQuery;

	HANDLE HandleValue = OpenProcess(PROCESS_VM_READ,0,GetCurrentProcessId());

	if(ProcessQuery.Fetch(SystemExtendedHandleInformation,sizeof(SYSTEM_HANDLE_INFO_EX)) != 0)
	{
		SYSTEM_HANDLE_INFO_EX* lpSystemHandleInfo = ProcessQuery.GetExtendedHandleInfo();

		if(lpSystemHandleInfo != 0)
		{
			SYSTEM_HANDLE_ENTRY_INFO_EX* lpSystemHandleEntryInfo = lpSystemHandleInfo->Handles;

			if(lpSystemHandleEntryInfo != 0)
			{
				for(DWORD n=0;n < lpSystemHandleInfo->NumberOfHandles;n++,lpSystemHandleEntryInfo++)
				{
					if(lpSystemHandleEntryInfo->UniqueProcessId == GetCurrentProcessId() && lpSystemHandleEntryInfo->HandleValue == ((DWORD)HandleValue))
					{
						HandleProtectionNumber = (DWORD)lpSystemHandleEntryInfo->ObjectTypeIndex;
						HandleProtectionObject = (DWORD)lpSystemHandleEntryInfo->Object;
						ProcessQuery.Close();
						return 1;
					}
				}
			}
		}
	}

	ProcessQuery.Close();

	return 0;
}

bool HANDLE_PROTECTION_SCAN() // OK
{
	if(gMemoryGuardSwitch == 0 || (gMemoryGuardNumber & MEMORY_GUARD_NUMBER_HANDLE) == 0)
	{
		return 1;
	}

	static CProcessQuery ProcessQuery;

	std::map<DWORD,std::vector<DWORD>> HandleProtectionTable;

	if(ProcessQuery.Fetch(SystemExtendedHandleInformation,sizeof(SYSTEM_HANDLE_INFO_EX)) != 0)
	{
		SYSTEM_HANDLE_INFO_EX* lpSystemHandleInfo = ProcessQuery.GetExtendedHandleInfo();

		if(lpSystemHandleInfo != 0)
		{
			SYSTEM_HANDLE_ENTRY_INFO_EX* lpSystemHandleEntryInfo = lpSystemHandleInfo->Handles;

			if(lpSystemHandleEntryInfo != 0)
			{
				for(DWORD n=0;n < lpSystemHandleInfo->NumberOfHandles;n++,lpSystemHandleEntryInfo++)
				{
					if(lpSystemHandleEntryInfo->UniqueProcessId != GetCurrentProcessId() && lpSystemHandleEntryInfo->ObjectTypeIndex == HandleProtectionNumber && lpSystemHandleEntryInfo->Object == ((LPVOID)HandleProtectionObject) && (lpSystemHandleEntryInfo->GrantedAccess & PROCESS_VM_WRITE) != 0)
					{
						std::map<DWORD,std::vector<DWORD>>::iterator it = HandleProtectionTable.find(lpSystemHandleEntryInfo->UniqueProcessId);

						if(it == HandleProtectionTable.end())
						{
							HandleProtectionTable.insert(std::pair<DWORD,std::vector<DWORD>>(lpSystemHandleEntryInfo->UniqueProcessId,std::vector<DWORD>(1,lpSystemHandleEntryInfo->HandleValue)));
							continue;
						}
						else
						{
							if(it->second.size() >= MAX_HANDLE_PROTECTION_COUNT)
							{
								CHClientDisconnectSend(CLIENT_DISCONNECT_MEMORY_DETECTION,0,lpSystemHandleEntryInfo->UniqueProcessId);
								return 0;
							}
							else
							{
								it->second.push_back(lpSystemHandleEntryInfo->HandleValue);
								continue;
							}
						}
					}
				}
			}
		}
	}

	return 1;
}

bool LIBRARY_LOAD_ATTACH() // OK
{
	BYTE protect_code[6] = {0xFF,0x25,0x00,0x00,0x00,0x00};

	DWORD protect_addr = (DWORD)GetProcAddress(GetModuleHandle("Ntdll.dll"),"LdrLoadDll");

	if(protect_addr == 0){return 0;}

	MemoryCpy((DWORD)LibraryLoadSource,(void*)protect_addr,sizeof(LibraryLoadSource));

	MemoryCpy(protect_addr,protect_code,sizeof(protect_code));

	return 1;
}

bool LIBRARY_LOAD_DETACH() // OK
{
	DWORD protect_addr = (DWORD)GetProcAddress(GetModuleHandle("Ntdll.dll"),"LdrLoadDll");

	if(protect_addr == 0){return 0;}

	MemoryCpy(protect_addr,LibraryLoadSource,sizeof(LibraryLoadSource));

	return 1;
}

bool MEMORY_CHECK_ATTACH() // OK
{
	CCRC32 CRC32;

	MODULEINFO ModuleInfo;

	memset(&ModuleInfo,0,sizeof(ModuleInfo));

	if(GetModuleInformation(GetCurrentProcess(),GetModuleHandle(0),&ModuleInfo,sizeof(ModuleInfo)) == 0)
	{
		return 0;
	}

	IMAGE_NT_HEADERS32* lpNtHeader = (IMAGE_NT_HEADERS32*)((DWORD)ModuleInfo.lpBaseOfDll+((IMAGE_DOS_HEADER*)ModuleInfo.lpBaseOfDll)->e_lfanew);

	IMAGE_SECTION_HEADER* lpSectionHeader = (IMAGE_SECTION_HEADER*)((DWORD)lpNtHeader+sizeof(IMAGE_NT_HEADERS32));

	for(int n=0;n < lpNtHeader->FileHeader.NumberOfSections;n++)
	{
		MEMORY_CHECK_SOURCE data;

		data.VirtualAddress = (DWORD)ModuleInfo.lpBaseOfDll+lpSectionHeader[n].VirtualAddress;

		data.VirtualSize = lpSectionHeader[n].Misc.VirtualSize;

		data.VirtualChecksum = CRC32.FullCRC((BYTE*)data.VirtualAddress,data.VirtualSize);

		MemoryCheckSource.insert(std::pair<DWORD,MEMORY_CHECK_SOURCE>(data.VirtualAddress,data));

		break;
	}

	return 1;
}

bool MEMORY_CHECK_DETACH() // OK
{
	CCRC32 CRC32;

	for(std::map<DWORD,MEMORY_CHECK_SOURCE>::iterator it=MemoryCheckSource.begin();it != MemoryCheckSource.end();it++)
	{
		if(it->second.VirtualChecksum != CRC32.FullCRC((BYTE*)it->second.VirtualAddress,it->second.VirtualSize))
		{
			return 0;
		}
	}

	return 1;
}
