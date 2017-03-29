// CustomAttack.cpp: implementation of the CCustomAttack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomAttack.h"
#include "ItemManager.h"
#include "Map.h"
#include "MasterSkillTree.h"
#include "Notice.h"
#include "SkillManager.h"
#include "SocketManager.h"
#include "Viewport.h"

CCustomAttack gCustomAttack;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomAttack::CCustomAttack() // OK
{

}

CCustomAttack::~CCustomAttack() // OK
{

}

void CCustomAttack::ReadCustomAttackInfo(char* section,char* path) // OK
{
	this->m_CustomAttackSwitch = GetPrivateProfileInt(section,"CustomAttackSwitch",0,path);

	this->m_CustomAttackEnable[0] = GetPrivateProfileInt(section,"CustomAttackEnable_AL0",0,path);

	this->m_CustomAttackEnable[1] = GetPrivateProfileInt(section,"CustomAttackEnable_AL1",0,path);

	this->m_CustomAttackEnable[2] = GetPrivateProfileInt(section,"CustomAttackEnable_AL2",0,path);

	this->m_CustomAttackEnable[3] = GetPrivateProfileInt(section,"CustomAttackEnable_AL3",0,path);

	this->m_CustomAttackRequireLevel[0] = GetPrivateProfileInt(section,"CustomAttackRequireLevel_AL0",0,path);

	this->m_CustomAttackRequireLevel[1] = GetPrivateProfileInt(section,"CustomAttackRequireLevel_AL1",0,path);

	this->m_CustomAttackRequireLevel[2] = GetPrivateProfileInt(section,"CustomAttackRequireLevel_AL2",0,path);

	this->m_CustomAttackRequireLevel[3] = GetPrivateProfileInt(section,"CustomAttackRequireLevel_AL3",0,path);

	this->m_CustomAttackRequireReset[0] = GetPrivateProfileInt(section,"CustomAttackRequireReset_AL0",0,path);

	this->m_CustomAttackRequireReset[1] = GetPrivateProfileInt(section,"CustomAttackRequireReset_AL1",0,path);

	this->m_CustomAttackRequireReset[2] = GetPrivateProfileInt(section,"CustomAttackRequireReset_AL2",0,path);

	this->m_CustomAttackRequireReset[3] = GetPrivateProfileInt(section,"CustomAttackRequireReset_AL3",0,path);

	GetPrivateProfileString(section,"CustomAttackCommandSyntax","",this->m_CustomAttackCommandSyntax,sizeof(this->m_CustomAttackCommandSyntax),path);

	GetPrivateProfileString(section,"CustomAttackText1","",this->m_CustomAttackText1,sizeof(this->m_CustomAttackText1),path);

	GetPrivateProfileString(section,"CustomAttackText2","",this->m_CustomAttackText2,sizeof(this->m_CustomAttackText2),path);

	GetPrivateProfileString(section,"CustomAttackText3","",this->m_CustomAttackText3,sizeof(this->m_CustomAttackText3),path);

	GetPrivateProfileString(section,"CustomAttackText4","",this->m_CustomAttackText4,sizeof(this->m_CustomAttackText4),path);

	GetPrivateProfileString(section,"CustomAttackText5","",this->m_CustomAttackText5,sizeof(this->m_CustomAttackText5),path);

	GetPrivateProfileString(section,"CustomAttackText6","",this->m_CustomAttackText6,sizeof(this->m_CustomAttackText6),path);

	this->m_CustomAttackOfflineSwitch = GetPrivateProfileInt(section,"CustomAttackOfflineSwitch",0,path);

	this->m_CustomAttackOfflineGPGain = GetPrivateProfileInt(section,"CustomAttackOfflineGPGain",0,path);

	this->m_CustomAttackOfflineEnable[0] = GetPrivateProfileInt(section,"CustomAttackOfflineEnable_AL0",0,path);

	this->m_CustomAttackOfflineEnable[1] = GetPrivateProfileInt(section,"CustomAttackOfflineEnable_AL1",0,path);

	this->m_CustomAttackOfflineEnable[2] = GetPrivateProfileInt(section,"CustomAttackOfflineEnable_AL2",0,path);

	this->m_CustomAttackOfflineEnable[3] = GetPrivateProfileInt(section,"CustomAttackOfflineEnable_AL3",0,path);

	this->m_CustomAttackOfflineRequireLevel[0] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireLevel_AL0",0,path);

	this->m_CustomAttackOfflineRequireLevel[1] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireLevel_AL1",0,path);

	this->m_CustomAttackOfflineRequireLevel[2] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireLevel_AL2",0,path);

	this->m_CustomAttackOfflineRequireLevel[3] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireLevel_AL3",0,path);

	this->m_CustomAttackOfflineRequireReset[0] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireReset_AL0",0,path);

	this->m_CustomAttackOfflineRequireReset[1] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireReset_AL1",0,path);

	this->m_CustomAttackOfflineRequireReset[2] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireReset_AL2",0,path);

	this->m_CustomAttackOfflineRequireReset[3] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireReset_AL3",0,path);

	this->m_CustomAttackOfflineRequireMoney[0] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireMoney_AL0",0,path);

	this->m_CustomAttackOfflineRequireMoney[1] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireMoney_AL1",0,path);

	this->m_CustomAttackOfflineRequireMoney[2] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireMoney_AL2",0,path);

	this->m_CustomAttackOfflineRequireMoney[3] = GetPrivateProfileInt(section,"CustomAttackOfflineRequireMoney_AL3",0,path);

	GetPrivateProfileString(section,"CustomAttackOfflineCommandSyntax","",this->m_CustomAttackOfflineCommandSyntax,sizeof(this->m_CustomAttackOfflineCommandSyntax),path);

	GetPrivateProfileString(section,"CustomAttackOfflineText1","",this->m_CustomAttackOfflineText1,sizeof(this->m_CustomAttackOfflineText1),path);

	GetPrivateProfileString(section,"CustomAttackOfflineText2","",this->m_CustomAttackOfflineText2,sizeof(this->m_CustomAttackOfflineText2),path);

	GetPrivateProfileString(section,"CustomAttackOfflineText3","",this->m_CustomAttackOfflineText3,sizeof(this->m_CustomAttackOfflineText3),path);

	GetPrivateProfileString(section,"CustomAttackOfflineText4","",this->m_CustomAttackOfflineText4,sizeof(this->m_CustomAttackOfflineText4),path);

	GetPrivateProfileString(section,"CustomAttackOfflineText5","",this->m_CustomAttackOfflineText5,sizeof(this->m_CustomAttackOfflineText5),path);

	GetPrivateProfileString(section,"CustomAttackOfflineText6","",this->m_CustomAttackOfflineText6,sizeof(this->m_CustomAttackOfflineText6),path);
}

