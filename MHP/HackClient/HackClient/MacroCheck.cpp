// MacroCheck.cpp: implementation of the CMacroCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MacroCheck.h"
#include "HackServerProtocol.h"
#include "Util.h"
//Modules
#include "ThreadCheck.h"

CMacroCheck gMacroCheck;
HHOOK CMacroCheck::m_HookLLKB;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMacroCheck::CMacroCheck()
{

}

CMacroCheck::~CMacroCheck()
{

}

void CMacroCheck::Init(HINSTANCE hins) // OK
{
	if(gMacroProtectSwitch == 0)
	{
		return;
	}

	this->m_MacroCheckHins = hins;

	memset(this->m_KeypressDelay,0,sizeof(this->m_KeypressDelay));

	memset(this->m_KeypressCount,0,sizeof(this->m_KeypressCount));

	this->m_MacroCheckThreadHandle = CreateThread(0,0,(LPTHREAD_START_ROUTINE)this->MacroCheckThread,this,0,&gThreadCheck.m_CheckThreadID[4]);
}

void CMacroCheck::OnKeyboardKeypress(int index) // OK
{
	if(gWindowHwnd == 0 || GetForegroundWindow() == (*(HWND*)(gWindowHwnd)))
	{
		if(this->CheckKeypessMaxDelay(index,KEYPRESS_DELAY) == 0)
		{
			this->m_KeypressDelay[index] = GetTickCount();
			this->m_KeypressCount[index] = 0;
		}

		switch(gMacroProtectNumber)
		{
			case MACRO_PROTECTION_NUMBER_NONE:
				if(this->CheckKeypessMaxCount(index,00) == 0){CHClientDisconnectSend(CLIENT_DISCONNECT_MACRO_DETECTION,0,0);}
				break;
			case MACRO_PROTECTION_NUMBER_LEVEL1:
				if(this->CheckKeypessMaxCount(index,25) == 0){CHClientDisconnectSend(CLIENT_DISCONNECT_MACRO_DETECTION,0,0);}
				break;
			case MACRO_PROTECTION_NUMBER_LEVEL2:
				if(this->CheckKeypessMaxCount(index,20) == 0){CHClientDisconnectSend(CLIENT_DISCONNECT_MACRO_DETECTION,0,0);}
				break;
			case MACRO_PROTECTION_NUMBER_LEVEL3:
				if(this->CheckKeypessMaxCount(index,15) == 0){CHClientDisconnectSend(CLIENT_DISCONNECT_MACRO_DETECTION,0,0);}
				break;
			case MACRO_PROTECTION_NUMBER_LEVEL4:
				if(this->CheckKeypessMaxCount(index,10) == 0){CHClientDisconnectSend(CLIENT_DISCONNECT_MACRO_DETECTION,0,0);}
				break;
			case MACRO_PROTECTION_NUMBER_LEVEL5:
				if(this->CheckKeypessMaxCount(index,05) == 0){CHClientDisconnectSend(CLIENT_DISCONNECT_MACRO_DETECTION,0,0);}
				break;
			default:
				CHClientDisconnectSend(CLIENT_DISCONNECT_MACRO_DETECTION,0,0);
				break;
		}
	}
}

bool CMacroCheck::CheckKeypessMaxDelay(int index,int MaxDelay) // OK
{
	return ((MaxDelay==0)?1:(((GetTickCount()-this->m_KeypressDelay[index])>=((DWORD)MaxDelay))?0:1));
}

bool CMacroCheck::CheckKeypessMaxCount(int index,int MaxCount) // OK
{
	return ((MaxCount==0)?1:(((++this->m_KeypressCount[index])>((DWORD)MaxCount))?0:1));
}

DWORD WINAPI CMacroCheck::MacroCheckThread(CMacroCheck* lpMacroCheck) // OK
{
	CMacroCheck::m_HookLLKB = SetWindowsHookEx(WH_KEYBOARD_LL,lpMacroCheck->LowLevelKeyboardProc,lpMacroCheck->m_MacroCheckHins,0);

	MSG msg;

	while(GetMessage(&msg,0,0,0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	UnhookWindowsHookEx(lpMacroCheck->m_HookLLKB);

	return 0;
}

LRESULT CALLBACK CMacroCheck::LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam) // OK
{
	if(nCode == HC_ACTION)
	{
		if(wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			KBDLLHOOKSTRUCT* HookStruct = (KBDLLHOOKSTRUCT*)lParam;

			if((HookStruct->flags & LLKHF_UP) != 0 && (HookStruct->flags & LLKHF_INJECTED) != 0 && (HookStruct->flags & LLKHF_LOWER_IL_INJECTED) == 0)
			{
				switch(HookStruct->vkCode)
				{
					case 0x30: //0
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x31: //1
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x32: //2
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x33: //3
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x34: //4
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x35: //5
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x36: //6
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x37: //7
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x38: //8
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x39: //9
						gMacroCheck.OnKeyboardKeypress(0);
						break;
					case 0x45: //E
						gMacroCheck.OnKeyboardKeypress(1);
						break;
					case 0x51: //Q
						gMacroCheck.OnKeyboardKeypress(1);
						break;
					case 0x52: //R
						gMacroCheck.OnKeyboardKeypress(1);
						break;
					case 0x57: //W
						gMacroCheck.OnKeyboardKeypress(1);
						break;
					default:
						break;
				}
			}
		}
	}

	return CallNextHookEx(CMacroCheck::m_HookLLKB,nCode,wParam,lParam);
}
