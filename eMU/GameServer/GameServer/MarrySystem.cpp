#include "stdafx.h"
#if (MARRY_SYSTEM == 1)
#include "MarrySystem.h"
#include "GameServer.h"
#include "GameMain.h"
#include "BloodCastle.h"
#include "ChaosCastle.h"
#include "DevilSquare.h"
#include "IllusionTemple.h"
#include "ImperialGuardian.h"
#include "DoubleGoer.h"
#include "readscript.h"
#include "Message.h"
#include "Notice.h"
#include "DSProtocol.h"
#include "MapServerManager.h"
#include "Util.h"
#include "PG_Custom.h"
#include "User.h"

MarrySystem Marry;

void MarrySystem::SendInfo(int aIndex)
{
	if(OBJECT_RANGE(aIndex) == 0)
	{ 
		return;
	}

	if(this->EnableMarry == true)
	{
		LPOBJ lpObj = &gObj[aIndex];

		SDHP_RECVMARRY pInfo;

		PHeadSubSetB((LPBYTE)&pInfo, 0xFA,0x10, sizeof(pInfo));
		memcpy(pInfo.Name,lpObj->MarriedName,sizeof(pInfo.Name));


		pInfo.Divorce = this->ZenDivorce;
		pInfo.ForceDivorce = this->ZenForceDivorce;
		pInfo.TraceCost = 0;
		pInfo.Map = this->MapPos;
		pInfo.Xpos1 = this->rXPos1;
		pInfo.Ypos1 = this->rYPos1;
		pInfo.Xpos2 = this->rXPos2;
		pInfo.Ypos2 = this->rYPos2;

		DataSend(lpObj->Index, (LPBYTE)&pInfo, sizeof(pInfo));
	}

}

int MarrySystem::GetSex(LPOBJ lpObj)	//OK
{
	if( lpObj->Class == CLASS_SU || lpObj->Class == CLASS_FE )
	{
		return 0;
	}else
	{
		return 1;
	}
}

int MarrySystem::GetPos(LPOBJ lpObj)	//OK
{
	BYTE Map = lpObj->Map;
	BYTE X = lpObj->X;
	BYTE Y = lpObj->Y;

	if( ((X >= rXPos1) && (X <= rXPos2) ) && ((Y >= rYPos1) && (Y <= rYPos2)) && (Map==MapPos))
	{
		return 1;
	}
	return 0;
}

void MarrySystem::Propose(LPOBJ lpObj, char * MarryHusbandWife)	//OK
{
	char sBuf[255]={0};

	if(lpObj->Married == 0)
	{
		int WhoID = gObjGetIndex(MarryHusbandWife);
		
		if(WhoID >= 0)
		{
			if(gObj[WhoID].Married == 0)
			{
				if( this->GetPos(lpObj) > 0 && this->GetPos(&gObj[WhoID]) > 0 )
				{
					int MySex = GetSex(lpObj);
					int WhoSex = GetSex(&gObj[WhoID]);
					if(MySex != WhoSex)
					{
						gObj[WhoID].MarrySeconds = 60;
						//wsprintf(gObj[WhoID].MarryTarget,"%s",lpObj->Name);
						gNotice.GCNoticeSend(gObj[WhoID].Index,1,0,0,0,0,0,"Do you want accept marry with %s?",lpObj->Name);

						lpObj->MarrySeconds = 60;
						//wsprintf(lpObj->MarryTarget,"%s",gObj[WhoID].Name);
						gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Do you want accept marry with %s?",gObj[WhoID].Name);

						//wsprintf(sBuf, gMessage.GetMessage(549),lpObj->Name);
						//GCServerMsgStringSend (sBuf,WhoID,0x00 ) ;

					}else
					{				
						//wsprintf(sBuf, gMessage.GetMessage(550));
						gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You cant marry with some one with the same sex!");
						//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
					}
				}else
				{
					//wsprintf(sBuf, gMessage.GetMessage(551));
					gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You cant marry in that position!");
					//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
				}
			}else
			{
				//wsprintf(sBuf, gMessage.GetMessage(552),gObj[WhoID].Name);
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"%s is already married",gObj[WhoID].Name);
				//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
			}
		}else
		{
			//wsprintf(sBuf, gMessage.GetMessage(553),MarryHusbandWife);
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Character %s doesnt exist or is disconnected",MarryHusbandWife);
			//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;		
		}
	}else
	{
		//wsprintf(sBuf, gMessage.GetMessage(554));
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You are already married!");
		//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
	}
}