void CCustomAttack::CommandCustomAttack(LPOBJ lpObj,char* arg) // OK
{
	if(this->m_CustomAttackSwitch == 0)
	{
		return;
	}

	if(this->m_CustomAttackEnable[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackText1);
		return;
	}

	if(((gMasterSkillTree.CheckMasterLevel(lpObj)==0)?lpObj->Level:(lpObj->Level+lpObj->MasterLevel)) < this->m_CustomAttackRequireLevel[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackText2,this->m_CustomAttackRequireLevel[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->Reset < this->m_CustomAttackRequireReset[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackText3,this->m_CustomAttackRequireReset[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->AttackCustom != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackText4);
		return;
	}

	if(gMap[lpObj->Map].CheckAttr(lpObj->X,lpObj->Y,1) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackText5);
		return;
	}

	if(CA_MAP_RANGE(lpObj->Map) != 0 || DS_MAP_RANGE(lpObj->Map) != 0 || BC_MAP_RANGE(lpObj->Map) != 0 || CC_MAP_RANGE(lpObj->Map) != 0 || IT_MAP_RANGE(lpObj->Map) != 0 || DA_MAP_RANGE(lpObj->Map) != 0 || DG_MAP_RANGE(lpObj->Map) != 0 || IG_MAP_RANGE(lpObj->Map) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackText5);
		return;
	}

	int SkillNumber = SKILL_NONE;

	if(this->GetAttackSkill(lpObj,&SkillNumber) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackText6);
		return;
	}

	lpObj->AttackCustom = 1;

	lpObj->AttackCustomSkill = SkillNumber;

	lpObj->AttackCustomDelay = GetTickCount();

	lpObj->AttackCustomZoneX = lpObj->X;

	lpObj->AttackCustomZoneY = lpObj->Y;

	lpObj->AttackCustomZoneMap = lpObj->Map;

	lpObj->AttackCustomOffline = 0;

	lpObj->AttackCustomOfflineTime = 0;

	lpObj->AttackCustomOfflineMoneyDelay = 0;
}

