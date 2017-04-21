
#if (MARRY_SYSTEM == 1)

#include "user.h"
#include "Map.h"

struct SDHP_RECVMARRY
{
	PBMSG_HEAD h;	// C1:FA:10
	BYTE SubCode;
	char Name[11];
	int Divorce;
	int ForceDivorce;
	int TraceCost;
	BYTE Map;
	BYTE Xpos1;
	BYTE Ypos1;
	BYTE Xpos2;
	BYTE Ypos2;
};

class MarrySystem
{
public:
	void Read(char * FilePath);
	//BOOL CommandCore(LPOBJ lpObj,char * Command);
	void CommandCore(LPOBJ lpObj,BYTE Command);
	void Propose(LPOBJ lpObj,char * HusbandWife);	 //marry
	void SendInfo(int aIndex);
	void SendMapServerGroupMsg(LPSTR lpszMsg);
		
	int EnableMarry;
	int Shop;
	int CmdMarryAF;

private:
	int GetSex(LPOBJ lpObj);
	int GetPos(LPOBJ lpObj);
	int HusWifeOnline(LPOBJ lpObj);

	void Accept(LPOBJ lpObj);						 // /acceptmarry
	void Divorce(LPOBJ lpObj);						 //	/divorce
	void ForceDivorce(LPOBJ lpObj);					 //	/forcedivorce
	void Trace(LPOBJ lpObj);						 // /tracemarry

//Vars

	int MapPos;
	int rXPos1;
	int rYPos1;
	int rXPos2;
	int rYPos2;

	int ZenDivorce;
	int ZenForceDivorce;

	WORD Maps[MAX_MAP];
};

extern MarrySystem Marry;

#endif