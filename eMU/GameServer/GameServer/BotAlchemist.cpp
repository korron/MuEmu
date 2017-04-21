#include "stdafx.h"
#include "GameServer.h"
#include "Log.h"
#include "GameMain.h"
#include "User.h"
#include "Protocol.h"
#include "BotAlchemist.h"
#include "Skill.h"
#include "DevilSquare.h"
#include "BloodCastle.h"
#include "ChaosCastle.h"
#include "util.h"
#include "readscript.h"
#include "SetItemOption.h"
#include "PG_Custom.h"
#include "ObjectManager.h"
#include "Item.h"
#include "Monster.h"
#include "MuunSystem.h"
#include "Trade.h"

#if (BOT_ALCHEMIST == 1)

ObjBotAlchemist BotAlchemist;

void ObjBotAlchemist::Read(char * FilePath)
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTALCHEMIST;botNum++)
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
	memset(&this->bot,0,sizeof(this->bot));
	this->Enabled = FALSE;
	int Token;

	if (FilePath == NULL || !strcmp(FilePath, ""))
	{
		ErrorMessageBox("[BotAlchemist] file load error - File Name Error");
		return ;
	}

	SMDFile = fopen(FilePath, "r");

	if ( SMDFile == NULL )
	{
		ErrorMessageBox("BotAlchemist data load error %s", FilePath);
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
				if(BotNum < 0 || BotNum > MAX_BOTALCHEMIST-1)
				{
					LogAdd(LOG_BOT,"BotAlchemist error: BotPetIndex:%d out of range!", BotNum);
					return;
				}

				Token = GetToken();
				this->bot[BotNum].Class = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].Rate = TokenNumber;

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
				if(BotNum < 0 || BotNum > MAX_BOTALCHEMIST-1)
				{
					LogAdd(LOG_BOT,"BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				if(this->bot[BotNum].Enabled == false)
				{	
					LogAdd(LOG_BOT,"BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				Token = GetToken();
				int Slot = TokenNumber;
				
				if(Slot < 0 || Slot > 8)
				{	
					LogAdd(LOG_BOT,"BotAlchemist error: Min Slot 0 ; Max Slot 8");
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
			while(true)
			{
				Token = GetToken();
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				int BotNum = TokenNumber;
				if(BotNum < 0 || BotNum > MAX_BOTALCHEMIST-1)
				{
					LogAdd(LOG_BOT,"BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				if(this->bot[BotNum].Enabled == false)
				{	
					LogAdd(LOG_BOT,"BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}

				Token = GetToken();
				this->bot[BotNum].AllowLevel = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].AllowOpt = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].AllowLuck = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].AllowSkill = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].AllowExc = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].AllowFFFF = TokenNumber;
			}
		}
		
		iType = GetToken();
		iType = TokenNumber;
		if ( iType == 4 )
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
				if(BotNum < 0 || BotNum > MAX_BOTALCHEMIST-1)
				{
					LogAdd(LOG_BOT,"BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				if(this->bot[BotNum].Enabled == false)
				{	
					LogAdd(LOG_BOT,"BotAlchemist error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}

				Token = GetToken();
				this->bot[BotNum].OnlyVip = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].VipMoney = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].Zen = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].PCPoint = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].OnlySameType = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].OnlyLowerIndex = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].AcceptAncient = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].MaxLevel = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].MaxExc = TokenNumber;
			}
		}
		
		break;
	}

	fclose(SMDFile);		
	LogAdd(LOG_BOT,"[BotAlchemist] - %s file is Loaded",FilePath);

}
void ObjBotAlchemist::MakeBot()
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTALCHEMIST;botNum++)
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
					gObj[result].IsBot = 2;
					gObjSetBots(result,this->bot[botNum].Class);

					gObj[result].ChangeUp = this->bot[botNum].Class & 0x07;	// Set Second Type of Character
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

					gObj[result].Inventory = new CItem[MAIN_INVENTORY_NORMAL_SIZE];					
					gObj[result].Inventory1 = new CItem[MAIN_INVENTORY_NORMAL_SIZE];
					gObj[result].InventoryMap1 = new BYTE[MAIN_INVENTORY_NORMAL_SIZE];
					gObj[result].InventoryMap = new BYTE[MAIN_INVENTORY_NORMAL_SIZE];
				
					gObj[result].MuunInventory = new CItem[MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE];
					gObj[result].MuunInventoryMap = new BYTE[MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE];


					for (int i=0;i<MAIN_INVENTORY_NORMAL_SIZE;i++)
					{
						gObj[result].Inventory[i].Clear();
						gObj[result].Inventory1[i].Clear();
						gObj[result].MuunInventory[i].Clear();

					}

					memset(&gObj[result].InventoryMap[0], (BYTE)-1, MAIN_INVENTORY_NORMAL_SIZE);
					memset(&gObj[result].InventoryMap1[0], (BYTE)-1, MAIN_INVENTORY_NORMAL_SIZE);
					memset(&gObj[result].MuunInventoryMap[0], (BYTE)-1, (MUUN_INVENTORY_SIZE));

					strncpy(gObj[result].Name,this->bot[botNum].Name,sizeof(gObj[result].Name));
					
					strncpy(gObj[result].GuildName,this->bot[botNum].GuildName,sizeof(gObj[result].GuildName));

					//LogAdd(LOG_BLUE,"NAME GUILD BOT %s",gObj[result].GuildName);

					for(int i=0;i<9;i++)
					{
						if(this->bot[botNum].body[i].num >= 0 && this->bot[botNum].body[i].Enabled == true)
						{
							CItem item;
							item.m_Level = this->bot[botNum].body[i].level;
							item.m_Option1 = 0;
							item.m_Option2 = 1;
							item.m_Option3 = this->bot[botNum].body[i].opt;
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

					ChatSend(&gObj[result],"I'll COMBINE YOUR ITEMS!");
					GCActionSend(&gObj[result],ACTION_SALUTE1,result,result);
				}
			}
		}
	}
}

