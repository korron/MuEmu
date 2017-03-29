// ProcessManager.h: interface for the CProcessManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CriticalSection.h"
#include "Util.h"

typedef NTSTATUS (WINAPI*LDRLOADDLL)(PWCHAR,ULONG,PUNICODE_STRING,PHANDLE);

class CProcessManager
{
public:
	CProcessManager();
	virtual ~CProcessManager();
	bool Init();
	bool CheckProcess(DWORD flag);
	bool CheckProcess(DWORD processID,DWORD flag);
	bool CheckProcessModule(HANDLE ProcessHandle,char* ModulePath);
	bool StartProcessModule(HANDLE ProcessHandle,char* ModulePath,int ModulePathSize);
	void ClearProcessCache();
	bool AddProcessCache(DWORD ProcessId);
	bool GetProcessCache(PROCESS_CACHE_INFO* lpProcessCacheInfo,DWORD ProcessId);
	void InsertProcessCacheInfo(PROCESS_CACHE_INFO ProcessCacheInfo);
	void RemoveProcessCacheInfo(PROCESS_CACHE_INFO ProcessCacheInfo);
	static NTSTATUS WINAPI MyLdrLoadDll(PWCHAR PathToFile,ULONG Flags,PUNICODE_STRING ModuleFileName,PHANDLE ModuleHandle);
private:
	char m_ModulePath[MAX_PATH];
	DWORD m_AddrLdrLoadDll;
	DWORD m_AddrLoadLibraryA;
	DWORD m_AddrLoadLibraryW;
	LDRLOADDLL m_LdrLoadDll;
	std::map<DWORD,DWORD> m_LdrLoadDllMap;
	CCriticalSection m_critical;
	std::map<DWORD,PROCESS_CACHE_INFO> m_ProcessCacheInfo;
};

extern CProcessManager gProcessManager;
