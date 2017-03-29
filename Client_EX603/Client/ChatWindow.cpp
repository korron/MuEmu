#include "stdafx.h"
#include "ChatWindow.h"
#include "Util.h"

DWORD ChatValueMessageType;
DWORD ChatValueMessagePosition;
DWORD ChatValueMessageHeight;
DWORD ChatValueMessageCount;
DWORD ChatValueMessageScroll;

void InitChatWindow() // OK
{
	SetCompleteHook(0xE9,0x0078B0BC,&ChatWindowDisplay);

	SetCompleteHook(0xE9,0x00789765,&ChatWindowMessage1);

	SetCompleteHook(0xE9,0x00789A61,&ChatWindowMessage2);

	SetCompleteHook(0xE9,0x00789DAA,&ChatWindowMessage3);
}

__declspec(naked) void ChatWindowDisplay() // OK
{
	static DWORD ChatWindowDisplayAddress1 = 0x0078B8C0;
	static DWORD ChatWindowDisplayAddress2 = 0x0078B870;
	static DWORD ChatWindowDisplayAddress3 = 0x00788A80;
	static DWORD ChatWindowDisplayAddress4 = 0x0078B0C1;

	__asm
	{
		Call [ChatWindowDisplayAddress1]
		Mov ChatValueMessageType,Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Mov Eax,Dword Ptr Ds:[Ecx+0x128]
		Mov ChatValueMessagePosition,Eax
		Mov Eax,Dword Ptr Ds:[Ecx+0x138]
		Mov ChatValueMessageHeight,Eax
		Mov Eax,Dword Ptr Ds:[Ecx+0x13C]
		Mov ChatValueMessageCount,Eax
		Mov Eax,Dword Ptr Ds:[Ecx+0x148]
		Mov ChatValueMessageScroll,Eax
		Mov Dword Ptr Ds:[Ecx+0x128],0xBA
		Mov Dword Ptr Ds:[Ecx+0x138],0x64
		Mov Dword Ptr Ds:[Ecx+0x13C],0x04
		Push 0x03
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Call [ChatWindowDisplayAddress2]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Call [ChatWindowDisplayAddress3]
		Push ChatValueMessageType
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Call [ChatWindowDisplayAddress2]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Mov Eax,ChatValueMessagePosition
		Mov Dword Ptr Ds:[Ecx+0x128],Eax
		Mov Eax,ChatValueMessageHeight
		Mov Dword Ptr Ds:[Ecx+0x138],Eax
		Mov Eax,ChatValueMessageCount
		Mov Dword Ptr Ds:[Ecx+0x13C],Eax
		Mov Eax,ChatValueMessageScroll
		Mov Dword Ptr Ds:[Ecx+0x148],Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Call [ChatWindowDisplayAddress3]
		Jmp [ChatWindowDisplayAddress4]
	}
}

__declspec(naked) void ChatWindowMessage1() // OK
{
	static DWORD ChatWindowMessageAddress1 = 0x00789824;
	static DWORD ChatWindowMessageAddress2 = 0x009D00C5;
	static DWORD ChatWindowMessageAddress3 = 0x0078976C;

	__asm
	{
		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
		Jnz EXIT
		Mov Dword Ptr Ss:[Ebp-0x94],0x00
		Jmp [ChatWindowMessageAddress1]
		EXIT:
		Push 0x40
		Call [ChatWindowMessageAddress2]
		Jmp [ChatWindowMessageAddress3]
	}
}

__declspec(naked) void ChatWindowMessage2() // OK
{
	static DWORD ChatWindowMessageAddress1 = 0x00789B5A;
	static DWORD ChatWindowMessageAddress2 = 0x009D00C5;
	static DWORD ChatWindowMessageAddress3 = 0x00789A68;

	__asm
	{
		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
		Jnz EXIT
		Mov Dword Ptr Ss:[Ebp-0xE4],0x00
		Jmp [ChatWindowMessageAddress1]
		EXIT:
		Push 0x40
		Call [ChatWindowMessageAddress2]
		Jmp [ChatWindowMessageAddress3]
	}
}

__declspec(naked) void ChatWindowMessage3() // OK
{
	static DWORD ChatWindowMessageAddress1 = 0x00789E6F;
	static DWORD ChatWindowMessageAddress2 = 0x009D00C5;
	static DWORD ChatWindowMessageAddress3 = 0x00789DB1;

	__asm
	{
		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
		Jnz EXIT
		Mov Dword Ptr Ss:[Ebp-0x154],0x00
		Jmp [ChatWindowMessageAddress1]
		EXIT:
		Push 0x40
		Call [ChatWindowMessageAddress2]
		Jmp [ChatWindowMessageAddress3]
	}
}
