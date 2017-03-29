// ProcessQuery.cpp: implementation of the CProcessQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProcessQuery.h"

NTQUERYSYSTEMINFORMATION CProcessQuery::m_NtQuerySystemInformation;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcessQuery::CProcessQuery() // OK
{
	this->Start();
}

CProcessQuery::~CProcessQuery() // OK
{
	this->Close();
}

void CProcessQuery::Start() // OK
{
	this->m_QueryData = 0;

	this->m_QuerySize = 0;

	this->m_QueryStatus = STATUS_SUCCESS;
}

void CProcessQuery::Close() // OK
{
	this->m_QueryData = ((this->m_QueryData==0)?(BYTE*)0:((HeapFree(GetProcessHeap(),0,this->m_QueryData)==0)?(BYTE*)0:(BYTE*)0));

	this->m_QuerySize = 0;

	this->m_QueryStatus = STATUS_SUCCESS;
}

bool CProcessQuery::Fetch(SYSTEM_INFORMATION_CLASS SysInfoClass,DWORD QuerySize) // OK
{
	while(this->m_QueryData != 0 || (this->m_QueryData=(BYTE*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(this->m_QuerySize=((this->m_QuerySize<QuerySize)?QuerySize:this->m_QuerySize)))) != 0)
	{
		DWORD ReturnLength;

		if((this->m_QueryStatus=CProcessQuery::m_NtQuerySystemInformation(SysInfoClass,this->m_QueryData,this->m_QuerySize,&ReturnLength)) == STATUS_INFO_LENGTH_MISMATCH)
		{
			this->m_QueryData = ((this->m_QueryData==0)?(BYTE*)0:((HeapFree(GetProcessHeap(),0,this->m_QueryData)==0)?(BYTE*)0:(BYTE*)0));
			this->m_QuerySize = ReturnLength;
		}
		else
		{
			return ((this->m_QueryStatus==STATUS_SUCCESS)?1:0);
		}
	}

	return 0;
}

SYSTEM_HANDLE_INFO* CProcessQuery::GetHandleInfo() // OK
{
	return ((SYSTEM_HANDLE_INFO*)this->m_QueryData);
}

SYSTEM_HANDLE_INFO_EX* CProcessQuery::GetExtendedHandleInfo() // OK
{
	return ((SYSTEM_HANDLE_INFO_EX*)this->m_QueryData);
}

SYSTEM_KERNEL_DEBUGGER_INFO* CProcessQuery::GetKernelDebuggerInfo() // OK
{
	return ((SYSTEM_KERNEL_DEBUGGER_INFO*)this->m_QueryData);
}

SYSTEM_PROCESS_INFO* CProcessQuery::GetProcessInfoByID(HANDLE ProcessId) // OK
{
	SYSTEM_PROCESS_INFO* lpSystemProcessInfo = (SYSTEM_PROCESS_INFO*)this->m_QueryData;

	while(true)
	{
		if(lpSystemProcessInfo->UniqueProcessId == ProcessId)
		{
			return lpSystemProcessInfo;
		}

		if(lpSystemProcessInfo->NextEntryOffset == 0)
		{
			break;
		}

		lpSystemProcessInfo = (SYSTEM_PROCESS_INFO*)((BYTE*)lpSystemProcessInfo+lpSystemProcessInfo->NextEntryOffset);
	}

	return 0;
}

SYSTEM_EXTENDED_PROCESS_INFO* CProcessQuery::GetExtendedProcessInfoByID(HANDLE ProcessId) // OK
{
	SYSTEM_EXTENDED_PROCESS_INFO* lpSystemProcessInfo = (SYSTEM_EXTENDED_PROCESS_INFO*)this->m_QueryData;

	while(true)
	{
		if(lpSystemProcessInfo->UniqueProcessId == ProcessId)
		{
			return lpSystemProcessInfo;
		}

		if(lpSystemProcessInfo->NextEntryOffset == 0)
		{
			break;
		}

		lpSystemProcessInfo = (SYSTEM_EXTENDED_PROCESS_INFO*)((BYTE*)lpSystemProcessInfo+lpSystemProcessInfo->NextEntryOffset);
	}

	return 0;
}

SYSTEM_THREAD_INFO* CProcessQuery::GetThreadInfoByID(SYSTEM_PROCESS_INFO* lpSystemProcessInfo,HANDLE ThreadId) // OK
{
	SYSTEM_THREAD_INFO* lpSystemThreadInfo = lpSystemProcessInfo->Threads;

	for(DWORD n=0;n < lpSystemProcessInfo->NumberOfThreads;n++,lpSystemThreadInfo++)
	{
		if(lpSystemThreadInfo->ClientId.UniqueThread == ThreadId)
		{
			return lpSystemThreadInfo;
		}
	}

	return 0;
}

SYSTEM_EXTENDED_THREAD_INFO* CProcessQuery::GetExtendedThreadInfoByID(SYSTEM_EXTENDED_PROCESS_INFO* lpSystemProcessInfo,HANDLE ThreadId) // OK
{
	SYSTEM_EXTENDED_THREAD_INFO* lpSystemThreadInfo = lpSystemProcessInfo->Threads;

	for(DWORD n=0;n < lpSystemProcessInfo->NumberOfThreads;n++,lpSystemThreadInfo++)
	{
		if(lpSystemThreadInfo->ThreadInfo.ClientId.UniqueThread == ThreadId)
		{
			return lpSystemThreadInfo;
		}
	}

	return 0;
}
