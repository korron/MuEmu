#include "StdAfx.h"
#include "SmokeEffect.h"
#include "ToolKit.h"
#include "Offset.h"
#include "Import.h"
#include "Defines.h"

DWORD pItemType = 0;

bool g_sEnabled = GetPrivateProfileIntA("Setting", "SmokerEffect", 0, ".\\Settings.ini");

__declspec(naked) void SetItemEffect()
{
	__asm
	{
		Mov pItemType, Eax
	}

	switch (pItemType)
	{
	case ITEM2(11, 100):
	{
							 __asm
							 {
								 Mov Esi, HDK_ITEM_EFFECT_ALLOW
									 JMP Esi
							 }
	}
		break;
	}

	__asm
	{
		Mov Esi, HDK_ITEM_EFFECT_NOT_ALLOW
			JMP Esi
	}
}

__declspec(naked) void SetColorEffect()
{
	__asm
	{
		Mov pItemType, Ecx
	}


	switch (pItemType)
	{
	case ITEM2(11, 100): //Yellow
		__asm
		{
			MOV EDX, DWORD PTR SS : [EBP + 0xC]
				MOV DWORD PTR DS : [EDX + 0x9C], 0x437a0000     //Red Color Value
				MOV EAX, DWORD PTR SS : [EBP + 0xC]
				MOV DWORD PTR DS : [EAX + 0xA0], 0x437a0000    //Green Color Value
				MOV ECX, DWORD PTR SS : [EBP + 0xC]
				MOV DWORD PTR DS : [ECX + 0xA4], 0x0   //Blue Color Value
		}
		break;	
	}

	__asm
	{
		Mov Esi, HDK_NEXT_ITEM_COLOR
			JMP Esi
	}
}

void AttachNewEffect()
{
	 if (!g_sEnabled)
		 return;

	DWORD dwPotect;

	dwPotect = ToolKit.UnProtect(HDK_SET_ITEM_EFFECT, 11); //12
	ToolKit.SetNop(HDK_SET_ITEM_EFFECT, 11);//12
	ToolKit.WriteJmp(HDK_SET_ITEM_EFFECT, (DWORD)&SetItemEffect);
	ToolKit.Protect(HDK_SET_ITEM_EFFECT, 21, dwPotect); //22

	dwPotect = ToolKit.UnProtect(HDK_SET_COLOR_EFFECT, 30);//46
	ToolKit.SetNop(HDK_SET_COLOR_EFFECT, 30); //46
	ToolKit.WriteJmp(HDK_SET_COLOR_EFFECT, (DWORD)&SetColorEffect);
	ToolKit.Protect(HDK_SET_COLOR_EFFECT, 45, dwPotect); //56
}