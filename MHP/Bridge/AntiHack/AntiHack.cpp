#include "stdafx.h"
#include "AntiHack.h"

void EntryProc()
{
	char MutexName[32];

	wsprintf(MutexName,"MHP_ELEVATE_%d",GetCurrentProcessId());

	HANDLE MutexHandle = CreateMutex(0,0,MutexName);

	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(MutexHandle);
	}
	else
	{
		ExitProcess(0);
	}
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			EntryProc();
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}
