// TrayMode.h: interface for the CTrayMode class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define WM_TRAY_MODE_ICON (WM_USER+100)
#define WM_TRAY_MODE_MESSAGE (WM_USER+101)

class CTrayMode
{
public:
	CTrayMode();
	void Init(HINSTANCE hins);
	void Toggle();
	LONG GetMainWndProc();
	void ShowNotify(bool mode);
	static LRESULT CALLBACK TrayModeWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
private:
	HICON m_TrayIcon;
	WNDPROC m_MainWndProc;
};

extern CTrayMode gTrayMode;
