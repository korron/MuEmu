#include "stdafx.h"
#include "Offset.h"
#include "User.h"
#include "TMemory.h"
#include "Interface.h"
#include "Protocol.h"
#include "array.h"
#include "Object.h"
#include "Import.h"
#include "Defines.h"
#include "Util.h"
#include "Config.h"
#include "PrintPlayer.h"
struct sMonsterBar
{
	DWORD GetTime;
    int aIndex;
    int Life;
    int MaxLife;
    short Level;
	int ViewID;
};

array<sMonsterBar> MonsterBar;

struct sPlayerBar : sMonsterBar
{
    int SD;
    int MaxSD;
    short Reset;
	short RankTitle;
	short Long;
	bool ChatShowed;
};

array<sPlayerBar> PlayerBar;

bool lifebar = false;
bool rankbar = true;

User	gObjUser;

DWORD LastTime = 0;


void User::Load()
{
	ZeroMemory(&this->lpPlayer, sizeof(this->lpPlayer));
	ZeroMemory(&this->lpViewPlayer, sizeof(this->lpViewPlayer));
	ZeroMemory(&this->lpViewTarget, sizeof(this->lpViewTarget));
	SetOp((LPVOID)0x005B96E8, (LPVOID)this->AllInOne, ASM::CALL);
	this->m_TargetUpdateTick	= 0;
	this->m_TargetType			= false;
	this->m_CursorX				= -1;
	this->m_CursorY				= -1;
	this->m_MapNumber			= -1;
}

void User::Refresh()
{
	this->lpPlayer			= &*(ObjectCharacter*)oUserObjectStruct;
	this->lpViewPlayer		= &*(ObjectPreview*)oUserPreviewStruct;
	this->GetTarget();
	
	this->m_CursorX			= pCursorX;
	this->m_CursorY			= pCursorY;
	this->m_MapNumber		= pMapNumber;
}

bool User::GetTarget()
{
	if( pViewNPCTargetID != -1 )
	{
		this->lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewNPCTargetID);
		this->m_TargetType	= 1;
		return true;
	}
	else if( pViewAttackTargetID != -1 )
	{
		this->lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewAttackTargetID);
		this->m_TargetType	= 2;
		return true;
	}
	
	if( this->lpViewTarget != 0 )
	{
		ZeroMemory(&this->lpViewTarget, sizeof(this->lpViewTarget));
	}
	
	this->m_TargetType = 0;
	return false;
}

void User::SetTargetData(PMSG_TARGETDATA_ANS * lpMsg)
{
    if(lpMsg->isMonster)
    {
        sMonsterBar *tempBar = NULL;
        for (int i = 0; i < MonsterBar.size(); ++i)
        {
            if (MonsterBar[i].aIndex == lpMsg->aIndex)
            {
                tempBar = &MonsterBar[i];
                break;
            }
        }

        if(tempBar == NULL)
        {
            sMonsterBar Temp;
			int ID = MonsterBar.add(Temp);
			tempBar = &MonsterBar[ID];
            tempBar->aIndex = lpMsg->aIndex;
        }

        PMSG_TARGET_MONSTER_DATA *pRecv = (PMSG_TARGET_MONSTER_DATA*)lpMsg;

        tempBar->Level = pRecv->Level;
        tempBar->Life = pRecv->Life;
        tempBar->MaxLife = pRecv->MaxLife;

		if (tempBar->Life > tempBar->MaxLife)
			tempBar->Life = tempBar->MaxLife;

		tempBar->ViewID = -1;
		tempBar->GetTime = GetTickCount();
    }
    else
    {
        sPlayerBar *tempBar = NULL;
        for (int i = 0; i < PlayerBar.size(); ++i)
        {
            if (PlayerBar[i].aIndex == lpMsg->aIndex)
            {
                tempBar = &PlayerBar[i];
                break;
            }
        }

        if(tempBar == NULL)
        {
            sPlayerBar Temp;
            int ID = PlayerBar.add(Temp);
			tempBar = &PlayerBar[ID];
            tempBar->aIndex = lpMsg->aIndex;
        }

        PMSG_TARGET_PLAYER_DATA *pRecv = (PMSG_TARGET_PLAYER_DATA*)lpMsg;

        tempBar->Level = pRecv->Level;
        tempBar->Reset = pRecv->Reset;
		tempBar->RankTitle = pRecv->RankTitle;
		tempBar->Long = pRecv->Long;

        tempBar->Life = pRecv->Life;
        tempBar->MaxLife = pRecv->MaxLife;
        tempBar->SD = pRecv->SD;
        tempBar->MaxSD = pRecv->MaxSD;

		if (tempBar->Life > tempBar->MaxLife)
			tempBar->Life = tempBar->MaxLife;
		if (tempBar->SD > tempBar->MaxSD)
			tempBar->SD = tempBar->MaxSD;

		tempBar->ViewID = -1;
		tempBar->ChatShowed = false;
		tempBar->GetTime = GetTickCount();
    }
}

char* User::ParsingHP(DWORD Num)
{
	char Text[50];
	if (Num >= 10000000000)
		sprintf(Text, "%ldkkk", Num / 1000000000);
	else if (Num >= 10000000)
		sprintf(Text, "%ldkk", Num / 1000000);
	else if (Num >= 10000)
		sprintf(Text, "%ldk", Num / 1000);
	else
		sprintf(Text, "%ld", Num);

	return strdup(Text);
}

