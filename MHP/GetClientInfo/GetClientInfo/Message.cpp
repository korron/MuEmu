// Message.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Message.h"
#include "MemScript.h"

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
		this->m_EngMessageInfo[n].Index = -1;
		this->m_PorMessageInfo[n].Index = -1;
		this->m_SpnMessageInfo[n].Index = -1;
	}
}

void CMessage::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}
		
			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					MESSAGE_INFO info;

					memset(&info,0,sizeof(info));

					info.Index = lpMemScript->GetNumber();

					strcpy_s(info.Message,lpMemScript->GetAsString());

					this->SetInfoEng(info);
				}
				else if(section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					MESSAGE_INFO info;

					memset(&info,0,sizeof(info));

					info.Index = lpMemScript->GetNumber();

					strcpy_s(info.Message,lpMemScript->GetAsString());

					this->SetInfoPor(info);
				}
				else if(section == 2)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					MESSAGE_INFO info;

					memset(&info,0,sizeof(info));

					info.Index = lpMemScript->GetNumber();

					strcpy_s(info.Message,lpMemScript->GetAsString());

					this->SetInfoSpn(info);
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CMessage::SetInfoEng(MESSAGE_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_MESSAGE)
	{
		return;
	}

	this->m_EngMessageInfo[info.Index] = info;
}

void CMessage::SetInfoPor(MESSAGE_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_MESSAGE)
	{
		return;
	}

	this->m_PorMessageInfo[info.Index] = info;
}

void CMessage::SetInfoSpn(MESSAGE_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_MESSAGE)
	{
		return;
	}

	this->m_SpnMessageInfo[info.Index] = info;
}

MESSAGE_INFO* CMessage::GetInfoEng(int index) // OK
{
	if(index < 0 || index >= MAX_MESSAGE)
	{
		wsprintf(this->m_DefaultMessage,"Message %d out of bound!",index);
		return 0;
	}

	if(this->m_EngMessageInfo[index].Index != index)
	{
		wsprintf(this->m_DefaultMessage,"Could not find message %d!",index);
		return 0;
	}

	return &this->m_EngMessageInfo[index];
}

MESSAGE_INFO* CMessage::GetInfoPor(int index) // OK
{
	if(index < 0 || index >= MAX_MESSAGE)
	{
		wsprintf(this->m_DefaultMessage,"Message %d out of bound!",index);
		return 0;
	}

	if(this->m_PorMessageInfo[index].Index != index)
	{
		wsprintf(this->m_DefaultMessage,"Could not find message %d!",index);
		return 0;
	}

	return &this->m_PorMessageInfo[index];
}

MESSAGE_INFO* CMessage::GetInfoSpn(int index) // OK
{
	if(index < 0 || index >= MAX_MESSAGE)
	{
		wsprintf(this->m_DefaultMessage,"Message %d out of bound!",index);
		return 0;
	}

	if(this->m_SpnMessageInfo[index].Index != index)
	{
		wsprintf(this->m_DefaultMessage,"Could not find message %d!",index);
		return 0;
	}

	return &this->m_SpnMessageInfo[index];
}
