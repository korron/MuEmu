// ServerInfo.h: interface for the CServerInfo class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CServerInfo
{
public:
	CServerInfo();
	virtual ~CServerInfo();
	void ReadInit();
	void ReadConfig();
	void ReadDumpList();
	void ReadChecksumList();
	void ReadInternalList();
	void ReadWindowList();
	void ReadBlackList();
	void ReadStartupInfo(char* section,char* path);
	void ReadConfig(char* section,char* path);
public:
	char m_CustomerName[32];
	char m_CustomerHardwareId[36];
	char m_ClientVersion[8];
	char m_ClientSerial[17];
	int m_HackServerPort;
	int m_MaxIpConnection;
	int m_DetectionLockTime;
	int m_EncDecKey1;
	int m_EncDecKey2;
	int m_EncDecSetNumber;
	int m_InternalVersion;
	int m_ReconnectSwitch;
	int m_MemoryGuardSwitch;
	int m_MemoryGuardNumber;
	int m_MacroProtectSwitch;
	int m_MacroProtectNumber;
	DWORD m_ClientFileCRC;
	DWORD m_MemoryAddress1;
	DWORD m_MemoryAddress2;
	DWORD m_MemoryAddress3;
	DWORD m_MemoryAddress4;
	DWORD m_MemoryAddress5;
	DWORD m_MemoryAddress6;
	DWORD m_MemoryAddress7;
	DWORD m_MemoryAddress8;
};

extern CServerInfo gServerInfo;
