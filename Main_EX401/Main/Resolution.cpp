#include "stdafx.h"
#include "Resolution.h"
#include "Offset.h"
#include "Util.h"

float Resolution_ClipX1 = 2000.0f;
float Resolution_ClipX2 = 2000.0f;

void InitResolution() // OK
{
	SetCompleteHook(0xE9,0x005E4775,&ResolutionSwitch);

	SetCompleteHook(0xE9,0x005E5A1B,&ResolutionSwitchFont);

	SetCompleteHook(0xE9,0x0073077D,&ResolutionMoveList);
}

__declspec(naked) void ResolutionSwitch() // OK
{
	static DWORD ResolutionSwitchAddress1 = 0x005E4803;

	_asm
	{
		Mov Edx,Dword Ptr Ds:[MAIN_RESOLUTION]
		Mov Dword Ptr Ss:[Ebp-0x338],Edx
		Cmp Dword Ptr Ss:[Ebp-0x338],0x00
		Jnz NEXT1
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],640
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],480
		Jmp EXIT
		NEXT1:
		Cmp Dword Ptr Ss:[Ebp-0x338],0x01
		Jnz NEXT2
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],800
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],600
		Jmp EXIT
		NEXT2:
		Cmp Dword Ptr Ss:[Ebp-0x338],0x02
		Jnz NEXT3
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1024
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],768
		Jmp EXIT
		NEXT3:
		Cmp Dword Ptr Ss:[Ebp-0x338],0x03
		Jnz NEXT4
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1280
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],1024
		Jmp EXIT
		NEXT4:
		Cmp Dword Ptr Ss:[Ebp-0x338],0x04
		Jnz NEXT5
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1366
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],768
		Jmp EXIT
		NEXT5:
		Cmp Dword Ptr Ss:[Ebp-0x338],0x05
		Jnz NEXT6
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1440
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],900
		Jmp EXIT
		NEXT6:
		Cmp Dword Ptr Ss:[Ebp-0x338],0x06
		Jnz NEXT7
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1600
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],900
		Jmp EXIT
		NEXT7:
		Cmp Dword Ptr Ss:[Ebp-0x338],0x07
		Jnz NEXT8
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1680
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],1050
		Jmp EXIT
		NEXT8:
		Cmp Dword Ptr Ss:[Ebp-0x338],0x08
		Jnz EXIT
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_X],1920
		Mov Dword Ptr Ds:[MAIN_RESOLUTION_Y],1080
		EXIT:
		Jmp [ResolutionSwitchAddress1]
	}
}

__declspec(naked) void ResolutionSwitchFont() // OK
{
	static DWORD ResolutionSwitchFontAddress1 = 0x005E5A95;

	_asm
	{
		Mov Ecx,Dword Ptr Ds:[MAIN_RESOLUTION_X]
		Mov Dword Ptr Ss:[Ebp-0xEB4],Ecx
		Cmp Dword Ptr Ss:[Ebp-0xEB4],640
		Jnz NEXT1
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0C
		Jmp EXIT
		NEXT1:
		Cmp Dword Ptr Ss:[Ebp-0xEB4],800
		Jnz NEXT2
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0D
		Jmp EXIT
		NEXT2:
		Cmp Dword Ptr Ss:[Ebp-0xEB4],1024
		Jnz NEXT3
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0E
		Jmp EXIT
		NEXT3:
		Cmp Dword Ptr Ss:[Ebp-0xEB4],1280
		Jnz NEXT4
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0F
		Jmp EXIT
		NEXT4:
		Mov Dword Ptr Ds:[MAIN_FONT_SIZE],0x0F
		Push Resolution_ClipX1
		Push 0x00814AA0
		Call [SetFloat]
		Add Esp,0x08
		Push Resolution_ClipX2
		Push 0x00814AB8
		Call [SetFloat]
		Add Esp,0x08
		EXIT:
		Jmp [ResolutionSwitchFontAddress1]
	}
}

__declspec(naked) void ResolutionMoveList() // OK
{
	static DWORD ResolutionMoveListAddress1 = 0x0073087B;
	static DWORD ResolutionMoveListAddress2 = 0x00730786;

	_asm
	{
		Mov Ecx,Dword Ptr Ds:[MAIN_RESOLUTION_X]
		Mov Dword Ptr Ss:[Ebp-0x08],Ecx
		Cmp Dword Ptr Ss:[Ebp-0x08],0x500
		Jbe EXIT
		Jmp [ResolutionMoveListAddress1]
		EXIT:
		Jmp [ResolutionMoveListAddress2]
	}
}
