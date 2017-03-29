#include "stdafx.h"
#include "Protocol.h"
#include "Common.h"
#include "Offset.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Reconnect.h"
#include "Util.h"

BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg,int size,int key) // OK
{
	switch(head)
	{
		case 0x11:
			GCDamageRecv((PMSG_DAMAGE_RECV*)lpMsg);
			break;
		case 0x16:
			GCMonsterDieRecv((PMSG_MONSTER_DIE_RECV*)lpMsg);
			break;
		case 0x17:
			GCUserDieRecv((PMSG_USER_DIE_RECV*)lpMsg);
			break;
		case 0x26:
			GCLifeRecv((PMSG_LIFE_RECV*)lpMsg);
			break;
		case 0x27:
			GCManaRecv((PMSG_MANA_RECV*)lpMsg);
			break;
		case 0x2C:
			GCFruitResultRecv((PMSG_FRUIT_RESULT_RECV*)lpMsg);
			break;
		case 0x9C:
			GCRewardExperienceRecv((PMSG_REWARD_EXPERIENCE_RECV*)lpMsg);
			break;
		case 0xA3:
			GCQuestRewardRecv((PMSG_QUEST_REWARD_RECV*)lpMsg);
			break;
		case 0xB1:
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
				case 0x00:
					GCMapServerMoveRecv((PMSG_MAP_SERVER_MOVE_RECV*)lpMsg);
					break;
				case 0x01:
					GCMapServerMoveAuthRecv((PMSG_MAP_SERVER_MOVE_AUTH_RECV*)lpMsg);
					break;
			}
			break;
		case 0xD8:
			GCElementalDamageRecv((PMSG_ELEMENTAL_DAMAGE_RECV*)lpMsg);
			break;
		case 0xEC:
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
				case 0x30:
					GCCharacterAttackSpeedRecv((PMSG_CHARACTER_ATTACK_SPEED_RECV*)lpMsg);
					break;
			}
			break;
		case 0xF1:
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
				case 0x00:
					GCConnectClientRecv((PMSG_CONNECT_CLIENT_RECV*)lpMsg);
					break;
				case 0x01:
					GCConnectAccountRecv((PMSG_CONNECT_ACCOUNT_RECV*)lpMsg);
					break;
				case 0x02:
					GCCloseClientRecv((PMSG_CLOSE_CLIENT_RECV*)lpMsg);
					break;
			}
			break;
		case 0xF3:
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
				case 0x00:
					GCCharacterListRecv((PMSG_CHARACTER_LIST_RECV*)lpMsg);
					break;
				case 0x03:
					GCCharacterInfoRecv((PMSG_CHARACTER_INFO_RECV*)lpMsg);
					break;
				case 0x04:
					GCCharacterRegenRecv((PMSG_CHARACTER_REGEN_RECV*)lpMsg);
					break;
				case 0x05:
					GCLevelUpRecv((PMSG_LEVEL_UP_RECV*)lpMsg);
					break;
				case 0x06:
					GCLevelUpPointRecv((PMSG_LEVEL_UP_POINT_RECV*)lpMsg);
					break;
				case 0x07:
					GCMonsterDamageRecv((PMSG_MONSTER_DAMAGE_RECV*)lpMsg);
					break;
				case 0x50:
					GCMasterInfoRecv((PMSG_MASTER_INFO_RECV*)lpMsg);
					break;
				case 0x51:
					GCMasterLevelUpRecv((PMSG_MASTER_LEVEL_UP_RECV*)lpMsg);
					break;
				case 0xE0:
					GCNewCharacterInfoRecv((PMSG_NEW_CHARACTER_INFO_RECV*)lpMsg);
					return 1;
				case 0xE1:
					GCNewCharacterCalcRecv((PMSG_NEW_CHARACTER_CALC_RECV*)lpMsg);
					return 1;
				case 0xE2:
					GCNewHealthBarRecv((PMSG_NEW_HEALTH_BAR_RECV*)lpMsg);
					return 1;
				case 0xE3:
					GCNewGensBattleInfoRecv((PMSG_NEW_GENS_BATTLE_INFO_RECV*)lpMsg);
					return 1;
				case 0xE4:
					GCNewMessageRecv((PMSG_NEW_MESSAGE_RECV*)lpMsg);
					return 1;
			}
			break;
	}

	return ProtocolCore(head,lpMsg,size,key);
}

