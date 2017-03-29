#include "stdafx.h"
#include "Reconnect.h"
#include "CustomMessage.h"
#include "HackCheck.h"
#include "Offset.h"
#include "Protect.h"
#include "Protocol.h"
#include "Util.h"

char GameServerAddress[16];
WORD GameServerPort;
char ReconnectAccount[11];
char ReconnectPassword[11];
char ReconnectName[11];
char ReconnectMapServerAddress[16];
WORD ReconnectMapServerPort;
DWORD ReconnectStatus = RECONNECT_STATUS_NONE;
DWORD ReconnectProgress = RECONNECT_PROGRESS_NONE;
DWORD ReconnectCurTime = 0;
DWORD ReconnectMaxTime = 0;
DWORD ReconnectCurWait = 0;
DWORD ReconnectMaxWait = 0;
DWORD ReconnectAuthSend = 0;
DWORD ReconnectHelperOn = 0;

void InitReconnect() // OK
{
	if(gProtect.m_MainInfo.ReconnectTime == 0)
	{
		return;
	}

	SetCompleteHook(0xE9,0x0043E91B,&ReconnectGetAccountInfo);

	SetCompleteHook(0xE9,0x004E13DA,&ReconnectCheckConnection);

	SetCompleteHook(0xE9,0x00633486,&ReconnectCloseSocket);

	SetCompleteHook(0xE9,0x007ADA2B,&ReconnectMenuExitGame);

	SetCompleteHook(0xE8,0x0043EC02,&ReconnectCreateConnection);

	SetCompleteHook(0xE8,0x004DE332,&ReconnectCreateConnection);

	SetCompleteHook(0xE8,0x004F749C,&ReconnectCreateConnection);

	SetCompleteHook(0xE8,0x00635914,&ReconnectCreateConnection);

	SetCompleteHook(0xE8,0x007F3F49,&ReconnectMainProc);
}

void ReconnectMainProc() // OK
{
	((void(*)())0x005AFA46)();

	if(*(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if(ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		return;
	}

	ReconnectDrawInterface();

	if((GetTickCount()-ReconnectMaxTime) > ReconnectMaxWait)
	{
		ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,RECONNECT_PROGRESS_NONE,0,0);
		((void(__thiscall*)(void*))0x00633474)((void*)0x08B15A70);
		return;
	}

	if((GetTickCount()-ReconnectCurTime) < ReconnectCurWait)
	{
		return;
	}

	switch(ReconnectProgress)
	{
		case RECONNECT_PROGRESS_NONE:
			ReconnecGameServerLoad();
			break;
		case RECONNECT_PROGRESS_CONNECTED:
			ReconnecGameServerAuth();
			break;
	}

	ReconnectCurTime = GetTickCount();
}

void ReconnectDrawInterface() // OK
{
	float StartX = (MAX_WIN_WIDTH/2.0f)-(160.0f/2.0f);

	float StartY = 100.0f;

	float progress = ((ReconnectMaxWait==0)?0:(((GetTickCount()-ReconnectMaxTime)*150.0f)/(float)ReconnectMaxWait));

	progress = ((progress>150)?150:progress);

	DrawInterface(0x7A65,StartX,StartY,160.0f,18.0f);

	DrawInterface(0x7A66,(StartX+5.0f),(StartY+5.0f),progress,8.0f);

	char buff[256];

	switch(ReconnectProgress)
	{
		case RECONNECT_PROGRESS_NONE:
			wsprintf(buff,gCustomMessage.GetMessage(1));
			DrawInterfaceText(buff,(int)StartX,(int)(StartY+5.0f),0xFFFFFFFF,0,3,160.0f,0);
			break;
		case RECONNECT_PROGRESS_CONNECTED:
			wsprintf(buff,gCustomMessage.GetMessage(2));
			DrawInterfaceText(buff,(int)StartX,(int)(StartY+5.0f),0xFFFFFFFF,0,3,160.0f,0);
			break;
		case RECONNECT_PROGRESS_JOINED:
			wsprintf(buff,gCustomMessage.GetMessage(3));
			DrawInterfaceText(buff,(int)StartX,(int)(StartY+5.0f),0xFFFFFFFF,0,3,160.0f,0);
			break;
		case RECONNECT_PROGRESS_CHAR_LIST:
			wsprintf(buff,gCustomMessage.GetMessage(4));
			DrawInterfaceText(buff,(int)StartX,(int)(StartY+5.0f),0xFFFFFFFF,0,3,160.0f,0);
			break;
	}
}

void ReconnectSetInfo(DWORD status,DWORD progress,DWORD CurWait,DWORD MaxWait) // OK
{
	ReconnectStatus = status;

	ReconnectProgress = progress;

	ReconnectCurTime = GetTickCount();

	ReconnectMaxTime = GetTickCount();

	ReconnectCurWait = CurWait;

	ReconnectMaxWait = MaxWait;

	ReconnectAuthSend = ((status==RECONNECT_STATUS_NONE)?0:ReconnectAuthSend);

	ReconnectHelperOn = ((status==RECONNECT_STATUS_NONE)?0:ReconnectHelperOn);
}

void ReconnecGameServerLoad() // OK
{
	if(ReconnectCreateConnection(GameServerAddress,GameServerPort) != 0)
	{
		*(DWORD*)(MAIN_CONNECTION_STATUS) = 1;

		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_CONNECTED,10000,30000);
	}
}

