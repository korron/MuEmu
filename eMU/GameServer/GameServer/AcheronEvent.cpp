#include "stdafx.h"
#include "AcheronEvent.h"
#include "GameMain.h"
#include "ReadScript.h"
#include "MapServerManager.h"
#include "DSProtocol.h"
#include "Util.h"
#include "Map.h"
#include "Notice.h"
#include "Message.h"
#include "Monster.h"
#include "ItemBagManager.h"
#include "MonsterSetBase.h"

#if(ACHERON_GUARDIAN == 1)

CAcheronGuardianEvent g_AcheronGuardianEvent;

CAcheronGuardianEvent::CAcheronGuardianEvent()
{
	this->m_iREMAIN_MSEC = 0; // 0
	this->m_iTICK_COUNT = 0;
	this->m_iState = 1;
	this->m_bAE_PLAY_START = 0;
	this->m_bAEInitState = 0;
	this->m_bWindowClose = 0;
}

CAcheronGuardianEvent::~CAcheronGuardianEvent()
{
}

int CAcheronGuardianEvent::LoadScriptAcheronEvent(LPSTR lpszFileName)
{
	if (lpszFileName == NULL || !strcmp(lpszFileName, ""))
	{
		ErrorMessageBox("[AcheronEvent] file load error - File Name Error");
		return 0;
	}

	SMDFile = fopen(lpszFileName, "r");

	if (!SMDFile)
	{
		ErrorMessageBox("[AcheronEvent] file load error - fopen In: %s",lpszFileName);
		return 0;
	}

	int type = -1;
	int iDayOfWeekCycleCnt = 0;

	while (true)
	{
		SMDToken Token = GetToken();

		if (Token == END)
		{
			break;
		}

		type = TokenNumber;

		if (Token == NUMBER)
		{
			if (type == 1)
			{
				while (true)
				{
					Token = GetToken();

					if (!strcmp("end", TokenString))
					{
						break;
					}

					this->m_iDayOfWeekCycle[iDayOfWeekCycleCnt] = TokenNumber;
					iDayOfWeekCycleCnt++;
				}
			}
			else if (type == 2)
			{
				while (true)
				{
					Token = GetToken();

					if (!strcmp("end", TokenString))
					{
						break;
					}
			
					int iAB_PlayTimeMin = TokenNumber;
					Token = GetToken();
					int iAB_ChCloseMin = TokenNumber;
					this->m_iAB_PlayTimeMin = iAB_PlayTimeMin;
					this->m_iAB_ChCloseMin = iAB_ChCloseMin;
				}
			}
			else if (type == 3)
			{
				while (true)
				{
					Token = GetToken();

					if (!strcmp("end", TokenString))
					{
						break;
					}

					_tagAcheronEventTime pRET;
					pRET.m_iHour = TokenNumber;
					Token = GetToken();
					pRET.m_iMinute = TokenNumber;
					Token = GetToken();
					pRET.m_btEvent = TokenNumber;
					this->m_vtAcheronEventTime.push_back(pRET);
				}
			}
			else if (type == 4)
			{
				while (true)
				{
					Token = GetToken();

					if (!strcmp("end", TokenString))
					{
						break;
					}

					int nGourpNumber = (int)TokenNumber - 1;

					if (nGourpNumber < 0 || nGourpNumber > 5)
					{
						LogAdd(LOG_EVENT,"[ArcaBattle][MonsterGroupRegen] Invalid Aura groupNumber");
						return 0;
					}

					this->m_stObeliskInfo[nGourpNumber].m_iGroupNumber = TokenNumber;
					this->m_stObeliskInfo[nGourpNumber].m_iAttrKind = 1;
					Token = GetToken();
					this->m_stObeliskInfo[nGourpNumber].m_iMapIndex = TokenNumber;
					Token = GetToken();
					this->m_stObeliskInfo[nGourpNumber].m_iPosX = TokenNumber;
					Token = GetToken();
					this->m_stObeliskInfo[nGourpNumber].m_iPosY = TokenNumber;
				}
			}
			else if (type == 5)
			{
				while (true)
				{
					Token = GetToken();

					if (!strcmp("end", TokenString))
					{
						break;
					}
					
					int nTempGourpNumber = TokenNumber;

					if (nTempGourpNumber < 0 || nTempGourpNumber > 50)
					{
						LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] Invalid monster groupNumber");
						return 0;
					}

					this->m_stMonsterGroupInfo[nTempGourpNumber].m_nGroupNumber = nTempGourpNumber;
					Token = GetToken();
					this->m_stMonsterGroupInfo[nTempGourpNumber].m_nMapNumber = TokenNumber;
					Token = GetToken();
					this->m_stMonsterGroupInfo[nTempGourpNumber].m_nCnt = TokenNumber;
					Token = GetToken();
					this->m_stMonsterGroupInfo[nTempGourpNumber].m_nRegenTimeMin = TokenNumber;
				}
			}
			else if (type == 6)
			{
				int nAreaCnt = 0;
				int nTempGroupNumber = 0;

				while (true)
				{
					Token = GetToken();

					if (!strcmp("end", TokenString))
					{
						break;
					}

					int nGroupNumber = TokenNumber;
					
					if (nTempGroupNumber != nGroupNumber)
					{
						nTempGroupNumber = nGroupNumber;
						nAreaCnt = 0;
					}

					if (nGroupNumber < 0 || nGroupNumber > 50)
					{
						LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] Invalid monster groupNumber");
						return 0;
					}

					this->m_stMonsterPosition[nGroupNumber].m_nGroupNumber = nGroupNumber;
					Token = GetToken();
					this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nAreaCnt].m_nBeginX = TokenNumber;
					Token = GetToken();
					this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nAreaCnt].m_nBeginY = TokenNumber;
					Token = GetToken();
					this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nAreaCnt].m_nEndX = TokenNumber;
					Token = GetToken();
					this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nAreaCnt].m_nEndY = TokenNumber;
					Token = GetToken();	//test
					this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nAreaCnt].m_iDir = TokenNumber;
					nAreaCnt++;
					this->m_stMonsterPosition[nGroupNumber].m_nRegenAreaCnt = nAreaCnt;


				}
			}
			else if (type == 7)
			{
				int nArrayIndex = 0;
				int nTempGroupNumber = 0;

				while (true)
				{
					Token = GetToken();

					if (!strcmp("end", TokenString))
					{
						break;
					}
						
					int nGroupNumber = TokenNumber;
					
					if (nTempGroupNumber != nGroupNumber)
					{
						nTempGroupNumber = nGroupNumber;
						nArrayIndex = 0;
					}

					if (nGroupNumber < 0 || nGroupNumber > 50)
					{
						LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] Invalid monster groupNumber");
						return 0;
					}

					if (this->m_stMonsterPosition[nGroupNumber].m_nGroupNumber < 0)
					{
						LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] Invalid groupNumber(%d)", nGroupNumber);
						return 0;
					}

					Token = GetToken();
					this->m_stMonsterPosition[nGroupNumber].m_stMonsterIndexInfo[nArrayIndex].m_nMonsterIndex = TokenNumber;
					Token = GetToken();
					this->m_stMonsterPosition[nGroupNumber].m_stMonsterIndexInfo[nArrayIndex].m_nGenSqe = TokenNumber;
					Token = GetToken();
					this->m_stMonsterPosition[nGroupNumber].m_stMonsterIndexInfo[nArrayIndex].m_nMonAttr = TokenNumber;
					nArrayIndex++;

					if (nArrayIndex >= 20)
					{
						LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] Out of Max MonsterKindIndex ");
						break;
					}

					this->m_stMonsterPosition[nGroupNumber].m_nMonsterKindCnt = nArrayIndex;
				}
			}
			else if (type == 8)
			{
				int iCount = 0;

				while (true)
				{
					Token = GetToken();

					if (!strcmp("end", TokenString))
					{
						break;
					}

					this->m_stItemDropCntRate[iCount].iCnt = TokenNumber;
					Token = GetToken();
					this->m_stItemDropCntRate[iCount].iRate = TokenNumber;
					iCount++;
				}
			}
		}
	}

	fclose(SMDFile);
	LogAdd(LOG_EVENT,"[AcheronEvent] %s [File Load Cargado] ",lpszFileName);
	return 0;
}

