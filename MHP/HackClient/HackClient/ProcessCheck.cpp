#include "stdafx.h"
#include "ProcessCheck.h"
#include "HackServerProtocol.h"
#include "ListManager.h"
//Modules
#include "DumpCheck.h"
#include "ExecutableCheck.h"
#include "LibraryCheck.h"

CProcessCheck gProcessCheck;

CProcessCheck::CProcessCheck()
{

}

CProcessCheck::~CProcessCheck()
{

}

bool CProcessCheck::CheckProcess(DWORD processID,DWORD flag)
{
	if((flag & 2) == 0 && (flag & 4) == 0 && (flag & 8) == 0)
	{
		return 1;
	}

	char CaptionName[64];

	wchar_t szProcessName[MAX_PATH], sTemp[MAX_PATH];

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

	if (hProcess != NULL)
	{
		if(GetProcessImageFileNameW(hProcess,szProcessName,MAX_PATH) != 0)
		{
			if(ConvertProcessImageFileNameW(szProcessName,sTemp,MAX_PATH) != 0)
			{
				if((flag & 2) != 0 && gDumpCheck.Check(sTemp,CaptionName) == 0)
				{
					CloseHandle(hProcess);
					CHClientDisconnectSend(CLIENT_DISCONNECT_DUMP_DETECTION,CaptionName,processID);
					return 0;
				}

				if((flag & 4) != 0 && gExecutableCheck.Check(sTemp,CaptionName) == 0)
				{
					CloseHandle(hProcess);
					CHClientDisconnectSend(CLIENT_DISCONNECT_EXECUTABLE_DETECTION,CaptionName,processID);
					return 0;
				}

				if((flag & 8) != 0 && gLibraryCheck.Check(sTemp,CaptionName) == 0)
				{
					CloseHandle(hProcess);
					CHClientDisconnectSend(CLIENT_DISCONNECT_LIBRARY_DETECTION,CaptionName,processID);
					return 0;
				}
			}
		}

		CloseHandle(hProcess);
	}

	return 1;
}
