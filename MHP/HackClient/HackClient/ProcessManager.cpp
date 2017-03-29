// ProcessManager.cpp: implementation of the CProcessManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProcessManager.h"
#include "HackServerProtocol.h"
#include "Message.h"
#include "ProcessQuery.h"
#include "Protect.h"
#include "Util.h"
//Modules
#include "ProcessCheck.h"
#include "ThreadCheck.h"

CProcessManager gProcessManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcessManager::CProcessManager() // OK
{

}

CProcessManager::~CProcessManager() // OK
{

}

bool CProcessManager::Init() // OK
{
	if(GetFullPathName(gProtect.m_MainInfo.VerifyName,sizeof(this->m_ModulePath),this->m_ModulePath,0) == 0)
	{
		return 0;
	}

	char MutexName[16];

	wsprintf(MutexName,"#PMBL%d#",GetCurrentProcessId());

	CreateMutex(0,0,MutexName);

	this->m_AddrLdrLoadDll = (DWORD)GetProcAddress(GetModuleHandle("ntdll.dll"),"LdrLoadDll");

	this->m_AddrLoadLibraryA = (DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"),"LoadLibraryA");

	this->m_AddrLoadLibraryW = (DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"),"LoadLibraryW");

	this->m_LdrLoadDll = (LDRLOADDLL)this->m_AddrLdrLoadDll;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)this->m_LdrLoadDll,CProcessManager::MyLdrLoadDll);
	DetourTransactionCommit();

	return 1;
}

bool CProcessManager::CheckProcess(DWORD flag) // OK
{
	if(flag == 1 && (gMemoryGuardSwitch == 0 || (gMemoryGuardNumber & MEMORY_GUARD_NUMBER_INJECT) == 0))
	{
		return 1;
	}

	if(flag == 1 && gProtect.m_MainInfo.VerifyCRC32 == 0)
	{
		return 1;
	}

	DWORD ProcessIds[1024],BytesReturned=0,ProcessCount=0;

	if(EnumProcesses(ProcessIds,sizeof(ProcessIds),&BytesReturned) == 0)
	{
		return 0;
	}

	for(int n=0,ProcessCount=(BytesReturned/sizeof(DWORD));n < ProcessCount;n++)
	{
		if(ProcessIds[n] != 0)
		{
			if(this->AddProcessCache(ProcessIds[n]) != 0)
			{
				if(this->CheckProcess(ProcessIds[n],flag) == 0)
				{
					return 0;
				}

				if(gProcessCheck.CheckProcess(ProcessIds[n],flag) == 0)
				{
					return 0;
				}
			}
		}
	}

	return 1;
}

bool CProcessManager::CheckProcess(DWORD processID,DWORD flag)
{
	if((flag & 1) == 0 || (gMemoryGuardSwitch == 0 || (gMemoryGuardNumber & MEMORY_GUARD_NUMBER_INJECT) == 0))
	{
		return 1;
	}

	HANDLE MutexHandle;

	char MutexName[16];

	wsprintf(MutexName,"#PMBL%d#",processID);

	CloseHandle((MutexHandle=OpenMutex(SYNCHRONIZE,0,MutexName)));

	HANDLE ProcessHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION,0,processID);

	if(ProcessHandle != 0 && MutexHandle == 0)
	{
		if(this->CheckProcessModule(ProcessHandle,this->m_ModulePath) == 0)
		{
			if(this->StartProcessModule(ProcessHandle,this->m_ModulePath,strlen(this->m_ModulePath)) == 0)
			{
				CloseHandle(ProcessHandle);
				return 1;
			}
		}
	}

	CloseHandle(ProcessHandle);
	return 1;
}

