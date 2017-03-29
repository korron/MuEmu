#include "stdafx.h"
#include "CCRC32.H"
#include "Message.h"
#include "ThemidaSDK.h"

struct MAIN_FILE_INFO
{
	char CustomerName[32];
	char IpAddress[32];
	WORD ServerPort;
	char ServerName[32];
	char ClientName[32];
	char PluginName[32];
	char VerifyName[32];
	DWORD ClientCRC32;
	DWORD PluginCRC32;
	DWORD VerifyCRC32;
	MESSAGE_INFO EngMessageInfo[MAX_MESSAGE];
	MESSAGE_INFO PorMessageInfo[MAX_MESSAGE];
	MESSAGE_INFO SpnMessageInfo[MAX_MESSAGE];
};

int _tmain(int argc,_TCHAR* argv[]) // OK
{
	VM_START

	MAIN_FILE_INFO info;

	memset(&info,0,sizeof(info));

	char TempInfo[100];

	GetPrivateProfileString("ClientInfo","CustomerName","",info.CustomerName,sizeof(info.CustomerName),".\\ClientInfo.ini");

	GetPrivateProfileString("ClientInfo","IpAddress","",info.IpAddress,sizeof(info.IpAddress),".\\ClientInfo.ini");

	info.ServerPort = GetPrivateProfileInt("ClientInfo","ServerPort",0,".\\ClientInfo.ini");

	GetPrivateProfileString("ClientInfo","ServerName","",info.ServerName,sizeof(info.ServerName),".\\ClientInfo.ini");

	GetPrivateProfileString("ClientInfo","ClientName","",info.ClientName,sizeof(info.ClientName),".\\ClientInfo.ini");

	GetPrivateProfileString("ClientInfo","PluginName","",info.PluginName,sizeof(info.PluginName),".\\ClientInfo.ini");

	GetPrivateProfileString("ClientInfo","VerifyName","",info.VerifyName,sizeof(info.VerifyName),".\\ClientInfo.ini");

	gMessage.Load("Message.txt");

	memcpy(info.EngMessageInfo,gMessage.m_EngMessageInfo,sizeof(info.EngMessageInfo));

	memcpy(info.PorMessageInfo,gMessage.m_PorMessageInfo,sizeof(info.PorMessageInfo));

	memcpy(info.SpnMessageInfo,gMessage.m_SpnMessageInfo,sizeof(info.SpnMessageInfo));

	CCRC32 CRC32;

	if(CRC32.FileCRC(info.ClientName,&info.ClientCRC32,1024) == 0)
	{
		info.ClientCRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName,&info.PluginCRC32,1024) == 0)
	{
		info.PluginCRC32 = 0;
	}

	if(CRC32.FileCRC(info.VerifyName,&info.VerifyCRC32,1024) == 0)
	{
		info.VerifyCRC32 = 0;
	}

	for(int n=0;n < sizeof(MAIN_FILE_INFO);n++)
	{
		((BYTE*)&info)[n] ^= 0xB3;
		((BYTE*)&info)[n] -= 0x78;
	}

	HANDLE file = CreateFile("ah.emu",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if(WriteFile(file,&info,sizeof(MAIN_FILE_INFO),&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);

	VM_END

	return 0;
}
