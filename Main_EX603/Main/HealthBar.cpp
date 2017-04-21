#include "stdafx.h"
/*
#include "HealthBar.h"
#include "Util.h"
#include "Interface.h"
#include "User.h"
#include "Import.h"
#include "Defines.h"

NEW_HEALTH_BAR gNewHealthBar[MAX_MAIN_VIEWPORT];
bool lifebar = false;
void ClearNewHealthBar() // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		gNewHealthBar[n].index = 0xFFFF;
		gNewHealthBar[n].type = 0;
		gNewHealthBar[n].rate = 0;
	}
}

void InsertNewHealthBar(WORD index,BYTE type,BYTE rate) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index == 0xFFFF)
		{
			gNewHealthBar[n].index = index;
			gNewHealthBar[n].type = type;
			gNewHealthBar[n].rate = rate;
			return;
		}
	}
}

NEW_HEALTH_BAR* GetNewHealthBar(WORD index,BYTE type) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index != 0xFFFF)
		{
			if(gNewHealthBar[n].index == index && gNewHealthBar[n].type == type)
			{
				return &gNewHealthBar[n];
			}
		}
	}

	return 0;
}

void DrawNewHealthBar() // OK
{
	if (!lifebar)
	{
	((void(*)())0x005BA770)();

	int PosX, PosY;

	float LifeBarWidth = 38.0f;
	char LifeDisplay[20];
	VAngle Angle;

	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		lpViewObj lpObj         = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), n);
		
		DWORD ViewportAddress = ((DWORD(__thiscall*)(void*,DWORD))0x0096A4C0)(((void*(*)())0x00402BC0)(),n);

		if(!ViewportAddress)
		{
			continue;
		}

		if(*(BYTE*)(ViewportAddress+0x30C) == 0)
		{
			continue;
		}

		NEW_HEALTH_BAR* lpNewHealthBar = GetNewHealthBar(*(WORD*)(ViewportAddress+0x7E),*(BYTE*)(ViewportAddress+0x320));

		if(lpNewHealthBar == 0)
		{
			continue;
		}

		float LifePercent = 6.0f * (lpNewHealthBar->rate/10);

		Angle.X = *(float*)(ViewportAddress+0x404);

		Angle.Y = *(float*)(ViewportAddress+0x408);

		Angle.Z = *(float*)(ViewportAddress+0x40C) + *(float*)(ViewportAddress+0x3E8) + 100.0f;

		pGetPosFromAngle(&Angle, &PosX, &PosY);

		PosX -= (int)floor(LifeBarWidth / (double)2.0);

		pSetBlend(true);

		glColor4f(0.0, 0.0, 0.0, 0.5);
		pDrawBarForm((float)(PosX - 13), (float)(PosY - 5.5), LifeBarWidth + 30.0f, 15.0f, 0.0f, 0);
		pGLSwitchBlend();

		glColor3f(2.0f, 0.0, 0.0);
		pDrawBarForm((float)(PosX - 9.5), (float)(PosY + 5), LifePercent, 2.0, 0.0, 0);

		pDrawColorText(lpObj->Name, PosX - 28, PosY - 6, 100, 1, eWhite, 9, 3);

		pGLSwitch();

	}

	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);
	}
}
*/