void ReconnecGameServerAuth() // OK
{
	if(((ReconnectAuthSend==0)?(ReconnectAuthSend++):ReconnectAuthSend) != 0)
	{
		return;
	}

	PMSG_CONNECT_ACCOUNT_SEND pMsg;

	pMsg.header.setE(0xF1,0x01,sizeof(pMsg));

	PacketArgumentEncrypt(pMsg.account,ReconnectAccount,(sizeof(ReconnectAccount)-1));

	PacketArgumentEncrypt(pMsg.password,ReconnectPassword,(sizeof(ReconnectPassword)-1));

	pMsg.TickCount = GetTickCount();

	pMsg.ClientVersion[0] = (*(BYTE*)(0x0118EF48))-1;

	pMsg.ClientVersion[1] = (*(BYTE*)(0x0118EF49))-2;

	pMsg.ClientVersion[2] = (*(BYTE*)(0x0118EF4A))-3;

	pMsg.ClientVersion[3] = (*(BYTE*)(0x0118EF4B))-4;

	pMsg.ClientVersion[4] = (*(BYTE*)(0x0118EF4C))-5;

	memcpy(pMsg.ClientSerial,(void*)0x0118EF50,sizeof(pMsg.ClientSerial));

	pMsg.LanguageCode = 0;

	DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void ReconnectOnCloseSocket() // OK
{
	if(*(DWORD*)(MAIN_SCREEN_STATE) == 5 && ReconnectStatus != RECONNECT_STATUS_DISCONNECT)
	{
		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_NONE,30000,gProtect.m_MainInfo.ReconnectTime);

		ReconnectAuthSend = 0;

		ReconnectHelperOn = *(BYTE*)(*(DWORD*)(MAIN_HELPER_STRUCT)+0x08);

		ReconnectViewportDestroy();

		memcpy(ReconnectName,(void*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x00),sizeof(ReconnectName));
	}
}

void ReconnectOnMapServerMove(char* address,WORD port) // OK
{
	if(ReconnectStatus != RECONNECT_STATUS_RECONNECT || ReconnectProgress == RECONNECT_PROGRESS_CHAR_LIST)
	{
		strcpy_s(ReconnectMapServerAddress,address);

		ReconnectMapServerPort = port;

		ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,((ReconnectProgress==RECONNECT_PROGRESS_CHAR_LIST)?ReconnectProgress:RECONNECT_PROGRESS_NONE),0,0);
	}
}

void ReconnectOnMapServerMoveAuth(BYTE result) // OK
{
	if(ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		if(result == 1)
		{
			ReconnectSetInfo(((ReconnectProgress==RECONNECT_PROGRESS_CHAR_LIST)?ReconnectStatus:RECONNECT_STATUS_NONE),((ReconnectProgress==RECONNECT_PROGRESS_CHAR_LIST)?ReconnectProgress:RECONNECT_PROGRESS_NONE),0,0);
		}
		else
		{
			ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,RECONNECT_PROGRESS_NONE,0,0);
		}
	}
}

void ReconnectOnConnectAccount(BYTE result) // OK
{
	if(ReconnectProgress == RECONNECT_PROGRESS_CONNECTED)
	{
		if(ReconnectAuthSend != 0)
		{
			if(result == 1)
			{
				PMSG_CHARACTER_LIST_SEND pMsg;

				pMsg.header.set(0xF3,0x00,sizeof(pMsg));

				DataSend((BYTE*)&pMsg,pMsg.header.size);

				ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_JOINED,30000,30000);
			}
			else
			{
				if(result == 3)
				{
					ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_CONNECTED,10000,30000);
					ReconnectAuthSend = 0;
				}
				else
				{
					ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,RECONNECT_PROGRESS_NONE,0,0);
					((void(__thiscall*)(void*))0x00633474)((void*)0x08B15A70);
				}
			}
		}
	}
}

void ReconnectOnCloseClient(BYTE result) // OK
{
	if(ReconnectStatus != RECONNECT_STATUS_RECONNECT)
	{
		if(result == 0 || result == 2)
		{
			ReconnectSetInfo(RECONNECT_STATUS_DISCONNECT,RECONNECT_PROGRESS_NONE,0,0);
		}
	}
}

void ReconnectOnCharacterList() // OK
{
	if(ReconnectProgress == RECONNECT_PROGRESS_JOINED)
	{
		PMSG_CHARACTER_INFO_SEND pMsg;

		pMsg.header.set(0xF3,0x03,sizeof(pMsg));

		memcpy(pMsg.name,ReconnectName,sizeof(pMsg.name));

		DataSend((BYTE*)&pMsg,pMsg.header.size);

		ReconnectSetInfo(RECONNECT_STATUS_RECONNECT,RECONNECT_PROGRESS_CHAR_LIST,30000,30000);
	}
}

