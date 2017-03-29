#include "stdafx.h"
#include "HackClient.h"
#include "Connection.h"
#include "FileProtect.h"
#include "HackCheck.h"
#include "HackServerProtocol.h"
#include "ListManager.h"
#include "Log.h"
#include "Message.h"
#include "ProcessManager.h"
#include "Protect.h"
#include "SplashScreen.h"
#include "resource.h"
#include "Util.h"
//Modules
#include "DumpCheck.h"
#include "ExecutableCheck.h"
#include "FileCheck.h"
#include "FileMappingCheck.h"
#include "LibraryCheck.h"
#include "MacroCheck.h"
#include "ProcessCheck.h"
#include "RegistryCheck.h"
#include "SimpleModules.h"
#include "ThreadCheck.h"
#include "WindowCheck.h"

HINSTANCE hins;
HANDLE ThreadHandles[3];

DWORD WINAPI ConnectionReconnectThread() // OK
{
	while(!DelayMe(5000,100))
	{
		if(gReconnectStatus == 1)
		{
			if(gConnection.Init(HackServerProtocolCore) == 0)
			{
				SplashScreen(&SplashError,2,1,gMessage.GetMessage(1),5000);
				continue;
			}

			if(gConnection.Connect(gProtect.m_MainInfo.IpAddress,gProtect.m_MainInfo.ServerPort) == 0)
			{
				gConnectionStatusTime = GetTickCount();
				continue;
			}

			CHClientInfoSend();

			gReconnectStatus = 2;

			gConnectionStatusTime = GetTickCount();
		}
	}

	return 0;
}

DWORD WINAPI ConnectionStatusThread() // OK
{
	while(!DelayMe(5000,100))
	{
		if(gConnection.CheckState() == 0)
		{
			if(gReconnectSwitch == 0)
			{
				SplashScreen(&SplashError,2,1,gMessage.GetMessage(2),5000);
				continue;
			}

			if(gReconnectStatus == 1)
			{
				gConnectionStatusTime = GetTickCount();
				continue;
			}

			if(gReconnectStatus == 0 || gReconnectStatus == 2)
			{
				gReconnectStatus = 1;
				continue;
			}
		}
		else
		{
			if((GetTickCount()-gConnectionStatusTime) > 60000)
			{
				SplashScreen(&SplashError,2,1,gMessage.GetMessage(3),5000);
				continue;
			}
			else
			{
				CHConnectionStatusSend();
				continue;
			}
		}
	}

	return 0;
}

DWORD WINAPI MainThread() // OK
{
	DWORD CycleCount = 0;

	DWORD CycleExecutionDelay = 500;

	LARGE_INTEGER Frequency;

	LARGE_INTEGER InitCounter;

	LARGE_INTEGER NextCounter;

	LARGE_INTEGER ElapsedMicroseconds;

	QueryPerformanceFrequency(&Frequency);

	QueryPerformanceCounter(&InitCounter);

	while(!DelayMe(((CycleExecutionDelay>500)?0:(500-CycleExecutionDelay)),1))
	{
		QueryPerformanceCounter(&NextCounter);

		ElapsedMicroseconds.QuadPart = ((NextCounter.QuadPart-InitCounter.QuadPart)*1000000)/Frequency.QuadPart;

		if((ElapsedMicroseconds.QuadPart/1000) > 1500)
		{
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(0),5000);
			return 0;
		}

		QueryPerformanceFrequency(&Frequency);

		QueryPerformanceCounter(&InitCounter);

		if(gDetectCloseTime != 0)
		{
			if((GetTickCount()-gDetectCloseTime) > 10000)
			{
				SplashScreen(&SplashError,2,1,gMessage.GetMessage(21),5000);
				return 0;
			}
		}

		if(gIpAddressAddress != 0)
		{
			MemoryCpy(gIpAddressAddress,gIpAddress,sizeof(gIpAddress));
		}

		if(gClientVersionAddress != 0)
		{
			MemoryCpy(gClientVersionAddress,gClientVersion,sizeof(gClientVersion));
		}

		if(gClientSerialAddress != 0)
		{
			MemoryCpy(gClientSerialAddress,gClientSerial,sizeof(gClientSerial));
		}

		switch(((CycleCount++)%10))
		{
			case 0:
				API_SCAN();
				gWindowCheck.Scan();
				gProcessManager.CheckProcess(15);
				break;
			case 1:
				CheckDetourIntegrity();
				MEMORY_PROTECTION_SCAN();
				gRegistryCheck.Scan();
				break;
			case 2:
				API_SCAN();
				gWindowCheck.Scan();
				gProcessManager.CheckProcess(15);
				break;
			case 3:
				DEBUGGER_SCAN();
				MEMORY_PROTECTION_SCAN();
				gFileCheck.Scan();
				break;
			case 4:
				API_SCAN();
				gWindowCheck.Scan();
				gProcessManager.CheckProcess(15);
				break;
			case 5:
				CheckDetourIntegrity();
				MEMORY_PROTECTION_SCAN();
				HANDLE_PROTECTION_SCAN();
				break;
			case 6:
				API_SCAN();
				gWindowCheck.Scan();
				gProcessManager.CheckProcess(15);
				break;
			case 7:
				DEBUGGER_SCAN();
				MEMORY_PROTECTION_SCAN();
				gFileMappingCheck.Scan();
				break;
			case 8:
				API_SCAN();
				gWindowCheck.Scan();
				gProcessManager.CheckProcess(15);
				break;
			case 9:
				CheckDetourIntegrity();
				MEMORY_PROTECTION_SCAN();
				gProcessManager.ClearProcessCache();
				break;
			default:
				break;
		}

		QueryPerformanceCounter(&NextCounter);

		ElapsedMicroseconds.QuadPart = ((NextCounter.QuadPart-InitCounter.QuadPart)*1000000)/Frequency.QuadPart;

		CycleExecutionDelay = (DWORD)(ElapsedMicroseconds.QuadPart/1000);

		QueryPerformanceFrequency(&Frequency);

		QueryPerformanceCounter(&InitCounter);
	}

	return 0;
}

