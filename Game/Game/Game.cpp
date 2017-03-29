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
		MessageBox(0,"Could not open main.exe (#1)","Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	STARTUPINFO si;

	PROCESS_INFORMATION pi;

	memset(&si,0,sizeof(si));

	memset(&pi,0,sizeof(pi));

	si.cb = sizeof(si);

	char CommandLine[MAX_PATH];

	wsprintf(CommandLine,"main.exe -test -k%d",GetTickCount());

	if(CreateProcess(0,CommandLine,0,0,0,NORMAL_PRIORITY_CLASS | CREATE_SUSPENDED,0,0,&si,&pi) == 0)
	{
		MessageBox(0,"Could not open main.exe (#2)","Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,0,pi.dwProcessId);

	if(ProcessHandle == 0)
	{
		MessageBox(0,"Could not open main.exe (#3)","Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	HANDLE ThreadHandle = OpenThread(THREAD_ALL_ACCESS,0,pi.dwThreadId);

	if(ThreadHandle == 0)
	{
		CloseHandle(ProcessHandle);
		MessageBox(0,"Could not open main.exe (#4)","Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	DWORD BytesRead;

	DWORD BytesWritten;

	BYTE ReadTable[2] = {0x60,0x9C};

	BYTE WriteTable[2] = {0xEB,0xFE};

	ReadProcessMemory(ProcessHandle,(void*)MAIN_EIP,ReadTable,sizeof(ReadTable),&BytesRead);

	WriteProcessMemory(ProcessHandle,(void*)MAIN_EIP,WriteTable,sizeof(WriteTable),&BytesWritten);

	ResumeThread(ThreadHandle);

	CONTEXT context;

	context.ContextFlags = CONTEXT_CONTROL;

	GetThreadContext(ThreadHandle,&context);

	for(int n=0;n < 50 && context.Eip != MAIN_EIP;n++)
	{
		Sleep(100);
		context.ContextFlags = CONTEXT_CONTROL;
		GetThreadContext(ThreadHandle,&context);
	}

	if(context.Eip != MAIN_EIP)
	{
		CloseHandle(ThreadHandle);
		CloseHandle(ProcessHandle);
		MessageBox(0,"Could not open main.exe (#5)","Error",MB_OK | MB_ICONERROR);
		return 0;
	}

	char LibraryPath[MAX_PATH] = "Main.dll";

	void* RemoteMemory = VirtualAllocEx(ProcessHandle,0,sizeof(LibraryPath),MEM_COMMIT,PAGE_READWRITE);

	WriteProcessMemory(ProcessHandle,RemoteMemory,LibraryPath,sizeof(LibraryPath),&BytesWritten);

	HANDLE RemoteThread = CreateRemoteThread(ProcessHandle,0,0,(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("Kernel32"),"LoadLibraryA"),RemoteMemory,0,0);

	WaitForSingleObject(RemoteThread,INFINITE);

	SuspendThread(ThreadHandle);

	WriteProcessMemory(ProcessHandle,(void*)MAIN_EIP,ReadTable,sizeof(ReadTable),&BytesWritten);

	ResumeThread(ThreadHandle);

	CloseHandle(ThreadHandle);

	CloseHandle(ProcessHandle);

	return 1;
}