void User::DrawHP()
{
	VAngle Angle;
	int PosX, PosY;

	bool MonsterTarget = false;
	bool PlayerTarget = false;

	// let's have fun with comments :DDD

	// first of all we check all Viewport and if server send monster/player HP it insert ViewPortID to our structure
	for (int ViewPortID = 0; ViewPortID < 120; ViewPortID++)
	{
		lpViewObj lpObj = (ObjectPreview*)pGetPreviewStruct(pPreviewThis(), ViewPortID);

		// check if it exist and it is player or monster
		if (!lpObj || (lpObj->m_Model.ObjectType != emMonster && lpObj->m_Model.ObjectType != emPlayer) || !lpObj->m_Model.Unknown4)
		{
			// check if we have same ViewportID monster in our array and delete it
			for (int i = 0; i < MonsterBar.size(); i++)
			{
				if (ViewPortID == MonsterBar[i].ViewID)
				{
					MonsterBar.remove_index_fast(i);
					break;
				}
			}

			// check if we have same ViewportID Player in our array and delete it
			for (int i = 0; i < PlayerBar.size(); i++)
			{
				if (ViewPortID == PlayerBar[i].ViewID)
				{
					PlayerBar.remove_index_fast(i);
					break;
				}
			}
			continue;
		}

		if (lpObj->m_Model.ObjectType == emMonster)
		{
			// goes throw all monsterbars (that server send to us)
			for (int i = 0; i < MonsterBar.size(); ++i)
			{
				// check if it needs to be deleted by life decrees or lifetime (too old)
				if (MonsterBar[i].Life <= 0 || GetTickCount() - MonsterBar[i].GetTime > 10000)
				{
					MonsterBar.remove_index_fast(i--);	// i--, so we could parse new item by same index in array
					continue;
				}

				// if monster exist in array, add ViewID so we could render it later
				if (MonsterBar[i].aIndex == lpObj->aIndex)
				{
					MonsterBar[i].ViewID = ViewPortID;

					// if monster is targeted by user, make it latest in array (so it would be rendered latest and on the top of all)
					if (gObjUser.m_TargetType > 0 && gObjUser.lpViewTarget != NULL && gObjUser.lpViewTarget->aIndex == lpObj->aIndex)
					{
						MonsterBar.make_latest(i);
						MonsterTarget = true;
					}
					break;
				}
			}
		}
		else
		{
			// goes  throw all playerbars (that server send to us)
			for (int i = 0; i < PlayerBar.size(); ++i)
			{
				// check if it needs to be deleted by life decrees or lifetime (too old)
				if (PlayerBar[i].Life <= 0 || GetTickCount() - PlayerBar[i].GetTime > 10000)
				{
					PlayerBar.remove_index_fast(i--);	// i--, so we could parse new item by same index in array
					continue;
				}

				// check if it is our player with hpbar
				if (PlayerBar[i].aIndex == lpObj->aIndex)
				{
					PlayerBar[i].ViewID = ViewPortID;

					// check player for chat window and player target
					for (int j = 0; j < 120; j++)
					{
						// search throw all structure of chat messages (or something)
						BYTE *pChatMember = (BYTE*)(pChatStructure + 700 * j);

						char TName[10];
						strncpy(TName, (char*)pChatMember, 10);

						// if it's not our player, goes next
						if (strcmp(TName, lpObj->Name))
							continue;

						// Check if guys is chating
						if (*(DWORD*)(pChatMember + 660) > 0)
						{
							PlayerBar[i].ChatShowed = true;
							break;							// break to prevent targeting
						}
						else
						{
							PlayerBar[i].ChatShowed = false;
						}

						// if player target him, make it latest so we could render it on top later
						if (*(DWORD*)(pChatMember + 144) > 0)
						{
							PlayerTarget = true;
							PlayerBar.make_latest(i);
						}

						break;
					}

					break;
				}
			}
		}
	}
	// Render time !!!
	// Take real line height for using it later
	float lineHeight = 25.0f * (pWinHeightReal - 0.6f);
	// monsters, so players would be always on top
	for (int i = 0; i < MonsterBar.size(); ++i)
	{
		// check if it's not an error
		if (MonsterBar[i].ViewID == -1)
			continue;
		
		// taking it's structure
		lpViewObj lpObj = (ObjectPreview*)pGetPreviewStruct(pPreviewThis(), MonsterBar[i].ViewID);

		// to prevent that player doesn't exist
		if (!lpObj || (lpObj->m_Model.ObjectType != emMonster && lpObj->m_Model.ObjectType != emPlayer) || !lpObj->m_Model.Unknown4)
		{
			MonsterBar.remove_index(i--);	// i--, so we could parse new item by same index in array
			continue;
		}

		// taking it's coordinates
		Angle.X = lpObj->m_Model.VecPosX;
		Angle.Y = lpObj->m_Model.VecPosY;
		Angle.Z = lpObj->m_Model.VecPosZ + lpObj->m_Model.Unknown216.Z + 100.0;

		pGetPosFromAngle(&Angle, &PosX, &PosY);

		// calculating some width and pos shit
		float BarWidth = 78.1f * (MonsterBar[i].Life / (MonsterBar[i].MaxLife * 1.0f));
		PosX -= 40;

		// taking this bool for more easier way to use it
		bool MouseOver = MonsterTarget && (i == MonsterBar.size() - 1);

		// For blend fix
		pSetBlend(true);

		// making needed color (if it is targeting, make it fully visible, others = 100/255 blank)
		DWORD Color = Color4f(255, 255, 255, 100);
		if (MouseOver)
			Color = Color4f(255, 255, 255, 255);
		if(!lifebar)
		{
		// render this background and life meter
        glColor4f(0.0, 0.0, 0.0, 0.7);
        pDrawBarForm((float)PosX, (float)PosY, 80, 6.0, 0, 0);
		glColor3f(2.0, 0.0, 0.0);
        pDrawBarForm((float)PosX + 1, (float)PosY + 1.3f, BarWidth, 3.0, 0, 0);
		//pDrawColorButton(32514, (float)PosX, (float)PosY, 80, 6.0, 0, 0, Color);
		//pDrawColorButton(32513, (float)PosX + 1, (float)PosY + 1.3f, BarWidth, 3.0, 0, 0, Color);

		// if targeting, show more info about monster
		if (MouseOver)
		{
			// draw background
		//	glColor4f(0.0f, 0.0f, 0.0f, 0.30f);
		//	pDrawBarForm((float)PosX -15, (float)PosY - 17, 110, lineHeight + 10.0f, 0.0, 0);

			// draw first line - Name
			pDrawColorText(lpObj->Name, PosX -7.5, PosY - 18, 100, 1, eGold, 9, 3);

			// draw second line - other stuff
			char Text[50];
			sprintf(Text, "Lvl %d, HP %s/%s", MonsterBar[i].Level, ParsingHP(MonsterBar[i].Life), ParsingHP(MonsterBar[i].MaxLife));
			pDrawColorText(Text, PosX, PosY - 9, 80, 1, eShinyGreen, 9, 3);
		}
		else
		{
			// draw background
			//glColor4f(0.0f, 0.0f, 0.0f, 0.25f);
			//pDrawBarForm((float)PosX -15, (float)PosY - 13, 110, lineHeight + 5.0f, 0.0, 0);

			// draw name
			pDrawColorText(lpObj->Name, PosX -7.5, PosY -11, 100, 1, eGold, 9, 3);
		}
		pGLSwitchBlend();
	}
	}
	// the sweetest part about players :DD
	for (int i = 0; i < PlayerBar.size(); ++i)
	{
		// check if it's not an error or chat showed
		if (PlayerBar[i].ViewID == -1 || PlayerBar[i].ChatShowed)
			continue;
		
		// taking it's structure
		lpViewObj lpObj = (ObjectPreview*)pGetPreviewStruct(pPreviewThis(), PlayerBar[i].ViewID);
		DWORD CurrentTick = GetTickCount();
		DWORD Delay = (CurrentTick - gObjUser.m_TargetUpdateTick);
		// to prevent that player doesn't exist
		if (!lpObj || (lpObj->m_Model.ObjectType != emMonster && lpObj->m_Model.ObjectType != emPlayer) || !lpObj->m_Model.Unknown4)
		{
			PlayerBar.remove_index(i--);	// i--, so we could parse new item by same index in array
			continue;
		}

		// taking it's coordinates
		Angle.X = lpObj->m_Model.VecPosX;
		Angle.Y = lpObj->m_Model.VecPosY;
		Angle.Z = lpObj->m_Model.VecPosZ + lpObj->m_Model.Unknown216.Z + 100.0;

		pGetPosFromAngle(&Angle, &PosX, &PosY);

		// calculating some width and pos shit
		PosX -= 40;
		PosY += lineHeight;			// taking 1 line down (with resolution fix problem) not to be collision with nickname

		// taking this bool for more easier way to use it
		bool MouseOver = PlayerTarget && (i == PlayerBar.size() - 1);
		
		// For blend fix
		pSetBlend(true);

		// making needed color (if it is targeting, make it fully visible, others = 150/255 blank)
		DWORD Color = Color4f(255, 255, 255, 150);
		if (MouseOver)
			Color = Color4f(255, 255, 255, 255);

		// render this background and life meter
		// goes throw partylist
		if (pPartyMemberCount > 0)
		{
			// temp variable for preverting double sd bar
			bool isShowed = false;

			for (int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++)
			{
				PartyList PartyMember = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
				lpViewObj lpPartyObj = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), PartyMember.ViewportID);

				// if it's not our partyman, goes to next
				if (!lpPartyObj || PartyMember.ViewportID != PlayerBar[i].ViewID)
					continue;

				// if that guy is our target
				if (MouseOver)
				{
					if(!rankbar) return;
			// Party Bar
	 pSetBlend(true);
		float lineHeight = 25.0f * (pWinHeightReal - 0.6f);
			
			glColor4f(0.0f, 0.0f, 0.0f, 0.30f);
			pDrawBarForm((float)PosX, (float)PosY - 19, 0, lineHeight - 0.0, 0.0, 0);
			pDrawGUI(0x9960, (float)PosX, (float)PosY - 41, 80, 10);
			pDrawGUI(0x9960, (float)PosX + 16, (float)PosY - 29, 44, 9);
			pDrawColorText(lpObj->Name, PosX + 999, PosY - 19, 67, 1.5, eShinyGreen, 9, 3);

			float BarWidth = 40.1f * (PlayerBar[i].Life / (PlayerBar[i].Life * 1.0f));
			pDrawColorButton(32513, (float)PosX + 18, (float)PosY - 27, BarWidth, 2.0, 0, 0, eBlue1);
			float SDBarWidth = 40.1f * (PlayerBar[i].SD / (PlayerBar[i].MaxSD * 1.0f));
			pDrawColorButton(32515, (float)PosX + 18, (float)PosY - 24, SDBarWidth, 2.0, 0, 0, eGold);


			
			switch (PlayerBar[i].RankTitle)
			{
			case 1:
			pDrawGUI(0x9960, (float)PosX - 3, (float)PosY - 65, 95, 25);
			break;
			case 2:
			pDrawGUI(0x9961, (float)PosX - 9, (float)PosY - 66, 95, 25);
			break;
			case 3:
			pDrawGUI(0x9962, (float)PosX - 1, (float)PosY - 70, 95, 27);
			break;
			case 4:
			pDrawGUI(0x9963, (float)PosX - 0, (float)PosY - 70, 95, 27);
			break;
			case 5:
			pDrawGUI(0x9964, (float)PosX - 5, (float)PosY - 70, 95, 28);
			break;
			case 6:
			pDrawGUI(0x9965, (float)PosX - 2, (float)PosY - 72, 95, 27);
			break;
			case 7:
			pDrawGUI(0x9966, (float)PosX - 3, (float)PosY - 72, 100, 27);
			break;
			case 8:
			pDrawGUI(0x9967, (float)PosX - 4, (float)PosY - 69, 100, 25);
			break;
			case 9:
			pDrawGUI(0x9968, (float)PosX - 1, (float)PosY - 70, 100, 25);
			break;
			case 10:
			pDrawGUI(0x9969, (float)PosX - 6, (float)PosY - 72, 100, 25);
			break;
			case 11:
			pDrawGUI(0x9970, (float)PosX - 11, (float)PosY - 70, 100, 27);
			break;
			case 12:
			pDrawGUI(0x9971, (float)PosX - 9, (float)PosY - 70, 100, 27);
			break;
			case 13:
			pDrawGUI(0x9972, (float)PosX - 2, (float)PosY - 70, 100, 29);
			break;
			case 14:
			pDrawGUI(0x9973, (float)PosX - 12, (float)PosY - 71, 110, 28);
			break;
			case 15:
			pDrawGUI(0x9980, (float)PosX - 12, (float)PosY - 71, 126, 27);
			break;
			}


		
			if (PlayerBar[i].Reset >= Config.Min && PlayerBar[i].Reset < Config.Max)
			{
				pDrawColorText(Config.RankText, PosX, PosY - 40, 80, 1.5, eWhite1, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min1 && PlayerBar[i].Reset < Config.Max1)
			{
				pDrawColorText(Config.RankText1, PosX, PosY - 40, 80, 1.5, eWhite, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min2 && PlayerBar[i].Reset < Config.Max2)
			{
				pDrawColorText(Config.RankText2, PosX, PosY - 40, 80, 1.5, eExcellent, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min3 && PlayerBar[i].Reset < Config.Max3)
			{
				pDrawColorText(Config.RankText3, PosX, PosY - 40, 80, 1.5, eExcellent, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min4 && PlayerBar[i].Reset < Config.Max4)
			{
				pDrawColorText(Config.RankText4, PosX, PosY - 40, 80, 1.5, eAncient, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min5 && PlayerBar[i].Reset < Config.Max5)
			{
				pDrawColorText(Config.RankText5, PosX, PosY - 40, 80, 1.5, eAncient, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min6 && PlayerBar[i].Reset < Config.Max6)
			{
				pDrawColorText(Config.RankText6, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min7 && PlayerBar[i].Reset < Config.Max7)
			{
				pDrawColorText(Config.RankText7, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min8 && PlayerBar[i].Reset < Config.Max8)
			{
				pDrawColorText(Config.RankText8, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min9 && PlayerBar[i].Reset < Config.Max9)
			{
				pDrawColorText(Config.RankText9, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min10 && PlayerBar[i].Reset < Config.Max10)
			{
				pDrawColorText(Config.RankText10, PosX, PosY - 40, 80, 1.5, eYellow, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min11 && PlayerBar[i].Reset < Config.Max11)
			{
				pDrawColorText(Config.RankText11, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min12 && PlayerBar[i].Reset < Config.Max12)
			{
				pDrawColorText(Config.RankText12, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min13 && PlayerBar[i].Reset < Config.Max13)
			{
				pDrawColorText(Config.RankText13, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min14 && PlayerBar[i].Reset < Config.Max14)
			{
				pDrawColorText(Config.RankText14, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min15 && PlayerBar[i].Reset < Config.Max15)
			{
				pDrawColorText(Config.RankText15, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min16 && PlayerBar[i].Reset < Config.Max16)
			{
				pDrawColorText(Config.RankText16, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min17 && PlayerBar[i].Reset < Config.Max17)
			{
				pDrawColorText(Config.RankText17, PosX, PosY - 40, 80, 1.5, eBlue, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min18 && PlayerBar[i].Reset < Config.Max18)
			{
				pDrawColorText(Config.RankText18, PosX, PosY - 40, 80, 1.5, eBlue, 32, 3);
			}
			//--------------------- Rank thuoc tinh (party)
			if (PlayerBar[i].Long >= 16 && PlayerBar[i].Long <= 17)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 17 && PlayerBar[i].Long <= 18)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 18 && PlayerBar[i].Long <= 19)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 0 && PlayerBar[i].Long <= 0)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 1 && PlayerBar[i].Long <= 1)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 2 && PlayerBar[i].Long <= 2)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 32 && PlayerBar[i].Long <= 32)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 33 && PlayerBar[i].Long <= 33)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 34 && PlayerBar[i].Long <= 34)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 48 && PlayerBar[i].Long <= 48)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 49 && PlayerBar[i].Long <= 49)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 64 && PlayerBar[i].Long <= 64)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 66 && PlayerBar[i].Long <= 66)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 80 && PlayerBar[i].Long <= 80)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 81 && PlayerBar[i].Long <= 81)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 82 && PlayerBar[i].Long <= 82)
			{
			pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 96 && PlayerBar[i].Long <= 96)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 97 && PlayerBar[i].Long <= 97)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
				}
				else
				{
				

					if(!rankbar) return;
			// Party Bar
			 pSetBlend(true);
		float lineHeight = 25.0f * (pWinHeightReal - 0.6f);
			
			glColor4f(0.0f, 0.0f, 0.0f, 0.30f);
			pDrawBarForm((float)PosX, (float)PosY - 19, 0, lineHeight - 0.0, 0.0, 0);
			pDrawGUI(0x9960, (float)PosX, (float)PosY - 41, 80, 10);
			pDrawGUI(0x9960, (float)PosX + 16, (float)PosY - 29, 44, 9);
			pDrawColorText(lpObj->Name, PosX + 999, PosY - 19, 67, 1.5, eShinyGreen, 9, 3);

			float BarWidth = 40.1f * (PlayerBar[i].Life / (PlayerBar[i].Life * 1.0f));
			pDrawColorButton(32513, (float)PosX + 18, (float)PosY - 27, BarWidth, 2.0, 0, 0, eBlue1);
			float SDBarWidth = 40.1f * (PlayerBar[i].SD / (PlayerBar[i].MaxSD * 1.0f));
			pDrawColorButton(32515, (float)PosX + 18, (float)PosY - 24, SDBarWidth, 2.0, 0, 0, eGold);


			
			switch (PlayerBar[i].RankTitle)
			{
			case 1:
			pDrawGUI(0x9960, (float)PosX - 3, (float)PosY - 65, 95, 25);
			break;
			case 2:
			pDrawGUI(0x9961, (float)PosX - 9, (float)PosY - 66, 95, 25);
			break;
			case 3:
			pDrawGUI(0x9962, (float)PosX - 1, (float)PosY - 70, 95, 27);
			break;
			case 4:
			pDrawGUI(0x9963, (float)PosX - 0, (float)PosY - 70, 95, 27);
			break;
			case 5:
			pDrawGUI(0x9964, (float)PosX - 5, (float)PosY - 70, 95, 28);
			break;
			case 6:
			pDrawGUI(0x9965, (float)PosX - 2, (float)PosY - 72, 95, 27);
			break;
			case 7:
			pDrawGUI(0x9966, (float)PosX - 3, (float)PosY - 72, 100, 27);
			break;
			case 8:
			pDrawGUI(0x9967, (float)PosX - 4, (float)PosY - 69, 100, 25);
			break;
			case 9:
			pDrawGUI(0x9968, (float)PosX - 1, (float)PosY - 70, 100, 25);
			break;
			case 10:
			pDrawGUI(0x9969, (float)PosX - 6, (float)PosY - 72, 100, 25);
			break;
			case 11:
			pDrawGUI(0x9970, (float)PosX - 11, (float)PosY - 70, 100, 27);
			break;
			case 12:
			pDrawGUI(0x9971, (float)PosX - 9, (float)PosY - 70, 100, 27);
			break;
			case 13:
			pDrawGUI(0x9972, (float)PosX - 2, (float)PosY - 70, 100, 29);
			break;
			case 14:
			pDrawGUI(0x9973, (float)PosX - 12, (float)PosY - 71, 110, 28);
			break;
			case 15:
			pDrawGUI(0x9980, (float)PosX - 12, (float)PosY - 71, 126, 27);
			break;
			}


		
			if (PlayerBar[i].Reset >= Config.Min && PlayerBar[i].Reset < Config.Max)
			{
				pDrawColorText(Config.RankText, PosX, PosY - 40, 80, 1.5, eWhite1, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min1 && PlayerBar[i].Reset < Config.Max1)
			{
				pDrawColorText(Config.RankText1, PosX, PosY - 40, 80, 1.5, eWhite, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min2 && PlayerBar[i].Reset < Config.Max2)
			{
				pDrawColorText(Config.RankText2, PosX, PosY - 40, 80, 1.5, eExcellent, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min3 && PlayerBar[i].Reset < Config.Max3)
			{
				pDrawColorText(Config.RankText3, PosX, PosY - 40, 80, 1.5, eExcellent, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min4 && PlayerBar[i].Reset < Config.Max4)
			{
				pDrawColorText(Config.RankText4, PosX, PosY - 40, 80, 1.5, eAncient, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min5 && PlayerBar[i].Reset < Config.Max5)
			{
				pDrawColorText(Config.RankText5, PosX, PosY - 40, 80, 1.5, eAncient, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min6 && PlayerBar[i].Reset < Config.Max6)
			{
				pDrawColorText(Config.RankText6, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min7 && PlayerBar[i].Reset < Config.Max7)
			{
				pDrawColorText(Config.RankText7, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min8 && PlayerBar[i].Reset < Config.Max8)
			{
				pDrawColorText(Config.RankText8, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min9 && PlayerBar[i].Reset < Config.Max9)
			{
				pDrawColorText(Config.RankText9, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min10 && PlayerBar[i].Reset < Config.Max10)
			{
				pDrawColorText(Config.RankText10, PosX, PosY - 40, 80, 1.5, eYellow, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min11 && PlayerBar[i].Reset < Config.Max11)
			{
				pDrawColorText(Config.RankText11, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min12 && PlayerBar[i].Reset < Config.Max12)
			{
				pDrawColorText(Config.RankText12, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min13 && PlayerBar[i].Reset < Config.Max13)
			{
				pDrawColorText(Config.RankText13, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min14 && PlayerBar[i].Reset < Config.Max14)
			{
				pDrawColorText(Config.RankText14, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min15 && PlayerBar[i].Reset < Config.Max15)
			{
				pDrawColorText(Config.RankText15, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min16 && PlayerBar[i].Reset < Config.Max16)
			{
				pDrawColorText(Config.RankText16, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min17 && PlayerBar[i].Reset < Config.Max17)
			{
				pDrawColorText(Config.RankText17, PosX, PosY - 40, 80, 1.5, eBlue, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min18 && PlayerBar[i].Reset < Config.Max18)
			{
				pDrawColorText(Config.RankText18, PosX, PosY - 40, 80, 1.5, eBlue, 32, 3);
			}
			//--------------------- Rank thuoc tinh (party)
			if (PlayerBar[i].Long >= 16 && PlayerBar[i].Long <= 17)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 17 && PlayerBar[i].Long <= 18)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 18 && PlayerBar[i].Long <= 19)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 0 && PlayerBar[i].Long <= 0)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 1 && PlayerBar[i].Long <= 1)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 2 && PlayerBar[i].Long <= 2)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 32 && PlayerBar[i].Long <= 32)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 33 && PlayerBar[i].Long <= 33)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 34 && PlayerBar[i].Long <= 34)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 48 && PlayerBar[i].Long <= 48)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 49 && PlayerBar[i].Long <= 49)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 64 && PlayerBar[i].Long <= 64)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 66 && PlayerBar[i].Long <= 66)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 80 && PlayerBar[i].Long <= 80)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 81 && PlayerBar[i].Long <= 81)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 82 && PlayerBar[i].Long <= 82)
			{
			pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 96 && PlayerBar[i].Long <= 96)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 97 && PlayerBar[i].Long <= 97)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}

				}

				// if we get's here, so we showed up all that we want
				isShowed = true;
				break;
			}
			if (isShowed)
		continue;
		}

		// if we get's here, so this is not partyman
		// and we just shows sd, and if targeting - some extra info 
		if (MouseOver)
		{
			if(!rankbar) return;
			// draw background and name
			 pSetBlend(true);
			float lineHeight = 25.0f * (pWinHeightReal - 0.6f);
			
			glColor4f(0.0f, 0.0f, 0.0f, 0.30f);
			pDrawBarForm((float)PosX, (float)PosY - 19, 0, lineHeight - 0.0, 0.0, 0);
			pDrawGUI(0x9960, (float)PosX, (float)PosY - 41, 80, 10);
			pDrawGUI(0x9960, (float)PosX + 16, (float)PosY - 29, 44, 9);
			pDrawColorText(lpObj->Name, PosX + 999, PosY - 19, 67, 1.5, eShinyGreen, 9, 3);

			float BarWidth = 40.1f * (PlayerBar[i].Life / (PlayerBar[i].Life * 1.0f));
			pDrawColorButton(32513, (float)PosX + 18, (float)PosY - 27, BarWidth, 2.0, 0, 0, eRed);
			float SDBarWidth = 40.1f * (PlayerBar[i].SD / (PlayerBar[i].MaxSD * 1.0f));
			pDrawColorButton(32515, (float)PosX + 18, (float)PosY - 24, SDBarWidth, 2.0, 0, 0, eGold);

			
			switch (PlayerBar[i].RankTitle)
			{
			case 1:
			pDrawGUI(0x9960, (float)PosX - 3, (float)PosY - 65, 95, 25);
			break;
			case 2:
			pDrawGUI(0x9961, (float)PosX - 9, (float)PosY - 66, 95, 25);
			break;
			case 3:
			pDrawGUI(0x9962, (float)PosX - 1, (float)PosY - 70, 95, 27);
			break;
			case 4:
			pDrawGUI(0x9963, (float)PosX - 0, (float)PosY - 70, 95, 27);
			break;
			case 5:
			pDrawGUI(0x9964, (float)PosX - 5, (float)PosY - 70, 95, 28);
			break;
			case 6:
			pDrawGUI(0x9965, (float)PosX - 2, (float)PosY - 72, 95, 27);
			break;
			case 7:
			pDrawGUI(0x9966, (float)PosX - 3, (float)PosY - 72, 100, 27);
			break;
			case 8:
			pDrawGUI(0x9967, (float)PosX - 4, (float)PosY - 69, 100, 25);
			break;
			case 9:
			pDrawGUI(0x9968, (float)PosX - 1, (float)PosY - 70, 100, 25);
			break;
			case 10:
			pDrawGUI(0x9969, (float)PosX - 6, (float)PosY - 72, 100, 25);
			break;
			case 11:
			pDrawGUI(0x9970, (float)PosX - 11, (float)PosY - 70, 100, 27);
			break;
			case 12:
			pDrawGUI(0x9971, (float)PosX - 9, (float)PosY - 70, 100, 27);
			break;
			case 13:
			pDrawGUI(0x9972, (float)PosX - 2, (float)PosY - 70, 100, 29);
			break;
			case 14:
			pDrawGUI(0x9973, (float)PosX - 12, (float)PosY - 71, 110, 28);
			break;
			case 15:
			pDrawGUI(0x9980, (float)PosX - 12, (float)PosY - 71, 126, 27);
			break;
			}


			if (PlayerBar[i].Reset >= Config.Min && PlayerBar[i].Reset < Config.Max)
			{
				pDrawColorText(Config.RankText, PosX, PosY - 40, 80, 1.5, eWhite1, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min1 && PlayerBar[i].Reset < Config.Max1)
			{
				pDrawColorText(Config.RankText1, PosX, PosY - 40, 80, 1.5, eWhite, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min2 && PlayerBar[i].Reset < Config.Max2)
			{
				pDrawColorText(Config.RankText2, PosX, PosY - 40, 80, 1.5, eExcellent, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min3 && PlayerBar[i].Reset < Config.Max3)
			{
				pDrawColorText(Config.RankText3, PosX, PosY - 40, 80, 1.5, eExcellent, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min4 && PlayerBar[i].Reset < Config.Max4)
			{
				pDrawColorText(Config.RankText4, PosX, PosY - 40, 80, 1.5, eAncient, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min5 && PlayerBar[i].Reset < Config.Max5)
			{
				pDrawColorText(Config.RankText5, PosX, PosY - 40, 80, 1.5, eAncient, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min6 && PlayerBar[i].Reset < Config.Max6)
			{
				pDrawColorText(Config.RankText6, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min7 && PlayerBar[i].Reset < Config.Max7)
			{
				pDrawColorText(Config.RankText7, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min8 && PlayerBar[i].Reset < Config.Max8)
			{
				pDrawColorText(Config.RankText8, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min9 && PlayerBar[i].Reset < Config.Max9)
			{
				pDrawColorText(Config.RankText9, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min10 && PlayerBar[i].Reset < Config.Max10)
			{
				pDrawColorText(Config.RankText10, PosX, PosY - 40, 80, 1.5, eYellow, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min11 && PlayerBar[i].Reset < Config.Max11)
			{
				pDrawColorText(Config.RankText11, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min12 && PlayerBar[i].Reset < Config.Max12)
			{
				pDrawColorText(Config.RankText12, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min13 && PlayerBar[i].Reset < Config.Max13)
			{
				pDrawColorText(Config.RankText13, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min14 && PlayerBar[i].Reset < Config.Max14)
			{
				pDrawColorText(Config.RankText14, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min15 && PlayerBar[i].Reset < Config.Max15)
			{
				pDrawColorText(Config.RankText15, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min16 && PlayerBar[i].Reset < Config.Max16)
			{
				pDrawColorText(Config.RankText16, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min17 && PlayerBar[i].Reset < Config.Max17)
			{
				pDrawColorText(Config.RankText17, PosX, PosY - 40, 80, 1.5, eBlue, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min18 && PlayerBar[i].Reset < Config.Max18)
			{
				pDrawColorText(Config.RankText18, PosX, PosY - 40, 80, 1.5, eBlue, 32, 3);
			}
			//------------ Rank thuoc tinh (chuot)
			if (PlayerBar[i].Long >= 16 && PlayerBar[i].Long <= 17)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 17 && PlayerBar[i].Long <= 18)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 18 && PlayerBar[i].Long <= 19)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 0 && PlayerBar[i].Long <= 0)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 1 && PlayerBar[i].Long <= 1)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 2 && PlayerBar[i].Long <= 2)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 32 && PlayerBar[i].Long <= 32)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 33 && PlayerBar[i].Long <= 33)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 34 && PlayerBar[i].Long <= 34)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 48 && PlayerBar[i].Long <= 48)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 49 && PlayerBar[i].Long <= 49)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 64 && PlayerBar[i].Long <= 64)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 66 && PlayerBar[i].Long <= 66)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 80 && PlayerBar[i].Long <= 80)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 81 && PlayerBar[i].Long <= 81)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 82 && PlayerBar[i].Long <= 82)
			{
			pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 96 && PlayerBar[i].Long <= 96)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 97 && PlayerBar[i].Long <= 97)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
		}
		else
		{
			if(!rankbar) return;
			// draw background and name
			 pSetBlend(true);
			float lineHeight = 25.0f * (pWinHeightReal - 0.6f);
			
			glColor4f(0.0f, 0.0f, 0.0f, 0.30f);
			pDrawBarForm((float)PosX, (float)PosY - 19, 0, lineHeight - 0.0, 0.0, 0);
			pDrawGUI(0x9960, (float)PosX, (float)PosY - 41, 80, 10);
			pDrawGUI(0x9960, (float)PosX + 16, (float)PosY - 29, 44, 9);
			pDrawColorText(lpObj->Name, PosX + 999, PosY - 19, 67, 1.5, eShinyGreen, 9, 3);

			float BarWidth = 40.1f * (PlayerBar[i].Life / (PlayerBar[i].Life * 1.0f));
			pDrawColorButton(32513, (float)PosX + 18, (float)PosY - 27, BarWidth, 2.0, 0, 0, eRed);
			float SDBarWidth = 40.1f * (PlayerBar[i].SD / (PlayerBar[i].MaxSD * 1.0f));
			pDrawColorButton(32515, (float)PosX + 18, (float)PosY - 24, SDBarWidth, 2.0, 0, 0, eGold);

			
			switch (PlayerBar[i].RankTitle)
			{
			case 1:
			pDrawGUI(0x9960, (float)PosX - 3, (float)PosY - 65, 95, 25);
			break;
			case 2:
			pDrawGUI(0x9961, (float)PosX - 9, (float)PosY - 66, 95, 25);
			break;
			case 3:
			pDrawGUI(0x9962, (float)PosX - 1, (float)PosY - 70, 95, 27);
			break;
			case 4:
			pDrawGUI(0x9963, (float)PosX - 0, (float)PosY - 70, 95, 27);
			break;
			case 5:
			pDrawGUI(0x9964, (float)PosX - 5, (float)PosY - 70, 95, 28);
			break;
			case 6:
			pDrawGUI(0x9965, (float)PosX - 2, (float)PosY - 72, 95, 27);
			break;
			case 7:
			pDrawGUI(0x9966, (float)PosX - 3, (float)PosY - 72, 100, 27);
			break;
			case 8:
			pDrawGUI(0x9967, (float)PosX - 4, (float)PosY - 69, 100, 25);
			break;
			case 9:
			pDrawGUI(0x9968, (float)PosX - 1, (float)PosY - 70, 100, 25);
			break;
			case 10:
			pDrawGUI(0x9969, (float)PosX - 6, (float)PosY - 72, 100, 25);
			break;
			case 11:
			pDrawGUI(0x9970, (float)PosX - 11, (float)PosY - 70, 100, 27);
			break;
			case 12:
			pDrawGUI(0x9971, (float)PosX - 9, (float)PosY - 70, 100, 27);
			break;
			case 13:
			pDrawGUI(0x9972, (float)PosX - 2, (float)PosY - 70, 100, 29);
			break;
			case 14:
			pDrawGUI(0x9973, (float)PosX - 12, (float)PosY - 71, 110, 28);
			break;
			case 15:
			pDrawGUI(0x9980, (float)PosX - 12, (float)PosY - 71, 126, 27);
			break;
			}


			if (PlayerBar[i].Reset >= Config.Min && PlayerBar[i].Reset < Config.Max)
			{
				pDrawColorText(Config.RankText, PosX, PosY - 40, 80, 1.5, eWhite1, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min1 && PlayerBar[i].Reset < Config.Max1)
			{
				pDrawColorText(Config.RankText1, PosX, PosY - 40, 80, 1.5, eWhite, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min2 && PlayerBar[i].Reset < Config.Max2)
			{
				pDrawColorText(Config.RankText2, PosX, PosY - 40, 80, 1.5, eExcellent, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min3 && PlayerBar[i].Reset < Config.Max3)
			{
				pDrawColorText(Config.RankText3, PosX, PosY - 40, 80, 1.5, eExcellent, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min4 && PlayerBar[i].Reset < Config.Max4)
			{
				pDrawColorText(Config.RankText4, PosX, PosY - 40, 80, 1.5, eAncient, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min5 && PlayerBar[i].Reset < Config.Max5)
			{
				pDrawColorText(Config.RankText5, PosX, PosY - 40, 80, 1.5, eAncient, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min6 && PlayerBar[i].Reset < Config.Max6)
			{
				pDrawColorText(Config.RankText6, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min7 && PlayerBar[i].Reset < Config.Max7)
			{
				pDrawColorText(Config.RankText7, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min8 && PlayerBar[i].Reset < Config.Max8)
			{
				pDrawColorText(Config.RankText8, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min9 && PlayerBar[i].Reset < Config.Max9)
			{
				pDrawColorText(Config.RankText9, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			// --
			if (PlayerBar[i].Reset >= Config.Min10 && PlayerBar[i].Reset < Config.Max10)
			{
				pDrawColorText(Config.RankText10, PosX, PosY - 40, 80, 1.5, eYellow, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min11 && PlayerBar[i].Reset < Config.Max11)
			{
				pDrawColorText(Config.RankText11, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min12 && PlayerBar[i].Reset < Config.Max12)
			{
				pDrawColorText(Config.RankText12, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min13 && PlayerBar[i].Reset < Config.Max13)
			{
				pDrawColorText(Config.RankText13, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min14 && PlayerBar[i].Reset < Config.Max14)
			{
				pDrawColorText(Config.RankText14, PosX, PosY - 40, 80, 1.5, eOrange, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min15 && PlayerBar[i].Reset < Config.Max15)
			{
				pDrawColorText(Config.RankText15, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min16 && PlayerBar[i].Reset < Config.Max16)
			{
				pDrawColorText(Config.RankText16, PosX, PosY - 40, 80, 1.5, eSocket, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min17 && PlayerBar[i].Reset < Config.Max17)
			{
				pDrawColorText(Config.RankText17, PosX, PosY - 40, 80, 1.5, eBlue, 32, 3);
			}
			if (PlayerBar[i].Reset >= Config.Min18 && PlayerBar[i].Reset < Config.Max18)
			{
				pDrawColorText(Config.RankText18, PosX, PosY - 40, 80, 1.5, eBlue, 32, 3);
			}

			//---------------------------------- Rank thuoc tinh

			if (PlayerBar[i].Long >= 16 && PlayerBar[i].Long <= 17)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 17 && PlayerBar[i].Long <= 18)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 18 && PlayerBar[i].Long <= 19)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 0 && PlayerBar[i].Long <= 0)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 1 && PlayerBar[i].Long <= 1)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 2 && PlayerBar[i].Long <= 2)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 32 && PlayerBar[i].Long <= 32)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 33 && PlayerBar[i].Long <= 33)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 34 && PlayerBar[i].Long <= 34)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 48 && PlayerBar[i].Long <= 48)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 49 && PlayerBar[i].Long <= 49)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 64 && PlayerBar[i].Long <= 64)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 66 && PlayerBar[i].Long <= 66)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 80 && PlayerBar[i].Long <= 80)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 81 && PlayerBar[i].Long <= 81)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 82 && PlayerBar[i].Long <= 82)
			{
			pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 96 && PlayerBar[i].Long <= 96)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			if (PlayerBar[i].Long >= 97 && PlayerBar[i].Long <= 97)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 30, 17, 17);
			}
			//--------
		}
		pGLSwitchBlend();	// for blend objects
	}
	
	pGLSwitchBlend();	// for blend objects
	glColor3f(1.0, 1.0, 1.0);
}

void User::DrawRank(){
	VAngle Angle;
	int PosX, PosY, LifeProgress;
			lpViewObj lpObj = gObjUser.lpViewPlayer;
			DWORD CurrentTick = GetTickCount();
			DWORD Delay = (CurrentTick - gObjUser.m_TargetUpdateTick);
			// ----
			if (!lpObj || lpObj->m_Model.ObjectType != emPlayer || !lpObj->m_Model.Unknown4)
			{
				return;
			}
			// ----
			if(!rankbar) return;
			Angle.X = lpObj->m_Model.VecPosX;
			Angle.Y = lpObj->m_Model.VecPosY;
			Angle.Z = lpObj->m_Model.VecPosZ + lpObj->m_Model.Unknown216.Z + 100.0;
			float BarWidth1 = 80.0f;
			pGetPosFromAngle(&Angle, &PosX, &PosY);
			PosX -= (int)floor(BarWidth1 / (double)2.0);
			// For blend fix
		    pSetBlend(true);

			float lineHeight = 25.0f * (pWinHeightReal - 0.6f);
			
			glColor4f(0.0f, 0.0f, 0.0f, 0.60f);
			pDrawBarForm((float)PosX, (float)PosY - 19, 0, lineHeight - 0.0, 0.0, 0);
			pDrawGUI(0x9960, (float)PosX, (float)PosY - 19, 80, 10);
			pDrawGUI(0x9960, (float)PosX + 16, (float)PosY - 7.5, 44, 9);
			pDrawColorText(lpObj->Name, PosX + 7, PosY - 17, 67, 1.5, eShinyGreen, 9, 3);

			

			switch (ViewTitle)
			{
			case 1:
			pDrawGUI(0x9960, (float)PosX - 3, (float)PosY - 45, 90, 25);
			break;
			case 2:
			pDrawGUI(0x9961, (float)PosX - 9, (float)PosY - 45, 95, 25);
			break;
			case 3:
			pDrawGUI(0x9962, (float)PosX - 2, (float)PosY - 50, 95, 33);
			break;
			case 4:
			pDrawGUI(0x9963, (float)PosX - 1, (float)PosY - 47, 95, 25);
			break;
			case 5:
			pDrawGUI(0x9964, (float)PosX - 5, (float)PosY - 47, 95, 29);
			break;
			case 6:
			pDrawGUI(0x9965, (float)PosX - 7, (float)PosY - 45, 95, 27);
			break;
			case 7:
			pDrawGUI(0x9966, (float)PosX - 5, (float)PosY - 47, 95, 27);
			break;
			case 8:
			pDrawGUI(0x9967, (float)PosX - 4, (float)PosY - 47, 95, 27);
			break;
			case 9:
			pDrawGUI(0x9968, (float)PosX - 1, (float)PosY - 47, 95, 27);
			break;
			case 10:
			pDrawGUI(0x9969, (float)PosX - 9, (float)PosY - 47, 95, 26);
			break;
			case 11:
			pDrawGUI(0x9970, (float)PosX - 10, (float)PosY - 47, 100, 29);
			break;
			case 12:
			pDrawGUI(0x9971, (float)PosX - 9, (float)PosY - 47, 100, 28);
			break;
			case 13:
			pDrawGUI(0x9972, (float)PosX - 2, (float)PosY - 48, 95, 29);
			break;
			case 14:
			pDrawGUI(0x9973, (float)PosX - 12, (float)PosY - 47, 126, 27);
			break;
			case 15:
			pDrawGUI(0x9980, (float)PosX - 14, (float)PosY - 49, 110, 30);
			break;
			}

			if (ViewReset >= Config.Min && ViewReset < Config.Max)
			{
				pDrawColorText(Config.RankText, PosX - 10, PosY - 18, 100, 1.5, eWhite1, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min1 && ViewReset < Config.Max1)
			{
				pDrawColorText(Config.RankText1, PosX - 10, PosY - 18, 100, 1.5, eWhite, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min2 && ViewReset < Config.Max2)
			{
				pDrawColorText(Config.RankText2, PosX - 10, PosY - 18, 100, 1.5, eExcellent, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min3 && ViewReset < Config.Max3)
			{
				pDrawColorText(Config.RankText3, PosX - 10, PosY - 18, 100, 1.5, eExcellent, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min4 && ViewReset < Config.Max4)
			{
				pDrawColorText(Config.RankText4, PosX - 10, PosY - 18, 100, 1.5, eAncient, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min5 && ViewReset < Config.Max5)
			{
				pDrawColorText(Config.RankText5, PosX - 10, PosY - 18, 100, 1.5, eAncient, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min6 && ViewReset < Config.Max6)
			{
				pDrawColorText(Config.RankText6, PosX - 10, PosY - 18, 100, 1.5, eSocket, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min7 && ViewReset < Config.Max7)
			{
				pDrawColorText(Config.RankText7, PosX - 10, PosY - 18, 100, 1.5, eSocket, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min8 && ViewReset < Config.Max8)
			{
				pDrawColorText(Config.RankText8, PosX - 10, PosY - 18, 100, 1.5, eOrange, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min9 && ViewReset < Config.Max9)
			{
				pDrawColorText(Config.RankText9, PosX - 10, PosY - 18, 100, 1.5, eOrange, 32, 3);
			}
			// --
			if (ViewReset >= Config.Min10 && ViewReset < Config.Max10)
			{
				pDrawColorText(Config.RankText10, PosX - 10, PosY - 18, 100, 1.5, eYellow, 32, 3);
			}
			if (ViewReset >= Config.Min11 && ViewReset < Config.Max11)
			{
				pDrawColorText(Config.RankText11, PosX - 10, PosY - 18, 100, 1.5, eOrange, 32, 3);
			}
			if (ViewReset >= Config.Min12 && ViewReset < Config.Max12)
			{
				pDrawColorText(Config.RankText12, PosX - 10, PosY - 18, 100, 1.5, eOrange, 32, 3);
			}
			if (ViewReset >= Config.Min13 && ViewReset < Config.Max13)
			{
				pDrawColorText(Config.RankText13, PosX - 10, PosY - 18, 100, 1.5, eOrange, 32, 3);
			}
			if (ViewReset >= Config.Min14 && ViewReset < Config.Max14)
			{
				pDrawColorText(Config.RankText14, PosX - 10, PosY - 18, 100, 1.5, eOrange, 32, 3);
			}
			if (ViewReset >= Config.Min15 && ViewReset < Config.Max15)
			{
				pDrawColorText(Config.RankText15, PosX - 10, PosY - 18, 100, 1.5, eSocket, 32, 3);
			}
			if (ViewReset >= Config.Min16 && ViewReset < Config.Max16)
			{
				pDrawColorText(Config.RankText16, PosX - 10, PosY - 18, 100, 1.5, eSocket, 32, 3);
			}
			if (ViewReset >= Config.Min17 && ViewReset < Config.Max17)
			{
				pDrawColorText(Config.RankText17, PosX - 10, PosY - 18, 100, 1.5, eBlue, 32, 3);
			}
			if (ViewReset >= Config.Min18 && ViewReset < Config.Max18)
			{
				pDrawColorText(Config.RankText18, PosX - 10, PosY - 18, 100, 1.5, eBlue, 32, 3);
			}

			//---------------------------------- Rank thuoc tinh

			if (ViewLong >= 16 && ViewLong <= 17)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 17 && ViewLong <= 18)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 18 && ViewLong <= 19)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 0 && ViewLong <= 0)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 1 && ViewLong <= 1)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 2 && ViewLong <= 2)
			{
				pDrawGUI(0x9985, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 32 && ViewLong <= 32)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 33 && ViewLong <= 33)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 34 && ViewLong <= 34)
			{
				pDrawGUI(0x9986, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 48 && ViewLong <= 48)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 49 && ViewLong <= 49)
			{
				pDrawGUI(0x9987, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 64 && ViewLong <= 64)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 66 && ViewLong <= 66)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 80 && ViewLong <= 80)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 81 && ViewLong <= 81)
			{
				pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 82 && ViewLong <= 82)
			{
			pDrawGUI(0x9988, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 96 && ViewLong <= 96)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			if (ViewLong >= 97 && ViewLong <= 97)
			{
				pDrawGUI(0x9984, (float)PosX - 2, (float)PosY - 8, 17, 17);
			}
			//--------


	pGLSwitchBlend();	// for blend objects
	glColor3f(1.0, 1.0, 1.0);
}
void User::AllInOne()
{
	gObjUser.DrawHP();
	gObjUser.DrawRank();
}