bool CProcessManager::CheckProcessModule(HANDLE ProcessHandle,char* ModulePath) // OK
{
	HMODULE ModuleTable[1024];
	DWORD BytesReturned=0,ModuleCount=0;

	if(EnumProcessModules(ProcessHandle,ModuleTable,sizeof(ModuleTable),&BytesReturned) == 0)
	{
		return 1;
	}

	for(int n=0,ModuleCount=(BytesReturned/sizeof(HMODULE));n < ModuleCount;n++)
	{
		char ModuleFilePath[MAX_PATH];

		if(GetModuleFileNameEx(ProcessHandle,ModuleTable[n],ModuleFilePath,MAX_PATH) != 0)
		{
			if(strcmp(ModuleFilePath,ModulePath) == 0)
			{
				return 1;
			}
		}
	}

	return 0;
}

bool CProcessManager::StartProcessModule(HANDLE ProcessHandle,char* ModulePath,int ModulePathSize) // OK
{
	LPVOID RemoteMemory = 0;
	HANDLE RemoteThread = 0;
	FARPROC LoadLibraryAddress = 0;

	if((RemoteMemory=VirtualAllocEx(ProcessHandle,0,ModulePathSize,MEM_COMMIT,PAGE_READWRITE)) == 0)
	{
		return 0;
	}

	if(WriteProcessMemory(ProcessHandle,RemoteMemory,ModulePath,ModulePathSize,0) == 0)
	{
		VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
		return 0;
	}

	if((LoadLibraryAddress=GetProcAddress(GetModuleHandle("kernel32.dll"),"LoadLibraryA")) == 0)
	{
		VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
		return 0;
	}

	if((RemoteThread=CreateRemoteThread(ProcessHandle,0,0,(LPTHREAD_START_ROUTINE)LoadLibraryAddress,RemoteMemory,0,0)) == 0)
	{
		VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
		return 0;
	}

	if(WaitForSingleObject(RemoteThread,INFINITE) != WAIT_OBJECT_0)
	{
		VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
		return 0;
	}

	VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
	return 1;
}

void CProcessManager::ClearProcessCache() // OK
{
	this->m_critical.lock();

	for(std::map<DWORD,PROCESS_CACHE_INFO>::iterator it=this->m_ProcessCacheInfo.begin();it != this->m_ProcessCacheInfo.end();)
	{
		if((GetTickCount()-it->second.TickCount) < 300000)
		{
			it++;
		}
		else
		{
			it = this->m_ProcessCacheInfo.erase(it);
		}
	}

	this->m_critical.unlock();
}

bool CProcessManager::GetProcessCache(PROCESS_CACHE_INFO* lpProcessCacheInfo,DWORD ProcessId)
{
	this->m_critical.lock();

	std::map<DWORD,PROCESS_CACHE_INFO>::iterator it = this->m_ProcessCacheInfo.find(ProcessId);

	if(it != this->m_ProcessCacheInfo.end())
	{
		(*lpProcessCacheInfo) = it->second;
		this->m_critical.unlock();
		return 1;
	}

	this->m_critical.unlock();
	return 0;
}

void CProcessManager::InsertProcessCacheInfo(PROCESS_CACHE_INFO ProcessCacheInfo)
{
	this->m_critical.lock();

	std::map<DWORD,PROCESS_CACHE_INFO>::iterator it = this->m_ProcessCacheInfo.find(ProcessCacheInfo.ProcessId);

	if(it == this->m_ProcessCacheInfo.end())
	{
		this->m_ProcessCacheInfo.insert(std::pair<DWORD,PROCESS_CACHE_INFO>(ProcessCacheInfo.ProcessId,ProcessCacheInfo));
	}
	else
	{
		it->second = ProcessCacheInfo;
	}

	this->m_critical.unlock();
}

void CProcessManager::RemoveProcessCacheInfo(PROCESS_CACHE_INFO ProcessCacheInfo)
{
	this->m_critical.lock();

	std::map<DWORD,PROCESS_CACHE_INFO>::iterator it = this->m_ProcessCacheInfo.find(ProcessCacheInfo.ProcessId);

	if(it != this->m_ProcessCacheInfo.end())
	{
		this->m_ProcessCacheInfo.erase(it);
		this->m_critical.unlock();
		return;
	}

	this->m_critical.unlock();
}

