// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_MESSAGE 50

struct MESSAGE_INFO
{
	int Index;
	char Message[128];
};

class CMessage
{
public:
	CMessage();
	virtual ~CMessage();
	void Init();
	void Load(char* path);
	void SetInfoEng(MESSAGE_INFO info);
	void SetInfoPor(MESSAGE_INFO info);
	void SetInfoSpn(MESSAGE_INFO info);
	MESSAGE_INFO* GetInfoEng(int index);
	MESSAGE_INFO* GetInfoPor(int index);
	MESSAGE_INFO* GetInfoSpn(int index);
public:
	char m_DefaultMessage[128];
	MESSAGE_INFO m_EngMessageInfo[MAX_MESSAGE];
	MESSAGE_INFO m_PorMessageInfo[MAX_MESSAGE];
	MESSAGE_INFO m_SpnMessageInfo[MAX_MESSAGE];
};

extern CMessage gMessage;
