#if(BOT_BUFFER == 1)

#define MAX_BOTBUFFER	30
#define MAX_BOTBUFFERSKILLS	5


struct BotBufferBodyItems
{
	int num;
	int level;
	int opt;
	bool Enabled;
};

struct botBufferSkill
{
	int BotIndex;
	WORD skill;
	int time;
};

struct botBufferStruct
{
	int Class;
	int OnlyVip;
	char Name[11];
	char GuildName[11];
	int  Gens;
	int  GensRank;
	BYTE Map;
	BYTE X;
	BYTE Y;
	BYTE Dir;
	bool Enabled;
	int index;
	WORD MaxLevel;
	BotBufferBodyItems body[9];
	botBufferSkill skill[MAX_BOTBUFFERSKILLS];
	BYTE SkillCount;
};

class ObjBotBuffer
{
public:

	BOOL S6E2;
	bool Enabled;
	void Read(char * path);
	void MakeBot();
	BOOL TradeOpen(int index,int nindex);
	botBufferStruct bot[MAX_BOTBUFFER];
	short Max_Normal_Level;

private:
	int GetBotIndex(int aIndex);
};

extern  ObjBotBuffer ObjBotBuff;

#endif