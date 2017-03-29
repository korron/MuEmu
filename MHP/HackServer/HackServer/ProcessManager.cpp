// ProcessManager.cpp: implementation of the CProcessManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProcessManager.h"
#include "ServerInfo.h"
#include "Util.h"

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

bool CProcessManager::CheckProcess() // OK
{
	if(gServerInfo.m_EncDecSetNumber == 0)
	{
		return 1;
	}

	char ModulePath[MAX_PATH];

	if(GetFullPathName("MHPDetect.dll",sizeof(ModulePath),ModulePath,0) == 0)
	{
		return 0;
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
				HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,0,ProcessIds[n]);

				if(ProcessHandle != 0)
				{
					char ProcessName[MAX_PATH];

					if(GetModuleBaseName(ProcessHandle,0,ProcessName,MAX_PATH) != 0)
					{
						if(strcmp(ProcessName,"GameServer.exe") == 0)
						{
							if(this->CheckProcessModule(ProcessHandle,ModulePath) == 0)
							{
								if(this->StartProcessModule(ProcessHandle,ModulePath,strlen(ModulePath)) == 0)
								{
									LogAdd(LOG_RED,"[ProcessManager][%d][%s] Could not initialize process!",ProcessIds[n],ProcessName);
									CloseHandle(ProcessHandle);
								}
								else
								{
									LogAdd(LOG_BLUE,"[ProcessManager][%d][%s] Initialization successful!",ProcessIds[n],ProcessName);
									CloseHandle(ProcessHandle);
								}
							}
							else
							{
								CloseHandle(ProcessHandle);
							}
						}
						else
						{
							CloseHandle(ProcessHandle);
						}
					}
					else
					{
						CloseHandle(ProcessHandle);
					}
				}
			}
		}
	}

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

	char MutexName[64];

	wsprintf(MutexName,"XTMPID%d",GetProcessId(ProcessHandle));

	HANDLE MutexHandle = CreateMutex(0,0,MutexName);

	if(MutexHandle == 0)
	{
		VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
		return 0;
	}

	if((RemoteThread=CreateRemoteThread(ProcessHandle,0,0,(LPTHREAD_START_ROUTINE)LoadLibraryAddress,RemoteMemory,0,0)) == 0)
	{
		VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
		CloseHandle(MutexHandle);
		return 0;
	}

	if(WaitForSingleObject(RemoteThread,INFINITE) != WAIT_OBJECT_0)
	{
		VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
		CloseHandle(MutexHandle);
		return 0;
	}

	VirtualFreeEx(ProcessHandle,RemoteMemory,ModulePathSize,MEM_RELEASE);
	CloseHandle(MutexHandle);
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
