#include "stdafx.h"
#include "Item.h"
#include "TMemory.h"
#include "Import.h"
#include "CustomBow.h"
#include "ToolKit.h"
#include "Defines.h"

// ----------------------------------------------------------------------------------------------
DWORD IsBowItem = 0;
DWORD IsCrossItem = 0;
DWORD BowValue = 0x09C;
DWORD MaxBoneCount = 0x108;
DWORD WorldPosition = 0x0FC;

DWORD oCreateEffect = 0x006D9070; // 1.04D ENG
DWORD ReturnBowCode = 0x0074A12E; // 1.04D ENG
DWORD BowPosition = 0x005CC8ED; // 1.04D ENG
DWORD NextBowPosition = 0x005CC92E; // 1.04D ENG
DWORD BowAddPlayerDimension_Offset = 0x0056617F; // 1.04D ENG

void __declspec(naked) cBowAddSkillEffect()
{
	_asm
	{
		mov ecx, dword ptr ss : [ebp - 0x4]
			mov dword ptr ss : [ebp - 0x14], ecx
			mov IsBowItem, ecx
	}
	// ---
	if (IsBowItem == ITEM2(4, 100)) // Angelic Bow
	{
		_asm
		{
			push - 1
				push 0
				push 0
				mov dx, word ptr ss : [ebp + 0x18]
				push edx
				mov ax, word ptr ss : [ebp + 0x14]
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				mov dx, word ptr ds : [ecx + 0x2C]
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				push eax
				mov ecx, dword ptr ss : [ebp - 0x0C]
				push ecx
				mov edx, dword ptr ss : [ebp + 0x0C]
				add edx, BowValue
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				add eax, MaxBoneCount
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				add ecx, WorldPosition
				push ecx
				push 297
				call oCreateEffect
		}
	}
	_asm
	{
		jmp ReturnBowCode
	}
}

void __declspec(naked) cBowAddInventoryPos()
{
	_asm
	{

		mov ecx, dword ptr ss : [ebp + 0x8]
			mov dword ptr ss : [ebp + 0x8], ecx
			mov IsBowItem, ecx
	}
	// ---
	if (IsBowItem == 0x0CAB)
	{
		_asm{jmp BowPosition}
	}
	else if (IsBowItem == ITEM2(4, 100))
	{
		_asm{jmp BowPosition}
	}
	else
	{
		_asm{jmp NextBowPosition}
	}
}

void __declspec(naked) cBowAddPlayerDimension()
{
	_asm
	{
		cmp dword ptr ss : [ebp + 0x1c], 0x0CA7
			je ReturnLoad
			cmp dword ptr ss : [ebp + 0x1c], ITEM2(4, 100)
			je ReturnLoad
			// ---
		ReturnLoad :
		// ---
		jmp BowAddPlayerDimension_Offset
	}
}

void InitBows()
{
	SetRange((LPVOID)iBowAddSkillEffect, 6, ASM::NOP);
	SetJmp((LPVOID)iBowAddSkillEffect, cBowAddSkillEffect);
	// ----
	SetRange((LPVOID)iBowAddInventoryPos, 6, ASM::NOP);
	SetJmp((LPVOID)iBowAddInventoryPos, cBowAddInventoryPos);
	// ----
	SetRange((LPVOID)iBowAddPlayerDimension, 7, ASM::NOP);
	SetJmp((LPVOID)iBowAddPlayerDimension, cBowAddPlayerDimension);
	// ----
}
