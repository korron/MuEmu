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
	SetCompleteHook(0xE9,0x006DE587,&ChatWindowDisplay);

	SetCompleteHook(0xE9,0x006DCD0A,&ChatWindowMessage1);

	SetCompleteHook(0xE9,0x006DD011,&ChatWindowMessage2);

	SetCompleteHook(0xE9,0x006DD373,&ChatWindowMessage3);
}

__declspec(naked) void ChatWindowDisplay() // OK
{
	static DWORD ChatWindowDisplayAddress1 = 0x006DEC40;
	static DWORD ChatWindowDisplayAddress2 = 0x006DEBF5;
	static DWORD ChatWindowDisplayAddress3 = 0x006DC1E4;
	static DWORD ChatWindowDisplayAddress4 = 0x006DE58C;

	__asm
	{
		Call [ChatWindowDisplayAddress1]
		Mov ChatValueMessageType,Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Mov Eax,Dword Ptr Ds:[Ecx+0x0B4]
		Mov ChatValueMessagePosition,Eax
		Mov Eax,Dword Ptr Ds:[Ecx+0x0C4]
		Mov ChatValueMessageHeight,Eax
		Mov Eax,Dword Ptr Ds:[Ecx+0x0C8]
		Mov ChatValueMessageCount,Eax
		Mov Eax,Dword Ptr Ds:[Ecx+0x0D4]
		Mov ChatValueMessageScroll,Eax
		Mov Dword Ptr Ds:[Ecx+0x0B4],0xBA
		Mov Dword Ptr Ds:[Ecx+0x0C4],0x64
		Mov Dword Ptr Ds:[Ecx+0x0C8],0x04
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
		Mov Dword Ptr Ds:[Ecx+0x0B4],Eax
		Mov Eax,ChatValueMessageHeight
		Mov Dword Ptr Ds:[Ecx+0x0C4],Eax
		Mov Eax,ChatValueMessageCount
		Mov Dword Ptr Ds:[Ecx+0x0C8],Eax
		Mov Eax,ChatValueMessageScroll
		Mov Dword Ptr Ds:[Ecx+0x0D4],Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Call [ChatWindowDisplayAddress3]
		Jmp [ChatWindowDisplayAddress4]
	}
}

__declspec(naked) void ChatWindowMessage1() // OK
{
	static DWORD ChatWindowMessageAddress1 = 0x006DCDC5;
	static DWORD ChatWindowMessageAddress2 = 0x007DF302;
	static DWORD ChatWindowMessageAddress3 = 0x006DCD11;

	__asm
	{
		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
		Jnz EXIT
		Jmp [ChatWindowMessageAddress1]
		EXIT:
		Push 0x28
		Call [ChatWindowMessageAddress2]
		Jmp [ChatWindowMessageAddress3]
	}
}

__declspec(naked) void ChatWindowMessage2() // OK
{
	static DWORD ChatWindowMessageAddress1 = 0x006DD116;
	static DWORD ChatWindowMessageAddress2 = 0x007DF302;
	static DWORD ChatWindowMessageAddress3 = 0x006DD018;

	__asm
	{
		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
		Jnz EXIT
		Jmp [ChatWindowMessageAddress1]
		EXIT:
		Push 0x28
		Call [ChatWindowMessageAddress2]
		Jmp [ChatWindowMessageAddress3]
	}
}

__declspec(naked) void ChatWindowMessage3() // OK
{
	static DWORD ChatWindowMessageAddress1 = 0x006DD43A;
	static DWORD ChatWindowMessageAddress2 = 0x007DF302;
	static DWORD ChatWindowMessageAddress3 = 0x006DD37A;

	__asm
	{
		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
		Jnz EXIT
		Jmp [ChatWindowMessageAddress1]
		EXIT:
		Push 0x28
		Call [ChatWindowMessageAddress2]
		Jmp [ChatWindowMessageAddress3]
	}
}