void GCDamageRecv(PMSG_DAMAGE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewCurHP = lpMsg->ViewCurHP;
		ViewCurSD = lpMsg->ViewCurSD;
	}

	ViewDamageHP = lpMsg->ViewDamageHP;
	ViewDamageSD = lpMsg->ViewDamageSD;

	if((MAKE_NUMBERW(lpMsg->type[0],lpMsg->type[1]) & 0x10) != 0)
	{
		if(ViewDamageCount < 3)
		{
			ViewDamageTable[ViewDamageCount++] = lpMsg->ViewDamageHP;
			ViewDamageValue = ViewDamageCount;
		}
	}

	if((MAKE_NUMBERW(lpMsg->type[0],lpMsg->type[1]) & 0x20) != 0)
	{
		if(ViewDamageCount < 4)
		{
			ViewDamageTable[ViewDamageCount++] = lpMsg->ViewDamageHP;
			ViewDamageValue = ViewDamageCount;
		}
	}
}

void GCMonsterDieRecv(PMSG_MONSTER_DIE_RECV* lpMsg) // OK
{
	ViewDamageHP = lpMsg->ViewDamageHP;
}

void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewCurHP = 0;
	}
}

void GCLifeRecv(PMSG_LIFE_RECV* lpMsg) // OK
{
	if(lpMsg->type == 0xFE)
	{
		ViewMaxHP = lpMsg->ViewHP;
		ViewMaxSD = lpMsg->ViewSD;
	}

	if(lpMsg->type == 0xFF)
	{
		ViewCurHP = ((ViewCurHP==0)?ViewCurHP:lpMsg->ViewHP);
		ViewCurSD = lpMsg->ViewSD;
	}
}

void GCManaRecv(PMSG_MANA_RECV* lpMsg) // OK
{
	if(lpMsg->type == 0xFE)
	{
		ViewMaxMP = lpMsg->ViewMP;
		ViewMaxBP = lpMsg->ViewBP;
	}

	if(lpMsg->type == 0xFF)
	{
		ViewCurMP = lpMsg->ViewMP;
		ViewCurBP = lpMsg->ViewBP;
	}
}

void GCFruitResultRecv(PMSG_FRUIT_RESULT_RECV* lpMsg) // OK
{
	if(lpMsg->result == 0 || lpMsg->result == 3 || lpMsg->result == 6 || lpMsg->result == 17)
	{
		ViewValue = lpMsg->ViewValue;
		ViewPoint = lpMsg->ViewPoint;
		ViewStrength = lpMsg->ViewStrength;
		ViewDexterity = lpMsg->ViewDexterity;
		ViewVitality = lpMsg->ViewVitality;
		ViewEnergy = lpMsg->ViewEnergy;
		ViewLeadership = lpMsg->ViewLeadership;
	}
}

void GCRewardExperienceRecv(PMSG_REWARD_EXPERIENCE_RECV* lpMsg) // OK
{
	ViewDamageHP = lpMsg->ViewDamageHP;
}

void GCQuestRewardRecv(PMSG_QUEST_REWARD_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewPoint = lpMsg->ViewPoint;
	}
}

void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg) // OK
{
	ReconnectOnMapServerMove(lpMsg->IpAddress,lpMsg->ServerPort);
}

void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg) // OK
{
	ReconnectOnMapServerMoveAuth(lpMsg->result);
}

void GCElementalDamageRecv(PMSG_ELEMENTAL_DAMAGE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewCurHP = lpMsg->ViewCurHP;
		ViewCurSD = lpMsg->ViewCurSD;
	}
}

