#include "stdafx.h"
#include "MasterHours.h"
#include "ScheduleManager.h"
#include "ServerInfo.h"
#include "Util.h"
#include "MemScript.h"
#include "Notice.h"
#include "Message.h"

#if(MASTER_HOURS == 1)

MasterHours ObjMasterH;

void MasterHours::Load(char* path)
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
		this->m_MasterHappyStartTime.clear();

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

					MASTER_HOURS_START_TIME info;

					info.Year = lpMemScript->GetNumber();

					info.Month = lpMemScript->GetAsNumber();

					info.Day = lpMemScript->GetAsNumber();

					info.DayOfWeek = lpMemScript->GetAsNumber();

					info.Hour = lpMemScript->GetAsNumber();

					info.Minute = lpMemScript->GetAsNumber();

					info.Second = lpMemScript->GetAsNumber();

					this->m_MasterHappyStartTime.push_back(info);

					LogAdd(LOG_EVENT,"[MasterHours] Datos Cargados..");

				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;

}

void MasterHours::CheckSync() // OK
{
	if(this->m_MasterHappyStartTime.empty() != 0)
	{
		return;
	}

	CTime ScheduleTime;

	CScheduleManager ScheduleManager;
	
	for(std::vector<MASTER_HOURS_START_TIME>::iterator it=this->m_MasterHappyStartTime.begin();it != this->m_MasterHappyStartTime.end();it++)
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
		this->SetProcState(STATE_MASTER_START);
	}

	for(int n; n<1;n++)
	{
	LogAdd(LOG_EVENT,"[MasterHours] Sync Start Time. [%d] min remain",this->m_RemainTime/60);
	}

}

void MasterHours::MainProc()
{
	switch(this->m_iState)
	{

	case STATE_MASTER_SYNC:
		this->CheckSync();
		break;

	case STATE_MASTER_START:
		StartMasterHours();
		break;
	}

}

void MasterHours::StartMasterHours()
{
	if((this->Start == 0) && (this->MasterEndable == 1)) 
	{
		_beginthread( cMasterHour__InsideTrigger, 0, NULL  );
		LogAdd(LOG_EVENT,"[MasterHour] Evento Iniciado!");
	}
}

void cMasterHour__InsideTrigger(void * lpParam)
{
	ObjMasterH.Start = 1;

	int *TotalMasterExp  = gServerInfo.m_AddMasterExperienceRate;
		*TotalMasterExp	+= ObjMasterH.ExtraMasterExp;
	
	//Start Master Event 
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(514),*TotalMasterExp);

	//StartEvent In Minutes
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(515),(ObjMasterH.MasterMinutes));

	//Logs GameServer
	LogAdd(LOG_EVENT,"[MasterHours] Extra Exp:%d,Total Exp:%d"
	,ObjMasterH.ExtraMasterExp,*TotalMasterExp);
	
	//Master Minutes 
	Sleep(ObjMasterH.MasterMinutes * 60000);

	//End Event
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(516));

	*TotalMasterExp -= ObjMasterH.ExtraMasterExp;

	LogAdd(LOG_EVENT,"[MasterHours] End!");

	ObjMasterH.Start = 0;

	ObjMasterH.SetProcState(STATE_MASTER_SYNC);

		_endthread();
}

#endif