void CAcheronGuardianEvent::SetAcheronEventProcMultiCast(int bABInitState)
{
	this->m_bAEInitState = bABInitState;
	this->GDReqAcheronEventProcMultiCast(this->IsPlayStart());
}

void CAcheronGuardianEvent::Clear()
{
	for (int i = 0; i < 5; i++)
	{
		this->m_stObeliskInfo[i].Clear();
	}
	
	for (int nGroupNumber = 0; nGroupNumber < 5; nGroupNumber++)
	{
		this->m_stMonsterGroupInfo[nGroupNumber].m_nGenTotCnt = 0;
	}
	
	this->m_bAE_PLAY_START = 0;
	this->m_bWindowClose = 0;
}


int CAcheronGuardianEvent::CheckSync()	//OK
{
	if (!gArcaBattle.IsArcaBattleServer())
	{
		return 0;
	}

	_SYSTEMTIME tmToDay;
	GetLocalTime(&tmToDay);
	int iTODAY_DATE_NUM = MAKELONG(MAKEWORD(tmToDay.wDay, tmToDay.wMonth), tmToDay.wYear);
	WORD wDayOfWeek = tmToDay.wDayOfWeek;

	if (wDayOfWeek >= 7)
	{
		LogAdd(LOG_EVENT, "[AcheronEvent] Error DayOfWeek -  wDayOfWeek [%d]", wDayOfWeek);
		return 0;
	}

	if (this->m_iDayOfWeekCycle[wDayOfWeek] != 1)
	{
		LogAdd(LOG_EVENT,"[AcheronEvent] Disabled for today");
		return 0;
	}

	if (this->m_vtAcheronEventTime.empty())
	{
		LogAdd(LOG_EVENT, "[AcheronEvent] No Schedule Time Data -  (m_vtAcheronEventTime.empty())");
		return 0;
	}

	_SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
    int iMIN_HOUR = 24;
    int iMIN_MINUTE = 60;
    int bTIME_CHANGED = 0;
	std::vector<_tagAcheronEventTime>::iterator it = this->m_vtAcheronEventTime.begin();
	_tagAcheronEventTime ;

	while (it != this->m_vtAcheronEventTime.end())
	{
		if (sysTime.wMinute + 60 * sysTime.wHour < it->m_iMinute + 60 * it->m_iHour)
		{
			if (iMIN_MINUTE + 60 * iMIN_HOUR > it->m_iMinute + 60 * it->m_iHour)
			{
                bTIME_CHANGED = 1;
                iMIN_HOUR = it->m_iHour;
				iMIN_MINUTE = it->m_iMinute;
			}
		}

		it++;
	}

	if (bTIME_CHANGED == 0)
	{
		iMIN_HOUR = 24;
		iMIN_MINUTE = 60;
		it = this->m_vtAcheronEventTime.begin();

		while (it != this->m_vtAcheronEventTime.end())
		{
			if (iMIN_MINUTE + 60 * iMIN_HOUR > it->m_iMinute + 60 * it->m_iHour)
			{
                bTIME_CHANGED = 2;
                iMIN_HOUR = it->m_iHour;
                iMIN_MINUTE = it->m_iMinute;
			}

			it++;
		}
	}

	if (bTIME_CHANGED == 1)
	{							//1000
		this->m_iREMAIN_MSEC = 1000 * (60 * iMIN_MINUTE + 3600 * iMIN_HOUR - (sysTime.wSecond + 60 * sysTime.wMinute + 3600 * sysTime.wHour));
		this->SetProcState(2);
	}
	else if (bTIME_CHANGED == 2)
	{
		this->m_iREMAIN_MSEC = -100; //-100
	}
	else
	{
		LogAdd(LOG_EVENT, "[AcheronEvent] No Schedule Time Data - Chaos Castle Terminated (bTIME_CHANGED=%d)", bTIME_CHANGED);
		return 0;

	}
		this->m_iTICK_COUNT = GetTickCount();
		LogAdd(LOG_EVENT,"[AcheronEvent] Start Time (START HOUR:%d, MIN:%d)",iMIN_HOUR, iMIN_MINUTE);
		return 1;
}