void ReconnectOnCharacterInfo() // OK
{
	if(ReconnectProgress == RECONNECT_PROGRESS_CHAR_LIST)
	{
		if(ReconnectHelperOn != 0)
		{
			PMSG_HELPER_START_SEND pMsg;

			pMsg.header.set(0xBF,0x51,sizeof(pMsg));

			pMsg.type = 0;

			DataSend((BYTE*)&pMsg,pMsg.header.size);
		}
	}

	ReconnectSetInfo(RECONNECT_STATUS_NONE,RECONNECT_PROGRESS_NONE,0,0);
}

void ReconnectViewportDestroy() // OK
{
	DWORD count = 0;

	DWORD ViewportAddress = 0;

	do
	{
		BYTE send[256];

		PMSG_VIEWPORT_DESTROY_RECV pMsg;

		pMsg.header.set(0x14,0);

		int size = sizeof(pMsg);

		pMsg.count = 0;

		PMSG_VIEWPORT_DESTROY info;

		for(;count < MAX_MAIN_VIEWPORT;count++)
		{
			if((ViewportAddress=((DWORD(__thiscall*)(void*,DWORD))0x009265D0)(((void*(*)())0x0043734E)(),count)) == 0)
			{
				continue;
			}

			if(*(BYTE*)(ViewportAddress+0x328) == 0)
			{
				continue;
			}

			info.index[0] = SET_NUMBERHB((*(WORD*)(ViewportAddress+0x7E)));
			info.index[1] = SET_NUMBERLB((*(WORD*)(ViewportAddress+0x7E)));

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

		pMsg.header.size = size;

		memcpy(send,&pMsg,sizeof(pMsg));

		ProtocolCoreEx(pMsg.header.head,send,size,-1);
	}
	while(count < MAX_MAIN_VIEWPORT);
}

BOOL ReconnectCreateConnection(char* address,WORD port) // OK
{
	if(PORT_RANGE(port) != 0 && GameServerAddress != address)
	{
		if(strcmp(ReconnectMapServerAddress,address) != 0 || ReconnectMapServerPort != port)
		{
			wsprintf(GameServerAddress,"%s",address);

			GameServerPort = port;

			memset(ReconnectMapServerAddress,0,sizeof(ReconnectMapServerAddress));

			ReconnectMapServerPort = 0;
		}
	}

	return ((BOOL(*)(char*,WORD))0x00635599)(address,port);
}

__declspec(naked) void ReconnectGetAccountInfo() // OK
{
	static DWORD ReconnectGetAccountInfoAddress1 = 0x0043E925;

	_asm
	{
		Push 0x0A
		Lea Eax,Dword Ptr Ss:[Ebp-0x18]
		Push Eax
		Lea Ecx,ReconnectAccount
		Push Ecx
		Call [MemoryCpy]
		Add Esp,0x0C
		Push 0x0A
		Lea Edx,Dword Ptr Ss:[Ebp-0x30]
		Push Edx
		Lea Eax,ReconnectPassword
		Push Eax
		Call [MemoryCpy]
		Add Esp,0x0C
		Mov Dword Ptr Ds:[0x08B159F4],0x01
		Jmp [ReconnectGetAccountInfoAddress1]
	}
}

__declspec(naked) void ReconnectCheckConnection() // OK
{
	static DWORD ReconnectCheckConnectionAddress1 = 0x004E13DF;
	static DWORD ReconnectCheckConnectionAddress2 = 0x004E1457;

	_asm
	{
		Cmp Eax,-1
		Jnz EXIT
		Mov Ecx,ReconnectStatus
		Cmp Ecx,RECONNECT_STATUS_RECONNECT
		Je EXIT
		Jmp [ReconnectCheckConnectionAddress1]
		EXIT:
		Jmp [ReconnectCheckConnectionAddress2]
	}
}

__declspec(naked) void ReconnectCloseSocket() // OK
{
	static DWORD ReconnectCloseSocketAddress1 = 0x0063348D;

	_asm
	{
		Mov Eax,Dword Ptr Ds:[MAIN_CONNECTION_STATUS]
		Cmp Eax,0x00
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp-0x0C]
		Mov Edx,Dword Ptr Ds:[Ecx+0x0C]
		Push Edx
		Call [CheckSocketPort]
		Add Esp,0x04
		Je EXIT
		Call [ReconnectOnCloseSocket]
		EXIT:
		Mov Dword Ptr Ds:[MAIN_CONNECTION_STATUS],0x00
		Jmp [ReconnectCloseSocketAddress1]
	}
}

__declspec(naked) void ReconnectMenuExitGame() // OK
{
	static DWORD ReconnectMenuExitGameAddress1 = 0x007ADA30;

	_asm
	{
		Mov Eax,ReconnectStatus
		Cmp Eax,RECONNECT_STATUS_RECONNECT
		Jnz EXIT
		Push 0
		Call [ExitProcess]
		EXIT:
		Mov ReconnectStatus,RECONNECT_STATUS_DISCONNECT
		Push 0x0101C398
		Jmp [ReconnectMenuExitGameAddress1]
	}
}
