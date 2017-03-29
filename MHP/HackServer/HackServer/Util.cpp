#include "stdafx.h"
#include "Util.h"
#include "ClientManager.h"
#include "HackServerProtocol.h"

int gClientCount = 0;

void ErrorMessageBox(char* message,...) // OK
{
	char buff[256];

	memset(buff,0,sizeof(buff));

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	MessageBox(0,buff,"Error",MB_OK | MB_ICONERROR);

	while(true)
	{
		TerminateProcess(GetCurrentProcess(),0);
		CRASH_APPLICATION_MACRO
	}
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

void TimeoutProc() // OK
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

int GetUserCount() // OK
{
	int count = 0;

	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[n].CheckState() != 0)
		{
			count++;
		}
	}

	return count;
}

int GetFreeClientIndex() // OK
{
	int index = -1;
	int count = gClientCount;

	if(SearchFreeClientIndex(&index,0,MAX_CLIENT,10000) != 0)
	{
		return index;
	}

	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[count].CheckState() == 0)
		{
			return count;
		}
		else
		{
			count = (((++count)>=MAX_CLIENT)?0:count);
		}
	}

	return -1;
}

int SearchFreeClientIndex(int* index,int MinIndex,int MaxIndex,DWORD MinTime) // OK
{
	DWORD CurOnlineTime = 0;
	DWORD MaxOnlineTime = 0;

	for(int n=MinIndex;n < MaxIndex;n++)
	{
		if(gClientManager[n].CheckState() == 0 && gClientManager[n].CheckAlloc() != 0)
		{
			if((CurOnlineTime=(GetTickCount()-gClientManager[n].m_OnlineTime)) > MinTime && CurOnlineTime > MaxOnlineTime)
			{
				(*index) = n;
				MaxOnlineTime = CurOnlineTime;
			}
		}
	}

	return (((*index)==-1)?0:1);
}

void PacketDecryptData(BYTE* lpMsg,int size,BYTE key) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]+key)^0xA0;
	}
}

void PacketEncryptData(BYTE* lpMsg,int size,BYTE key) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]^0xA0)-key;
	}
}

void GetHardwareId(char* hid)  //OK
{
	DWORD VolumeSerialNumber;

	if(GetVolumeInformation("C:\\",0,0,&VolumeSerialNumber,0,0,0,0) == 0)
	{
		return;
	}

	UUID uuid;

	UuidCreateSequential(&uuid);

	SYSTEM_INFO SystemInfo;

	GetSystemInfo(&SystemInfo);

	DWORD ComputerHardwareId1 = VolumeSerialNumber ^ 0x12B586FE;

	DWORD ComputerHardwareId2 = *(DWORD*)(&uuid.Data4[2]) ^ 0x5D78A569;

	DWORD ComputerHardwareId3 = ((*(WORD*)(&uuid.Data4[6]) & 0xFFFF) | (SystemInfo.wProcessorArchitecture << 16)) ^ 0xF45BC123;

	DWORD ComputerHardwareId4 = ((SystemInfo.wProcessorLevel & 0xFFFF) | (SystemInfo.wProcessorRevision << 16)) ^ 0xB542D8E1;

	wsprintf(hid,"%08X-%08X-%08X-%08X",ComputerHardwareId1,ComputerHardwareId2,ComputerHardwareId3,ComputerHardwareId4);
}

DWORD GetCurrentVersion()
{
	char Temp[10];
	sprintf_s(Temp,"%s",HACKSERVER_VERSION);
	strcpy_s(Temp,RemoveCharacter(Temp,'.'));
	return atoi(Temp);
}

DWORD ConvertHackVersion(char* version)
{
	char Temp[10];
	sprintf_s(Temp,"%s",version);
	strcpy_s(Temp,RemoveCharacter(Temp,'.'));
	return atoi(Temp);
}

char* RemoveCharacter(char* Input, char Character) //OK
{
	for(DWORD i=0; i<=strlen(Input); i++)
	{
		if(Input[i] == Character)
		{
			for(DWORD n=i; n<=strlen(Input); n++)
			{
				Input[n] = Input[n+1];
			}
		}
	}
	return Input;
}

void AuthenticateError() //OK
{
	MessageBox(0,"Authorization failed.\n\nVisit: muemu.pl","Error",MB_ICONSTOP|MB_OK);

	while(true)
	{
		TerminateProcess(GetCurrentProcess(),0);
		CRASH_APPLICATION_MACRO
	}
}
