// CustomAttack.h: interface for the CCustomAttack class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"

class CCustomAttack
{
public:
	CCustomAttack();
	virtual ~CCustomAttack();
	void ReadCustomAttackInfo(char* section,char* path);
	void CommandCustomAttack(LPOBJ lpObj,char* arg);
	void CommandCustomAttackOffline(LPOBJ lpObj,char* arg);
	bool GetAttackSkill(LPOBJ lpObj,int* SkillNumber);
	bool GetTargetMonster(LPOBJ lpObj,int SkillNumber,int* MonsterIndex);
	bool CheckRequireMoney(LPOBJ lpObj);
	void OnAttackClose(LPOBJ lpObj);
	void OnAttackSecondProc(LPOBJ lpObj);
	void OnAttackAlreadyConnected(LPOBJ lpObj);
	void OnAttackMonsterAndMsgProc(LPOBJ lpObj);
	void SendSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber);
	void SendMultiSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber);
	void SendDurationSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber);
public:
	int m_CustomAttackSwitch;
	int m_CustomAttackEnable[4];
	int m_CustomAttackRequireLevel[4];
	int m_CustomAttackRequireReset[4];
	char m_CustomAttackCommandSyntax[32];
	char m_CustomAttackText1[128];
	char m_CustomAttackText2[128];
	char m_CustomAttackText3[128];
	char m_CustomAttackText4[128];
	char m_CustomAttackText5[128];
	char m_CustomAttackText6[128];
	int m_CustomAttackOfflineSwitch;
	int m_CustomAttackOfflineGPGain;
	int m_CustomAttackOfflineEnable[4];
	int m_CustomAttackOfflineRequireLevel[4];
	int m_CustomAttackOfflineRequireReset[4];
	int m_CustomAttackOfflineRequireMoney[4];
	char m_CustomAttackOfflineCommandSyntax[32];
	char m_CustomAttackOfflineText1[128];
	char m_CustomAttackOfflineText2[128];
	char m_CustomAttackOfflineText3[128];
	char m_CustomAttackOfflineText4[128];
	char m_CustomAttackOfflineText5[128];
	char m_CustomAttackOfflineText6[128];
};

extern CCustomAttack gCustomAttack;