void MarrySystem::Accept(LPOBJ lpObj)
{
	char sBuf[255]={0};
	int WhoID = gObjGetIndex(lpObj->MarryTarget);
	LogAdd(LOG_BLUE,"MARRY TARGET %s",lpObj->MarryTarget);
	if(WhoID >= 0)
	{
		int MePos = this->GetPos(lpObj);
		int WhoPos = this->GetPos(&gObj[WhoID]);
		
		if (lpObj->MarrySeconds<=0) 
		{
			//GCServerMsgStringSend (gMessage.GetMessage(555),lpObj->Index,0x01) ;
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Time for answer is finished!");
			return;
		}
		
		if ((MePos == 0) || (WhoPos == 0))
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You cant marry in that position!");
			//GCServerMsgStringSend (gMessage.GetMessage(556),lpObj->Index,0x01) ;
			return;
		}

		/*if (lpObj->PlayerExtraInfoReceived != 1 || gObj[WhoID].PlayerExtraInfoReceived != 1)
		{
			GCServerMsgStringSend ("ERROR: Please relogin!",lpObj->Index,0x01 ) ;
			LogAdd(LOG_BLUE,"ERROR: GENS Info [%s][%s] Line: %d", lpObj->Account, lpObj->Name, __LINE__);
			return;
		}*/

		if (lpObj->Married == 0)
		{
			lpObj->PlayerExtraInfoModified = 1;
			lpObj->Married = 1;
			lpObj->MarrySeconds = 0;
			//wsprintf(lpObj->MarriedName,"%s",lpObj->MarryTarget);
			gNotice.GCNoticeSend(gObj[WhoID].Index,1,0,0,0,0,0,"Congratulations you are married with %s",lpObj->MarryTarget);
			memset( lpObj->MarryTarget, 0, MAX_ACCOUNT_LEN);

			//The Other
			gObj[WhoID].PlayerExtraInfoModified = 1;
			gObj[WhoID].Married = 1;
			gObj[WhoID].MarrySeconds = 0;
			//wsprintf(gObj[WhoID].MarriedName,"%s",gObj[WhoID].MarryTarget);
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Congratulations you are married with %s",gObj[WhoID].MarryTarget);
			memset(gObj[WhoID].MarryTarget, 0, MAX_ACCOUNT_LEN);

			GCFireworksSend(lpObj,this->rXPos1,this->rYPos1);
			GCFireworksSend(lpObj,this->rXPos2,this->rYPos2);

			//wsprintf(sBuf, gMessage.GetMessage(557),lpObj->Name);
			//GCServerMsgStringSend (sBuf,gObj[WhoID].Index,0x01 ) ;

			//wsprintf(sBuf, gMessage.GetMessage(558),gObj[WhoID].Name);
			gNotice.GCNoticeSendToAll(0,0,0,0,0,0,"Congratulations To %s And %s - Newly WED!",gObj[WhoID].Name,lpObj->Name);
			//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;

			//gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(557),gObj[WhoID].Name,lpObj->Name);
			this->SendInfo(WhoID);
			this->SendInfo(lpObj->Index);
		} else {
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You are already married!");
			//GCServerMsgStringSend(gMessage.GetMessage(559),lpObj->Index,0x01 ) ;
			return;
		}
	}else
	{
		//wsprintf(sBuf, gMessage.GetMessage(560),lpObj->MarryTarget);
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Character %s doesnt exist or is disconnected",lpObj->MarryTarget);
		//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;		
	}
}

