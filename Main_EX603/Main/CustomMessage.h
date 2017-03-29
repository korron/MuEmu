// CustomMessage.h: interface for the CCustomMessage class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_MESSAGE 50

struct CUSTOM_MESSAGE_INFO
{
	int Index;
	char Message[128];
};

class CCustomMessage
{
public:
	CCustomMessage();
	virtual ~CCustomMessage();
	void Init();
	void LoadEng(CUSTOM_MESSAGE_INFO* info);
	void LoadPor(CUSTOM_MESSAGE_INFO* info);
	void LoadSpn(CUSTOM_MESSAGE_INFO* info);
	void SetInfoEng(CUSTOM_MESSAGE_INFO info);
	void SetInfoPor(CUSTOM_MESSAGE_INFO info);
	void SetInfoSpn(CUSTOM_MESSAGE_INFO info);
	CUSTOM_MESSAGE_INFO* GetInfoEng(int index);
	CUSTOM_MESSAGE_INFO* GetInfoPor(int index);
	CUSTOM_MESSAGE_INFO* GetInfoSpn(int index);
	char* GetMessage(int index);
public:
	char m_DefaultMessage[128];
	CUSTOM_MESSAGE_INFO m_EngCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO m_PorCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO m_SpnCustomMessageInfo[MAX_CUSTOM_MESSAGE];
};

extern CCustomMessage gCustomMessage;
