#include "stdafx.h"
#include "GameServer.h"
#include "Util.h"
#include "GameMain.h"
#include "SkyEvent.h"
#include "Notice.h"
#include "Message.h"
#include "readscript.h"
#include "Monster.h"
#include "MonsterSetBase.h"
#include "MapServerManager.h"
#include "DSProtocol.h"
#include "Event.h"
#include "DSProtocol.h"
#include "ItemManager.h"
#include "PG_Custom.h"
#include "MemScript.h"
#include "ScheduleManager.h"

#if(SKY_EVENT == 1)


cSkyEvent SkyEvent;

BOOL SKYEVENT_MAP_RANGE(int Map, BYTE X)	//OK
{
	if (Map != 10)
	{
		return FALSE;
	}else
	{
		if(X >= 130)
			return TRUE;
	}
	return FALSE;
}

void cSkyEvent::Read(char * FilePath)	//OK
{
	if (FilePath == NULL || !strcmp(FilePath, ""))
	{
		ErrorMessageBox("[SkyEvent] file load error - File Name Error");
		return;
	}

	SMDFile = fopen(FilePath, "r");

	if (!SMDFile)
	{
		ErrorMessageBox("[SkyEvent] file load error - fopen In: %s",FilePath);
		return;
	}

	char sBuf[255]={0};
	char sBuf2[255]={0};
	char sBuf3[255]={0};
	
	this->Start		= 0;
	this->Enabled		= GetPrivateProfileInt("Common", "EventEnabled",0, FilePath) ;
		
	for(int iLevel = 0; iLevel < MAX_SKY_EVENT_LEVEL; iLevel++)
	{		
		this->PlayerCount[iLevel] = 0;
		wsprintf(sBuf,"Level %d",iLevel+1);

		this->Level_Min[iLevel]			= GetPrivateProfileInt(sBuf, "MinLevelReq", 1, FilePath);
		this->Level_Max[iLevel]			= GetPrivateProfileInt(sBuf, "MaxLevelReq", 1000, FilePath);
		this->ItemWinType[iLevel]		= GetPrivateProfileInt(sBuf, "ItemType", 14, FilePath);
		this->ItemWinIndex[iLevel]		= GetPrivateProfileInt(sBuf, "ItemIndex", 14, FilePath);
		this->ItemWinLevel[iLevel]		= GetPrivateProfileInt(sBuf, "ItemLevel", 0, FilePath);
		this->ItemWinDur[iLevel]		= GetPrivateProfileInt(sBuf, "ItemOpt", 0, FilePath);
		this->ItemWinLuck[iLevel]		= GetPrivateProfileInt(sBuf, "ItemLuck", 0, FilePath);
		this->ItemWinSkill[iLevel]		= GetPrivateProfileInt(sBuf, "ItemSkill", 0, FilePath);
		this->ItemWinOpt[iLevel]		= GetPrivateProfileInt(sBuf, "ItemDur", 1, FilePath);
		this->ItemWinExc[iLevel]		= GetPrivateProfileInt(sBuf, "ItemIsExc", 0, FilePath);
	}
	for(int iStage = 0 ; iStage < MAX_SKY_EVENT_STAGES; iStage++)
	{
		wsprintf(sBuf2,"ExtraExpStage%d",iStage+1);
		wsprintf(sBuf3,"MinutesStage%d",iStage+1);
		this->StageMinutes[iStage]		= GetPrivateProfileInt("Common", sBuf3, 0, FilePath);
		for(int iLevel = 0; iLevel < MAX_SKY_EVENT_LEVEL; iLevel++)
		{
			wsprintf(sBuf,"Level %d",iLevel+1);
			this->ExtraExp[iLevel][iStage] = GetPrivateProfileInt(sBuf, sBuf2, (10*(iStage+1)), FilePath);
		}
	}
	fclose(SMDFile);
	LogAdd(LOG_EVENT,"[SkyEvent] - %s file is Loaded",FilePath);
}

