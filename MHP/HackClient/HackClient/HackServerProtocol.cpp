#include "stdafx.h"
#include "HackServerProtocol.h"
#include "Connection.h"
#include "ListManager.h"
#include "Log.h"
#include "Message.h"
#include "Protect.h"
#include "Util.h"

DWORD gConnectionStatusTime = 0;
DWORD gEncDecKey1 = 0;
DWORD gEncDecKey2 = 0;
DWORD gClientInfoOK = 0;
DWORD gDumpListOK = 0;
DWORD gChecksumListOK = 0;
DWORD gInternalListOK = 0;
DWORD gWindowListOK = 0;
DWORD gDumpListMaxCount = 0;
DWORD gChecksumListMaxCount = 0;
DWORD gInternalListMaxCount = 0;
DWORD gWindowListMaxCount = 0;
DWORD gMemoryGuardSwitch = 0;
DWORD gMemoryGuardNumber = 0;
DWORD gMacroProtectSwitch = 0;
DWORD gMacroProtectNumber = 0;
DWORD gReconnectSwitch = 0;
DWORD gReconnectStatus = 0;
DWORD gDetectCloseTime = 0;
DWORD gInternalVersion = 0;
DWORD gUserAccount = 0;
DWORD gUserStruct = 0;
DWORD gWindowHwnd = 0;
DWORD gIpAddressAddress = 0;
DWORD gClientVersionAddress = 0;
DWORD gClientSerialAddress = 0;
DWORD gFileProtectAddress1 = 0;
DWORD gFileProtectAddress2 = 0;
char gIpAddress[32];
BYTE gClientVersion[5];
BYTE gClientSerial[17];

void HackServerProtocolCore(BYTE head,BYTE* lpMsg,int size) // OK
{
	switch(head)
	{
		case 0x00:
			HCClientInfoRecv((SDHP_CLIENT_INFO_RECV*)lpMsg);
			break;
		case 0x01:
			HCConnectionStatusRecv((SDHP_CONNECTION_STATUS_RECV*)lpMsg);
			break;
		case 0x02:
			switch(lpMsg[5])
			{
				case 0x00:
					HCDumpListRecv((SDHP_DUMP_LIST_RECV*)lpMsg);
					break;
				case 0x01:
					HCChecksumListRecv((SDHP_CHECKSUM_LIST_RECV*)lpMsg);
					break;
				case 0x02:
					HCInternalListRecv((SDHP_INTERNAL_LIST_RECV*)lpMsg);
					break;
				case 0x03:
					HCWindowListRecv((SDHP_WINDOW_LIST_RECV*)lpMsg);
					break;
			}
			break;
		case 0x03:
			HCClientDisconnectRecv((SDHP_CLIENT_DISCONNECT_RECV*)lpMsg);
			break;
		default:
			gLog.Output(LOG_DEBUG,GetEncryptedString(25),head,size);
			gConnection.Disconnect();
			break;
	}
}

void HCClientInfoRecv(SDHP_CLIENT_INFO_RECV* lpMsg) // OK
{
	gLog.Output(LOG_DEBUG,GetEncryptedString(26),lpMsg->result,lpMsg->EncDecKey1,lpMsg->EncDecKey2,lpMsg->InternalVersion,lpMsg->ReconnectSwitch,lpMsg->MemoryGuardSwitch,lpMsg->MemoryGuardNumber,lpMsg->MacroProtectSwitch,lpMsg->MacroProtectNumber,lpMsg->MemoryAddress1,lpMsg->MemoryAddress2,lpMsg->MemoryAddress3,lpMsg->MemoryAddress4,lpMsg->MemoryAddress5,lpMsg->MemoryAddress6,lpMsg->MemoryAddress7,lpMsg->MemoryAddress8);

	if(lpMsg->result == 0)
	{
		gClientInfoOK = 1;

		gConnectionStatusTime = GetTickCount();

		gEncDecKey1 = lpMsg->EncDecKey1;

		gEncDecKey2 = lpMsg->EncDecKey2;

		gInternalVersion = lpMsg->InternalVersion;

		gReconnectSwitch = lpMsg->ReconnectSwitch;

		gMemoryGuardSwitch = lpMsg->MemoryGuardSwitch;

		gMemoryGuardNumber = lpMsg->MemoryGuardNumber;

		gMacroProtectSwitch = lpMsg->MacroProtectSwitch;

		gMacroProtectNumber = lpMsg->MacroProtectNumber;

		if(lpMsg->MemoryAddress1 != 0)
		{
			gIpAddressAddress = lpMsg->MemoryAddress1;

			MemoryCpy((DWORD)gIpAddress,gProtect.m_MainInfo.IpAddress,sizeof(gIpAddress));
		}

		if(lpMsg->MemoryAddress2 != 0)
		{
			gClientVersionAddress = lpMsg->MemoryAddress2;

			gClientVersion[0] = (lpMsg->ClientVersion[0]+1);

			gClientVersion[1] = (lpMsg->ClientVersion[2]+2);

			gClientVersion[2] = (lpMsg->ClientVersion[3]+3);

			gClientVersion[3] = (lpMsg->ClientVersion[5]+4);

			gClientVersion[4] = (lpMsg->ClientVersion[6]+5);
		}

		if(lpMsg->MemoryAddress3 != 0)
		{
			gClientSerialAddress = lpMsg->MemoryAddress3;

			MemoryCpy((DWORD)gClientSerial,lpMsg->ClientSerial,sizeof(gClientSerial));
		}

		if(lpMsg->MemoryAddress4 != 0)
		{
			gUserAccount = lpMsg->MemoryAddress4;
		}

		if(lpMsg->MemoryAddress5 != 0)
		{
			gUserStruct = lpMsg->MemoryAddress5;
		}

		if(lpMsg->MemoryAddress6 != 0)
		{
			gWindowHwnd = lpMsg->MemoryAddress6;
		}

		if(lpMsg->MemoryAddress7 != 0)
		{
			gFileProtectAddress1 = lpMsg->MemoryAddress7;
		}

		if(lpMsg->MemoryAddress8 != 0)
		{
			gFileProtectAddress2 = lpMsg->MemoryAddress8;
		}
	}
	else
	{
		switch(lpMsg->result)
		{
			case 1:
				SplashScreen(&SplashAlert,1,1,gMessage.GetMessage(8),5000);
				break;
			case 2:
				SplashScreen(&SplashAlert,1,1,gMessage.GetMessage(9),5000);
				break;
			case 3:
				SplashScreen(&SplashAlert,1,1,gMessage.GetMessage(10),5000);
				break;
			case 4:
				SplashScreen(&SplashAlert,1,1,gMessage.GetMessage(11),5000);
				break;
			case 5:
				SplashScreen(&SplashAlert,1,1,gMessage.GetMessage(12),5000);
				break;
			default:
				SplashScreen(&SplashAlert,1,1,gMessage.GetMessage(13),5000);
				break;
		}
	}
}

