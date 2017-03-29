#include "stdafx.h"
#include "HackServerProtocol.h"
#include "ClientManager.h"
#include "HidManager.h"
#include "Log.h"
#include "ReadFiles.h"
#include "BlackList.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "Util.h"

void HackServerProtocolCore(int index,BYTE head,BYTE* lpMsg,int size) // OK
{
	gClientManager[index].m_PacketTime = GetTickCount();

	switch(head)
	{
		case 0x00:
			CHClientInfoRecv((SDHP_CLIENT_INFO_RECV*)lpMsg,index);
			break;
		case 0x01:
			CHConnectionStatusRecv((SDHP_CONNECTION_STATUS_RECV*)lpMsg,index);
			break;
		case 0x03:
			CHClientDisconnectRecv((SDHP_CLIENT_DISCONNECT_RECV*)lpMsg,index);
			break;
		default:
			gSocketManager.Disconnect(index);
			break;
	}
}

void CHClientInfoRecv(SDHP_CLIENT_INFO_RECV* lpMsg,int index) // OK
{
	SDHP_CLIENT_INFO_SEND pMsg;

	pMsg.header.set(0x00,sizeof(pMsg));

	pMsg.result = 0;

	if(gServerInfo.m_ClientFileCRC != 0 && gServerInfo.m_ClientFileCRC != lpMsg->ClientFileCRC)
	{
		pMsg.result = 1;
		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
		return;
	}

	if(GetCurrentVersion() != ConvertHackVersion(lpMsg->HackVersion))
	{
		pMsg.result = 2;
		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
		return;
	}

	if(gHidManager.CheckHardwareId(lpMsg->HardwareId) == 0)
	{
		pMsg.result = 3;
		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
		return;
	}

	if(gBlackList.CheckHardwareId(lpMsg->HardwareId) == 0)
	{
		pMsg.result = 4;
		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
		return;
	}

	if(gBlackList.CheckIpAddress(gClientManager[index].m_IpAddr) == 0)
	{
		pMsg.result = 5;
		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
		return;
	}

	if(lpMsg->IsReconnect == 0)
	{
		gClientManager[index].SetClientInfo(lpMsg->HardwareId);

		pMsg.EncDecKey1 = gServerInfo.m_EncDecKey1;

		pMsg.EncDecKey2 = gServerInfo.m_EncDecKey2;

		pMsg.InternalVersion = gServerInfo.m_InternalVersion;

		pMsg.ReconnectSwitch = gServerInfo.m_ReconnectSwitch;

		pMsg.MemoryGuardSwitch = gServerInfo.m_MemoryGuardSwitch;

		pMsg.MemoryGuardNumber = gServerInfo.m_MemoryGuardNumber;

		pMsg.MacroProtectSwitch = gServerInfo.m_MacroProtectSwitch;

		pMsg.MacroProtectNumber = gServerInfo.m_MacroProtectNumber;

		memcpy(pMsg.ClientVersion,gServerInfo.m_ClientVersion,sizeof(pMsg.ClientVersion));

		memcpy(pMsg.ClientSerial,gServerInfo.m_ClientSerial,sizeof(pMsg.ClientSerial));

		pMsg.MemoryAddress1 = gServerInfo.m_MemoryAddress1;

		pMsg.MemoryAddress2 = gServerInfo.m_MemoryAddress2;

		pMsg.MemoryAddress3 = gServerInfo.m_MemoryAddress3;

		pMsg.MemoryAddress4 = gServerInfo.m_MemoryAddress4;

		pMsg.MemoryAddress5 = gServerInfo.m_MemoryAddress5;

		pMsg.MemoryAddress6 = gServerInfo.m_MemoryAddress6;

		pMsg.MemoryAddress7 = gServerInfo.m_MemoryAddress7;

		pMsg.MemoryAddress8 = gServerInfo.m_MemoryAddress8;

		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);

		HCDumpListSend(index);

		HCChecksumListSend(index);

		HCInternalListSend(index);

		HCWindowListSend(index);
	}
	else
	{
		gClientManager[index].SetClientInfo(lpMsg->HardwareId);
	}
}