BOOL ObjBotAlchemist::IsInTrade(int aIndex)
{
	int number = this->GetBotIndex(gObj[aIndex].TargetNumber);

	if(number != -1)
	{
		return 1;
	}else
	{
		return 0;
	}
}

int ObjBotAlchemist::GetBotIndex(int aIndex)
{
	for(int i=0;i<MAX_BOTALCHEMIST;i++)
	{
		if(this->bot[i].Enabled == true)
		{
			if(this->bot[i].index == aIndex)
			{
				return i;
			}
		}
	}
	return -1;
}

bool ObjBotAlchemist::AllowExc(BYTE BotNum, BYTE ExcOpt)
{				
	int dwExOpCount = getNumberOfExcOptions(ExcOpt);

	if(dwExOpCount < this->bot[BotNum].MaxExc)
	{
		return true;
	}
	return false;
}

BYTE ObjBotAlchemist::Alchemy(int aIndex,int BotNum)
{
	char sbuf[512]={0};
	int fitem=-1;
	int sitem=-1;
	int count=0;

	if(gObjIsConnected(aIndex) == 0)
	{
		return 0;
	}

	if((gObj[aIndex].TradeMoney - this->bot[BotNum].Zen) < 0)	
	{
		wsprintf(sbuf,"I Need %d Money!",this->bot[BotNum].Zen );
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,sbuf);
		LogAdd(LOG_BOT,"[BotAlchemist][Bot:%d](%s) Insuficent Money",BotNum,gObj[aIndex].Account);
		goto Cancel;
	}

	if(gObj[aIndex].PCPoints - this->bot[BotNum].PCPoint < 0)
	{
		wsprintf(sbuf,"I Need %d PcPoints!",this->bot[BotNum].PCPoint );
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,sbuf);
		LogAdd(LOG_BOT,"[BotAlchemist][Bot:%d](%s) Insuficent PcPoints",BotNum,gObj[aIndex].Account);
		goto Cancel;
	}

	if(this->bot[BotNum].VipMoney > 0)
	{
		if(gObj[aIndex].VipMoney - this->bot[BotNum].VipMoney < 0)
		{
			wsprintf(sbuf,"I Need %d VipMoney!",this->bot[BotNum].VipMoney );
			GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,sbuf);
			LogAdd(LOG_BOT,"[BotAlchemist][Bot:%d](%s) Insuficent VipMoney",BotNum,gObj[aIndex].Account);
			goto Cancel;
		}
	}

	for(int n = 0; n < TRADE_SIZE; n++)
	{
		if(gObj[aIndex].Trade[n].IsItem() == 1)
		{
			if((n >= 0 && n<=3) || (n >= 8 && n<=11) || (n >= 16 && n<=19) || (n >= 24 && n<=27))
			{
				fitem = n;
			}else
			{
				sitem = n;
			}

			count++;
		}
	}
	if(count != 2)
	{
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"You must put only 2 items!");
		LogAdd(LOG_BOT,"[BotAlchemist](%s)(%s) Items Count Error (%d)",gObj[aIndex].Account,gObj[aIndex].Name,count);
		goto Cancel;
	}
	if((gObj[aIndex].Trade[fitem].m_Index >= 6144) || (gObj[aIndex].Trade[sitem].m_Index >= 6144))
	{
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"Only weapons and sets are allowed!");
		LogAdd(LOG_BOT,"[BotAlchemist](%s)(%s) Items Error",gObj[aIndex].Account,gObj[aIndex].Name);
		goto Cancel;
	}
	if(fitem == -1 || sitem == -1)
	{
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"You must put two items!");
		LogAdd(LOG_BOT,"[BotAlchemist](%s)(%s) Items Position Error",gObj[aIndex].Account,gObj[aIndex].Name);
		goto Cancel;
	}

	if(this->bot[BotNum].OnlySameType == 1)
	{
		int fType = gObj[aIndex].Trade[fitem].m_Index/512;
		int sType = gObj[aIndex].Trade[sitem].m_Index/512;
		if(fType != sType)
		{
			GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"You must put two items of same type!");
			LogAdd(LOG_BOT,"[BotAlchemist](%s)(%s) Item Types Error",gObj[aIndex].Account,gObj[aIndex].Name);
			goto Cancel;
		}
	}

	if(this->bot[BotNum].OnlyLowerIndex == 1)
	{
		int fLevel = ItemAttribute[gObj[aIndex].Trade[fitem].m_Index].Level;
		int sLevel = ItemAttribute[gObj[aIndex].Trade[sitem].m_Index].Level;

		if(fLevel > sLevel)
		{
			if(fLevel > (sLevel + 10))
			{
				GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"Only lower items than source works with my alchemy!");
				LogAdd(LOG_BOT,"[BotAlchemist](%s)(%s) Item Destiny Lower Index Error",gObj[aIndex].Account,gObj[aIndex].Name);
				goto Cancel;
			}
		}
	}

	if(this->bot[BotNum].AcceptAncient == 0 && gObj[aIndex].Trade[fitem].m_SetOption > 0)
	{
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"I cant work with Ancient Items!");
		LogAdd(LOG_BOT,"[BotAlchemist](%s)(%s) Ancient Item Error",gObj[aIndex].Account,gObj[aIndex].Name);
		goto Cancel;
	}

	if(this->bot[BotNum].AllowFFFF == 0)
	{
		if(gObj[aIndex].Trade[fitem].GetNumber() >= 0xFFFFFFF0 || gObj[aIndex].Trade[sitem].GetNumber() >= 0xFFFFFFF0)
		{
			GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"You cant transmutate those items!");
			LogAdd(LOG_BOT,"[BotAlchemist](%s)(%s) FFFF Item Error",gObj[aIndex].Account,gObj[aIndex].Name);
			goto Cancel;
		}
	}

	srand(static_cast<int>(time(NULL)));
	int random = rand()%100;
	bool failed = false;

	if(random > this->bot[BotNum].Rate )
	{
		failed = true;
	}

	if(this->bot[BotNum].AllowLuck == 1)
	{
		if(gObj[aIndex].Trade[fitem].m_Option2 == 0 && gObj[aIndex].Trade[sitem].m_Option2 == 1)
		{
			if(!failed)
				gObj[aIndex].Trade[fitem].m_Option2 = 1;
			gObj[aIndex].Trade[sitem].m_Option2 = 0;
		}
	}
	if(this->bot[BotNum].AllowLevel == 1)
	{
		int fLevel = gObj[aIndex].Trade[fitem].m_Level;
		if(fLevel < this->bot[BotNum].MaxLevel)
		{
			int sLevel = gObj[aIndex].Trade[sitem].m_Level;
			if ((fLevel + sLevel) > this->bot[BotNum].MaxLevel)
			{
				sLevel -= (this->bot[BotNum].MaxLevel - fLevel);
				if(!failed)
					fLevel = this->bot[BotNum].MaxLevel;
			}else
			{
				if(!failed)
					fLevel += sLevel;
				sLevel = 0;
			}
			gObj[aIndex].Trade[fitem].m_Level = fLevel;
			gObj[aIndex].Trade[sitem].m_Level = sLevel;
		}
	}
	if(this->bot[BotNum].AllowSkill == 1)
	{
		if(gObj[aIndex].Trade[fitem].m_Index < 3584)
		{
			if(gObj[aIndex].Trade[fitem].m_Option1 == 0 && gObj[aIndex].Trade[sitem].m_Option1 == 1)
			{
				if(!failed)
					gObj[aIndex].Trade[fitem].m_Option1 = 1;
				gObj[aIndex].Trade[sitem].m_Option1 = 0;
			}
		}
	}
	if(this->bot[BotNum].AllowOpt == 1)
	{
		int fOpt = gObj[aIndex].Trade[fitem].m_Option3;
		if(fOpt < 7)
		{
			int sOpt = gObj[aIndex].Trade[sitem].m_Option3;
			if ((fOpt + sOpt) > 7)
			{
				sOpt -= (7 - fOpt);
				if(!failed)
					fOpt = 7;
			}else
			{
				if(!failed)
					fOpt += sOpt;
				sOpt = 0;
			}
			gObj[aIndex].Trade[fitem].m_Option3 = fOpt;
			gObj[aIndex].Trade[sitem].m_Option3 = sOpt;
		}
	}
	if(this->bot[BotNum].AllowExc == 1)
	{
		if(gObj[aIndex].Trade[fitem].m_NewOption != 63)
		{
			if(gObj[aIndex].Trade[sitem].m_NewOption != 0)
			{		
				if(this->AllowExc(BotNum,gObj[aIndex].Trade[fitem].m_NewOption) == true)
				{
					BYTE fLife		= gObj[aIndex].Trade[fitem].IsExtLifeAdd();
					BYTE fMana		= gObj[aIndex].Trade[fitem].IsExtManaAdd();
					BYTE fDmg		= gObj[aIndex].Trade[fitem].IsExtDamageMinus();
					BYTE fReflect	= gObj[aIndex].Trade[fitem].IsExtDamageReflect();
					BYTE fDef		= gObj[aIndex].Trade[fitem].IsExtDefenseSuccessfull();
					BYTE fMoney		= gObj[aIndex].Trade[fitem].IsExtMonsterMoney();
					
					BYTE sLife		= gObj[aIndex].Trade[sitem].IsExtLifeAdd();
					BYTE sMana		= gObj[aIndex].Trade[sitem].IsExtManaAdd();
					BYTE sDmg		= gObj[aIndex].Trade[sitem].IsExtDamageMinus();
					BYTE sReflect	= gObj[aIndex].Trade[sitem].IsExtDamageReflect();
					BYTE sDef		= gObj[aIndex].Trade[sitem].IsExtDefenseSuccessfull();
					BYTE sMoney		= gObj[aIndex].Trade[sitem].IsExtMonsterMoney();

					
					if(fLife == 0 && sLife != 0)
					{
						if(!failed)
							gObj[aIndex].Trade[fitem].m_NewOption |= 0x20;
						gObj[aIndex].Trade[sitem].m_NewOption &= ~0x20;
					}
					if(this->AllowExc(BotNum,gObj[aIndex].Trade[fitem].m_NewOption) == true)
					{
						if(fMana == 0 && sMana != 0)
						{
							if(!failed)
								gObj[aIndex].Trade[fitem].m_NewOption |= 0x10;
							gObj[aIndex].Trade[sitem].m_NewOption &= ~0x10;
						}
					}
		
					if(this->AllowExc(BotNum,gObj[aIndex].Trade[fitem].m_NewOption) == true)
					{
						if(fDmg == 0 && sDmg != 0)
						{
							if(!failed)
								gObj[aIndex].Trade[fitem].m_NewOption |= 8;
							gObj[aIndex].Trade[sitem].m_NewOption &= ~8;
						}
					}
					
					if(this->AllowExc(BotNum,gObj[aIndex].Trade[fitem].m_NewOption) == true)
					{
						if(fReflect == 0 && sReflect != 0)
						{
							if(!failed)
								gObj[aIndex].Trade[fitem].m_NewOption |= 4;
							gObj[aIndex].Trade[sitem].m_NewOption &= ~4;
						}
					}
					
					if(this->AllowExc(BotNum,gObj[aIndex].Trade[fitem].m_NewOption) == true)
					{
						if(fDef == 0 && sDef != 0)
						{
							if(!failed)
								gObj[aIndex].Trade[fitem].m_NewOption |= 2;
							gObj[aIndex].Trade[sitem].m_NewOption &= ~2;
						}
					}
					
					if(this->AllowExc(BotNum,gObj[aIndex].Trade[fitem].m_NewOption) == true)
					{
						if(fMoney == 0 && sMoney != 0)
						{
							if(!failed)
							{
								gObj[aIndex].Trade[fitem].m_NewOption |= 1;
							gObj[aIndex].Trade[sitem].m_NewOption &= ~1;
							}
						}
					}
				}
			}
		}
	}

	int a = gObjInventoryInsertItem(aIndex,gObj[aIndex].Trade[fitem]);
	int b = gObjInventoryInsertItem(aIndex,gObj[aIndex].Trade[sitem]);

	if(a == 255 || b == 255)
	{
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"Insuficent space in inventory!");
		LogAdd(LOG_BOT,"[BotAlchemist](%s)(%s) Doesnt have space on inventory",gObj[aIndex].Account,gObj[aIndex].Name);
		goto Cancel;
	}

	if(failed)
	{
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"Transmutation failed!");
		LogAdd(LOG_BOT,"[BotAlchemist][Bot:%d](%s)(%s) Alchemy Failed",BotNum,gObj[aIndex].Account,gObj[aIndex].Name);
	}
	else
	{
		GCChatTargetSend(&gObj[this->bot[BotNum].index],aIndex,"Transmutation success!");
		LogAdd(LOG_BOT,"[BotAlchemist][Bot:%d](%s)(%s) Alchemy Success",BotNum,gObj[aIndex].Account,gObj[aIndex].Name);
	}

	gObj[aIndex].Money -= this->bot[BotNum].Zen;

	if(this->bot[BotNum].PCPoint > 0)
	{
		gObj[aIndex].PCPoints -= this->bot[BotNum].PCPoint;
		gObj[aIndex].PlayerExtraInfoModified = 1;
	}

	if(this->bot[BotNum].VipMoney > 0)
	{
		gObj[aIndex].VipMoney -= this->bot[BotNum].VipMoney;
		gObj[aIndex].AccountExtraInfoModified = 1;
	}

	gObjInventoryCommit(aIndex);
	gObjectManager.CharacterMakePreviewCharSet(aIndex);
	gObj[aIndex].TargetNumber = -1;
	gObj[aIndex].Interface.use = 0;
	gObj[aIndex].TradeOk = 0;
	gObj[aIndex].TradeMoney = 0;
	GCMoneySend(aIndex,gObj[aIndex].Money);
	gTrade.GCTradeResultSend(aIndex,1);
	gItemManager.GCItemListSend(aIndex);

	for(int n = 0; n < TRADE_SIZE; n++)
	{
		gObj[aIndex].Trade[n].Clear();
	}

	gObjNotifyUpdateUnionV1(&gObj[aIndex]);
	gObjNotifyUpdateUnionV2(&gObj[aIndex]);
	return 1;

