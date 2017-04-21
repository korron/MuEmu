#include "stdafx.h"
#include "HappyHours.h"
#include "ScheduleManager.h"
#include "ServerInfo.h"
#include "Util.h"
#include "MemScript.h"
#include "Notice.h"
#include "Message.h"

#if(HAPPY_HOURS == 1)

HappyHours ObjHappy;

void HappyHours::Load(char* path)
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
		this->m_HappyHoursTime.clear();
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

					HAPPY_HOURS_START_TIME info;

					info.Year = lpMemScript->GetNumber();

					info.Month = lpMemScript->GetAsNumber();

					info.Day = lpMemScript->GetAsNumber();

					info.DayOfWeek = lpMemScript->GetAsNumber();

					info.Hour = lpMemScript->GetAsNumber();
					
					info.Minute = lpMemScript->GetAsNumber();

					info.Second = lpMemScript->GetAsNumber();
					
					this->m_HappyHoursTime.push_back(info);
					
					LogAdd(LOG_EVENT,"[HappyHours] Datos Cargados..");
					
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

void HappyHours::CheckSync() // OK
{
	if(this->m_HappyHoursTime.empty() != 0)
	{
		return;
	}

	CTime ScheduleTime;

	CScheduleManager ScheduleManager;
	
	for(std::vector<HAPPY_HOURS_START_TIME>::iterator it=this->m_HappyHoursTime.begin();it != this->m_HappyHoursTime.end();it++)
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
		this->SetProcState(STATE_NORMAL_START);
	}

	for(int n; n<1;n++)
	{
	LogAdd(LOG_EVENT,"[HappyHours] Sync Start Time. [%d] min remain",this->m_RemainTime/60);
	}

}

void HappyHours::MainProc()
{
	switch(this->m_iState)
	{

	case STATE_NORMAL_SYNC:
		this->CheckSync();
		break;

	case STATE_NORMAL_START:
		StartNormalHappyHours();
		break;
	}

}

void HappyHours::StartNormalHappyHours()
{
	if((this->Start == 0) && (this->NormalEnable == 1))
	{
		_beginthread( cHappyHour__InsideTrigger, 0, NULL  );
		LogAdd(LOG_EVENT,"[HappyHours] Evento Iniciado!");
	}
}

void cHappyHour__InsideTrigger(void * lpParam)

{
	ObjHappy.Start = 1;
	
	int *TotalNormalExp = gServerInfo.m_AddExperienceRate;
	int *ItemDrop		= gServerInfo.m_ItemDropRate;

	*ItemDrop		+= ObjHappy.ExtraDrop;
	*TotalNormalExp += ObjHappy.ExtraExp;
	
	//Start Normal Event 
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(511),*TotalNormalExp,*ItemDrop);

	//StartEvent In Minutes
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(512),(ObjHappy.NormalMinutes));

	//Logs GameServer
	LogAdd(LOG_EVENT,"[HappyHours] Extra Drop:%d,Extra Exp:%d"
	,ObjHappy.ExtraDrop,ObjHappy.ExtraExp);

	LogAdd(LOG_EVENT,"[HappyHours] Total Drop:%d,Total Exp:%d"
	,*ItemDrop,*TotalNormalExp);
	
	//Minutes 
	Sleep(ObjHappy.NormalMinutes * 60000);

	//End Event
	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(513));

	*ItemDrop		-= ObjHappy.ExtraDrop;
	*TotalNormalExp -= ObjHappy.ExtraExp;

	LogAdd(LOG_EVENT,"[HappyHours] End!");

	ObjHappy.Start = 0;

	ObjHappy.SetProcState(STATE_NORMAL_SYNC);

		_endthread();
}

#endif