void MarrySystem::Trace(LPOBJ lpObj)	//OK
{
	char sBuf[255]={0};

	if(lpObj->Married==1)
	{
		int WhoID = gObjGetIndex(lpObj->MarriedName);
		int WhoMap = gObj[WhoID].Map;

		if(WhoID >= 0)
		{
			if(WhoMap == MAP_ICARUS)
			{
				if(!(lpObj->Inventory[8].m_Index == GET_ITEM(13,3)
					|| lpObj->Inventory[7].m_Index == GET_ITEM(13,30)
					|| (lpObj->Inventory[7].m_Index >= GET_ITEM(12,0)
						&& lpObj->Inventory[7].m_Index <=GET_ITEM(12,6))
					|| (lpObj->Inventory[7].m_Index >= GET_ITEM(12,130)
						&& lpObj->Inventory[7].m_Index <=GET_ITEM(12,135))
					|| (lpObj->Inventory[7].m_Index >= GET_ITEM(12,36)
						&& lpObj->Inventory[7].m_Index <=GET_ITEM(12,43))
					|| (lpObj->Inventory[7].m_Index >= GET_ITEM(12,49)
						&& lpObj->Inventory[7].m_Index <=GET_ITEM(12,50))
#if (CRYSTAL_EDITION == 1)
					|| (lpObj->pInventory[7].m_Type >= GET_ITEM(12,200) && lpObj->pInventory[7].m_Type <= GET_ITEM(12,254))
#endif
						)
					)
				{
					gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You need wings to teleport to this map");
					//GCServerMsgStringSend(gMessage.GetMessage(570),lpObj->Index,1);
					return;
				}
			}

			if(WhoMap == MAP_KANTURU3)	//BOSS
			{
				if(!(lpObj->Inventory[8].m_Index == GET_ITEM(13,3)
					|| lpObj->Inventory[7].m_Index == GET_ITEM(13,30)
					|| (lpObj->Inventory[7].m_Index >= GET_ITEM(12,0)
						&& lpObj->Inventory[7].m_Index <=GET_ITEM(12,6))
					|| (lpObj->Inventory[7].m_Index >= GET_ITEM(12,130)
						&& lpObj->Inventory[7].m_Index <=GET_ITEM(12,135))
					|| (lpObj->Inventory[7].m_Index >= GET_ITEM(12,36)
						&& lpObj->Inventory[7].m_Index <=GET_ITEM(12,43))
					|| (lpObj->Inventory[7].m_Index >= GET_ITEM(12,49)
						&& lpObj->Inventory[7].m_Index <=GET_ITEM(12,50))
#if (CRYSTAL_EDITION == 1)
					|| (lpObj->pInventory[7].m_Type >= GET_ITEM(12,200) && lpObj->pInventory[7].m_Type <= GET_ITEM(12,254))
#endif
						)
					)
				{
					gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You need wings to teleport to this map");
					//GCServerMsgStringSend(gMessage.GetMessage(570),lpObj->Index,1);
					return;
				}
			}

			if(lpObj->PKLevel >= 5)
			{
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Pk lvl can not teleport");
				//GCServerMsgStringSend(gMessage.GetMessage(571),lpObj->Index,1);
				return;
			}

			if( (WhoMap != 30) && 
				(BC_MAP_RANGE(WhoMap) == 0) && 
				(CC_MAP_RANGE(WhoMap) == 0) && 
				(IT_MAP_RANGE(WhoMap) == 0) && 
				(DS_MAP_RANGE(WhoMap) == 0) && 
				(KALIMA_MAP_RANGE(WhoMap) == 0)
#if (PACK_EDITION>=2)
				&& (IMPERIALGUARDIAN_MAP_RANGE(WhoMap) == 0) 
				&& (SKYEVENT_MAP_RANGE(WhoMap,gObj[WhoID].X) == 0) 
#endif 
#if (PACK_EDITION>=3)
				&& (DG_MAP_RANGE(WhoMap) == 0)
#endif
				&& (WhoMap != 64))
			{
#if (PACK_EDITION>=3)
				if(GensCloseMap.Enabled == 1)
				{
					if(GensCloseMap.CheckMap2(WhoID, WhoMap) == true || GensCloseMap.CheckMap2(lpObj->m_Index, lpObj->MapNumber) == true)
					{
						GCServerMsgStringSend(lMsg.Get(MSGGET(14, 148)),lpObj->m_Index, 0x01);
						return;
					}
				}
#endif
				if(lpObj->Level < this->Maps[WhoMap])
				{
					//char buf[255]={0};
					//wsprintf(buf,gMessage.GetMessage(572),this->Maps[WhoMap]);
					//GCServerMsgStringSend(buf,lpObj->Index, 0x01);
					gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You need level %s for teleporting",this->Maps[WhoMap]);// SI CRACHEA ES AKA EL RPBOELA TIENE LA S Y CREO QUE VA LA D
					return;
				}

				int x = rand()%4+1;
				int y = rand()%3+1;
				x+=gObj[WhoID].X;
				y+=gObj[WhoID].Y;
				gObjTeleport(lpObj->Index, gObj[WhoID].Map, x, y);
			}else
			{
				//wsprintf(sBuf, gMessage.GetMessage(561),lpObj->MarriedName);
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"%s is inside of one event, you cant warp there!",lpObj->MarriedName);
				//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
			}
		}else
		{
			//wsprintf(sBuf, gMessage.GetMessage(562),lpObj->MarriedName);
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"%s is disconnected",lpObj->MarriedName);
			//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
		}
	}
}