void cSkyEvent::Load(char* path)
{

	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}
		this->m_SkyEventTime.clear();
	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}
		
			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					SKY_EVENT_START_TIME info;

					info.Year = lpMemScript->GetNumber();

					info.Month = lpMemScript->GetAsNumber();

					info.Day = lpMemScript->GetAsNumber();

					info.DayOfWeek = lpMemScript->GetAsNumber();

					info.Hour = lpMemScript->GetAsNumber();
					
					info.Minute = lpMemScript->GetAsNumber();

					info.Second = lpMemScript->GetAsNumber();
					
					this->m_SkyEventTime.push_back(info);
					
					LogAdd(LOG_EVENT,"[SkyEvent] - %s file is Loaded ",path);
					
					}
				else 
					break;
				}
			}
		}
	
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;

}

void cSkyEvent::CheckSync() // OK
{
	if(this->m_SkyEventTime.empty() != 0)
	{
		return;
	}

	CTime ScheduleTime;

	CScheduleManager ScheduleManager;
	
	for(std::vector<SKY_EVENT_START_TIME>::iterator it=this->m_SkyEventTime.begin();it != this->m_SkyEventTime.end();it++)
	{
		ScheduleManager.AddSchedule(it->Year,it->Month,it->Day,it->Hour,it->Minute,it->Second,it->DayOfWeek);
	}

	if(ScheduleManager.GetSchedule(&ScheduleTime) == 0)
	{
		return;
	}

	this->m_RemainTime = (int)difftime(ScheduleTime.GetTime(),time(0));

	this->m_TargetTime = (int)ScheduleTime.GetTime();

	if(this->m_RemainTime <= 0)
	{
		this->SetProcState(STATE_SKY_START);
	}

	for(int n; n<1;n++)
	{
	LogAdd(LOG_EVENT,"[SkyEvent] Sync Start Time. [%d] min remain",this->m_RemainTime/60);
	}

}

void cSkyEvent::MainProc()
{
	switch(this->m_iState)
	{

	case STATE_SKY_SYNC:
		this->CheckSync();
		break;

	case STATE_SKY_START:
		this->StartEvent();
		break;
	}

}

int cSkyEvent::GetWinner(BYTE iLevel)	//OK
{
	int MaxKillMob = 0;
	int WinUser = -1;

		for(int iUser = 0; iUser < MAX_SKY_EVENT_SUB_LEVEL; iUser++)
		{
			if(this->m_UserData[iLevel][iUser].m_Index > -1)
			{
				int PlayerKillMobs = 0;
				for(int iStage = 0;iStage < MAX_SKY_EVENT_STAGES; iStage++)
				{
					PlayerKillMobs += (this->m_UserData[iLevel][iUser].KillCount[iStage] * (iStage+1));
				}
				if(PlayerKillMobs > MaxKillMob)
				{
					MaxKillMob = PlayerKillMobs;
					WinUser = iUser;
				}
			}			
		}
	return WinUser;
}

int cSkyEvent::GetPlayerSubIndex(LPOBJ lpObj, BYTE iLevel) //OK
{
	for(int iUser = 0; iUser < MAX_SKY_EVENT_SUB_LEVEL; iUser++)
	{
		int m_Index = this->m_UserData[iLevel][iUser].m_Index;
		
		if(m_Index == lpObj->Index)
		{
			return iUser;
		}
	}
	return -1;
}

int cSkyEvent::GetLevel(LPOBJ lpObj) //OK
{
	int Err = -1;
	if((this->Enabled == 1) && (this->Start == 1))
	{
		if((lpObj->Map == MAP_ICARUS) && (lpObj->X >= 130))
		{
			int X = lpObj->X;
			int Y = lpObj->Y;

			if( X >= 130 && X <= 166 )
			{
				if( Y >= 188 && Y <= 228 ) //Lvl 1
				{
					return 0;
				}else if( Y >= 128 && Y <= 170 ) //Lvl 3
				{
					return 2;
				}
			}else if( X >= 193 && X <= 228 )
			{
				if( Y >= 188 && Y <= 228 ) //Lvl 2
				{
					return 1;
				}else if( Y >= 128 && Y <= 170 ) //Lvl 4
				{
					return 3;
				}else if( Y >= 68 && Y <= 111 ) //Lvl 5
				{
					return 4;
				}
			}
		}
	}
	return Err;
}

