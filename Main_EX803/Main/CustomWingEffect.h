// CustomWingEffect.h: interface for the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_WING_EFFECT 300

struct CUSTOM_WING_EFFECT_INFO
{
	int Index;
	int ItemIndex;
	int EffectIndex;
	int EffectValue;
	int EffectLevel;
	float ColorR;
	float ColorG;
	float ColorB;
	float ColorSize;
	float ColorMain;
	float ColorSide;
};

class CCustomWingEffect
{
public:
	CCustomWingEffect();
	virtual ~CCustomWingEffect();
	void Init();
	void Load(CUSTOM_WING_EFFECT_INFO* info);
	void SetInfo(CUSTOM_WING_EFFECT_INFO info);
	BOOL SetWingEffect(int ItemIndex,DWORD a,DWORD b,DWORD c,DWORD d);
public:
	CUSTOM_WING_EFFECT_INFO m_CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
};

extern CCustomWingEffect gCustomWingEffect;