void CCustomAttack::CommandCustomAttackOffline(LPOBJ lpObj,char* arg) // OK
{
	if(this->m_CustomAttackOfflineSwitch == 0)
	{
		return;
	}

	if(this->m_CustomAttackOfflineEnable[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackOfflineText1);
		return;
	}

	if(((gMasterSkillTree.CheckMasterLevel(lpObj)==0)?lpObj->Level:(lpObj->Level+lpObj->MasterLevel)) < this->m_CustomAttackOfflineRequireLevel[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackOfflineText2,this->m_CustomAttackOfflineRequireLevel[lpObj->AccountLevel]);
		return;
	}

	if(((int)lpObj->Reset) < this->m_CustomAttackOfflineRequireReset[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackOfflineText3,this->m_CustomAttackOfflineRequireReset[lpObj->AccountLevel]);
		return;
	}

	if(((int)lpObj->Money) < this->m_CustomAttackOfflineRequireMoney[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackOfflineText4,this->m_CustomAttackOfflineRequireMoney[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->AttackCustom == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackOfflineText5);
		return;
	}

	if(gMap[lpObj->Map].CheckAttr(lpObj->X,lpObj->Y,1) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackOfflineText6);
		return;
	}

	if(CA_MAP_RANGE(lpObj->Map) != 0 || DS_MAP_RANGE(lpObj->Map) != 0 || BC_MAP_RANGE(lpObj->Map) != 0 || CC_MAP_RANGE(lpObj->Map) != 0 || IT_MAP_RANGE(lpObj->Map) != 0 || DA_MAP_RANGE(lpObj->Map) != 0 || DG_MAP_RANGE(lpObj->Map) != 0 || IG_MAP_RANGE(lpObj->Map) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomAttackOfflineText6);
		return;
	}

	lpObj->Socket = INVALID_SOCKET;

	lpObj->AttackCustomOffline = 1;

	lpObj->AttackCustomOfflineTime = 0;

	lpObj->AttackCustomOfflineMoneyDelay = GetTickCount();

	lpObj->Money -= this->m_CustomAttackOfflineRequireMoney[lpObj->AccountLevel];

	closesocket(lpObj->PerSocketContext->Socket);
}

bool CCustomAttack::GetAttackSkill(LPOBJ lpObj,int* SkillNumber) // OK
{
	CSkill* lpSkill = 0;

	switch(lpObj->Class)
	{
		case CLASS_DW:
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_ICE_STORM):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_EVIL_SPIRIT):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_INFERNO):lpSkill);
			break;
		case CLASS_DK:
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_TWISTING_SLASH):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_DEATH_STAB):lpSkill);
			break;
		case CLASS_FE:
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_FIVE_SHOT):lpSkill);
			break;
		case CLASS_MG:
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_SWORD_SLASH):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_LIGHTNING_STORM):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_POWER_SLASH):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_EVIL_SPIRIT):lpSkill);
			break;
		case CLASS_DL:
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_BIRDS):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_FIRE_BURST):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_FORCE):lpSkill);
			break;
		case CLASS_SU:
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_RED_STORM):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_CHAIN_LIGHTNING):lpSkill);
			break;
		case CLASS_RF:
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_DRAGON_LORE):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_PHOENIX_SHOT):lpSkill);
			lpSkill = ((lpSkill==0)?gSkillManager.GetSkill(lpObj,SKILL_LARGE_RING_BLOWER):lpSkill);
			break;
	}

	if(lpSkill == 0)
	{
		return 0;
	}
	else
	{
		(*SkillNumber) = lpSkill->m_index;
		return 1;
	}
}

