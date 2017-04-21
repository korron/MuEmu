// CustomWingEffect.cpp: implementation of the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomWing.h"
#include "DynamicEffect.h"

CDynamicWingEffect gDynamicWingEffect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynamicWingEffect::CDynamicWingEffect() // OK
{
	this->Init();
}

CDynamicWingEffect::~CDynamicWingEffect() // OK
{

}

void CDynamicWingEffect::Init() // OK
{
	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		this->m_DynamicWingEffectInfo[n].Index = -1;
	}
}

void CDynamicWingEffect::Load(DYNAMIC_WING_EFFECT_INFO* info) // OK
{
	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CDynamicWingEffect::SetInfo(DYNAMIC_WING_EFFECT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_DYNAMIC_WING_EFFECT)
	{
		return;
	}

	this->m_DynamicWingEffectInfo[info.Index] = info;
}

BOOL CDynamicWingEffect::DynamicWingEffect(int ItemIndex,DWORD a,DWORD b,DWORD c) // OK
{

	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		if(this->m_DynamicWingEffectInfo[n].ItemIndex == ItemIndex)
		{
			float ItemColor[3];

			ItemColor[0] = this->m_DynamicWingEffectInfo[n].ColorR;

			ItemColor[1] = this->m_DynamicWingEffectInfo[n].ColorG;

			ItemColor[2] = this->m_DynamicWingEffectInfo[n].ColorB;

			((void(__thiscall*)(void*,DWORD,DWORD,DWORD,DWORD))0x00544E60)((void*)a,b,c,this->m_DynamicWingEffectInfo[n].EffectValue,this->m_DynamicWingEffectInfo[n].EffectLevel);
			((void(*)(DWORD,DWORD,DWORD,float*,DWORD,float,DWORD))0x0074CD30)(this->m_DynamicWingEffectInfo[n].EffectIndex,b,c,ItemColor,this->m_DynamicWingEffectInfo[n].Effect1,this->m_DynamicWingEffectInfo[n].Effect,this->m_DynamicWingEffectInfo[n].Effect2);
		}
	}
	return 0;
}