void CAcheronGuardianEvent::Run()	//OK
{
	if (!gArcaBattle.IsArcaBattleServer())
	{
		return;
	}

	if(Endable == 0)
	{

	}
	switch (this->m_iState)
	{
	case AE_STATE_NONE:
		this->CheckSync();
		break;
	case AE_STATE_CLOSED:
		this->ProcStateClosed();
		break;
	case AE_STATE_READY:
		this->ProcStateReady();
		break;
	case AE_STATE_PLAYING:
		this->ProcStatePlaying();
		break;
	case AE_STATE_CLOSE:
		this->ProcStateChannelClose();
		break;
	case AE_STATE_END:
		this->ProcStateEnd();
		break;
		}
	}

void CAcheronGuardianEvent::ProcStateEnd()	//OK
{
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(527));
	this->DelObelisk();
	this->DeleteArcaBattleAllMonster();
	this->m_bAE_PLAY_START = 0;
	this->GDReqAcheronEventProcMultiCast(this->m_bAE_PLAY_START);
	this->m_iREMAIN_MSEC = 60000 * this->m_iAB_ChCloseMin;
	this->m_iTICK_COUNT = GetTickCount();
	this->SetProcState(5);
}

void CAcheronGuardianEvent::ProcStateClosed()	//OK
{
	if (this->m_iREMAIN_MSEC != -100)
	{
		int iTICK_MSEC = GetTickCount() - this->m_iTICK_COUNT;
		
		if (iTICK_MSEC >= 1000)
		{
			this->m_iREMAIN_MSEC -= iTICK_MSEC;
			this->m_iTICK_COUNT = GetTickCount();

			if (this->m_iREMAIN_MSEC <= 0)
			{
				this->SetProcState(3);
			}
		}
	}
}

