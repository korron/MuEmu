#include "StdAfx.h"
#include "Utils.h"

void Warning(int Id)
{
	char szTmp[128];
	sprintf_s(szTmp,"Protection Macro #%d",Id);
	MessageBox(NULL,szTmp,"Warning!",NULL);
}

DWORD __ProtectionWarn1_MOV = 0x006D202C;

void __declspec(naked) __ProtectionWarn1()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 1
		CALL Warning
		ADD ESP,4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn1_MOV]
	}
}

DWORD __ProtectionWarn2_MOV = 0x006D1E75;

void __declspec(naked) __ProtectionWarn2()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 2
		CALL Warning
		ADD ESP,4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn2_MOV]
	}
}

DWORD __ProtectionWarn3_MOV = 0x006D12D5;

void __declspec(naked) __ProtectionWarn3()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 3
		CALL Warning
		ADD ESP,4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn3_MOV]
	}
}

DWORD __ProtectionWarn4_MOV = 0x006D092E;

void __declspec(naked) __ProtectionWarn4()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 4
		CALL Warning
		ADD ESP,4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn4_MOV]
	}
}

DWORD __ProtectionWarn5_MOV = 0x006D06CC;

void __declspec(naked) __ProtectionWarn5()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 5
		CALL Warning
		ADD ESP, 4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn5_MOV]
	}
}

DWORD __ProtectionWarn6_MOV = 0x006D11C6;

void __declspec(naked) __ProtectionWarn6()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 6
		CALL Warning
		ADD ESP, 4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn6_MOV]
	}
}

DWORD __ProtectionWarn7_MOV = 0x006D0A19;

void __declspec(naked) __ProtectionWarn7()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 7
		CALL Warning
		ADD ESP, 4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn7_MOV]
	}
}

DWORD __ProtectionWarn8_MOV = 0x006D07FD;

void __declspec(naked) __ProtectionWarn8()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 8
		CALL Warning
		ADD ESP, 4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn8_MOV]
	}
}

DWORD __ProtectionWarn9_MOV = 0x006D1F53;

void __declspec(naked) __ProtectionWarn9()
{
	__asm
	{
		PUSHAD
		PUSHFD
		PUSH 9
		CALL Warning
		ADD ESP, 4
		POPFD
		POPAD
		JMP DWORD PTR DS:[__ProtectionWarn9_MOV]
	}
}

LPBYTE _HOOK		= (LPBYTE)0x00CA0BC0;

void Hook()
{
	DWORD OldProtect;
	VirtualProtect((LPVOID)0x0401000,0x00C16FFF,PAGE_EXECUTE_READ,&OldProtect);
}

void __declspec(naked) __Hook()
{
	__asm
	{
		PUSHAD
		PUSHFD
		CALL Hook
		POPFD
		POPAD
		JMP DWORD PTR DS:[_HOOK]
	}
}

void ProtectionWarnStart()
{
	HookBYTE((LPVOID)0x0A294765,0xE9);
	HookDWORD((LPVOID)(0x0A294765+1),((DWORD)&__ProtectionWarn1 - (0x0A294765+5)));

	HookBYTE((LPVOID)0x0A339F06,0xE9);
	HookDWORD((LPVOID)(0x0A339F06+1),((DWORD)&__ProtectionWarn2 - (0x0A339F06+5)));

	HookBYTE((LPVOID)0x0A33C348,0xE9);
	HookDWORD((LPVOID)(0x0A33C348+1),((DWORD)&__ProtectionWarn3 - (0x0A33C348+5)));

	HookBYTE((LPVOID)0x0A42052E,0xE9);
	HookDWORD((LPVOID)(0x0A42052E+1),((DWORD)&__ProtectionWarn4 - (0x0A42052E+5)));

	HookBYTE((LPVOID)0x0A5E001A,0xE9);
	HookDWORD((LPVOID)(0x0A5E001A+1),((DWORD)&__ProtectionWarn5 - (0x0A5E001A+5)));

	HookBYTE((LPVOID)0x0A985490,0xE9);
	HookDWORD((LPVOID)(0x0A985490+1),((DWORD)&__ProtectionWarn6 - (0x0A985490+5)));

	HookBYTE((LPVOID)0x0AD20B2F,0xE9);
	HookDWORD((LPVOID)(0x0AD20B2F+1),((DWORD)&__ProtectionWarn7 - (0x0AD20B2F+5)));

	HookBYTE((LPVOID)0x09E0184D,0xE9);
	HookDWORD((LPVOID)(0x09E0184D+1),((DWORD)&__ProtectionWarn8 - (0x09E0184D+5)));

	HookBYTE((LPVOID)0x01188833,0xE9);
	HookDWORD((LPVOID)(0x01188833+1),((DWORD)&__ProtectionWarn9 - (0x01188833+5)));

	HookDWORD((LPVOID)(0x004D8E0F+1),(DWORD)&__Hook - (0x004D8E0F+5));
}