int cSkyEvent::MonsterDie(LPOBJ lpObj)	//OK
{
	int iLevel = this->GetLevel(lpObj);
	if(iLevel > -1)
	{
		int iUser = this->GetPlayerSubIndex(lpObj,iLevel);
		if(iUser > -1)
		{
			if(this->CurrentStage > 0)
			{
				this->m_UserData[iLevel][iUser].KillCount[(this->CurrentStage-1)]++;
				return (this->ExtraExp[iLevel][(this->CurrentStage-1)]);
			}
		}else
		{
			LogAdd(LOG_EVENT,"error-L3 : [Sky Event] (%d) doesn't match the user (%d) %s",
				iLevel+1, lpObj->Index,lpObj->Name);
		}
	}
	return 1;
}

void cSkyEvent::DropWinnerItem(int iLevel,int iUser,BYTE SocketBonus,LPBYTE SocketOptions)	
{

	int iIndex = this->m_UserData[iLevel][iUser].m_Index;
	if ( OBJMAX_RANGE(iIndex) == FALSE )
	{
		return;
	}
	int iType = ::ItemGetNumberMake(this->ItemWinType[iLevel], this->ItemWinIndex[iLevel]);	

	ItemSerialCreateSend(gObj[iIndex].Index, gObj[iIndex].Map, gObj[iIndex].X,
		gObj[iIndex].Y, iType, this->ItemWinLevel[iLevel], this->ItemWinDur[iLevel], this->ItemWinSkill[iLevel], this->ItemWinLuck[iLevel], this->ItemWinOpt[iLevel], iIndex, this->ItemWinExc[iLevel],SocketBonus,0, 0);
}

void cSkyEvent::MsgStringSend(LPSTR  szMsg, BYTE type) //OK
{
	for ( int n = OBJ_STARTUSERINDEX ; n < MAX_OBJECT ; n++)
	{
		if ( gObj[n].Connected == OBJECT_ONLINE )
		{
			if (( gObj[n].Type  == OBJECT_USER ) && ( gObj[n].Map == MAP_ICARUS) && ( gObj[n].X >= 130))
			{
				gNotice.GCNoticeSend(gObj[n].Index,1,0,0,0,0,0,szMsg);
			}
		}
	}
}

void cSkyEvent::ClearAllMonsters()	//OK
{		
	for(int iStage = 0; iStage < MAX_SKY_EVENT_STAGES; iStage++)
	{
		for(int iLevel = 0; iLevel < MAX_SKY_EVENT_LEVEL; iLevel++)
		{
			for(int MobCount=0; MobCount < this->MonsterStageCount[iLevel][iStage] ;MobCount++)
			{
				if (this->m_MonsterData[iLevel][iStage][MobCount].ID >= 0)
				{
					int aIndex = this->m_MonsterData[iLevel][iStage][MobCount].ID;
					if (gObj[aIndex].Class == this->m_MonsterData[iLevel][iStage][MobCount].Number &&
						SKYEVENT_MAP_RANGE(gObj[aIndex].Map,gObj[aIndex].X)
						)
					{
						gObjDel(aIndex);
					}

					this->m_MonsterData[iLevel][iStage][MobCount].ID = -1;
				}
			}
		}
	}
}

