#include "stdafx.h"
#include "HealthBar.h"
#include "Util.h"

NEW_HEALTH_BAR gNewHealthBar[MAX_MAIN_VIEWPORT];

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
	((void(*)())0x005BA770)();

	int PosX, PosY, LifeProgress;
	float LifeBarWidth = 38.0f;
	char LifeDisplay[20];
	VAngle Angle;

	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
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

		int LifePercent = lpNewHealthBar->rate/10;

		Angle.X = *(float*)(ViewportAddress+0x404);

		Angle.Y = *(float*)(ViewportAddress+0x408);

		Angle.Z = *(float*)(ViewportAddress+0x40C) + *(float*)(ViewportAddress+0x3E8) + 100.0f;

		pGetPosFromAngle(&Angle, &PosX, &PosY);

		PosX -= (int)floor(LifeBarWidth / (double)2.0);

		if((pCursorX >= PosX) && ((float)pCursorX <= (float)PosX + LifeBarWidth) && (pCursorY >= PosY - 2) && (pCursorY < PosY + 6))
		{
			wsprintf(LifeDisplay, "HP : %d0%%", LifePercent);
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF);
			pDrawText(pTextThis(), PosX, PosY - 6, LifeDisplay, 0, 0, (LPINT)1, 0);
		}

		pSetBlend(true);

		glColor4f(0.0, 0.0, 0.0, 0.5);
		pDrawBarForm((float)(PosX + 1), (float)(PosY + 1), LifeBarWidth + 4.0f, 5.0f, 0.0f, 0);
		pGLSwitchBlend();

		glColor3f(0.2f, 0.0, 0.0);
		pDrawBarForm((float)PosX, (float)PosY, LifeBarWidth + 4.0f, 5.0f, 0.0, 0);

		glColor3f(0.19607843f, 0.039215688f, 0.0);
		pDrawBarForm((float)(PosX + 2), (float)(PosY + 2), LifeBarWidth, 1.0f, 0.0, 0);

		if(LifePercent > 10)
		{
			LifeProgress = 10;
		}
		else
		{
			LifeProgress = LifePercent;
		}

		glColor3f(0.98039216f, 0.039215688f, 0.0);

		for(int i = 0; i < LifeProgress; i++)
		{
			pDrawBarForm((float)(i * 4 + PosX + 2), (float)(PosY + 2), 3.0, 2.0, 0.0, 0);
		}

		pGLSwitch();
	}

	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);
}
