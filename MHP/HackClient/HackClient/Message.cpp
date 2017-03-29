// Message.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Message.h"

CMessage gMessage;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessage::CMessage() // OK
{
	this->Init();
}

CMessage::~CMessage() // OK
{

}

void CMessage::Init() // OK
{
	memset(this->m_DefaultMessage,0,sizeof(this->m_DefaultMessage));

	for(int n=0;n < MAX_MESSAGE;n++)
	{
		this->m_EngCustomMessageInfo[n].Index = -1;
		this->m_PorCustomMessageInfo[n].Index = -1;
		this->m_SpnCustomMessageInfo[n].Index = -1;
	}
}

void CMessage::GetLanguage() // OK
{
	HKEY key;

	if(RegOpenKeyEx(HKEY_CURRENT_USER,"SOFTWARE\\Webzen\\Mu\\Config",0,KEY_ALL_ACCESS,&key) == ERROR_SUCCESS)
	{
		DWORD type=REG_SZ,size=sizeof(this->m_Language);

		if(RegQueryValueEx(key,"LangSelection",0,&type,(BYTE*)this->m_Language,&size) != ERROR_SUCCESS)
		{
			strcpy_s(this->m_Language,"Eng");
		}

		RegCloseKey(key);
	}
}

void CMessage::LoadEng(MESSAGE_INFO* info) // OK
{
	for(int n=0;n < MAX_MESSAGE;n++)
	{
		this->SetInfoEng(info[n]);
	}
}

void CMessage::LoadPor(MESSAGE_INFO* info) // OK
{
	for(int n=0;n < MAX_MESSAGE;n++)
	{
		this->SetInfoPor(info[n]);
	}
}

void CMessage::LoadSpn(MESSAGE_INFO* info) // OK
{
	for(int n=0;n < MAX_MESSAGE;n++)
	{
		this->SetInfoSpn(info[n]);
	}
}

void CMessage::SetInfoEng(MESSAGE_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_MESSAGE)
	{
		return;
	}

	this->m_EngCustomMessageInfo[info.Index] = info;
}

void CMessage::SetInfoPor(MESSAGE_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_MESSAGE)
	{
		return;
	}

	this->m_PorCustomMessageInfo[info.Index] = info;
}

void CMessage::SetInfoSpn(MESSAGE_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_MESSAGE)
	{
		return;
	}

	this->m_SpnCustomMessageInfo[info.Index] = info;
}

MESSAGE_INFO* CMessage::GetInfoEng(int index) // OK
{
	if(index < 0 || index >= MAX_MESSAGE)
	{
		wsprintf(this->m_DefaultMessage,"Message %d out of bound!",index);
		return 0;
	}

	if(this->m_EngCustomMessageInfo[index].Index != index)
	{
		wsprintf(this->m_DefaultMessage,"Could not find message %d!",index);
		return 0;
	}

	return &this->m_EngCustomMessageInfo[index];
}

MESSAGE_INFO* CMessage::GetInfoPor(int index) // OK
{
	if(index < 0 || index >= MAX_MESSAGE)
	{
		wsprintf(this->m_DefaultMessage,"Message %d out of bound!",index);
		return 0;
	}

	if(this->m_PorCustomMessageInfo[index].Index != index)
	{
		wsprintf(this->m_DefaultMessage,"Could not find message %d!",index);
		return 0;
	}

	return &this->m_PorCustomMessageInfo[index];
}

MESSAGE_INFO* CMessage::GetInfoSpn(int index) // OK
{
	if(index < 0 || index >= MAX_MESSAGE)
	{
		wsprintf(this->m_DefaultMessage,"Message %d out of bound!",index);
		return 0;
	}

	if(this->m_SpnCustomMessageInfo[index].Index != index)
	{
		wsprintf(this->m_DefaultMessage,"Could not find message %d!",index);
		return 0;
	}

	return &this->m_SpnCustomMessageInfo[index];
}

char* CMessage::GetMessage(int index) // OK
{
	if(strcmp(this->m_Language,"Eng") == 0)
	{
		MESSAGE_INFO* lpInfo = this->GetInfoEng(index);
		if(lpInfo==0){return this->m_DefaultMessage;}
		return lpInfo->Message;
	}

	if(strcmp(this->m_Language,"Por") == 0)
	{
		MESSAGE_INFO* lpInfo = this->GetInfoPor(index);
		if(lpInfo==0){return this->m_DefaultMessage;}
		return lpInfo->Message;
	}

	if(strcmp(this->m_Language,"Spn") == 0)
	{
		MESSAGE_INFO* lpInfo = this->GetInfoSpn(index);
		if(lpInfo==0){return this->m_DefaultMessage;}
		return lpInfo->Message;
	}

	MESSAGE_INFO* lpInfo = this->GetInfoPor(index);
	if(lpInfo==0){return this->m_DefaultMessage;}
	return lpInfo->Message;
}