void cSkyEvent::ClearMonsters(BYTE iLevel,BYTE iStage)	//OK
{
	if(this->Enabled == 1 && this->Start == 1)
	{
		for(int MobCount=0; MobCount < this->MonsterStageCount[iLevel][iStage] ;MobCount++)
		{
			if (this->m_MonsterData[iLevel][iStage][MobCount].ID >= 0)
			{
				int aIndex = this->m_MonsterData[iLevel][iStage][MobCount].ID;
				if (gObj[aIndex].Class == this->m_MonsterData[iLevel][iStage][MobCount].Number &&
					SKYEVENT_MAP_RANGE(gObj[aIndex].Map,gObj[aIndex].X)
					)
				{
					gObjDel(aIndex);
				}

				this->m_MonsterData[iLevel][iStage][MobCount].ID = -1;
			}
		}
	}
}

void cSkyEvent::SetMonsters(BYTE iLevel,BYTE iStage)	//OK
{
	if(this->Enabled == 1 && this->Start == 1)
	{
		for(int MobCount=0; MobCount < this->MonsterStageCount[iLevel][iStage] ;MobCount++)
		{			
			int MobID = gObjAddMonster(gMonsterSetBase.m_Mp[this->m_MonsterData[iLevel][iStage][MobCount].Pos].Map);
			if(MobID >= 0)
			{
				this->m_MonsterData[iLevel][iStage][MobCount].ID = MobID;
				SetPosMonsterSkyEvent(MobID, this->m_MonsterData[iLevel][iStage][MobCount].Pos);
				gObjSetMonster(MobID, gMonsterSetBase.m_Mp[this->m_MonsterData[iLevel][iStage][MobCount].Pos].Type);
			}
		}
	}
}

void cSkyEvent::ReadMonsters(char * FilePath)	//OK
{
	MONSTER_SET_BASE_INFO info;

	if(this->Enabled == 1)
	{
		int Token;
		int iLevel;
		info.MonsterClass;
		int X;
		int Y;
		int Count;

	if (FilePath == NULL || !strcmp(FilePath, ""))
	{
		ErrorMessageBox("[SkyEvent] file load error - File Name Error");
		return;
	}

	SMDFile = fopen(FilePath, "r");

	if (!SMDFile)
	{
		ErrorMessageBox("[SkyEvent] file load error - fopen In: %s",FilePath);
		return;
	}

		for(int Stages = 0; Stages < MAX_SKY_EVENT_STAGES; Stages++)
		{
			for(int Level = 0; Level < MAX_SKY_EVENT_LEVEL; Level++)
			{
				this->MonsterStageCount[Level][Stages] = 0;
			}
		}

		for(int iL = 0; iL < MAX_SKY_EVENT_LEVEL; iL++)
		{
			for (int iS = 0; iS < MAX_SKY_EVENT_STAGES; iS++)
			{
				for (int iM = 0; iM <MAX_SKY_EVENT_STAGE_MOB_COUNT; iM++)
				{
					this->m_MonsterData[iL][iS][iM].ID = -1;
					this->m_MonsterData[iL][iS][iM].Pos = -1;
					this->m_MonsterData[iL][iS][iM].Number = -1;
				}
			}
		}

		while ( true )
		{
			
			for(int iStages = 1; iStages < (MAX_SKY_EVENT_STAGES+1); iStages++)
			{
				int iType = GetToken();
				while(true)
				{
					Token = GetToken();
					if ( strcmp("end", TokenString) == 0 )
					{
						break;
					}
					iLevel = TokenNumber;

					Token = GetToken();
					info.MonsterClass = TokenNumber;

					Token = GetToken();
					X = TokenNumber;

					Token = GetToken();
					Y = TokenNumber;

					Token = GetToken();
					Count = TokenNumber;

					for(int i=0;i<Count;i++)
					{
						int MobCount = this->MonsterStageCount[(iLevel-1)][(iStages-1)];

						if (iLevel <= MAX_SKY_EVENT_LEVEL &&
							iStages <= MAX_SKY_EVENT_STAGES &&
							MobCount < MAX_SKY_EVENT_STAGE_MOB_COUNT)
						{
							int MobPos = gObjMonsterAdd(info.MonsterClass,10,X,Y);
							if(MobPos >= 0)
							{
								this->m_MonsterData[(iLevel-1)][(iStages-1)][MobCount].ID = -1;
								this->m_MonsterData[(iLevel-1)][(iStages-1)][MobCount].Pos = MobPos;
								this->m_MonsterData[(iLevel-1)][(iStages-1)][MobCount].Number = info.MonsterClass;
								this->MonsterStageCount[(iLevel-1)][(iStages-1)]++;

							} else {
								LogAdd(LOG_EVENT,"[SkyEvent] - Cant add monster to Lvl:%d, Stage:%d, Count:%d [ID:%d:,X:%d,Y:%d] Pos:%d",
									iLevel,iStages,MobCount,info.MonsterClass,X,Y,MobPos);
							}
						} else {
							LogAdd(LOG_EVENT,"[SkyEvent][Overflow] - Cant add monster to Lvl:%d, Stage:%d, Count:%d [ID:%d:,X:%d,Y:%d]",
								iLevel,iStages,MobCount,info.MonsterClass,X,Y);
						}
					}
				}
			}
			break;
		}
			
		fclose(SMDFile);
		LogAdd(LOG_EVENT,"[SkyEvent] - %s file is Loaded",FilePath);
		
	}
}