void CHConnectionStatusRecv(SDHP_CONNECTION_STATUS_RECV* lpMsg,int index) // OK
{
	SDHP_CONNECTION_STATUS_SEND pMsg;

	pMsg.header.set(0x01,sizeof(pMsg));

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);

	gClientManager[index].m_OnlineTime = GetTickCount();
}

void CHClientDisconnectRecv(SDHP_CLIENT_DISCONNECT_RECV* lpMsg,int index) // OK
{
	char buff[128] = {0};
	
	switch(lpMsg->type)
	{
		case CLIENT_DISCONNECT_NONE:
			HCClientDisconnectSend(index,lpMsg->type);
			return;
		case CLIENT_DISCONNECT_DUMP_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"DUMP_DETECTION");
			break;
		case CLIENT_DISCONNECT_EXECUTABLE_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"EXECUTABLE_DETECTION");
			break;
		case CLIENT_DISCONNECT_FILE_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"FILE_DETECTION");
			break;
		case CLIENT_DISCONNECT_FILE_MAPPING_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"FILE_MAPPING_DETECTION");
			break;
		case CLIENT_DISCONNECT_LIBRARY_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"LIBRARY_DETECTION");
			break;
		case CLIENT_DISCONNECT_REGISTRY_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"REGISTRY_DETECTION");
			break;
		case CLIENT_DISCONNECT_MEMORY_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"MEMORY_DETECTION");
			break;
		case CLIENT_DISCONNECT_WINDOW_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"WINDOW_DETECTION");
			break;
		case CLIENT_DISCONNECT_MACRO_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"MACRO_DETECTION");
			break;
		case CLIENT_DISCONNECT_DEBUGGER_DETECTION:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"DEBUGGER_DETECTION");
			break;
		default:
			gHidManager.InsertHardwareId(gClientManager[index].m_HardwareId);
			wsprintf(buff,"DEFAULT_DETECTION");
			break;
	}

	HCClientDisconnectSend(index,lpMsg->type);
	gLog.Output(LOG_HACK,"[HackDetected][%s][%s] IpAddress: %s, HardwareId: %s, DetectionType: %s, CaptionName: %s, ProcessName: %s",lpMsg->account,lpMsg->name,gClientManager[index].m_IpAddr,gClientManager[index].m_HardwareId,buff,lpMsg->CaptionName,lpMsg->ProcessName);
}

void HCDumpListSend(int index) // OK
{
	std::vector<DUMP_LIST_INFO>::iterator MakeList = gReadFiles.gDumpListInfo.begin();

	do
	{
		BYTE send[8192];

		SDHP_DUMP_LIST_SEND pMsg;

		pMsg.header.set(0x02,0x00,0);

		int size = sizeof(pMsg);

		pMsg.MaxCount = gReadFiles.gDumpListInfo.size();

		pMsg.count = 0;

		DUMP_LIST_INFO info;

		for(;MakeList != gReadFiles.gDumpListInfo.end();MakeList++)
		{
			info.type = MakeList->type;

			info.offset = MakeList->offset;

			memcpy(info.dump,MakeList->dump,sizeof(info.dump));

			memcpy(info.name,MakeList->name,sizeof(info.name));

			if((size+sizeof(info)) > sizeof(send))
			{
				break;
			}
			else
			{
				memcpy(&send[size],&info,sizeof(info));
				size += sizeof(info);

				pMsg.count++;
			}
		}

		pMsg.header.size[0] = SET_NUMBERHB(size);

		pMsg.header.size[1] = SET_NUMBERLB(size);

		memcpy(send,&pMsg,sizeof(pMsg));

		gSocketManager.DataSend(index,send,size);
	}
	while(MakeList != gReadFiles.gDumpListInfo.end());
}