bool CCustomAttack::GetTargetMonster(LPOBJ lpObj,int SkillNumber,int* MonsterIndex) // OK
{
	int NearestDistance = 100;

	for(int n=0;n < MAX_VIEWPORT;n++)
	{
		if(lpObj->VpPlayer2[n].state == VIEWPORT_NONE || OBJECT_RANGE(lpObj->VpPlayer2[n].index) == 0 || lpObj->VpPlayer2[n].type != OBJECT_MONSTER)
		{
			continue;
		}

		if(gSkillManager.CheckSkillTarget(lpObj,lpObj->VpPlayer2[n].index,-1,lpObj->VpPlayer2[n].type) == 0)
		{
			continue;
		}

		if(gObjCalcDistance(lpObj,&gObj[lpObj->VpPlayer2[n].index]) >= NearestDistance)
		{
			continue;
		}

		if(gSkillManager.CheckSkillRange(SkillNumber,lpObj->X,lpObj->Y,gObj[lpObj->VpPlayer2[n].index].X,gObj[lpObj->VpPlayer2[n].index].Y) != 0)
		{
			(*MonsterIndex) = lpObj->VpPlayer2[n].index;
			NearestDistance = gObjCalcDistance(lpObj,&gObj[lpObj->VpPlayer2[n].index]);
			continue;
		}

		if(gSkillManager.CheckSkillRadio(SkillNumber,lpObj->X,lpObj->Y,gObj[lpObj->VpPlayer2[n].index].X,gObj[lpObj->VpPlayer2[n].index].Y) != 0)
		{
			(*MonsterIndex) = lpObj->VpPlayer2[n].index;
			NearestDistance = gObjCalcDistance(lpObj,&gObj[lpObj->VpPlayer2[n].index]);
			continue;
		}
	}

	return ((NearestDistance==100)?0:1);
}

bool CCustomAttack::CheckRequireMoney(LPOBJ lpObj) // OK
{
	if(lpObj->AttackCustomOffline == 0)
	{
		return 1;
	}

	if((GetTickCount()-((DWORD)lpObj->AttackCustomOfflineMoneyDelay)) < 60000)
	{
		return 1;
	}

	if(((int)lpObj->Money) < this->m_CustomAttackOfflineRequireMoney[lpObj->AccountLevel])
	{
		return 0;
	}

	lpObj->Money -= this->m_CustomAttackOfflineRequireMoney[lpObj->AccountLevel];

	lpObj->AttackCustomOfflineMoneyDelay = GetTickCount();

	return 1;
}

void CCustomAttack::OnAttackClose(LPOBJ lpObj) // OK
{
	if(lpObj->AttackCustom != 0)
	{
		lpObj->AttackCustom = 0;
		lpObj->AttackCustomSkill = 0;
		lpObj->AttackCustomDelay = 0;
		lpObj->AttackCustomZoneX = 0;
		lpObj->AttackCustomZoneY = 0;
		lpObj->AttackCustomZoneMap = 0;
	}

	if(lpObj->AttackCustomOffline == 1)
	{
		lpObj->AttackCustomOffline = 2;
		lpObj->AttackCustomOfflineTime = 5;
	}
}

void CCustomAttack::OnAttackSecondProc(LPOBJ lpObj) // OK
{
	if(lpObj->AttackCustomOffline != 0)
	{
		if(lpObj->AttackCustomOffline == 2)
		{
			if((--lpObj->AttackCustomOfflineTime) == 0)
			{
				gObjDel(lpObj->Index);
				lpObj->AttackCustomOffline = 0;
				lpObj->AttackCustomOfflineTime = 0;
				lpObj->AttackCustomOfflineMoneyDelay = 0;
			}
		}

		lpObj->CheckSumTime = GetTickCount();
		lpObj->ConnectTickCount = GetTickCount();
		lpObj->PcPointPointTime = ((this->m_CustomAttackOfflineGPGain==0)?GetTickCount():lpObj->PcPointPointTime);
		lpObj->CashShopGoblinPointTime = ((this->m_CustomAttackOfflineGPGain==0)?GetTickCount():lpObj->CashShopGoblinPointTime);
	}
}

void CCustomAttack::OnAttackAlreadyConnected(LPOBJ lpObj) // OK
{
	if(lpObj->AttackCustomOffline != 0)
	{
		gObjDel(lpObj->Index);
		lpObj->AttackCustomOffline = 0;
		lpObj->AttackCustomOfflineTime = 0;
		lpObj->AttackCustomOfflineMoneyDelay = 0;
	}
}