void cSkyEvent::StartEvent()	//OK
{
	if((this->Start == 0) && (this->Enabled == 1))
		_beginthread( cSkyEvent__InsideTrigger, 0, NULL  );
}

void cSkyEvent__InsideTrigger(void * lpParam)	//OK
{
	SkyEvent.Start = 1;
	SkyEvent.NPCEnabled = TRUE;
	char sBuf[1024] = {0};
	SkyEvent.CurrentStage = 0;
	BYTE ActiveLevelsSum = 0;

	for(int i=5;i>0;i--) 
	{
		LogAdd(LOG_EVENT, "[Sky Event] will close after %d minute(s)", i);
		gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(534),i);
		Sleep(60000);
	}

	SkyEvent.NPCEnabled = FALSE;
	LogAdd(LOG_EVENT,"[Sky Event] Event entrance is closed!");
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(535));
	
	for(int iStages = 0; iStages < MAX_SKY_EVENT_STAGES; iStages++)
	{
		SkyEvent.CurrentStage++;
		ActiveLevelsSum = 0;
		for(int iLevel = 0; iLevel < MAX_SKY_EVENT_LEVEL; iLevel++)
		{
				int ActiveUsers = SkyEvent.CheckUsersAlive(iLevel);
				if(ActiveUsers > 0)
				{
					if(iLevel > 0 && iStages > 0)
						SkyEvent.ClearMonsters((iLevel-1),(iStages-1));	

					SkyEvent.SetMonsters(iLevel,iStages);
					ActiveLevelsSum++;
				}
				else
				{			
					if(iLevel > 0 && iStages > 0)
						SkyEvent.ClearMonsters((iLevel-1),(iStages-1));	
					SkyEvent.ClearLevelData(iLevel);
				}

			//Send Experience Information to Users
			SkyEvent.SendUserExpInfo(iLevel);
		}
		SkyEvent.MsgStringSend("[SkyEvent] Stage Experience has changed!",0x01);

		if(ActiveLevelsSum > 0)
			Sleep(SkyEvent.StageMinutes[iStages] * 60000);
		else
			break;
	}

	SkyEvent.ClearAllMonsters();

	for(int iLevel = 0; iLevel < MAX_SKY_EVENT_LEVEL; iLevel++)
	{
		int ActiveUsers = SkyEvent.CheckUsersAlive(iLevel);
		if(ActiveUsers > 0)
		{
			int WinUser = SkyEvent.GetWinner(iLevel);
			if(WinUser > -1)
			{
				SkyEvent.DropWinnerItem(iLevel,WinUser,0,0);
			}
		}
	}

	LogAdd(LOG_EVENT,"[Sky Event] Event End");
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(536));

	for(int i=3;i>0;i--)
	{
		wsprintf(sBuf, "%d Seconds to warp to Devias", i*10);
		SkyEvent.MsgStringSend(sBuf,0x01);
		Sleep(10000);
	}
	
	SkyEvent.ExitPlayers();

	for(int iLevel = 0; iLevel < MAX_SKY_EVENT_LEVEL; iLevel++)
	{
		SkyEvent.ClearLevelData(iLevel);
	}

	SkyEvent.Start = 0;
	SkyEvent.SetProcState(STATE_SKY_SYNC);
	
	_endthread();
}