void CAcheronGuardianEvent::ProcStateReady()	//OK?
{
	/*for(int i=5;i>0;i--)
		{
			if (i == 5)
			{
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(506));

				LogAdd(LOG_BLUE,"[AcheronGuardianEvent] Acheron Event Prepare Attack ");
			}
			else
			{
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(507),i);

				LogAdd(LOG_BLUE,"[AcheronGuardianEvent] Acheron Event Start In Minutes:%d ",i);

			}
			Sleep(m_iREMAIN_MSEC * 60000);
		}*/

	this->m_iREMAIN_MSEC = 60000 * this->m_iAB_PlayTimeMin;
	this->m_iTICK_COUNT = GetTickCount();
	this->m_bAE_PLAY_START = 1;
	this->GDReqAcheronEventProcMultiCast(this->m_bAE_PLAY_START);
	this->m_iGroupNum = rand() % 5;

	if (this->m_iGroupNum < 0 || this->m_iGroupNum > 5)
	{
		LogAdd(LOG_EVENT,"[AcheronEvent] Error Obelisk GroupNum [%d]", this->m_iGroupNum);
		this->m_iGroupNum = 0;
	}

	LogAdd(LOG_EVENT,"[AcheronEvent] Obelisk GroupNum %d", this->m_iGroupNum);
	
	this->SetRandomObeliskAttr();
	this->GenObelisk(this->m_iGroupNum);
	this->RegenMonster(this->m_iGroupNum, 1, 10);
	this->ResetGenTime();

	char szTemp[256] = { 0 };
	sprintf_s(szTemp, gMessage.GetMessage(517), m_iGroupNum);
	this->SendMapServerGroupMsg(szTemp);
	this->SetProcState(4);
}

void CAcheronGuardianEvent::ProcStatePlaying()	//OK
{
	DWORD iTICK_MSEC = GetTickCount() - this->m_iTICK_COUNT;

	if (iTICK_MSEC >= 1000)
	{
		this->m_iREMAIN_MSEC -= iTICK_MSEC;
		this->m_iTICK_COUNT = GetTickCount();
		this->RegenMonsterRun();
	}

	if (this->m_iREMAIN_MSEC <= 0)
	{
		char szTemp[256] = { 0 };
		sprintf_s(szTemp,  gMessage.GetMessage(519));
		this->SendMapServerGroupMsg(szTemp);
		this->m_iREMAIN_MSEC = 0;
		this->DelObelisk();
		this->DeleteArcaBattleAllMonster();
		this->SetProcState(6);
	}
}

void CAcheronGuardianEvent::ProcStatePlayEnd()
{
	//not filled
}

