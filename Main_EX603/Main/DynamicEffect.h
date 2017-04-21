// CustomWingEffect.h: interface for the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_DYNAMIC_WING_EFFECT 300

struct DYNAMIC_WING_EFFECT_INFO
{
	int Index;
	int ItemIndex;
	int EffectIndex;
	int EffectValue;
	int EffectLevel;
	float ColorR;
	float ColorG;
	float ColorB;
	float Effect1;
	float Effect2;
	float Effect;
};

class CDynamicWingEffect
{
public:
	CDynamicWingEffect();
	virtual ~CDynamicWingEffect();
	void Init();
	void Load(DYNAMIC_WING_EFFECT_INFO* info);
	void SetInfo(DYNAMIC_WING_EFFECT_INFO info);
	BOOL DynamicWingEffect(int ItemIndex,DWORD a,DWORD b,DWORD c);
public:
	DYNAMIC_WING_EFFECT_INFO m_DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
};

extern CDynamicWingEffect gDynamicWingEffect;