void GCCharacterAttackSpeedRecv(PMSG_CHARACTER_ATTACK_SPEED_RECV* lpMsg) // OK
{
	lpMsg->PhysiSpeed = ((lpMsg->PhysiSpeed>((WORD)(&gProtect.m_MainInfo.DWMaxAttackSpeed)[(*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B) & 7)]))?((WORD)(&gProtect.m_MainInfo.DWMaxAttackSpeed)[(*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B) & 7)]):lpMsg->PhysiSpeed);

	lpMsg->MagicSpeed = ((lpMsg->MagicSpeed>((WORD)(&gProtect.m_MainInfo.DWMaxAttackSpeed)[(*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B) & 7)]))?((WORD)(&gProtect.m_MainInfo.DWMaxAttackSpeed)[(*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B) & 7)]):lpMsg->MagicSpeed);
}

void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg) // OK
{
	ViewIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);
}

void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg) // OK
{
	ReconnectOnConnectAccount(lpMsg->result);
}

void GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg) // OK
{
	ReconnectOnCloseClient(lpMsg->result);
}

void GCCharacterListRecv(PMSG_CHARACTER_LIST_RECV* lpMsg) // OK
{
	ReconnectOnCharacterList();
}

void GCCharacterInfoRecv(PMSG_CHARACTER_INFO_RECV* lpMsg) // OK
{
	ReconnectOnCharacterInfo();

	ViewReset = lpMsg->ViewReset;
	ViewPoint = lpMsg->ViewPoint;
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewStrength = lpMsg->ViewStrength;
	ViewDexterity = lpMsg->ViewDexterity;
	ViewVitality = lpMsg->ViewVitality;
	ViewEnergy = lpMsg->ViewEnergy;
	ViewLeadership = lpMsg->ViewLeadership;

	*(WORD*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x07E) = 0;

	*(BYTE*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x328) = 0;

	switch(((*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B)) & 7))
	{
		case 0:
			SetByte(0x0055B6A2,((gProtect.m_MainInfo.DWMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 1:
			SetByte(0x0055B6A2,((gProtect.m_MainInfo.DKMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 2:
			SetByte(0x0055B6A2,((gProtect.m_MainInfo.FEMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 3:
			SetByte(0x0055B6A2,((gProtect.m_MainInfo.MGMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 4:
			SetByte(0x0055B6A2,((gProtect.m_MainInfo.DLMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 5:
			SetByte(0x0055B6A2,((gProtect.m_MainInfo.SUMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 6:
			SetByte(0x0055B6A2,((gProtect.m_MainInfo.RFMaxAttackSpeed>=0xFFFF)?0x0F:0x0F));
			break;
	}
}

void GCCharacterRegenRecv(PMSG_CHARACTER_REGEN_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewCurSD = lpMsg->ViewCurSD;
}

void GCLevelUpRecv(PMSG_LEVEL_UP_RECV* lpMsg) // OK
{
	ViewPoint = lpMsg->ViewPoint;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewExperience = lpMsg->ViewExperience;
	ViewNextExperience = lpMsg->ViewNextExperience;
}

void GCLevelUpPointRecv(PMSG_LEVEL_UP_POINT_RECV* lpMsg) // OK
{
	if(lpMsg->result >= 16 && lpMsg->result <= 20)
	{
		ViewPoint = lpMsg->ViewPoint;
		ViewMaxHP = lpMsg->ViewMaxHP;
		ViewMaxMP = lpMsg->ViewMaxMP;
		ViewMaxBP = lpMsg->ViewMaxBP;
		ViewMaxSD = lpMsg->ViewMaxSD;
		ViewStrength = lpMsg->ViewStrength;
		ViewDexterity = lpMsg->ViewDexterity;
		ViewVitality = lpMsg->ViewVitality;
		ViewEnergy = lpMsg->ViewEnergy;
		ViewLeadership = lpMsg->ViewLeadership;
	}
}

void GCMonsterDamageRecv(PMSG_MONSTER_DAMAGE_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewDamageHP = lpMsg->ViewDamageHP;
	ViewDamageSD = lpMsg->ViewDamageSD;
}

void GCMasterInfoRecv(PMSG_MASTER_INFO_RECV* lpMsg) // OK
{
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
}

void GCMasterLevelUpRecv(PMSG_MASTER_LEVEL_UP_RECV* lpMsg) // OK
{
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewMasterExperience = lpMsg->ViewMasterExperience;
	ViewMasterNextExperience = lpMsg->ViewMasterNextExperience;
}

void GCNewCharacterInfoRecv(PMSG_NEW_CHARACTER_INFO_RECV* lpMsg) // OK
{
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0E) = lpMsg->Level;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x74) = lpMsg->LevelUpPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x18) = lpMsg->Strength;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1A) = lpMsg->Dexterity;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1C) = lpMsg->Vitality;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1E) = lpMsg->Energy;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x20) = lpMsg->Leadership;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x22) = lpMsg->Life;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x26) = lpMsg->MaxLife;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x24) = lpMsg->Mana;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x28) = lpMsg->MaxMana;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x40) = lpMsg->BP;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x42) = lpMsg->MaxBP;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x2A) = lpMsg->Shield;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x2C) = lpMsg->MaxShield;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x4C) = lpMsg->FruitAddPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x4E) = lpMsg->MaxFruitAddPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x50) = lpMsg->FruitSubPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x52) = lpMsg->MaxFruitSubPoint;

	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10) = lpMsg->Experience;

	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x14) = lpMsg->NextExperience;

	//EXTRA
	ViewReset = lpMsg->ViewReset;
	ViewPoint = lpMsg->ViewPoint;
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewStrength = lpMsg->ViewStrength;
	ViewDexterity = lpMsg->ViewDexterity;
	ViewVitality = lpMsg->ViewVitality;
	ViewEnergy = lpMsg->ViewEnergy;
	ViewLeadership = lpMsg->ViewLeadership;
}

