// CustomWing.cpp: implementation of the CCustomWing class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomWing.h"
#include "MemScript.h"

CCustomWing gCustomWing;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomWing::CCustomWing() // OK
{
	this->Init();
}

CCustomWing::~CCustomWing() // OK
{

}

void CCustomWing::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		this->m_CustomWingInfo[n].Index = -1;
	}
}

void CCustomWing::Load(char* path) // OK
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

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			CUSTOM_WING_INFO info;

			memset(&info,0,sizeof(info));

			info.Index = lpMemScript->GetNumber();

			info.ItemIndex = lpMemScript->GetAsNumber();

			info.DefenseConstA = lpMemScript->GetAsNumber();

			info.IncDamageConstA = lpMemScript->GetAsNumber();

			info.IncDamageConstB = lpMemScript->GetAsNumber();

			info.DecDamageConstA = lpMemScript->GetAsNumber();

			info.DecDamageConstB = lpMemScript->GetAsNumber();

			info.OptionIndex1 = lpMemScript->GetAsNumber();

			info.OptionValue1 = lpMemScript->GetAsNumber();

			info.OptionIndex2 = lpMemScript->GetAsNumber();

			info.OptionValue2 = lpMemScript->GetAsNumber();

			info.OptionIndex3 = lpMemScript->GetAsNumber();

			info.OptionValue3 = lpMemScript->GetAsNumber();

			info.NewOptionIndex1 = lpMemScript->GetAsNumber();

			info.NewOptionValue1 = lpMemScript->GetAsNumber();

			info.NewOptionIndex2 = lpMemScript->GetAsNumber();

			info.NewOptionValue2 = lpMemScript->GetAsNumber();

			info.NewOptionIndex3 = lpMemScript->GetAsNumber();

			info.NewOptionValue3 = lpMemScript->GetAsNumber();

			info.NewOptionIndex4 = lpMemScript->GetAsNumber();

			info.NewOptionValue4 = lpMemScript->GetAsNumber();

			info.ModelType = lpMemScript->GetAsNumber();

			strcpy_s(info.ModelName,lpMemScript->GetAsString());

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomWing::SetInfo(CUSTOM_WING_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_WING)
	{
		return;
	}

	this->ConvertOptionIndex(&info.OptionIndex1);

	this->ConvertOptionIndex(&info.OptionIndex2);

	this->ConvertOptionIndex(&info.OptionIndex3);

	this->ConvertOptionIndex(&info.NewOptionIndex1);

	this->ConvertOptionIndex(&info.NewOptionIndex2);

	this->ConvertOptionIndex(&info.NewOptionIndex3);

	this->ConvertOptionIndex(&info.NewOptionIndex4);

	this->m_CustomWingInfo[info.Index] = info;
}

void CCustomWing::ConvertOptionIndex(int* OptionIndex) // OK
{
	switch((*OptionIndex))
	{
		case 80:
			(*OptionIndex) = 80;
			break;
		case 81:
			(*OptionIndex) = 81;
			break;
		case 82:
			(*OptionIndex) = 83;
			break;
		case 83:
			(*OptionIndex) = 84;
			break;
		case 84:
			(*OptionIndex) = 85;
			break;
		case 85:
			(*OptionIndex) = 86;
			break;
		case 108:
			(*OptionIndex) = 103;
			break;
		case 109:
			(*OptionIndex) = 106;
			break;
		case 110:
			(*OptionIndex) = 107;
			break;
		case 111:
			(*OptionIndex) = 108;
			break;
		case 113:
			(*OptionIndex) = 82;
			break;
	}
}