void CAcheronGuardianEvent::ProcStateChannelClose()	//OK
{
	DWORD iTICK_MSEC = GetTickCount() - this->m_iTICK_COUNT;

	if (iTICK_MSEC >= 1000)
	{
		this->m_iREMAIN_MSEC -= iTICK_MSEC;
		this->m_iTICK_COUNT = GetTickCount();

		if (!this->m_bWindowClose && this->m_iREMAIN_MSEC <= 10000 && this->m_iREMAIN_MSEC > 0)
		{
			for (int n = OBJECT_START_USER; n < MAX_OBJECT; n++)
			{
				if (gObj[n].Connected == OBJECT_ONLINE && gObj[n].Map == MAP_ACHERON2 && gObj[n].Type == OBJECT_USER)
				{
					gNotice.GCNoticeSend(gObj[n].Index,1,0,0,0,0,0,gMessage.GetMessage(532),this->m_iREMAIN_MSEC / 1000);
				}
			}

			LogAdd(LOG_EVENT,"[AcheronEvent] Send Close Window Sec[%d]", this->m_iREMAIN_MSEC / 1000);
		}

		if (this->m_iREMAIN_MSEC <= 0)
		{
			for (int aIndex = OBJECT_START_USER; aIndex < MAX_OBJECT; aIndex++)
			{
				if (gObj[aIndex].Connected == OBJECT_ONLINE && gObj[aIndex].Map == MAP_ACHERON2 && gObj[aIndex].Type == OBJECT_USER)
				{
					gObjMoveGate(aIndex, 27);
				}
			}

			this->Clear();
			this->SetProcState(1);
		}
	}
}