void CCustomAttack::OnAttackMonsterAndMsgProc(LPOBJ lpObj) // OK
{
	CSkill* lpSkill;

	if(lpObj->AttackCustom == 0)
	{
		return;
	}

	if(this->CheckRequireMoney(lpObj) == 0)
	{
		this->OnAttackClose(lpObj);
		return;
	}

	if(gMap[lpObj->Map].CheckAttr(lpObj->X,lpObj->Y,1) != 0)
	{
		this->OnAttackClose(lpObj);
		return;
	}

	if((lpSkill=gSkillManager.GetSkill(lpObj,lpObj->AttackCustomSkill)) == 0)
	{
		this->OnAttackClose(lpObj);
		return;
	}

	if(gViewport.CheckViewportObjectPosition(lpObj->Index,lpObj->AttackCustomZoneMap,lpObj->AttackCustomZoneX,lpObj->AttackCustomZoneY,5) == 0)
	{
		this->OnAttackClose(lpObj);
		return;
	}

	if(((lpObj->Life*100)/(lpObj->MaxLife+lpObj->AddLife)) < 50)
	{
		PMSG_ITEM_USE_RECV pMsg;

		pMsg.header.set(0x26,sizeof(pMsg));

		pMsg.SourceSlot = 0xFF;

		pMsg.SourceSlot = ((pMsg.SourceSlot==0xFF)?gItemManager.GetInventoryItemSlot(lpObj,GET_ITEM(14,3),-1):pMsg.SourceSlot);

		pMsg.SourceSlot = ((pMsg.SourceSlot==0xFF)?gItemManager.GetInventoryItemSlot(lpObj,GET_ITEM(14,2),-1):pMsg.SourceSlot);

		pMsg.SourceSlot = ((pMsg.SourceSlot==0xFF)?gItemManager.GetInventoryItemSlot(lpObj,GET_ITEM(14,1),-1):pMsg.SourceSlot);

		pMsg.TargetSlot = 0xFF;

		pMsg.type = 0;

		if(INVENTORY_FULL_RANGE(pMsg.SourceSlot) != 0){gItemManager.CGItemUseRecv(&pMsg,lpObj->Index);}
	}

	if(((lpObj->Mana*100)/(lpObj->MaxMana+lpObj->AddMana)) < 50)
	{
		PMSG_ITEM_USE_RECV pMsg;

		pMsg.header.set(0x26,sizeof(pMsg));

		pMsg.SourceSlot = 0xFF;

		pMsg.SourceSlot = ((pMsg.SourceSlot==0xFF)?gItemManager.GetInventoryItemSlot(lpObj,GET_ITEM(14,6),-1):pMsg.SourceSlot);

		pMsg.SourceSlot = ((pMsg.SourceSlot==0xFF)?gItemManager.GetInventoryItemSlot(lpObj,GET_ITEM(14,4),-1):pMsg.SourceSlot);

		pMsg.SourceSlot = ((pMsg.SourceSlot==0xFF)?gItemManager.GetInventoryItemSlot(lpObj,GET_ITEM(14,3),-1):pMsg.SourceSlot);

		pMsg.TargetSlot = 0xFF;

		pMsg.type = 0;

		if(INVENTORY_FULL_RANGE(pMsg.SourceSlot) != 0){gItemManager.CGItemUseRecv(&pMsg,lpObj->Index);}
	}

	if((GetTickCount()-((DWORD)lpObj->AttackCustomDelay)) >= (((((DWORD)lpObj->PhysiSpeed)*5)>1500)?0:(1500-(((DWORD)lpObj->PhysiSpeed)*5))))
	{
		int MonsterIndex = -1;

		lpObj->AttackCustomDelay = GetTickCount();

		if(this->GetTargetMonster(lpObj,lpSkill->m_index,&MonsterIndex) != 0)
		{
			switch(lpSkill->m_skill)
			{
				case SKILL_EVIL_SPIRIT:
					this->SendMultiSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_INFERNO:
					this->SendMultiSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_ICE_STORM:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_TWISTING_SLASH:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_POWER_SLASH:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_FORCE:
					this->SendSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_FIRE_BURST:
					this->SendSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_CHAIN_LIGHTNING:
					this->SendSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_RED_STORM:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_FIVE_SHOT:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_SWORD_SLASH:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_LIGHTNING_STORM:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_BIRDS:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_LARGE_RING_BLOWER:
					this->SendSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_DRAGON_LORE:
					this->SendDurationSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
				case SKILL_PHOENIX_SHOT:
					this->SendSkillAttack(lpObj,MonsterIndex,lpSkill->m_index);
					break;
			}
		}
	}
}

void CCustomAttack::SendSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber) // OK
{
	PMSG_SKILL_ATTACK_RECV pMsg;

	pMsg.header.set(0x19,sizeof(pMsg));

	#if(GAMESERVER_UPDATE>=701)

	pMsg.skillH = SET_NUMBERHB(SkillNumber);

	pMsg.skillL = SET_NUMBERLB(SkillNumber);

	pMsg.indexH = SET_NUMBERHB(aIndex);

	pMsg.indexL = SET_NUMBERLB(aIndex);

	#else

	pMsg.skill[0] = SET_NUMBERHB(SkillNumber);

	pMsg.skill[1] = SET_NUMBERLB(SkillNumber);

	pMsg.index[0] = SET_NUMBERHB(aIndex);

	pMsg.index[1] = SET_NUMBERLB(aIndex);

	#endif

	pMsg.dis = 0;

	gSkillManager.CGSkillAttackRecv(&pMsg,lpObj->Index);
}