void HCConnectionStatusRecv(SDHP_CONNECTION_STATUS_RECV* lpMsg) // OK
{
	gConnectionStatusTime = GetTickCount();
}

void HCDumpListRecv(SDHP_DUMP_LIST_RECV* lpMsg) // OK
{
	gLog.Output(LOG_DEBUG,GetEncryptedString(27),lpMsg->count,lpMsg->MaxCount);

	gDumpListMaxCount = lpMsg->MaxCount;

	for(int n=0;n < lpMsg->count;n++)
	{
		DUMP_LIST_INFO* lpInfo = (DUMP_LIST_INFO*)(((BYTE*)lpMsg)+sizeof(SDHP_DUMP_LIST_RECV)+(sizeof(DUMP_LIST_INFO)*n));

		gListManager.gDumpListInfo.push_back((*lpInfo));
	}

	gDumpListOK = 1;
}

void HCChecksumListRecv(SDHP_CHECKSUM_LIST_RECV* lpMsg) // OK
{
	gLog.Output(LOG_DEBUG,GetEncryptedString(28),lpMsg->count,lpMsg->MaxCount);

	gChecksumListMaxCount = lpMsg->MaxCount;

	for(int n=0;n < lpMsg->count;n++)
	{
		CSUM_LIST_INFO* lpInfo = (CSUM_LIST_INFO*)(((BYTE*)lpMsg)+sizeof(SDHP_CHECKSUM_LIST_RECV)+(sizeof(CSUM_LIST_INFO)*n));

		gListManager.gChecksumListInfo.push_back((*lpInfo));
	}

	gChecksumListOK = 1;
}

void HCInternalListRecv(SDHP_INTERNAL_LIST_RECV* lpMsg) // OK
{
	gLog.Output(LOG_DEBUG,GetEncryptedString(29),lpMsg->count,lpMsg->MaxCount);

	gInternalListMaxCount = lpMsg->MaxCount;

	for(int n=0;n < lpMsg->count;n++)
	{
		ITRN_LIST_INFO* lpInfo = (ITRN_LIST_INFO*)(((BYTE*)lpMsg)+sizeof(SDHP_INTERNAL_LIST_RECV)+(sizeof(ITRN_LIST_INFO)*n));

		gListManager.gInternalListInfo.push_back((*lpInfo));
	}

	gInternalListOK = 1;
}

void HCWindowListRecv(SDHP_WINDOW_LIST_RECV* lpMsg) // OK
{
	gLog.Output(LOG_DEBUG,GetEncryptedString(43),lpMsg->count,lpMsg->MaxCount);

	gWindowListMaxCount = lpMsg->MaxCount;

	for(int n=0;n < lpMsg->count;n++)
	{
		WNDW_LIST_INFO* lpInfo = (WNDW_LIST_INFO*)(((BYTE*)lpMsg)+sizeof(SDHP_WINDOW_LIST_RECV)+(sizeof(WNDW_LIST_INFO)*n));

		gListManager.gWindowListInfo.push_back((*lpInfo));
	}

	gWindowListOK = 1;
}