void CAcheronGuardianEvent::CGReqAcheronEventEnter(_tagPMSG_REQ_ACHERON_EVENT_ENTER* lpMsg, int iIndex)
{
	if (!OBJECT_RANGE(iIndex))
	 {
	 return;
	 }
 
 LPOBJ lpObj = &gObj[iIndex];

	if (!gObjIsConnected(iIndex))
	 {
	 return;
	 }

	if (lpObj->Teleport)
	 {
		return;
	 }

 
	BYTE attr = gMap[lpObj->Map].GetAttr(lpObj->X, lpObj->Y);
 
	if (attr & 1)
		{
	 if (lpObj->UsePartyMatching)
	  {
		_PMSG_ANS_NOTI_ENTER_EVENTMAP_ERROR stEnterResult;
		 stEnterResult.h.set((LPBYTE)&stEnterResult, 0xEF, 0x09, sizeof(_PMSG_ANS_NOTI_ENTER_EVENTMAP_ERROR));
		stEnterResult.nResult = -1;
		 DataSend(iIndex, (LPBYTE)&stEnterResult, stEnterResult.h.size);
		 return;
	  }

		_tagPMSG_ANS_ACHERON_EVENT_ENTER pMsg;
		 pMsg.h.set((LPBYTE)&pMsg, 0xF8, 0x4C, sizeof(_tagPMSG_ANS_ACHERON_EVENT_ENTER));
		 pMsg.btResult = 1;

	 if (this->IsPlayStart())
	  {
		 LogAdd(LOG_EVENT,"[AcheronEvent] [%s] Acheron Event Enter",lpObj->Name);
		 gObjMoveGate(iIndex, 426);
		return;
      }

	 DataSend(iIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
}



void CAcheronGuardianEvent::GDReqAcheronEventProcMultiCast(BYTE btPlay) 
{
//	int index;
//	SOCKET socket;
	_tagPMSG_REQ_AE_PLAY_DS pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xF8, 0xF0, sizeof(_tagPMSG_REQ_AE_PLAY_DS));
	pMsg.btPlay = btPlay;
	pMsg.wMapSvrNum = gMapServerManager.GetMapServerGroup();

}

void CAcheronGuardianEvent::DGAnsAcheronEventProcMultiCast(_tagPMSG_ANS_AE_PLAY_DS* lpMsg)
{
	if (!gArcaBattle.IsArcaBattleServer())
	{
		this->SetPlayStart(lpMsg->btPlay);
	}

	LogAdd(LOG_EVENT,"[AcheronEvent] Acheron Event Play [%d]", lpMsg->btPlay);
}

void CAcheronGuardianEvent::SetRandomObeliskAttr()	//OK
{
	int iArrObeliskAttr[] = { 0, 1, 2, 3, 4 };
	int iArrMonsterIndex[] = { 627, 628, 629, 630, 631 };
	
	for(int iObeliskAttrCnt = 0; iObeliskAttrCnt < AE_MAX_BATTLEPOS; iObeliskAttrCnt++)
	{
		int iRand = rand() % AE_MAX_BATTLEPOS + 1;
		bool bflag = true;

		for (int i = 0; i < AE_MAX_BATTLEPOS; i++)
		{
			if (iArrObeliskAttr[i] == iRand)
			{
				bflag = true;
			}
		}

		if (!bflag)
		{
			iArrObeliskAttr[iObeliskAttrCnt] = iRand;
		}
	}

	for (int j = 0; j < AE_MAX_BATTLEPOS; j++)
	{
		this->m_stObeliskInfo[j].m_iAttrKind = iArrObeliskAttr[j];
		this->m_stObeliskInfo[j].m_iMonsterNum = iArrMonsterIndex[iArrObeliskAttr[j]];
	}
}

void CAcheronGuardianEvent::GenObelisk(int iGroupNum)	//OK
{
	int result = gObjAddMonster(this->m_stObeliskInfo[iGroupNum].m_iMapIndex);

	if (result > 0)
	{
		gObjSetMonster(result, this->m_stObeliskInfo[iGroupNum].m_iMonsterNum);
		this->m_stObeliskInfo[iGroupNum].m_iMonIndex = result;
		gObj[result].Class = this->m_stObeliskInfo[iGroupNum].m_iMonsterNum;
		gObj[result].Change = this->m_stObeliskInfo[iGroupNum].m_iMonsterNum;
		gObj[result].Map = this->m_stObeliskInfo[iGroupNum].m_iMapIndex;
		gObj[result].X = this->m_stObeliskInfo[iGroupNum].m_iPosX;
		gObj[result].Y = this->m_stObeliskInfo[iGroupNum].m_iPosY;
		gObj[result].TX = this->m_stObeliskInfo[iGroupNum].m_iPosX;
		gObj[result].TY = this->m_stObeliskInfo[iGroupNum].m_iPosY;
		gObj[result].OldX = this->m_stObeliskInfo[iGroupNum].m_iPosX;
		gObj[result].OldY = this->m_stObeliskInfo[iGroupNum].m_iPosY;
		gObj[result].StartX = this->m_stObeliskInfo[iGroupNum].m_iPosX;
		gObj[result].StartY = this->m_stObeliskInfo[iGroupNum].m_iPosY;
		gObj[result].Dir = 1;
		gObj[result].Live = 1;
		gObj[result].DieRegen = 0;
		gObj[result].State = 1;
		gObj[result].MaxRegenTime = 0;

		LogAdd(LOG_EVENT,"[AcheronEvent] Mapa (%d) Obelisk be created. Monster Clase (%d) ", gObj[result].Map,gObj[result].Class);
	}

}

void CAcheronGuardianEvent::DelObelisk()	//OK
{
	for (int iCnt = 0; iCnt < AE_MAX_BATTLEPOS; iCnt++)
	{
		int iIndex = this->m_stObeliskInfo[iCnt].m_iMonIndex;

		if (iIndex >= 0)
		{
			LogAdd(LOG_EVENT,"[AcheronEvent][Obelisk] Delete Monster - %d ", iIndex);
			gObjDel(iIndex);
		}
	}
}

void CAcheronGuardianEvent::DestoryObelisk(LPOBJ lpObj, BYTE btMapNumber, BYTE cX, BYTE cY, int nMaxHitUser)
{
	LogAdd(LOG_EVENT,"[AcheronEvent] Destoryed an Obelisk SetProcState(6)");

	this->SetProcState(6);
}

void CAcheronGuardianEvent::RegenMonsterRun()	//OK
{
	DWORD dwTick = GetTickCount();

	if (this->m_stMonsterGroupInfo[this->m_iGroupNum].m_nGroupNumber > 5)
	{
		if (dwTick >= this->m_stMonsterGroupInfo[this->m_iGroupNum].m_dwNextRegenTime)
		{
			this->DeleteMonster(this->m_iGroupNum);
			this->RegenMonster(this->m_iGroupNum, 5, 0);
			this->m_stMonsterGroupInfo[this->m_iGroupNum].m_dwNextRegenTime = GetTickCount() + 60000 * this->m_stMonsterGroupInfo[this->m_iGroupNum].m_nRegenTimeMin;
		}
	}
}

void CAcheronGuardianEvent::RegenMonster(int nGroupNumber, int iGenSeq, int iGenMonCnt)//OK
{
	if (nGroupNumber < 0 || nGroupNumber > AE_MAX_MONGROUP - 5)
	{
		//LogAddTD(89EBB1);
		return;
	}

	int nMapNumber = this->m_stMonsterGroupInfo[nGroupNumber].m_nMapNumber;
    int nMonsterArrayIndex = this->m_stMonsterGroupInfo[nGroupNumber].m_nGenTotCnt;
    int nMonsterCount = this->m_stMonsterGroupInfo[nGroupNumber].m_nCnt;
    int nMonsterKindCnt = this->m_stMonsterPosition[nGroupNumber].m_nMonsterKindCnt;

    if (iGenMonCnt)
	{
		nMonsterCount = iGenMonCnt;
	}

	for (int n = 0; n < nMonsterCount; n++)
    {
		int nRegenArea = rand() % this->m_stMonsterPosition[nGroupNumber].m_nRegenAreaCnt;
		int nBeginX = this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nRegenArea].m_nBeginX;
		int nBeginY = this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nRegenArea].m_nBeginY;
		int nEndX = this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nRegenArea].m_nEndX;
		int nEndY = this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nRegenArea].m_nEndY;
		int nDir = this->m_stMonsterPosition[nGroupNumber].m_stRegenArea[nRegenArea].m_iDir;

		BYTE Element = (BYTE)-1;

		if (nMapNumber == -1)	
		{
			
			break;
		}
        
		int nResult = gObjAddMonster(nMapNumber);
		int nMonsterIndex = 0;

		nMonsterIndex = this->m_stMonsterPosition[nGroupNumber].m_stMonsterIndexInfo[n].m_nMonsterIndex;

		for (int i = 0; i < nMonsterKindCnt; i++)
		{

			if (this->m_stMonsterPosition[nGroupNumber].m_stMonsterIndexInfo[i].m_nGenSqe == iGenSeq
				&& this->m_stMonsterPosition[nGroupNumber].m_stMonsterIndexInfo[i].m_nMonAttr == this->m_stObeliskInfo[this->m_iGroupNum].m_iAttrKind)
			{
				nMonsterIndex = this->m_stMonsterPosition[nGroupNumber].m_stMonsterIndexInfo[i].m_nMonsterIndex;
				Element = this->m_stMonsterPosition[nGroupNumber].m_stMonsterIndexInfo[i].m_nMonAttr;

				break;
			}
		}

		this->m_stMonsterGroupInfo[nGroupNumber].m_stMonsterAccountNumInfo[nMonsterArrayIndex].m_nIndex = nResult;

		if (nResult < 0)
		{
			LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] AddMonster fail!! [GROUP]:%d, [INDEX]:%d",
				nGroupNumber, nMonsterIndex);
			continue;
		}

		if (!this->SetPosMonster(nResult, nMapNumber, nBeginX, nBeginY, nEndX, nEndY, Element)) 
		{
			gObjDel(nResult);
			LogAdd(LOG_EVENT,"[AcheronEvent] error : %s %d", __FILE__, __LINE__);
			continue;
		}
	
		if (!gObjSetMonster(nResult, nMonsterIndex))
		{
			gObjDel(nResult);
           LogAdd(LOG_EVENT,"[AcheronEvent] error : %s %d", __FILE__, __LINE__);
			continue;
		}

		nMonsterArrayIndex++;

       LogAdd(LOG_EVENT,"[AcheronEvent] Group:%d, MonsInd:%d, MapNum:%d, X:%d, Y:%d ",
			nGroupNumber, nMonsterIndex, nMapNumber, gObj[nResult].X, gObj[nResult].Y);
	}

	this->m_stMonsterGroupInfo[nGroupNumber].m_nGenTotCnt = nMonsterArrayIndex;
   LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] Group: %d, MonsterTotCnt: %d ",
		nGroupNumber, this->m_stMonsterGroupInfo[nGroupNumber].m_nGenTotCnt);
}

