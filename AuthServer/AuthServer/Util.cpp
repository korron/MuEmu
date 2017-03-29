#include "stdafx.h"
#include "Util.h"
#include "AuthServerProtocol.h"
#include "ClientManager.h"
#include "SocketManager.h"
#include "ThemidaSDK.h"

void ErrorMessageBox(char* message,...) // OK
{
	VM_START

	char buff[256];

	memset(buff,0,sizeof(buff));

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	MessageBox(0,buff,"Error",MB_OK | MB_ICONERROR);

	VM_END

	ExitProcess(0);
}

void LogAdd(eLogColor color,char* text,...) // OK
{
	tm today;
	time_t ltime;
	time(&ltime);

	if(localtime_s(&today,&ltime) != 0)
	{
		return;
	}

	char time[32];

	if(asctime_s(time,sizeof(time),&today) != 0)
	{
		return;
	}

	char temp[1024];

	va_list arg;
	va_start(arg,text);
	vsprintf_s(temp,text,arg);
	va_end(arg);

	char log[1024];

	wsprintf(log,"%.8s %s",&time[11],temp);

	gServerDisplayer.LogAddText(color,log,strlen(log));
}

void PacketDecryptData(BYTE* lpMsg,int size,BYTE key) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]+0x69)^(key+0x1A);
	}
}

void PacketEncryptData(BYTE* lpMsg,int size,BYTE key) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]^(key+0x25))-0xDA;
	}
}

void CheckComputerHardwareId() // OK
{
	VM_START

	DWORD VolumeSerialNumber;

	if(GetVolumeInformation("C:\\",0,0,&VolumeSerialNumber,0,0,0,0) == 0)
	{
		while(true)
		{
			TerminateProcess(GetCurrentProcess(),0);
			CRASH_APPLICATION_MACRO
		}
	}

	UUID uuid;

	UuidCreateSequential(&uuid);

	SYSTEM_INFO SystemInfo;

	GetSystemInfo(&SystemInfo);

	DWORD ComputerHardwareId1 = VolumeSerialNumber ^ 0x12B586FE;

	DWORD ComputerHardwareId2 = *(DWORD*)(&uuid.Data4[2]) ^ 0x5D78A569;

	DWORD ComputerHardwareId3 = ((*(WORD*)(&uuid.Data4[6]) & 0xFFFF) | (SystemInfo.wProcessorArchitecture << 16)) ^ 0xF45BC123;

	DWORD ComputerHardwareId4 = ((SystemInfo.wProcessorLevel & 0xFFFF) | (SystemInfo.wProcessorRevision << 16)) ^ 0xB542D8E1;

	char ComputerHardwareId[36] = {0};

	wsprintf(ComputerHardwareId,"%08X-%08X-%08X-%08X",ComputerHardwareId1,ComputerHardwareId2,ComputerHardwareId3,ComputerHardwareId4);

	if(strcmp(AUTHSERVER_HARDWAREID,ComputerHardwareId) != 0)
	{
		while(true)
		{
			TerminateProcess(GetCurrentProcess(),0);
			CRASH_APPLICATION_MACRO
		}
	}

	VM_END
}

void AuthServerTimeoutProc() // OK
{
	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[n].CheckState() != 0)
		{
			if(gClientManager[n].CheckOnlineTime() == 0)
			{
				gSocketManager.Disconnect(n);
			}
		}
	}
}

int GetDatabaseProductId(int ProductId) // OK
{
	switch(ProductId)
	{
		case AUTH_SERVER_TYPE_S6_CONNECT_SERVER:
		case AUTH_SERVER_TYPE_S6_JOIN_SERVER:
		case AUTH_SERVER_TYPE_S6_DATA_SERVER:
		case AUTH_SERVER_TYPE_S6_GAME_SERVER:
			return 2;
		case AUTH_SERVER_TYPE_S8_CONNECT_SERVER:
		case AUTH_SERVER_TYPE_S8_JOIN_SERVER:
		case AUTH_SERVER_TYPE_S8_DATA_SERVER:
		case AUTH_SERVER_TYPE_S8_GAME_SERVER:
			return 3;
		case AUTH_SERVER_TYPE_S4_CONNECT_SERVER:
		case AUTH_SERVER_TYPE_S4_JOIN_SERVER:
		case AUTH_SERVER_TYPE_S4_DATA_SERVER:
		case AUTH_SERVER_TYPE_S4_GAME_SERVER:
			return 1;
		case AUTH_SERVER_TYPE_S2_CONNECT_SERVER:
		case AUTH_SERVER_TYPE_S2_JOIN_SERVER:
		case AUTH_SERVER_TYPE_S2_DATA_SERVER:
		case AUTH_SERVER_TYPE_S2_GAME_SERVER:
			return 0;
	}

	return -1;
}