void HCClientDisconnectRecv(SDHP_CLIENT_DISCONNECT_RECV* lpMsg) // OK
{
	gLog.Output(LOG_DEBUG,GetEncryptedString(30),lpMsg->type);

	switch(lpMsg->type)
	{
		case CLIENT_DISCONNECT_NONE:
			break;
		case CLIENT_DISCONNECT_DUMP_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(14),5000);
			break;
		case CLIENT_DISCONNECT_EXECUTABLE_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(15),5000);
			break;
		case CLIENT_DISCONNECT_FILE_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(16),5000);
			break;
		case CLIENT_DISCONNECT_FILE_MAPPING_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(17),5000);
			break;
		case CLIENT_DISCONNECT_LIBRARY_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(18),5000);
			break;
		case CLIENT_DISCONNECT_REGISTRY_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(19),5000);
			break;
		case CLIENT_DISCONNECT_MEMORY_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(20),5000);
			break;
		case CLIENT_DISCONNECT_WINDOW_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(22),5000);
			break;
		case CLIENT_DISCONNECT_MACRO_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(24),5000);
			break;
		case CLIENT_DISCONNECT_DEBUGGER_DETECTION:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(25),5000);
			break;
		default:
			SplashScreen(&SplashError,2,1,gMessage.GetMessage(21),5000);
			break;
	}
}

void CHClientInfoSend() // OK
{
	if(gReconnectStatus != 1)
	{
		gClientInfoOK = 0;

		gDumpListOK = 0;

		gChecksumListOK = 0;

		gInternalListOK = 0;

		gWindowListOK = 0;

		gDumpListMaxCount = 0;

		gChecksumListMaxCount = 0;

		gInternalListMaxCount = 0;

		gWindowListMaxCount = 0;

		gListManager.gDumpListInfo.clear();

		gListManager.gChecksumListInfo.clear();

		gListManager.gInternalListInfo.clear();

		gListManager.gWindowListInfo.clear();
	}

	SDHP_CLIENT_INFO_SEND pMsg;

	pMsg.header.set(0x00,sizeof(pMsg));

	pMsg.IsReconnect = gReconnectStatus;

	pMsg.ClientFileCRC = gProtect.m_ClientFileCRC;

	memcpy(pMsg.HackVersion,HACKCLIENT_VERSION,sizeof(pMsg.HackVersion));

	memcpy(pMsg.HardwareId,GetHardwareId(),sizeof(pMsg.HardwareId));

	gLog.Output(LOG_DEBUG,GetEncryptedString(31),pMsg.IsReconnect,pMsg.ClientFileCRC,pMsg.HackVersion,pMsg.HardwareId);

	gConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void CHConnectionStatusSend() // OK
{
	SDHP_CONNECTION_STATUS_SEND pMsg;

	pMsg.header.set(0x01,sizeof(pMsg));

	gConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void CHClientDisconnectSend(int type,char* text,DWORD pid) // OK
{
	if(gDetectCloseTime == 0)
	{
		gDetectCloseTime = GetTickCount();

		SDHP_CLIENT_DISCONNECT_RECV pMsg;

		pMsg.header.set(0x03,sizeof(pMsg));

		pMsg.type = type;

		if(gConnection.CheckState() == 0){HCClientDisconnectRecv(&pMsg);return;}
	}
	else
	{
		return;
	}

	SDHP_CLIENT_DISCONNECT_SEND pMsg;

	pMsg.header.set(0x03,sizeof(pMsg));

	pMsg.type = type;

	if(gUserAccount == 0)
	{
		memset(pMsg.account,0,sizeof(pMsg.account));
	}
	else
	{
		memcpy(pMsg.account,(void*)gUserAccount,sizeof(pMsg.account));
	}

	if(gUserStruct == 0 || (*(DWORD*)(gUserStruct)) == 0)
	{
		memset(pMsg.name,0,sizeof(pMsg.name));
	}
	else
	{
		memcpy(pMsg.name,(void*)(*(DWORD*)(gUserStruct)+0x00),sizeof(pMsg.name));
	}

	if(text == 0)
	{
		memset(pMsg.CaptionName,0,sizeof(pMsg.CaptionName));
	}
	else
	{
		memcpy(pMsg.CaptionName,text,sizeof(pMsg.CaptionName));
	}

	if(pid == 0)
	{
		memset(pMsg.ProcessName,0,sizeof(pMsg.ProcessName));
	}
	else
	{
		memset(pMsg.ProcessName,0,sizeof(pMsg.ProcessName));

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,0,pid);

		if(hProcess != 0)
		{
			wchar_t szProcessName[MAX_PATH];

			if(GetProcessImageFileNameW(hProcess,szProcessName,MAX_PATH) != 0)
			{
				wsprintf(pMsg.ProcessName,"%S",ConvertModuleFileName(szProcessName));
			}

			CloseHandle(hProcess);
		}
	}

	gLog.Output(LOG_DEBUG,GetEncryptedString(32),pMsg.type,pMsg.account,pMsg.name,pMsg.CaptionName,pMsg.ProcessName);

	gConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
}