int CAcheronGuardianEvent::SetPosMonster(int aIndex, int nMapNumber, int nBeginX, int nBeginY, int nEndX, int nEndY, BYTE Element)	//OK
{
	if (!OBJECT_RANGE(aIndex))
	{
		LogAdd(LOG_EVENT,"[AcheronEvent] error : %s %d", __FILE__, __LINE__);
		return 0;
	}

	LPOBJ lpObj = &gObj[aIndex];

    lpObj->PosNum = -1;
    lpObj->Map = nMapNumber;

    this->GetBoxPosition(nMapNumber, nBeginX, nBeginY, nEndX, nEndY, lpObj->X , lpObj->Y);

	lpObj->TX = lpObj->X;
    lpObj->TY = lpObj->Y;
    lpObj->OldX = lpObj->X;
    lpObj->OldY = lpObj->Y;
    lpObj->Dir = rand() % 8;
	lpObj->MoveRange = 130;
//    lpObj->StartX = lpObj->X;
//   lpObj->StartY = lpObj->Y;
    lpObj->DieRegen = 0;
    lpObj->MaxRegenTime = 0;


	if (Element != (BYTE)-1)
	{
		lpObj->Attribute = Element;
	}

	return 1;
}

int CAcheronGuardianEvent::GetBoxPosition(int mapnumber, int ax, int ay, int aw, int ah, short& mx, short& my) /*BYTE& mx, BYTE& my ||short& mx, short& my*/
{
	int count = 99 ; 
	int w;
	int h;
	int tx; 
	int ty;
	BYTE attr;

	while (count-- != 0)
	{
		w = aw - ax;
		h = ah - ay;

		__try
		{
			tx = ax + (rand() % w);
			ty = ay + (rand() % h);
		}
		__except (w = 1, h = 1, 1)
		{

		}

		attr = gMap[mapnumber].GetAttr(tx, ty);

		mx = tx;
		my = ty;

	return 1;
	}

	return 0;
}

