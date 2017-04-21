
#include "User.h"

#if(HAPPY_HOURS == 1)

#define MAX_EXP 5000

enum eHappyHourState
{
	HP_STATE_START = 0,

};

struct HAPPY_HOURS_START_TIME
{
	int Year;
	int Month;
	int Day;
	int DayOfWeek;
	int Hour;
	int Minute;
	int Second;

	std::vector<HAPPY_HOURS_START_TIME> m_HappyHoursStartTime;

};
struct HAPPY_INFO
{
	int RemainTime;
	int TargetTime;
	int EventTime;
};

enum iState
{	
	STATE_NORMAL_SYNC= 1,
	STATE_NORMAL_START,
};

class HappyHours
{
public:
	HappyHours(){Start= 0; this->m_iState = 1;}	//Constructor Inline !
	~HappyHours(){}			//Destructor Inline !
//Fun
		
	void Load(char* path);
	void Init();
	void SetState(int state);
	void SetState_START();
	void CheckSync();
	void MainProc();
	void StartNormalHappyHours(); 
    void SetProcState(int iState) { this->m_iState = iState; };
    int GetProcState() { return this->m_iState; };
	
//Vars

	int Start;
	int NormalEnable;
	int NormalMinutes;

	int ExtraExp;  
	int ExtraDrop;

	int State;

private:
	int m_iState;
	int m_State;
	int m_RemainTime;
	int m_TargetTime;
	std::vector<HAPPY_HOURS_START_TIME> m_HappyHoursTime;
	HAPPY_HOURS_START_TIME m_EventHappyExp[MAX_EXP];
};

void cHappyHour__InsideTrigger(void * lpParam);
extern HappyHours ObjHappy;
#endif