void HCChecksumListSend(int index) // OK
{
	std::vector<CSUM_LIST_INFO>::iterator MakeList = gReadFiles.gChecksumListInfo.begin();

	do
	{
		BYTE send[8192];

		SDHP_CHECKSUM_LIST_SEND pMsg;

		pMsg.header.set(0x02,0x01,0);

		int size = sizeof(pMsg);

		pMsg.MaxCount = gReadFiles.gChecksumListInfo.size();

		pMsg.count = 0;

		CSUM_LIST_INFO info;

		for(;MakeList != gReadFiles.gChecksumListInfo.end();MakeList++)
		{
			memcpy(info.path,MakeList->path,sizeof(info.path));

			info.checksum = MakeList->checksum;

			if((size+sizeof(info)) > sizeof(send))
			{
				break;
			}
			else
			{
				memcpy(&send[size],&info,sizeof(info));
				size += sizeof(info);

				pMsg.count++;
			}
		}

		pMsg.header.size[0] = SET_NUMBERHB(size);

		pMsg.header.size[1] = SET_NUMBERLB(size);

		memcpy(send,&pMsg,sizeof(pMsg));

		gSocketManager.DataSend(index,send,size);
	}
	while(MakeList != gReadFiles.gChecksumListInfo.end());
}

void HCInternalListSend(int index) // OK
{
	std::vector<ITRN_LIST_INFO>::iterator MakeList = gReadFiles.gInternalListInfo.begin();

	do
	{
		BYTE send[8192];

		SDHP_INTERNAL_LIST_SEND pMsg;

		pMsg.header.set(0x02,0x02,0);

		int size = sizeof(pMsg);

		pMsg.MaxCount = gReadFiles.gInternalListInfo.size();

		pMsg.count = 0;

		ITRN_LIST_INFO info;

		for(;MakeList != gReadFiles.gInternalListInfo.end();MakeList++)
		{
			info.type = MakeList->type;

			memcpy(info.value,MakeList->value,sizeof(info.value));

			if((size+sizeof(info)) > sizeof(send))
			{
				break;
			}
			else
			{
				memcpy(&send[size],&info,sizeof(info));
				size += sizeof(info);

				pMsg.count++;
			}
		}

		pMsg.header.size[0] = SET_NUMBERHB(size);

		pMsg.header.size[1] = SET_NUMBERLB(size);

		memcpy(send,&pMsg,sizeof(pMsg));

		gSocketManager.DataSend(index,send,size);
	}
	while(MakeList != gReadFiles.gInternalListInfo.end());
}

void HCWindowListSend(int index) // OK
{
	std::vector<WNDW_LIST_INFO>::iterator MakeList = gReadFiles.gWindowListInfo.begin();

	do
	{
		BYTE send[8192];

		SDHP_WINDOW_LIST_SEND pMsg;

		pMsg.header.set(0x02,0x03,0);

		int size = sizeof(pMsg);

		pMsg.MaxCount = gReadFiles.gWindowListInfo.size();

		pMsg.count = 0;

		WNDW_LIST_INFO info;

		for(;MakeList != gReadFiles.gWindowListInfo.end();MakeList++)
		{
			info.type = MakeList->type;

			memcpy(info.text,MakeList->text,sizeof(info.text));

			if((size+sizeof(info)) > sizeof(send))
			{
				break;
			}
			else
			{
				memcpy(&send[size],&info,sizeof(info));
				size += sizeof(info);

				pMsg.count++;
			}
		}

		pMsg.header.size[0] = SET_NUMBERHB(size);

		pMsg.header.size[1] = SET_NUMBERLB(size);

		memcpy(send,&pMsg,sizeof(pMsg));

		gSocketManager.DataSend(index,send,size);
	}
	while(MakeList != gReadFiles.gWindowListInfo.end());
}

void HCClientDisconnectSend(int index,int type) // OK
{
	SDHP_CLIENT_DISCONNECT_SEND pMsg;

	pMsg.header.set(0x03,sizeof(pMsg));

	pMsg.type = type;

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}