void GCNewCharacterCalcRecv(PMSG_NEW_CHARACTER_CALC_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewAddStrength = lpMsg->ViewAddStrength;
	ViewAddDexterity = lpMsg->ViewAddDexterity;
	ViewAddVitality = lpMsg->ViewAddVitality;
	ViewAddEnergy = lpMsg->ViewAddEnergy;
	ViewAddLeadership = lpMsg->ViewAddLeadership;
	ViewPhysiDamageMin = lpMsg->ViewPhysiDamageMin;
	ViewPhysiDamageMax = lpMsg->ViewPhysiDamageMax;
	ViewMagicDamageMin = lpMsg->ViewMagicDamageMin;
	ViewMagicDamageMax = lpMsg->ViewMagicDamageMax;
	ViewCurseDamageMin = lpMsg->ViewCurseDamageMin;
	ViewCurseDamageMax = lpMsg->ViewCurseDamageMax;
	ViewMulPhysiDamage = lpMsg->ViewMulPhysiDamage;
	ViewDivPhysiDamage = lpMsg->ViewDivPhysiDamage;
	ViewMulMagicDamage = lpMsg->ViewMulMagicDamage;
	ViewDivMagicDamage = lpMsg->ViewDivMagicDamage;
	ViewMulCurseDamage = lpMsg->ViewMulCurseDamage;
	ViewDivCurseDamage = lpMsg->ViewDivCurseDamage;
	ViewMagicDamageRate = lpMsg->ViewMagicDamageRate;
	ViewCurseDamageRate = lpMsg->ViewCurseDamageRate;
	ViewPhysiSpeed = lpMsg->ViewPhysiSpeed;
	ViewMagicSpeed = lpMsg->ViewMagicSpeed;
	ViewAttackSuccessRate = lpMsg->ViewAttackSuccessRate;
	ViewAttackSuccessRatePvP = lpMsg->ViewAttackSuccessRatePvP;
	ViewDefense = lpMsg->ViewDefense;
	ViewDefenseSuccessRate = lpMsg->ViewDefenseSuccessRate;
	ViewDefenseSuccessRatePvP = lpMsg->ViewDefenseSuccessRatePvP;
	ViewDamageMultiplier = lpMsg->ViewDamageMultiplier;
	ViewRFDamageMultiplierA = lpMsg->ViewRFDamageMultiplierA;
	ViewRFDamageMultiplierB = lpMsg->ViewRFDamageMultiplierB;
	ViewRFDamageMultiplierC = lpMsg->ViewRFDamageMultiplierC;
	ViewDarkSpiritAttackDamageMin = lpMsg->ViewDarkSpiritAttackDamageMin;
	ViewDarkSpiritAttackDamageMax = lpMsg->ViewDarkSpiritAttackDamageMax;
	ViewDarkSpiritAttackSpeed = lpMsg->ViewDarkSpiritAttackSpeed;
	ViewDarkSpiritAttackSuccessRate = lpMsg->ViewDarkSpiritAttackSuccessRate;
}