void cSkyEvent::ExitPlayers()	//OK
{
	for ( int n = OBJ_STARTUSERINDEX ; n < MAX_OBJECT ; n++)
	{
		if ( gObj[n].Connected == OBJECT_ONLINE )
		{
			if (( gObj[n].Type  == OBJECT_USER ) && ( gObj[n].Map == MAP_ICARUS) && ( gObj[n].X >= 130))
			{
				this->Teleport(&gObj[n],255);
			}
		}
	}
}

void cSkyEvent::SendUserExpInfo(BYTE iLevel)	//OK
{
	for(int iUser = 0; iUser < MAX_SKY_EVENT_SUB_LEVEL; iUser++)
	{
		int m_Index = this->m_UserData[iLevel][iUser].m_Index;
		if(m_Index != -1)
		{
			if ( gObj[m_Index].Connected >= OBJECT_CONNECTED )
			{
				if (this->m_UserData[iLevel][iUser].DBNumber == gObj[m_Index].DBNumber)
				{
					if((gObj[this->m_UserData[iLevel][iUser].m_Index].Map == MAP_ICARUS) && (gObj[this->m_UserData[iLevel][iUser].m_Index].X >= 130)) 
					{
						//gObjGetExtraExperienceInfoMsg(this->m_UserData[iLevel][iUser].m_Index);
						
					}
				}
			}
		}
	}
}

int cSkyEvent::CheckUsersAlive(BYTE iLevel)	//OK
{
	int UserCount = 0;
	for(int iUser = 0; iUser < MAX_SKY_EVENT_SUB_LEVEL; iUser++)
	{
		int m_Index = this->m_UserData[iLevel][iUser].m_Index;
		if(m_Index != -1)
		{
			if ( gObj[m_Index].Connected >= OBJECT_CONNECTED )
			{
				//if (strcmp(this->m_UserData[iLevel][iUser].Name,gObj[m_Index].Name))
				if (this->m_UserData[iLevel][iUser].DBNumber != gObj[m_Index].DBNumber)
				{
					this->RemoveUser(iLevel,iUser);
				}else
				{
					if((gObj[this->m_UserData[iLevel][iUser].m_Index].Map == MAP_ICARUS) && (gObj[this->m_UserData[iLevel][iUser].m_Index].X >= 130)) 
					{
						UserCount++;
					}
					else 
					{
						this->RemoveUser(iLevel,iUser);
					}
				}
			}else
			{
				this->RemoveUser(iLevel,iUser);
			}
		}
	}
	return UserCount;
}

void cSkyEvent::RemoveUser(BYTE iLevel,int iUser)	//OK
{
	this->m_UserData[iLevel][iUser].m_Index = -1;
	this->m_UserData[iLevel][iUser].DBNumber = -1;
	for(int iStages = 0; iStages < MAX_SKY_EVENT_STAGES; iStages++)
	{
		this->m_UserData[iLevel][iUser].KillCount[iStages] = 0;		
	}
}

void cSkyEvent::ClearLevelData(BYTE iLevel)	//OK
{
	this->PlayerCount[iLevel] = 0;

	for(int iUser = 0; iUser < MAX_SKY_EVENT_SUB_LEVEL; iUser++)
	{
		this->m_UserData[iLevel][iUser].m_Index = -1;	
		this->m_UserData[iLevel][iUser].DBNumber = -1;			
		for(int iStages = 0; iStages < MAX_SKY_EVENT_STAGES; iStages++)
		{
			this->m_UserData[iLevel][iUser].KillCount[iStages] = 0;		
		}
	}
}

