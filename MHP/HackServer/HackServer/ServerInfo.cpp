// ServerInfo.cpp: implementation of the CServerInfo class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ServerInfo.h"
#include "CCRC32.H"
#include "ReadFiles.h"
#include "BlackList.h"
#include "Util.h"

CServerInfo gServerInfo;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerInfo::CServerInfo() // OK
{

}

CServerInfo::~CServerInfo() // OK
{

}

void CServerInfo::ReadInit() // OK
{
	CCRC32 CRC32;

	this->ReadConfig();

	this->ReadDumpList();

	this->ReadChecksumList();

	this->ReadInternalList();

	this->ReadWindowList();

	this->ReadBlackList();

	if(CRC32.FileCRC(".\\Data\\info.xtm",&this->m_ClientFileCRC,1024) == 0)
	{
		this->m_ClientFileCRC = 0;
	}
}

void CServerInfo::ReadConfig() // OK
{
	this->ReadConfig("MHPServerInfo",".\\MHPServer.ini");

	LogAdd(LOG_BLUE,"[ServerInfo] Config loaded successfully");
}

void CServerInfo::ReadDumpList() // OK
{
	gReadFiles.DumpList(".\\Data\\Dump.List.db");

	LogAdd(LOG_BLUE,"[ServerInfo] DumpList loaded successfully");
}

void CServerInfo::ReadChecksumList() // OK
{
	gReadFiles.ChecksumList(".\\Data\\Checksum.List.db");

	LogAdd(LOG_BLUE,"[ServerInfo] ChecksumList loaded successfully");
}

void CServerInfo::ReadInternalList() // OK
{
	gReadFiles.InternalList(".\\Data\\Internal.List.db");

	LogAdd(LOG_BLUE,"[ServerInfo] InternalList loaded successfully");
}

void CServerInfo::ReadWindowList() // OK
{
	gReadFiles.WindowList(".\\Data\\Window.List.db");

	LogAdd(LOG_BLUE,"[ServerInfo] WindowList loaded successfully");
}

void CServerInfo::ReadBlackList() //OK
{
	gBlackList.SetList(".\\BlackList.txt");

	LogAdd(LOG_BLUE,"[ServerInfo] BlackList loaded successfully");
}

void CServerInfo::ReadStartupInfo(char* section,char* path) // OK
{
	char HackServerInfo[100] = {0};

	GetPrivateProfileString(section,"CustomerName","",this->m_CustomerName,sizeof(this->m_CustomerName),path);

	GetPrivateProfileString(section,"CustomerHardwareId","",this->m_CustomerHardwareId,sizeof(this->m_CustomerHardwareId),path);

	this->m_HackServerPort = GetPrivateProfileInt(section,"MHPServerPort",0,path);

	this->m_MaxIpConnection = GetPrivateProfileInt(section,"MaxIpConnection",0,path);

	this->m_EncDecKey1 = GetPrivateProfileInt(section,"EncDecKey1",0,path);

	this->m_EncDecKey2 = GetPrivateProfileInt(section,"EncDecKey2",0,path);

	this->m_EncDecSetNumber = GetPrivateProfileInt(section,"EncDecSetNumber",0,path);
}

void CServerInfo::ReadConfig(char* section,char* path) // OK
{
	char HackServerInfo[100] = {0};

	GetPrivateProfileString(section,"ClientVersion","",this->m_ClientVersion,sizeof(this->m_ClientVersion),path);

	GetPrivateProfileString(section,"ClientSerial","",this->m_ClientSerial,sizeof(this->m_ClientSerial),path);

	this->m_DetectionLockTime = GetPrivateProfileInt(section,"DetectionLockTime",0,path);

	this->m_InternalVersion = GetPrivateProfileInt(section,"InternalVersion",0,path);

	this->m_ReconnectSwitch = GetPrivateProfileInt(section,"ReconnectSwitch",0,path);

	this->m_MemoryGuardSwitch = GetPrivateProfileInt(section,"MemoryGuardSwitch",0,path);

	this->m_MemoryGuardNumber = GetPrivateProfileInt(section,"MemoryGuardNumber",0,path);

	this->m_MacroProtectSwitch = GetPrivateProfileInt(section,"MacroProtectSwitch",0,path);

	this->m_MacroProtectNumber = GetPrivateProfileInt(section,"MacroProtectNumber",0,path);

	GetPrivateProfileString(section,"MemoryAddress1","",HackServerInfo,sizeof(HackServerInfo),path);

	this->m_MemoryAddress1 = (((this->m_MemoryAddress1=strtoul(HackServerInfo,NULL,0))>0x10000000)?(this->m_MemoryAddress1^0xC47A0E9F):this->m_MemoryAddress1);

	GetPrivateProfileString(section,"MemoryAddress2","",HackServerInfo,sizeof(HackServerInfo),path);

	this->m_MemoryAddress2 = (((this->m_MemoryAddress2=strtoul(HackServerInfo,NULL,0))>0x10000000)?(this->m_MemoryAddress2^0xC47A0E9F):this->m_MemoryAddress2);

	GetPrivateProfileString(section,"MemoryAddress3","",HackServerInfo,sizeof(HackServerInfo),path);

	this->m_MemoryAddress3 = (((this->m_MemoryAddress3=strtoul(HackServerInfo,NULL,0))>0x10000000)?(this->m_MemoryAddress3^0xC47A0E9F):this->m_MemoryAddress3);

	GetPrivateProfileString(section,"MemoryAddress4","",HackServerInfo,sizeof(HackServerInfo),path);

	this->m_MemoryAddress4 = (((this->m_MemoryAddress4=strtoul(HackServerInfo,NULL,0))>0x10000000)?(this->m_MemoryAddress4^0xC47A0E9F):this->m_MemoryAddress4);

	GetPrivateProfileString(section,"MemoryAddress5","",HackServerInfo,sizeof(HackServerInfo),path);

	this->m_MemoryAddress5 = (((this->m_MemoryAddress5=strtoul(HackServerInfo,NULL,0))>0x10000000)?(this->m_MemoryAddress5^0xC47A0E9F):this->m_MemoryAddress5);

	GetPrivateProfileString(section,"MemoryAddress6","",HackServerInfo,sizeof(HackServerInfo),path);

	this->m_MemoryAddress6 = (((this->m_MemoryAddress6=strtoul(HackServerInfo,NULL,0))>0x10000000)?(this->m_MemoryAddress6^0xC47A0E9F):this->m_MemoryAddress6);

	GetPrivateProfileString(section,"MemoryAddress7","",HackServerInfo,sizeof(HackServerInfo),path);

	this->m_MemoryAddress7 = (((this->m_MemoryAddress7=strtoul(HackServerInfo,NULL,0))>0x10000000)?(this->m_MemoryAddress7^0xC47A0E9F):this->m_MemoryAddress7);

	GetPrivateProfileString(section,"MemoryAddress8","",HackServerInfo,sizeof(HackServerInfo),path);

	this->m_MemoryAddress8 = (((this->m_MemoryAddress8=strtoul(HackServerInfo,NULL,0))>0x10000000)?(this->m_MemoryAddress8^0xC47A0E9F):this->m_MemoryAddress8);
}
