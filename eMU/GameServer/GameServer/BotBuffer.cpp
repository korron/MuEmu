#include "stdafx.h"
#include "BotBuffer.h"
#include "Monster.h"
#include "Protocol.h"
#include "Util.h"
#include "MemScript.h"
#include "Message.h"
#include "Notice.h"
#include "ItemManager.h"
#include "Map.h"
#include "ScheduleManager.h"
#include "ReadScript.h"
#include "ObjectManager.h"
#include "QuestReward.h"
#include "Quest.h"
#include "DSProtocol.h"
#include "Viewport.h"
#include "SkillManager.h"
#include "MuunSystem.h"
#include "PG_Custom.h"

#if (BOT_BUFFER == 1)

ObjBotBuffer ObjBotBuff;

CMemScript objScript;

void ObjBotBuffer::Read(char * FilePath)
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTBUFFER;botNum++)
		{
			if(this->bot[botNum].Enabled == true)
			{
				int bIndex = this->bot[botNum].index;
				if(gObjIsConnected(bIndex) == TRUE)
				{
					gObjDel(bIndex);
				}
			}
		}
	}
	for(int i=0;i<MAX_BOTBUFFER;i++)
	{
		this->bot[i].index = -1;
		this->bot[i].SkillCount = 0;
		this->bot[i].MaxLevel = ObjBotBuff.Max_Normal_Level;
		memset(&this->bot[i].skill,0,sizeof(this->bot[i].skill));
		this->bot[i].Enabled = false;
		for(int j=0;j<9;j++)
			this->bot[i].body[j].num =-1;
	}

	this->Enabled = FALSE;
	int Token;
	SMDFile = fopen(FilePath, "r");

	if ( SMDFile == NULL )
	{
		ErrorMessageBox("BotBuffer data load error %s", FilePath);
		return;
	}

	while ( true )
	{
		int iType = GetToken();
		
		if ( iType == 1 )
		{
			while(true)
			{
				Token = GetToken();
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				int BotNum = TokenNumber;
				if(BotNum < 0 || BotNum > MAX_BOTBUFFER-1)
				{
					ErrorMessageBox("BotBuffer error: BotPetIndex:%d out of range!", BotNum);
					return;
				}

				Token = GetToken();
				this->bot[BotNum].Class = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].OnlyVip = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].MaxLevel = TokenNumber;

				Token = GetToken();
				strncpy(this->bot[BotNum].Name,TokenString,sizeof(this->bot[BotNum].Name));

				Token = GetToken();
				strncpy(this->bot[BotNum].GuildName,TokenString,sizeof(this->bot[BotNum].GuildName));

				Token = GetToken();
				this->bot[BotNum].Gens = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].GensRank = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].Map = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].X = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].Y = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].Dir = TokenNumber;

				this->bot[BotNum].Enabled = true;
			}
		}
		
		iType = GetToken();
		iType = TokenNumber;
		if ( iType == 2 )
		{
			while(true)
			{
				Token = GetToken();
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				int BotNum = TokenNumber;
				if(BotNum < 0 || BotNum > MAX_BOTBUFFER-1)
				{
					ErrorMessageBox("BotBuffer error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				if(this->bot[BotNum].Enabled == false)
				{	
					ErrorMessageBox("BotBuffer error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				Token = GetToken();
				int Slot = TokenNumber;
				
				if(Slot < 0 || Slot > 8)
				{	
					ErrorMessageBox("BotBuffer error: Min Slot 0 ; Max Slot 8");
					return;
				}

				Token = GetToken();
				int iType = TokenNumber;

				Token = GetToken();
				int iIndex = TokenNumber;

				this->bot[BotNum].body[Slot].num = GET_ITEM(iType,iIndex);

				Token = GetToken();
				this->bot[BotNum].body[Slot].level = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].body[Slot].opt = TokenNumber;

				this->bot[BotNum].body[Slot].Enabled = true;
			}
		}
		
		iType = GetToken();
		iType = TokenNumber;
		if ( iType == 3 )
		{
			this->Enabled = TRUE;
			while(true)
			{
				Token = GetToken();
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				int BotNum = TokenNumber;
				if(BotNum < 0 || BotNum > MAX_BOTBUFFER-1)
				{
					ErrorMessageBox("BotBuffer error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				if(this->bot[BotNum].Enabled == false)
				{	
					ErrorMessageBox("BotBuffer error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				if(this->bot[BotNum].SkillCount < 0 || this->bot[BotNum].SkillCount > MAX_BOTBUFFERSKILLS-1)
				{
					ErrorMessageBox("BotBuffer error: Skill Buff out of range (MAX BUFF PER BOT = %d)!", this->bot[BotNum].SkillCount);
					return;
				}

				Token = GetToken();
				this->bot[BotNum].skill[this->bot[BotNum].SkillCount].skill = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].skill[this->bot[BotNum].SkillCount].time = TokenNumber;

				this->bot[BotNum].SkillCount++;
			}
		}
		break;
	}
	LogAdd(LOG_BOT,"[BotBuffer] - %s file is Loaded",FilePath);
	fclose(SMDFile);
}

int ObjBotBuffer::GetBotIndex(int aIndex)
{
	for(int i=0; i<MAX_BOTBUFFER; i++)
	{
		if(this->bot[i].Enabled == true)
		{
			if(this->bot[i].index == aIndex)
				return i;
		}
	}
	return -1;
}

void ObjBotBuffer::MakeBot()
{

	if(this->Enabled == true)
	{
	
		for(int botNum=0; botNum<MAX_BOTBUFFER; botNum++)
		{
			if(this->bot[botNum].Enabled == true)	
			{

				int result = gObjAddSummon(); 

				if(result >= 0)
				{
					this->bot[botNum].index = result;
					gObj[result].PosNum = (WORD)-1;
					gObj[result].X = this->bot[botNum].X;
					gObj[result].Y = this->bot[botNum].Y;
					gObj[result].OldX = this->bot[botNum].X;
					gObj[result].OldY = this->bot[botNum].Y;
					gObj[result].TX = this->bot[botNum].X;
					gObj[result].TY = this->bot[botNum].Y;
					gObj[result].MTX = this->bot[botNum].X;
					gObj[result].MTY = this->bot[botNum].Y;
					gObj[result].Dir = this->bot[botNum].Dir;
					gObj[result].Map = this->bot[botNum].Map;
					gObj[result].Live = TRUE;	
					gObj[result].PathCount = 0; 
					gObj[result].IsBot = 3;
					gObjSetBots(result,this->bot[botNum].Class);

					gObj[result].ChangeUp = this->bot[botNum].Class;
					gObj[result].Class = this->bot[botNum].Class;
					gObj[result].Level = 400;
					gObj[result].Life = 1;
					gObj[result].MaxLife = 2;
					gObj[result].Mana = 1;
					gObj[result].MaxMana = 2;
					gObj[result].Experience = 0;
					gObj[result].DBClass = this->bot[botNum].Class;
					gObj[result].PKLevel = 3;
					gObj[result].GensFamily = this->bot[botNum].Gens;		// 1: VARNERT 2: DUPRIAN
					gObj[result].GensSymbol = this->bot[botNum].GensRank;	// 1 to 14

					gObj[result].Inventory = new CItem[INVENTORY_SIZE];					
					gObj[result].Inventory1 = new CItem[INVENTORY_SIZE];
					gObj[result].InventoryMap1 = new BYTE[INVENTORY_SIZE];
					gObj[result].InventoryMap = new BYTE[INVENTORY_SIZE];
					gObj[result].MuunInventory = new CItem[MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE];
					gObj[result].MuunInventoryMap = new BYTE[MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE];

					for (int i=0;i<INVENTORY_SIZE;i++)
					{
						gObj[result].Inventory[i].Clear();
						gObj[result].Inventory1[i].Clear();
					}

					memset(&gObj[result].InventoryMap[0], (BYTE)-1, INVENTORY_SIZE);
					memset(&gObj[result].InventoryMap1[0], (BYTE)-1, INVENTORY_SIZE);
					memset(&gObj[result].MuunInventoryMap[0], (BYTE)-1, (MUUN_INVENTORY_SIZE));

					strncpy(gObj[result].Name,this->bot[botNum].Name,sizeof(gObj[result].Name));

					for(int i=0;i<9;i++)
					{
						if(this->bot[botNum].body[i].num >= 0 && this->bot[botNum].body[i].Enabled == true)
						{
							CItem item;
							item.m_Level = this->bot[botNum].body[i].level;
							item.m_Option1 = 0;	//Skill
							item.m_Option2 = 1;	//Luck
							item.m_Option3 = this->bot[botNum].body[i].opt;	//Option +28
							item.m_Durability = 255.0f;
							item.m_JewelOfHarmonyOption = 0;
							item.m_ItemOptionEx = 0;
							item.m_SocketOption[1] = 0;
							item.m_SocketOption[2] = 0;
							item.m_SocketOption[3] = 0;
							item.m_SocketOption[4] = 0;
							item.m_SocketOption[5] = 0;
							item.Convert(this->bot[botNum].body[i].num,item.m_Option1,item.m_Option2,item.m_Option3,item.m_NewOption,item.m_SetOption,item.m_JewelOfHarmonyOption,item.m_ItemOptionEx,item.m_SocketOption,item.m_SocketOptionBonus);
							gObj[result].Inventory[i].m_Option1 = item.m_Option1;
							gObj[result].Inventory[i].m_Option2 = item.m_Option2;
							gObj[result].Inventory[i].m_Option3 = item.m_Option3;
							gObj[result].Inventory[i].m_JewelOfHarmonyOption = item.m_JewelOfHarmonyOption;
							gObj[result].Inventory[i].m_ItemOptionEx = item.m_ItemOptionEx;

							item.m_Number = 0;
							gObjInventoryInsertItemPos(gObj[result].Index,item,i,0);
						}
					}
					
					gObj[result].Inventory1 = gObj[result].Inventory;
					gObj[result].InventoryMap1 = gObj[result].InventoryMap;
					gObj[result].MuunInventory = gObj[result].MuunInventory;
					gObj[result].MuunInventoryMap = gObj[result].MuunInventoryMap;

					gObjectManager.CharacterMakePreviewCharSet(result);

					gObj[result].AttackType = 0;
					gObj[result].BotSkillAttack = 0;					

					gObj[result].Attribute = 100;
					gObj[result].TargetNumber = (WORD)-1;
					gObj[result].ActionState.Emotion = 0;
					gObj[result].ActionState.Attack = 0;
					gObj[result].ActionState.EmotionCount = 0;
					gObj[result].PathCount = 0;
					gObj[result].BotPower = 0;
					gObj[result].BotDefense = this->bot[botNum].OnlyVip;
					gObj[result].BotLife = 1;
					gObj[result].BotMaxLife = 1;
					
					gObj[result].BotLvlUpDefense = 1;
					gObj[result].BotLvlUpPower = 1;
					gObj[result].BotLvlUpLife = 1;
					gObj[result].BotLvlUpMana = 1;
					gObj[result].BotLvlUpExp = 1;
					gObj[result].BotLvlUpMaxLevel = 1;

					gObj[result].MoveRange = 1;
					gObj[result].BotFollowMe = 0;
					gObj[result].NextExperience = gLevelExperience[gObj[result].Level];
					

					GCSummonLifeSend(gObj[result].SummonIndex,gObj[result].MaxLife,gObj[result].Life);

					ChatSend(&gObj[result],"I'll HELP ALL FIGHTERS!"); //test
					GCActionSend(&gObj[result],ACTION_SALUTE1,result,result);
				}
			}
		}
	}
}

BOOL ObjBotBuffer::TradeOpen(int index, int nindex)
{

	if ( gObjIsConnectedGP(index) == FALSE )
	{
		LogAdd(LOG_BLUE, "error-L3 [%s][%d]", __FILE__, __LINE__);
		return 0;
	}
	if(gObjIsConnected(nindex) == 0)
	{
		return 0;
	}

	int number = this->GetBotIndex(nindex);

	if(number == -1)
	{
		return 0;
	}

	char sbuf[512]={0};
	LPOBJ lpObj = &gObj[index];
	LPOBJ lpBot = &gObj[nindex];


	if(gObj[index].Level > this->bot[number].MaxLevel)
	{
		GCChatTargetSend(&gObj[this->bot[number].index],nindex,"You can go without my help!");
		return 0;
	}

	if(this->bot[number].OnlyVip == 1 && gObj[index].AccountLevel == 0)
	{
		GCChatTargetSend(&gObj[this->bot[number].index],nindex,"Im only work for VIPs!");
		return 0;
	}

	for(int x=0;x<this->bot[number].SkillCount;x++)
	{
		switch(this->bot[number].skill[x].skill)
		{
			
		case EFFECT_MANA_SHIELD:	//mago
			{
				GCActionSend(&gObj[nindex],ACTION_SALUTE1,nindex,nindex);
				lpObj->ManaShieldTime = this->bot[number].skill[x].time;
				gEffectManager.AddEffect(lpObj,0,EFFECT_MANA_SHIELD,lpObj->ManaShieldTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_MANA_SHIELD User: %s Time: %d",lpObj->Name,lpObj->ManaShieldTime);
			}
			break;
		case EFFECT_GREATER_LIFE:	//bk
			{	GCActionSend(&gObj[nindex],ACTION_SALUTE1,nindex,nindex);
				lpObj->GreaterLifeTime = this->bot[number].skill[x].time;
				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_LIFE,lpObj->GreaterLifeTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_GREATER_LIFE User: %s Time: %d",lpObj->Name,lpObj->GreaterLifeTime);
			}
			break;
		case EFFECT_GREATER_DEFENSE:	//elf
			{	
				GCActionSend(&gObj[nindex],ACTION_SALUTE1,nindex,nindex);
				lpObj->GreaterDefenseTime = this->bot[number].skill[x].time;
				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_DEFENSE,lpObj->GreaterDefenseTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_GREATER_DEFENSE User: %s Time: %d",lpObj->Name,lpObj->GreaterDefenseTime);
			}
			break;

		case EFFECT_GREATER_DAMAGE:	//elf
			{	GCActionSend(&gObj[nindex],ACTION_SALUTE1,nindex,nindex);
				lpObj->GreaterDamageTime = this->bot[number].skill[x].time;	
				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_DAMAGE,lpObj->GreaterDamageTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_GREATER_DAMAGE User: %s Time: %d",lpObj->Name,lpObj->GreaterDamageTime);
			}
			break;

		case EFFECT_GREATER_CRITICAL_DAMAGE:	//dl
			{	GCActionSend(&gObj[nindex],ACTION_SALUTE1,nindex,nindex);
				lpObj->GreaterCriticalDamageTime = this->bot[number].skill[x].time;	
				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_CRITICAL_DAMAGE,lpObj->GreaterCriticalDamageTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_CRITICAL_DAMAGE User: %s Time: %d",lpObj->Name,lpObj->GreaterCriticalDamageTime);
			}
			break;
		
		case EFFECT_DAMAGE_REFLECT:	//sum
			{	GCActionSend(&gObj[nindex],ACTION_SALUTE1,nindex,nindex);
				lpObj->DamageReflectTime = this->bot[number].skill[x].time;	
				gEffectManager.AddEffect(lpObj,0,EFFECT_DAMAGE_REFLECT,lpObj->DamageReflectTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_DAMAGE_REFLECT User: %s Time: %d",lpObj->Name,lpObj->DamageReflectTime);
			}
			break;
		
		case EFFECT_MAGIC_CIRCLE:	// ni puta idea
			{	GCActionSend(&gObj[nindex],ACTION_SALUTE1,nindex,nindex);
				lpObj->MagicCircleTime = this->bot[number].skill[x].time;
				gEffectManager.AddEffect(lpObj,0,EFFECT_MAGIC_CIRCLE,lpObj->MagicCircleTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_MAGIC_CIRCLE User: %s Time: %d",lpObj->Name,lpObj->MagicCircleTime);
			}
			break;
		/* Skill RageFigther */
		case EFFECT_GREATER_IGNORE_DEFENSE_RATE:
			{	GCActionSend(&gObj[nindex],ACTION_RAGEBUFF_1,nindex,nindex);	//OK
				lpObj->GreaterIgnoreDefenseRateTime = this->bot[number].skill[x].time;
				gEffectManager.AddEffect(lpObj,0,EFFECT_GREATER_IGNORE_DEFENSE_RATE,lpObj->GreaterIgnoreDefenseRateTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_IGNORE_DEFENSE User: %s Time: %d",lpObj->Name,lpObj->GreaterIgnoreDefenseRateTime);
			}
			break;

		case EFFECT_FITNESS:
			{	GCActionSend(&gObj[nindex],ACTION_RAGEBUFF_2,nindex,nindex);	//OK
				lpObj->FitnessTime = this->bot[number].skill[x].time;
				gEffectManager.AddEffect(lpObj,0,EFFECT_FITNESS,lpObj->FitnessTime,(45+(lpObj->Level/3)),(50+(lpObj->Level/5)),0,0);
				LogAdd(LOG_BOT,"[BotBuffer] - ADD_SKILL_FITNESS User: %s Time: %d",lpObj->Name,lpObj->FitnessTime);
			}
			break;
		}
	}
	GCChatTargetSend(&gObj[this->bot[number].index],nindex,"Now you are Buffer!");
	return 1;
}
#endif
