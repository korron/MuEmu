#include "stdafx.h"
#include "Resource.h"
#include "Game.h"

bool SetAdminPrivilege() // OK
{
	HANDLE TokenHandle;

	if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&TokenHandle) == 0)
	{
		return 0;
	}

	LUID luid;

	if(LookupPrivilegeValue(0,SE_DEBUG_NAME,&luid) == 0)
	{
		CloseHandle(TokenHandle);
		return 0;
	}

	TOKEN_PRIVILEGES tp;

	memset(&tp,0,sizeof(tp));

	tp.PrivilegeCount = 1;

	tp.Privileges[0].Luid = luid;

	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if(AdjustTokenPrivileges(TokenHandle,0,&tp,sizeof(tp),0,0) == 0)
	{
		CloseHandle(TokenHandle);
		return 0;
	}

	CloseHandle(TokenHandle);
	return 1;
}

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) // OK
{
	if(SetAdminPrivilege() == 0)
	{
		MessageBox(0,"Could not open game.exe (#1)","Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	STARTUPINFO si;

	PROCESS_INFORMATION pi;

	memset(&si,0,sizeof(si));

	memset(&pi,0,sizeof(pi));

	si.cb = sizeof(si);

	char CommandLine[MAX_PATH];

	wsprintf(CommandLine,"game.exe -test -k%d",GetTickCount());

	if(CreateProcess(0,CommandLine,0,0,0,NORMAL_PRIORITY_CLASS,0,0,&si,&pi) == 0)
	{
		MessageBox(0,"Could not open game.exe (#2)","Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	char MutexName[32];

	wsprintf(MutexName,"MHP_ELEVATE_%d",pi.dwProcessId);

	HANDLE MutexHandle = CreateMutex(0,0,MutexName);

	Sleep(30000);

	return 1;
}