bool CProcessManager::AddProcessCache(DWORD ProcessId)
{
	PROCESS_CACHE_INFO ProcessCacheInfo;

	if(this->GetProcessCache(&ProcessCacheInfo,ProcessId) != 0)
	{
		return 0;
	}

	ProcessCacheInfo.ProcessId = ProcessId;

	ProcessCacheInfo.TickCount = GetTickCount();

	this->InsertProcessCacheInfo(ProcessCacheInfo);

	return 1;
}

NTSTATUS WINAPI CProcessManager::MyLdrLoadDll(PWCHAR PathToFile,ULONG Flags,PUNICODE_STRING ModuleFileName,PHANDLE ModuleHandle)
{
	gThreadCheck.CheckThreadIntegrity();

	std::map<DWORD,DWORD>::iterator it = gProcessManager.m_LdrLoadDllMap.find(GetCurrentThreadId());

	if(it == gProcessManager.m_LdrLoadDllMap.end())
	{
		CProcessQuery ProcessQuery;

		gProcessManager.m_LdrLoadDllMap.insert(std::pair<DWORD,DWORD>(GetCurrentThreadId(),1));

		if(ProcessQuery.Fetch(SystemExtendedProcessInformation,sizeof(SYSTEM_EXTENDED_PROCESS_INFO)) != 0)
		{
			SYSTEM_EXTENDED_PROCESS_INFO* lpSystemProcessInfo = ProcessQuery.GetExtendedProcessInfoByID((HANDLE)GetCurrentProcessId());

			if(lpSystemProcessInfo != 0)
			{
				SYSTEM_EXTENDED_THREAD_INFO* lpSystemThreadInfo = ProcessQuery.GetExtendedThreadInfoByID(lpSystemProcessInfo,(HANDLE)GetCurrentThreadId());

				if(lpSystemThreadInfo != 0)
				{
					if(((lpSystemThreadInfo->Win32StartAddress<((PVOID)0x10000))?lpSystemThreadInfo->ThreadInfo.StartAddress:lpSystemThreadInfo->Win32StartAddress) == ((PVOID)gProcessManager.m_AddrLdrLoadDll))
					{
						SplashScreen(&SplashError,2,1,gMessage.GetMessage(23),5000);
						return 0;
					}

					if(((lpSystemThreadInfo->Win32StartAddress<((PVOID)0x10000))?lpSystemThreadInfo->ThreadInfo.StartAddress:lpSystemThreadInfo->Win32StartAddress) == ((PVOID)gProcessManager.m_AddrLoadLibraryA))
					{
						SplashScreen(&SplashError,2,1,gMessage.GetMessage(23),5000);
						return 0;
					}

					if(((lpSystemThreadInfo->Win32StartAddress<((PVOID)0x10000))?lpSystemThreadInfo->ThreadInfo.StartAddress:lpSystemThreadInfo->Win32StartAddress) == ((PVOID)gProcessManager.m_AddrLoadLibraryW))
					{
						SplashScreen(&SplashError,2,1,gMessage.GetMessage(23),5000);
						return 0;
					}

					MEMORY_BASIC_INFORMATION mbi;

					memset(&mbi,0,sizeof(MEMORY_BASIC_INFORMATION));

					if(VirtualQuery(((lpSystemThreadInfo->Win32StartAddress<((PVOID)0x10000))?(void*)lpSystemThreadInfo->ThreadInfo.StartAddress:(void*)lpSystemThreadInfo->Win32StartAddress),&mbi,sizeof(mbi)) != 0)
					{
						if(mbi.BaseAddress == mbi.AllocationBase)
						{
							SplashScreen(&SplashError,2,1,gMessage.GetMessage(23),5000);
							return 0;
						}
					}
				}
			}
		}

		ProcessQuery.Close();
	}

	return gProcessManager.m_LdrLoadDll(PathToFile,Flags,ModuleFileName,ModuleHandle);
}
