// CustomWingEffect.cpp: implementation of the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomWingEffect.h"
#include "MemScript.h"

CCustomWingEffect gCustomWingEffect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomWingEffect::CCustomWingEffect() // OK
{
	this->Init();
}

CCustomWingEffect::~CCustomWingEffect() // OK
{

}

void CCustomWingEffect::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_WING_EFFECT;n++)
	{
		this->m_CustomWingEffectInfo[n].Index = -1;
	}
}

void CCustomWingEffect::Load(char* path) // OK
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

			CUSTOM_WING_EFFECT_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomWingEffectIndexCount = 0;

			info.Index = CustomWingEffectIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.EffectIndex = lpMemScript->GetAsNumber();

			info.EffectValue = lpMemScript->GetAsNumber();

			info.EffectLevel = lpMemScript->GetAsNumber();

			info.ColorR = lpMemScript->GetAsFloatNumber();

			info.ColorG = lpMemScript->GetAsFloatNumber();

			info.ColorB = lpMemScript->GetAsFloatNumber();

			info.ColorSize = lpMemScript->GetAsFloatNumber();

			info.ColorMain = lpMemScript->GetAsFloatNumber();

			info.ColorSide = lpMemScript->GetAsFloatNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomWingEffect::SetInfo(CUSTOM_WING_EFFECT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_WING_EFFECT)
	{
		return;
	}

	this->m_CustomWingEffectInfo[info.Index] = info;
}
