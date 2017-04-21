#include "ServerInfo.h"
#include "Notice.h"
#include "Message.h"
#include "Util.h"
#include "MemScript.h"

#if(MASTER_HOURS == 1)

#define MAX_EXP 5000

struct MASTER_HOURS_START_TIME
{
	int Year;
	int Month;
	int Day;
	int DayOfWeek;
	int Hour;
	int Minute;
	int Second;
};

enum iStateM
{	
	STATE_MASTER_SYNC= 1,
	STATE_MASTER_START,
};

class MasterHours
{
public:
	MasterHours(){Start	= 0; this->m_iState = 1;}
	~MasterHours(){}	

//Fun
	void StartMasterHours();
	void Load(char* path);

	void CheckSync();
	void MainProc();
    void SetProcState(int iState) { this->m_iState = iState; };
	 int GetProcState() { return this->m_iState; };

//Vars
	int Start;
	int MasterEndable;
	int ExtraMasterExp;
	int MasterMinutes;

private:
	int m_iState;
	int m_State;
	int m_RemainTime;
	int m_TargetTime;
	MASTER_HOURS_START_TIME m_EventHappyExp[MAX_EXP];
	std::vector<MASTER_HOURS_START_TIME> m_MasterHappyStartTime;

};

void cMasterHour__InsideTrigger(void * lpParam);

extern MasterHours ObjMasterH;

#endif