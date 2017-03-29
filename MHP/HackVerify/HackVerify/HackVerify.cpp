#include "stdafx.h"

typedef DWORD (NTAPI*NTREADVIRTUALMEMORY)(HANDLE,PVOID,PVOID,ULONG,PULONG);
typedef DWORD (NTAPI*NTWRITEVIRTUALMEMORY)(HANDLE,PVOID,PVOID,ULONG,PULONG);

#define MIN_HACK_VERIFY_SIZE 0
#define MAX_HACK_VERIFY_SIZE 256

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

HANDLE FileMappingHandle;
NTREADVIRTUALMEMORY HookNtReadVirtualMemory;
NTWRITEVIRTUALMEMORY HookNtWriteVirtualMemory;
HACK_VERIFY_FILE_MAPPING* lpHackVerifyFileMapping;
static const char* STRING_NtDll = "ntdll.dll";
static const char* STRING_NtReadVirtualMemory = "NtReadVirtualMemory";
static const char* STRING_NtWriteVirtualMemory = "NtWriteVirtualMemory";

DWORD NTAPI MyNtReadVirtualMemory(HANDLE ProcessHandle,PVOID BaseAddress,PVOID Buffer,ULONG NumberOfBytesToRead,PULONG NumberOfBytesReaded) // OK
{
	lpHackVerifyFileMapping->ReadVirtualMemoryTable[lpHackVerifyFileMapping->ReadVirtualMemoryIndex].time = GetTickCount();

	lpHackVerifyFileMapping->ReadVirtualMemoryTable[lpHackVerifyFileMapping->ReadVirtualMemoryIndex].spid = GetCurrentProcessId();

	lpHackVerifyFileMapping->ReadVirtualMemoryTable[lpHackVerifyFileMapping->ReadVirtualMemoryIndex].tpid = GetProcessId(ProcessHandle);

	lpHackVerifyFileMapping->ReadVirtualMemoryCount = (((lpHackVerifyFileMapping->ReadVirtualMemoryCount+1)>=MAX_HACK_VERIFY_SIZE)?MAX_HACK_VERIFY_SIZE:(lpHackVerifyFileMapping->ReadVirtualMemoryCount+1));

	lpHackVerifyFileMapping->ReadVirtualMemoryIndex = (((lpHackVerifyFileMapping->ReadVirtualMemoryIndex+1)>=MAX_HACK_VERIFY_SIZE)?MIN_HACK_VERIFY_SIZE:(lpHackVerifyFileMapping->ReadVirtualMemoryIndex+1));

	return HookNtReadVirtualMemory(ProcessHandle,BaseAddress,Buffer,NumberOfBytesToRead,NumberOfBytesReaded);
}

DWORD NTAPI MyNtWriteVirtualMemory(HANDLE ProcessHandle,PVOID BaseAddress,PVOID Buffer,ULONG NumberOfBytesToWrite,PULONG NumberOfBytesWritten) // OK
{
	lpHackVerifyFileMapping->WriteVirtualMemoryTable[lpHackVerifyFileMapping->WriteVirtualMemoryIndex].time = GetTickCount();

	lpHackVerifyFileMapping->WriteVirtualMemoryTable[lpHackVerifyFileMapping->WriteVirtualMemoryIndex].spid = GetCurrentProcessId();

	lpHackVerifyFileMapping->WriteVirtualMemoryTable[lpHackVerifyFileMapping->WriteVirtualMemoryIndex].tpid = GetProcessId(ProcessHandle);

	lpHackVerifyFileMapping->WriteVirtualMemoryCount = (((lpHackVerifyFileMapping->WriteVirtualMemoryCount+1)>=MAX_HACK_VERIFY_SIZE)?MAX_HACK_VERIFY_SIZE:(lpHackVerifyFileMapping->WriteVirtualMemoryCount+1));

	lpHackVerifyFileMapping->WriteVirtualMemoryIndex = (((lpHackVerifyFileMapping->WriteVirtualMemoryIndex+1)>=MAX_HACK_VERIFY_SIZE)?MIN_HACK_VERIFY_SIZE:(lpHackVerifyFileMapping->WriteVirtualMemoryIndex+1));

	return HookNtWriteVirtualMemory(ProcessHandle,BaseAddress,Buffer,NumberOfBytesToWrite,NumberOfBytesWritten);
}

void EntryProc(HINSTANCE hins) // OK
{
	if((FileMappingHandle=CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,sizeof(HACK_VERIFY_FILE_MAPPING),"Local\\HACK_VERIFY_FILE_MAPPING")) == 0)
	{
		return;
	}

	if((lpHackVerifyFileMapping=(HACK_VERIFY_FILE_MAPPING*)MapViewOfFile(FileMappingHandle,FILE_MAP_ALL_ACCESS,0,0,sizeof(HACK_VERIFY_FILE_MAPPING))) == 0)
	{
		return;
	}

	if((HookNtReadVirtualMemory=(NTREADVIRTUALMEMORY)GetProcAddress(GetModuleHandle(STRING_NtDll),STRING_NtReadVirtualMemory)) != 0)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)HookNtReadVirtualMemory,MyNtReadVirtualMemory);
		DetourTransactionCommit();
	}

	if((HookNtWriteVirtualMemory=(NTWRITEVIRTUALMEMORY)GetProcAddress(GetModuleHandle(STRING_NtDll),STRING_NtWriteVirtualMemory)) != 0)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)HookNtWriteVirtualMemory,MyNtWriteVirtualMemory);
		DetourTransactionCommit();
	}
}

void CloseProc(HINSTANCE hins) // OK
{
	if(HookNtReadVirtualMemory != 0)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)HookNtReadVirtualMemory,MyNtReadVirtualMemory);
		DetourTransactionCommit();
	}

	if(HookNtWriteVirtualMemory != 0)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)HookNtWriteVirtualMemory,MyNtWriteVirtualMemory);
		DetourTransactionCommit();
	}

	CloseHandle(FileMappingHandle);
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			EntryProc((HINSTANCE)hModule);
			break;
		case DLL_PROCESS_DETACH:
			CloseProc((HINSTANCE)hModule);
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}