void MarrySystem::Divorce(LPOBJ lpObj)
{
	char sBuf[255]={0};

	if(lpObj->Married == 1)
	{
		int WhoID = gObjGetIndex(lpObj->MarriedName);
	
		if(WhoID >= 0)
		{
			int MeZen = (lpObj->Money - this->ZenDivorce);
			
			if(MeZen >= 0)
			{
				lpObj->Money = MeZen;
				GCMoneySend(lpObj->Index,lpObj->Money);				
				gObj[WhoID].Money += this->ZenDivorce;
				GCMoneySend(gObj[WhoID].Index,lpObj->Money);

				lpObj->PlayerExtraInfoModified = 1;
				lpObj->Married = 0;
				lpObj->MarrySeconds = 0;
				memset( lpObj->MarryTarget, 0, MAX_ACCOUNT_LEN);
				memset( lpObj->MarriedName, 0, MAX_ACCOUNT_LEN);
				
				gObj[WhoID].PlayerExtraInfoModified = 1;
				gObj[WhoID].Married = 0;
				gObj[WhoID].MarrySeconds = 0;
				memset( gObj[WhoID].MarryTarget, 0, MAX_ACCOUNT_LEN);
				memset( gObj[WhoID].MarriedName, 0, MAX_ACCOUNT_LEN);

				//wsprintf(sBuf, gMessage.GetMessage(563),ZenDivorce);
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You Get Divorced, your Zen is decreased by %d",ZenDivorce);
				//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;

				//wsprintf(sBuf,gMessage.GetMessage(564),ZenDivorce);
				gNotice.GCNoticeSend(gObj[WhoID].Index,1,0,0,0,0,0,"You Get Divorced, your Zen is increase by %d",ZenDivorce);
				//GCServerMsgStringSend (sBuf,gObj[WhoID].Index,0x01 ) ;

				this->SendInfo(WhoID);
				this->SendInfo(lpObj->Index);
			}else
			{
				//wsprintf(sBuf,gMessage.GetMessage(565),this->ZenDivorce);
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You need %d zen to divorce",ZenDivorce);
				//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
			}
		}else
		{			
			//wsprintf(sBuf, gMessage.GetMessage(562),lpObj->MarriedName);
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"%s is disconnected",lpObj->MarriedName);
			//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
		}
	}else
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You are not married!");
		//GCServerMsgStringSend (gMessage.GetMessage(566),lpObj->Index,0x01 ) ;
	}
}

void MarrySystem::ForceDivorce(LPOBJ lpObj)
{
	char sBuf[255]={0};

	if(lpObj->Married == 1)
	{
		int MeZen = (lpObj->Money - this->ZenForceDivorce);

		if(MeZen >= 0)
		{
			int WhoID = gObjGetIndex(lpObj->MarriedName);
			
			if(WhoID >= 0)
			{
				//wsprintf(sBuf, gMessage.GetMessage(567),lpObj->MarriedName);
				//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"%s is online please use /divorce command",lpObj->MarriedName);
			}else
			{
				lpObj->Money = MeZen;
				GCMoneySend(lpObj->Index,lpObj->Money);		

//				JGSetPlayerMarryDivorseInfo(lpObj->MarriedName); //probado

				lpObj->PlayerExtraInfoModified = 1;
				lpObj->Married = 0;
				lpObj->MarrySeconds = 0;
				memset( lpObj->MarryTarget, 0, MAX_ACCOUNT_LEN);
				memset( lpObj->MarriedName, 0, MAX_ACCOUNT_LEN);
				this->SendInfo(lpObj->Index);
			}
		}else
		{
			//wsprintf(sBuf, gMessage.GetMessage(568),this->ZenForceDivorce);
			//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You need %d zen to force the divorce",this->ZenForceDivorce);
		}
	}else
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You are not married!");
		//GCServerMsgStringSend (gMessage.GetMessage(566),lpObj->Index,0x01 ) ;
	}
}

