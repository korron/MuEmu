// ThreadCheck.cpp: implementation of the CThreadCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadCheck.h"
#include "Connection.h"
#include "HackServerProtocol.h"
#include "Message.h"
#include "Protect.h"
#include "SplashScreen.h"
#include "Util.h"

CThreadCheck gThreadCheck;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreadCheck::CThreadCheck()
{
	this->m_IsActive = 0;

	this->m_IsActiveTime = 0;

	this->m_CheckThreadID[0] = (DWORD)INVALID_HANDLE_VALUE;

	this->m_CheckThreadID[1] = (DWORD)INVALID_HANDLE_VALUE;

	this->m_CheckThreadID[2] = (DWORD)INVALID_HANDLE_VALUE;

	this->m_CheckThreadID[3] = (DWORD)INVALID_HANDLE_VALUE;

	this->m_CheckThreadID[4] = (DWORD)INVALID_HANDLE_VALUE;

	InitializeCriticalSection(&this->m_CheckThreadCriticalSection);
}

CThreadCheck::~CThreadCheck()
{
	DeleteCriticalSection(&this->m_CheckThreadCriticalSection);
}

void CThreadCheck::Init() //OK
{
	this->m_IsActive = 1;

	this->m_IsActiveTime = GetTickCount();
}

bool CThreadCheck::CheckThreadState() // OK
{
	DWORD result = 0;

	if(this->m_ProcessQuery.Fetch(SystemProcessInformation,sizeof(SYSTEM_PROCESS_INFO)) != 0)
	{
		SYSTEM_PROCESS_INFO* lpSystemProcessInfo = this->m_ProcessQuery.GetProcessInfoByID((HANDLE)GetCurrentProcessId());

		if(lpSystemProcessInfo != 0)
		{
			for(int n=0;n < MAX_THREAD_CHECK;n++)
			{
				if(((HANDLE)this->m_CheckThreadID[n]) != INVALID_HANDLE_VALUE)
				{
					SYSTEM_THREAD_INFO* lpSystemThreadInfo = this->m_ProcessQuery.GetThreadInfoByID(lpSystemProcessInfo,((HANDLE)this->m_CheckThreadID[n]));

					if(lpSystemThreadInfo == 0 || (lpSystemThreadInfo->ThreadState == Waiting && lpSystemThreadInfo->WaitReason == Suspended))
					{
						return 0;
					}
					else
					{
						result++;
					}
				}
			}
		}
	}

	return ((result==0)?0:1);
}

void CThreadCheck::CheckThreadIntegrity() //OK
{
	if(this->m_IsActive != 0 && (GetTickCount()-this->m_IsActiveTime) > 5000)
	{
		if(TryEnterCriticalSection(&this->m_CheckThreadCriticalSection) != 0)
		{
			if((this->m_IsActiveTime=GetTickCount()) != 0 && this->CheckThreadState() == 0)
			{
				SplashScreen(&SplashError,2,1,gMessage.GetMessage(0),5000);
			}
			else
			{
				LeaveCriticalSection(&this->m_CheckThreadCriticalSection);
			}
		}
	}
}
