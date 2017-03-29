// Protect.h: interface for the CProtect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Message.h"

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

class CProtect
{
public:
	CProtect();
	virtual ~CProtect();
	bool ReadMainFile(char* name);
	void CheckClientFile();
	void CheckPluginFile();
	void CheckVerifyFile();
public:
	MAIN_FILE_INFO m_MainInfo;
	DWORD m_ClientFileCRC;
};

extern CProtect gProtect;