void MarrySystem::Read(char * FilePath)
{
	this->EnableMarry			= GetPrivateProfileInt("Marry", "MarryEnabled", 1, FilePath);
	this->MapPos				= GetPrivateProfileInt("Marry", "MarryMap", 2, FilePath);

	this->rXPos1			 	= GetPrivateProfileInt("Marry", "MarryX1", 13, FilePath);
	this->rYPos1	 			= GetPrivateProfileInt("Marry", "MarryY1", 25, FilePath);
	this->rXPos2			 	= GetPrivateProfileInt("Marry", "MarryX2", 13, FilePath);
	this->rYPos2			 	= GetPrivateProfileInt("Marry", "MarryY2", 26, FilePath);

	this->ZenDivorce	 		= GetPrivateProfileInt("Marry", "MarryZenDivorce", 2000000, FilePath);
	this->ZenForceDivorce		= GetPrivateProfileInt("Marry", "MarryZenForceDivorce", 20000000, FilePath);
	this->Shop					= GetPrivateProfileInt("Marry", "MarryIsShop379OnlyForMarried", 0, FilePath);

	LogAdd(LOG_BLUE,"[Marry System] [Endable %d] [Map %d] ",this->EnableMarry,this->MapPos);
	LogAdd(LOG_BLUE,"[Marry System] [Poss X 1 %d] [Poss Y 1 %d] ",this->rXPos1,this->rYPos1);
	LogAdd(LOG_BLUE,"[Marry System] [Poss X 2 %d] [Poss Y 2 %d] ",this->rXPos2,this->rYPos2);
	
	char etiqueta[8] = {0};
    for(int n=0;n<MAX_MAP;n++) 
	{
		wsprintf(etiqueta,"Map%02d", n);
		this->Maps[n] = GetPrivateProfileInt("TraceMinLevel", etiqueta,0, FilePath) ;
	}

	LogAdd(LOG_BLUE,"[Marry System] - %s file is Loaded",FilePath);
}

int MarrySystem::HusWifeOnline(LPOBJ lpObj)
{
	char sBuf[255]={0};

	if(lpObj->Married == 1)
	{
		int WhoID = gObjGetIndex(lpObj->MarriedName);
		
		if(WhoID >= 0)
		{
			return 2;
		}else
		{
			//wsprintf(sBuf, gMessage.GetMessage(562),lpObj->MarriedName);
			//GCServerMsgStringSend (sBuf,lpObj->Index,0x01 ) ;
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"%s is disconnected",lpObj->MarriedName);
			return 1;
		}
	}else
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You are not married!");
		//GCServerMsgStringSend (gMessage.GetMessage(566),lpObj->Index,0x01 ) ;
		return 0;
	}
}

void MarrySystem::CommandCore(LPOBJ lpObj,BYTE Command)
{
	if(this->EnableMarry == 1)
	{
	
		if(CmdMarryAF > 0)
		{
			if(lpObj->aFloodMarryCmd != 0)
			{
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You must wait before use marry command again");
				//GCServerMsgStringSend("You must wait before use marry command again", lpObj->Index, 1);
				return;	
			}
			lpObj->aFloodMarryCmd = CmdMarryAF;
		}

		switch(Command)
		{
			case 0:
			{
				char sbuff[1024]={0};
				if(lpObj->Married == 1)
				{
				//	wsprintf(sbuff, gMessage.GetMessage(569),lpObj->MarriedName);
					gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You are married with %s",lpObj->MarriedName);
				}else
				{
					gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You are not married!");
					//wsprintf(sbuff, gMessage.GetMessage(566));
				}
				//GCServerMsgStringSend (sbuff,lpObj->Index,0x01 ) ;
			}break;
			case 1:
			{
				this->Accept(lpObj);
			}break;
			case 2:
			{
				this->Divorce(lpObj);
			}break;
			case 3:
			{
				this->ForceDivorce(lpObj);
			}break;
			case 4:
			{
				this->Trace(lpObj);
			}break;
		}
	}
}

#endif