extern "C" _declspec(dllexport) void EntryProc() // OK
{
	gLog.AddLog(1,"MHP_LOG");

	CheckSystemInformation();

	if(gProtect.ReadMainFile("ah.emu") == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(18));
		SafeExitProcess();
		return;
	}

	if(LIBRARY_LOAD_DETACH() == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(19));
		SafeExitProcess();
		return;
	}

	if(MEMORY_CHECK_DETACH() == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(20));
		SafeExitProcess();
		return;
	}

	if(SetAdminPrivilege(SE_DEBUG_NAME) == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(21));
		SafeExitProcess();
		return;
	}

	if(API_INIT() == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(22));
		SafeExitProcess();
		return;
	}

	if(gProcessManager.Init() == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(23));
		SafeExitProcess();
		return;
	}

	if(MEMORY_PROTECTION_INIT() == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(45));
		SafeExitProcess();
		return;
	}

	if(HANDLE_PROTECTION_INIT() == 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(46));
		SafeExitProcess();
		return;
	}

	if(gConnection.Init(HackServerProtocolCore) == 0)
	{
		SplashScreen(&SplashError,2,1,gMessage.GetMessage(4),5000);
		return;
	}

	char buff[256];

	wsprintf(buff,gMessage.GetMessage(5),gProtect.m_MainInfo.ServerName);

	SplashScreen(&SplashInit,0,1,buff,0);

	if(gConnection.Connect(gProtect.m_MainInfo.IpAddress,gProtect.m_MainInfo.ServerPort) == 0)
	{
		SplashScreen(&SplashError,2,1,gMessage.GetMessage(6),5000);
		return;
	}

	CHClientInfoSend();

	DWORD ClientInfoTimeOut = GetTickCount();

	while(!DelayMe(500,1))
	{
		if((GetTickCount()-ClientInfoTimeOut) > 60000)
		{
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(7),5000);
			return;
		}

		if(gConnection.CheckState() == 0 && gConnection.Init(HackServerProtocolCore) != 0)
		{
			if(gConnection.Connect(gProtect.m_MainInfo.IpAddress,gProtect.m_MainInfo.ServerPort) != 0)
			{
				CHClientInfoSend();
				continue;
			}
		}

		if(gClientInfoOK != 0 && gDumpListOK != 0 && gChecksumListOK != 0 && gInternalListOK != 0 && gWindowListOK != 0)
		{
			DWORD CurProgress = gListManager.gDumpListInfo.size()+gListManager.gChecksumListInfo.size()+gListManager.gInternalListInfo.size()+gListManager.gWindowListInfo.size();

			DWORD MaxProgress = gDumpListMaxCount+gChecksumListMaxCount+gInternalListMaxCount+gWindowListMaxCount;

			if(CurProgress == MaxProgress)
			{
				break;
			}
		}
	}

	gLog.Output(LOG_DEBUG,GetEncryptedString(24),gDumpListMaxCount,gChecksumListMaxCount,gInternalListMaxCount,gWindowListMaxCount);

	if(MEMORY_CHECK_DETACH() == 0)
	{
		SplashScreen(&SplashError,2,1,gMessage.GetMessage(20),5000);
		return;
	}

	InitHackCheck();

	gProtect.CheckClientFile();

	gProtect.CheckVerifyFile();

	ThreadHandles[0] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)MainThread,0,0,(DWORD*)&gThreadCheck.m_CheckThreadID[1]);

	ThreadHandles[1] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ConnectionStatusThread,0,0,(DWORD*)&gThreadCheck.m_CheckThreadID[2]);

	ThreadHandles[2] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ConnectionReconnectThread,0,0,(DWORD*)&gThreadCheck.m_CheckThreadID[3]);

	SetThreadPriority(ThreadHandles[0],THREAD_PRIORITY_HIGHEST);

	WaitForMultipleObjects(3,ThreadHandles,1,2000);

	gMacroCheck.Init(hins);

	gThreadCheck.Init();

	gFileProtect.Init();

	SplashInit.CloseSplash();

	gProtect.CheckPluginFile();

	gLog.Output(LOG_DEBUG,GetEncryptedString(44));
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hins = (HINSTANCE)hModule;
			LIBRARY_LOAD_ATTACH();
			MEMORY_CHECK_ATTACH();
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