void GCNewHealthBarRecv(PMSG_NEW_HEALTH_BAR_RECV* lpMsg) // OK
{

}

void GCNewGensBattleInfoRecv(PMSG_NEW_GENS_BATTLE_INFO_RECV* lpMsg) // OK
{
	GensBattleMapCount = lpMsg->GensBattleMapCount;

	GensMoveIndexCount = lpMsg->GensMoveIndexCount;

	memcpy(GensBattleMap,lpMsg->GensBattleMap,sizeof(GensBattleMap));

	memcpy(GensMoveIndex,lpMsg->GensMoveIndex,sizeof(GensMoveIndex));
}

void GCNewMessageRecv(PMSG_NEW_MESSAGE_RECV* lpMsg) // OK
{
	wchar_t buffW[128];

	if(MultiByteToWideChar(CP_ACP,0,lpMsg->message,sizeof(lpMsg->message),buffW,_countof(buffW)) != 0)
	{
		char buffA[256];

		if(WideCharToMultiByte(CP_UTF8,0,buffW,_countof(buffW),buffA,sizeof(buffA),0,0) != 0)
		{
			DWORD value = ((DWORD(*)())0x00936AAC)();

			((void(*)(DWORD,char*,char*,char*,int))0x00927D4B)((*(DWORD*)(value+0x124)),"SetChatLogText","%s %d",buffA,2);
		}
	}
}

void DataSend(BYTE* lpMsg,DWORD size) // OK
{
	BYTE EncBuff[2048];

	if(gPacketManager.AddData(lpMsg,size) != 0 && gPacketManager.ExtractPacket(EncBuff) != 0)
	{
		BYTE send[2048];

		memcpy(send,EncBuff,size);

		if(EncBuff[0] == 0xC3 || EncBuff[0] == 0xC4)
		{
			if(EncBuff[0] == 0xC3)
			{
				BYTE save = EncBuff[1];

				EncBuff[1] = (*(BYTE*)(MAIN_PACKET_SERIAL))++;

				size = gPacketManager.Encrypt(&send[2],&EncBuff[1],(size-1))+2;

				EncBuff[1] = save;

				send[0] = 0xC3;
				send[1] = LOBYTE(size);
			}
			else
			{
				BYTE save = EncBuff[2];

				EncBuff[2] = (*(BYTE*)(MAIN_PACKET_SERIAL))++;

				size = gPacketManager.Encrypt(&send[3],&EncBuff[2],(size-2))+3;

				EncBuff[2] = save;

				send[0] = 0xC4;
				send[1] = HIBYTE(size);
				send[2] = LOBYTE(size);
			}
		}

		((void(__thiscall*)(void*,BYTE*,DWORD))0x00439764)((void*)0x08B15A70,send,size);
	}
}
