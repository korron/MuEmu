

#include "stdafx.h"
#include "user.h"

#if (SKY_EVENT == 1)

#define MAX_SKY_EVENT_SUB_LEVEL			 10
#define MAX_SKY_EVENT_LEVEL				  5
#define MAX_SKY_EVENT_STAGES			  3
#define MAX_SKY_EVENT_STAGE_MOB_COUNT	255
#define MAX_EXP 5000

void cSkyEvent__InsideTrigger(void * lpParam);

BOOL SKYEVENT_MAP_RANGE(int Map, BYTE X);

struct SKY_EVENT_START_TIME
{
	int Year;
	int Month;
	int Day;
	int DayOfWeek;
	int Hour;
	int Minute;
	int Second;

	std::vector<SKY_EVENT_START_TIME> m_SkyEventStartTime;

};

enum iStateSky
{	
	STATE_SKY_SYNC= 1,
	STATE_SKY_START,
};

struct SkyEventMob
{
	short Number;
	short ID;
	short Pos;
};

struct SkyEventStruct
{
	short m_Index;
	short DBNumber;
	//char Name[11];
	short KillCount[MAX_SKY_EVENT_STAGES];
};

class cSkyEvent
{
public:
	cSkyEvent(){Start= 0; this->m_iState = 1;}
	~cSkyEvent(){}
	void SetProcState(int iState) { this->m_iState = iState; };
	void Read(char * FilePath);
	void Load(char* path);
	void CheckSync();
	void MainProc();
	void DropWinnerItem(int iLevel,int iUser,BYTE SocketBonus,LPBYTE SocketOptions);
	int GetWinner(BYTE iLevel);
	int GetPlayerSubIndex(LPOBJ lpObj, BYTE iLevel);
	int GetLevel(LPOBJ lpObj);
	int MonsterDie(LPOBJ lpObj);
	void ExitPlayers();
	void MsgStringSend(LPSTR  szMsg, BYTE type) ;
	void AddUser(BYTE iLevel,int iIndex,LPOBJ lpObj);
	BOOL NpcTalk(LPOBJ lpNpc, LPOBJ lpObj);
	int CheckEnterLevel(int iIndex);
	void Teleport(LPOBJ lpObj, BYTE iLevel);
	void SetMonsters(BYTE iLevel,BYTE iStage);
	void ClearAllMonsters();
	void ClearMonsters(BYTE iLevel,BYTE iStage);
	void ReadMonsters(char * FilePath);
	void StartEvent();
	void SendUserExpInfo(BYTE iLevel);
	int CheckUsersAlive(BYTE iLevel);
	void ClearLevelData(BYTE iLevel);
	void RemoveUser(BYTE iLevel,int iUser);
	int ExtraExp[MAX_SKY_EVENT_LEVEL][MAX_SKY_EVENT_STAGES];

	BYTE CurrentStage;
	//BOOL ActiveLevel[MAX_SKY_EVENT_LEVEL];
	SkyEventStruct m_UserData[MAX_SKY_EVENT_LEVEL][MAX_SKY_EVENT_SUB_LEVEL];
	SkyEventMob m_MonsterData[MAX_SKY_EVENT_LEVEL][MAX_SKY_EVENT_STAGES][MAX_SKY_EVENT_STAGE_MOB_COUNT];

	BOOL Start;
	BOOL Enabled;
	BOOL NPCEnabled;
	BYTE StageMinutes[MAX_SKY_EVENT_STAGES];
	short MonsterStageCount[MAX_SKY_EVENT_LEVEL][MAX_SKY_EVENT_STAGES];
	short Level_Max[MAX_SKY_EVENT_LEVEL];
	short Level_Min[MAX_SKY_EVENT_LEVEL];
	short PlayerCount[MAX_SKY_EVENT_LEVEL];

	short ItemWinType[MAX_SKY_EVENT_LEVEL];
	short ItemWinIndex[MAX_SKY_EVENT_LEVEL];
	short ItemWinLevel[MAX_SKY_EVENT_LEVEL];
	short ItemWinDur[MAX_SKY_EVENT_LEVEL];
	short ItemWinLuck[MAX_SKY_EVENT_LEVEL];
	short ItemWinSkill[MAX_SKY_EVENT_LEVEL];
	short ItemWinOpt[MAX_SKY_EVENT_LEVEL];
	short ItemWinExc[MAX_SKY_EVENT_LEVEL];

private:
	int m_iState;
	int m_State;
	int m_RemainTime;
	int m_TargetTime;
	std::vector<SKY_EVENT_START_TIME> m_SkyEventTime;
	SKY_EVENT_START_TIME m_EventSkyEvent[MAX_SKY_EVENT_LEVEL];
};

extern cSkyEvent SkyEvent;

#endif