Cancel:
	gObjTradeCancel(aIndex);
	gTrade.GCTradeResultSend(aIndex,3);
	
	return 0;
}

void ObjBotAlchemist::TradeOk(int aIndex)
{
	int MixNum=-1;
	int MixItem=-1;

	int number = this->GetBotIndex(gObj[aIndex].TargetNumber);

	if(number == -1)
	{			
		gObj[aIndex].Interface.state = 0;
		gObj[aIndex].Interface.type = 0;
		gObj[aIndex].TargetShopNumber = -1;
		gObj[aIndex].Transaction = 0;

		return;
	}
	this->Alchemy(aIndex,number);
}

BOOL ObjBotAlchemist::TradeOpen(int index, int nindex)
{
	if(gObjIsConnected(index) == 0)
	{
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
		
	if(this->bot[number].OnlyVip == 1 && gObj[index].AccountLevel == 0)
	{
		GCChatTargetSend(&gObj[this->bot[number].index],nindex,"Im only work for VIPs!");
		LogAdd(LOG_BOT,"[BotAlchemist][Bot:%d](%s) Account is not VIP",number,gObj[index].Account);
		return 0;
	}

	if((gObj[index].VipMoney - this->bot[number].VipMoney) < 0)
	{
		wsprintf(sbuf,"I Need %d VIPMoney!",this->bot[number].VipMoney );
		GCChatTargetSend(&gObj[this->bot[number].index],nindex,sbuf);
		LogAdd(LOG_BOT,"[BotAlchemist][Bot:%d](%s) Insuficent VIPMoney",number,gObj[index].Account);
		return 0;
	}
	if((gObj[index].PCPoints - this->bot[number].PCPoint) < 0)
	{
		wsprintf(sbuf,"I Need %d PCPoints!",this->bot[number].PCPoint );
		GCChatTargetSend(&gObj[this->bot[number].index],nindex,sbuf);
		LogAdd(LOG_BOT,"[BotAlchemist][Bot:%d](%s) Insuficent PCPoints",number,gObj[index].Account);
		return 0;
	}
	if(this->Enabled == TRUE)
	{
		if ( lpObj->Interface.use > 0 )
		{
			return 0;
		}else
		{
			for(int n = 0; n < TRADE_SIZE; n++)
			{
				lpObj->Trade[n].Clear();
			}
			memset(lpObj->TradeMap, (BYTE)-1, TRADE_SIZE );
	
			gObjInventoryTransaction(lpObj->Index);
			gTrade.GCTradeResponseSendBOT(true, lpObj->Index, lpBot->Name, 400, 0);
			gTrade.GCTradeOkButtonSend(lpObj->Index, 1);
			lpObj->Interface.state = 1;
			lpObj->Interface.use = 1;
			lpObj->Interface.type = INTERFACE_TRADE;
			lpObj->TradeMoney = 0;
			lpObj->TargetNumber = lpBot->Index;
			lpObj->Transaction = 1;

			LogAdd(LOG_BOT,"[BotAlchemist] (%s)(%s) OPEN",gObj[index].Account,gObj[index].Name);
			GCChatTargetSend(&gObj[this->bot[number].index],nindex,"Im Ready!");

			if(this->bot[number].PCPoint > 0)
			{
				wsprintf(sbuf,"I Need %d PCPoints!",this->bot[number].PCPoint );
				GCChatTargetSend(&gObj[this->bot[number].index],nindex,sbuf);
			}
			
			if(this->bot[number].VipMoney > 0)
			{
				wsprintf(sbuf,"I Need %d VIPMoney!",this->bot[number].VipMoney );
				GCChatTargetSend(&gObj[this->bot[number].index],nindex,sbuf);
			}
			
			if(this->bot[number].Zen > 0)
			{
				wsprintf(sbuf,"I Need %d Money!",this->bot[number].Zen);
				GCChatTargetSend(&gObj[this->bot[number].index],nindex,sbuf);
			}				
		}
	}
	return 1;
}

void ObjBotAlchemist::TradeCancel(int aIndex)
{
	gObjTradeCancel(aIndex);
	gTrade.GCTradeResultSend(aIndex,3);

}

#endif