void CCustomAttack::SendMultiSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber) // OK
{
	this->SendDurationSkillAttack(lpObj,aIndex,SkillNumber);

	BYTE send[256];

	PMSG_MULTI_SKILL_ATTACK_RECV pMsg;

	pMsg.header.set(PROTOCOL_CODE4,sizeof(pMsg));

	int size = sizeof(pMsg);

	#if(GAMESERVER_UPDATE>=701)

	pMsg.skillH = SET_NUMBERHB(SkillNumber);

	pMsg.skillL = SET_NUMBERLB(SkillNumber);

	#else

	pMsg.skill[0] = SET_NUMBERHB(SkillNumber);

	pMsg.skill[1] = SET_NUMBERLB(SkillNumber);

	#endif

	pMsg.x = (BYTE)lpObj->X;

	pMsg.y = (BYTE)lpObj->Y;

	pMsg.serial = 0;

	pMsg.count = 0;

	PMSG_MULTI_SKILL_ATTACK info;

	for(int n=0;n < MAX_VIEWPORT;n++)
	{
		if(lpObj->VpPlayer2[n].state == VIEWPORT_NONE || OBJECT_RANGE(lpObj->VpPlayer2[n].index) == 0 || lpObj->VpPlayer2[n].type != OBJECT_MONSTER)
		{
			continue;
		}

		int index = lpObj->VpPlayer2[n].index;

		if(gSkillManager.CheckSkillTarget(lpObj,index,aIndex,lpObj->VpPlayer2[n].type) == 0)
		{
			continue;
		}

		if(gSkillManager.CheckSkillRadio(SkillNumber,lpObj->X,lpObj->Y,gObj[index].X,gObj[index].Y) == 0)
		{
			continue;
		}

		#if(GAMESERVER_UPDATE>=701)

		info.indexH = SET_NUMBERHB(index);

		info.indexL = SET_NUMBERLB(index);

		#else

		info.index[0] = SET_NUMBERHB(index);

		info.index[1] = SET_NUMBERLB(index);

		#endif

		info.MagicKey = 0;

		memcpy(&send[size],&info,sizeof(info));
		size += sizeof(info);

		if(CHECK_SKILL_ATTACK_COUNT(pMsg.count) == 0)
		{
			break;
		}
	}

	pMsg.header.size = size;

	memcpy(send,&pMsg,sizeof(pMsg));

	gSkillManager.CGMultiSkillAttackRecv((PMSG_MULTI_SKILL_ATTACK_RECV*)send,lpObj->Index,0);
}

void CCustomAttack::SendDurationSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber) // OK
{
	PMSG_DURATION_SKILL_ATTACK_RECV pMsg;

	pMsg.header.set(0x1E,sizeof(pMsg));

	#if(GAMESERVER_UPDATE>=701)

	pMsg.skillH = SET_NUMBERHB(SkillNumber);

	pMsg.skillL = SET_NUMBERLB(SkillNumber);

	#else

	pMsg.skill[0] = SET_NUMBERHB(SkillNumber);

	pMsg.skill[1] = SET_NUMBERLB(SkillNumber);

	#endif

	pMsg.x = (BYTE)gObj[aIndex].X;

	pMsg.y = (BYTE)gObj[aIndex].Y;

	pMsg.dir = (gSkillManager.GetSkillAngle(gObj[aIndex].X,gObj[aIndex].Y,lpObj->X,lpObj->Y)*255)/360;

	pMsg.dis = 0;

	pMsg.angle = (gSkillManager.GetSkillAngle(lpObj->X,lpObj->Y,gObj[aIndex].X,gObj[aIndex].Y)*255)/360;

	#if(GAMESERVER_UPDATE>=803)

	pMsg.indexH = SET_NUMBERHB(aIndex);

	pMsg.indexL = SET_NUMBERLB(aIndex);

	#else

	pMsg.index[0] = SET_NUMBERHB(aIndex);

	pMsg.index[1] = SET_NUMBERLB(aIndex);

	#endif

	pMsg.MagicKey = 0;

	gSkillManager.CGDurationSkillAttackRecv(&pMsg,lpObj->Index);
}