void cSkyEvent::Teleport(LPOBJ lpObj, BYTE iLevel)	//OK
{
	int rNum = rand()%5;
	switch(iLevel)
	{
		case 0:
		{
			gObjTeleport(lpObj->Index,10,148 + rNum,209 + rNum);	
		}break;

		case 1:
		{
			gObjTeleport(lpObj->Index,10,210 + rNum,209 + rNum);	
		}break;

		case 2:
		{
			gObjTeleport(lpObj->Index,10,147 + rNum,148 + rNum);	
		}break;
		
		case 3:
		{
			gObjTeleport(lpObj->Index,10,211 + rNum,148 + rNum);	
		}break;
		
		case 4:
		{
			gObjTeleport(lpObj->Index,10,211 + rNum,89 + rNum);	
		}break;
		case 255:
		{			
			gObjMoveGate(lpObj->Index, 22);
		}break;
	}
}

int cSkyEvent::CheckEnterLevel(int iIndex)	// RET : [-1:Error][0-4:Success] //OK
{
	if ( OBJMAX_RANGE(iIndex) == FALSE )
	{
		return -1;
	}

	if ( gObj[iIndex].Type != OBJECT_USER || gObj[iIndex].Connected <= OBJECT_LOGGED )
	{
		return -1;
	}

	if(gObjIsNewClass(&gObj[iIndex]) == 1)
	{
		return (MAX_SKY_EVENT_LEVEL-1);
	}

	int pLevel = gObj[iIndex].Level;

	for(int iLevel = 0; iLevel < MAX_SKY_EVENT_LEVEL; iLevel++)
	{
		if(pLevel >= Level_Min[iLevel] && pLevel <= Level_Max[iLevel])
			return iLevel;
	
	LogAdd(LOG_EVENT,"[SkyEvent] Level %d",iLevel+1);
	}
	return -1;
}

BOOL cSkyEvent::NpcTalk(LPOBJ lpNpc, LPOBJ lpObj)	//OK
{
	int iIndex = lpObj->Index;

	if((this->Enabled == 1) && (this->Start == 1) && (this->NPCEnabled == 1))
	{
		char sBuf[255]={0};
		int iLevel = this->CheckEnterLevel(iIndex);
		if(iLevel > -1)
		{
			if(this->PlayerCount[iLevel] < MAX_SKY_EVENT_SUB_LEVEL)
			{
				if(DeleteItemByLevel(iIndex,0x1C33,iLevel+1) == 1)
				{
					lpObj->Interface.use = 0;
					this->AddUser(iLevel,iIndex,lpObj);
					this->Teleport(&gObj[iIndex],iLevel);
					return TRUE;
				}else
				{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(539), ItemAttribute[0x1C33].Name, iLevel+1, iLevel+1);
				}
			}else
			{
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(540), iLevel+1);

			}
		}
	}
	return FALSE;
}

void cSkyEvent::AddUser(BYTE iLevel,int iIndex,LPOBJ lpObj)	//OK
{
	int iUser = this->PlayerCount[iLevel];
	this->m_UserData[iLevel][iUser].m_Index = iIndex;	
	this->m_UserData[iLevel][iUser].DBNumber = gObj[iIndex].DBNumber;	
	for(int iStages = 0; iStages < MAX_SKY_EVENT_STAGES; iStages++)
	{
		this->m_UserData[iLevel][iUser].KillCount[iStages] = 0;		
	}
	this->PlayerCount[iLevel]++;
	
	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"[SkyEvent] TotalUser %d",this->PlayerCount[iLevel]);		
	LogAdd(LOG_EVENT,"[SkyEvent]AddUser TotalUser %d",this->PlayerCount[iLevel]);
}

#endif