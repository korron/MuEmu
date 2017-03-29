// MacroCheck.h: interface for the CMacroCheck class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define LLKHF_LOWER_IL_INJECTED 0x00000002

#define MAX_MACRO_CHECK_KEY 2

#define KEYPRESS_DELAY 5000

class CMacroCheck
{
public:
	CMacroCheck();
	virtual ~CMacroCheck();
	void Init(HINSTANCE hins);
	void OnKeyboardKeypress(int index);
	bool CheckKeypessMaxDelay(int index,int MaxDelay);
	bool CheckKeypessMaxCount(int index,int MaxCount);
	static DWORD WINAPI MacroCheckThread(CMacroCheck* lpMacroCheck);
	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam);
public:
	static HHOOK m_HookLLKB;
private:
	HINSTANCE m_MacroCheckHins;
	HANDLE m_MacroCheckThreadHandle;
	DWORD m_KeypressDelay[MAX_MACRO_CHECK_KEY];
	DWORD m_KeypressCount[MAX_MACRO_CHECK_KEY];
};

extern CMacroCheck gMacroCheck;
