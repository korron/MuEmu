// ProcessManager.h: interface for the CProcessManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CriticalSection.h"

struct PROCESS_CACHE_INFO
{
	DWORD ProcessId;
	DWORD TickCount;
};

class CProcessManager
{
public:
	CProcessManager();
	virtual ~CProcessManager();
	bool CheckProcess();
	bool CheckProcessModule(HANDLE ProcessHandle,char* ModulePath);
	bool StartProcessModule(HANDLE ProcessHandle,char* ModulePath,int ModulePathSize);
	void ClearProcessCache();
	bool AddProcessCache(DWORD ProcessId);
	bool GetProcessCache(PROCESS_CACHE_INFO* lpProcessCacheInfo,DWORD ProcessId);
	void InsertProcessCacheInfo(PROCESS_CACHE_INFO ProcessCacheInfo);
	void RemoveProcessCacheInfo(PROCESS_CACHE_INFO ProcessCacheInfo);
private:
	CCriticalSection m_critical;
	std::map<DWORD,PROCESS_CACHE_INFO> m_ProcessCacheInfo;
};

extern CProcessManager gProcessManager;