void CAcheronGuardianEvent::ResetGenTime()	//??
{
	for (int nGroupNumber = 0; nGroupNumber < AE_REWARD_MAX_ITEMCOUNT; nGroupNumber++)
	{
		if (this->m_stMonsterGroupInfo[nGroupNumber].m_nGroupNumber >= 0)
		{
			if (nGroupNumber < 0 || nGroupNumber > AE_MAX_BATTLEPOS - 1)
			{
				return;
			}
			
			this->m_stMonsterGroupInfo[nGroupNumber].m_dwNextRegenTime = GetTickCount() + 60000 * this->m_stMonsterGroupInfo[nGroupNumber].m_nRegenTimeMin;
		}
	}
}

void CAcheronGuardianEvent::DeleteMonster(int nGroupNumber)	//OK
{
	if (nGroupNumber < 0 || nGroupNumber > AE_MAX_BATTLEPOS - 1)
	{
		return;
	}

    for (int i = 0; i < AE_MAX_MONGROUP; i++)
    {
		if (this->m_stMonsterGroupInfo[nGroupNumber].m_stMonsterAccountNumInfo[i].m_nIndex > -1)
		{
			int nIndex = this->m_stMonsterGroupInfo[nGroupNumber].m_stMonsterAccountNumInfo[i].m_nIndex;

			if (!gObj[nIndex].Live)
			{
				gObjDel(nIndex);
				LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] Delete Monster - %d ", nIndex);
				this->m_stMonsterGroupInfo[nGroupNumber].m_stMonsterAccountNumInfo[i].m_nIndex = -1;
			}
		}
	}
}

void CAcheronGuardianEvent::DeleteArcaBattleAllMonster()	//OK
{
	for (int nGroupNumber = 0; nGroupNumber < AE_MAX_BATTLEPOS; nGroupNumber++)
	{
		if (this->m_stMonsterGroupInfo[nGroupNumber].m_nGroupNumber >= 0)
		{
			if (nGroupNumber < 0 || nGroupNumber > AE_MAX_BATTLEPOS - 1)
			{
				return;
			}

			for (int i = 0; i < AE_MAX_MONGROUP; i++)
			{
				if (this->m_stMonsterGroupInfo[nGroupNumber].m_stMonsterAccountNumInfo[i].m_nIndex > -1)
				{
					int nIndex = this->m_stMonsterGroupInfo[nGroupNumber].m_stMonsterAccountNumInfo[i].m_nIndex;

					gObjDel(nIndex);
					LogAdd(LOG_EVENT,"[AcheronEvent][MonsterGroupRegen] Delete Monster - %d ", nIndex);
					this->m_stMonsterGroupInfo[nGroupNumber].m_stMonsterAccountNumInfo[i].m_nIndex = -1;
				}
			}

			this->m_stMonsterGroupInfo[nGroupNumber].m_dwNextRegenTime = 0;
		}
	}
}

void CAcheronGuardianEvent::SendMapServerGroupMsg(LPSTR lpszMsg)	//OK!
{
	GS_GDReqMapSvrMsgMultiCast(gMapServerManager.GetMapServerGroup(), lpszMsg); 
}
#endif