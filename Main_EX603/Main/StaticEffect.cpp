// CustomWingEffect.cpp: implementation of the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StaticEffect.h"
#include "CustomWing.h"

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

void CCustomWingEffect::Load(CUSTOM_WING_EFFECT_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_WING_EFFECT;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomWingEffect::SetInfo(CUSTOM_WING_EFFECT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_WING_EFFECT)
	{
		return;
	}

	this->m_CustomWingEffectInfo[info.Index] = info;
}

BOOL CCustomWingEffect::SetWingEffect(int ItemIndex,DWORD a,DWORD b,DWORD c,DWORD d) // OK
{
	for(int n=0;n < MAX_CUSTOM_WING_EFFECT;n++)
	{
		if(this->m_CustomWingEffectInfo[n].ItemIndex == ItemIndex)
		{
			float ItemColor[3];

			ItemColor[0] = this->m_CustomWingEffectInfo[n].ColorR;

			ItemColor[1] = this->m_CustomWingEffectInfo[n].ColorG;

			ItemColor[2] = this->m_CustomWingEffectInfo[n].ColorB;

			((void(__thiscall*)(void*,DWORD,DWORD,DWORD,DWORD))0x00544E60)((void*)a,b,c,this->m_CustomWingEffectInfo[n].EffectValue,this->m_CustomWingEffectInfo[n].EffectLevel);

			((void(*)(DWORD,DWORD,float,float*,DWORD,float,DWORD))0x00771310)(this->m_CustomWingEffectInfo[n].EffectIndex,b,this->m_CustomWingEffectInfo[n].ColorSize,ItemColor,d,this->m_CustomWingEffectInfo[n].ColorMain,(DWORD)this->m_CustomWingEffectInfo[n].ColorSide);
		}
	}

	return 0;
}
