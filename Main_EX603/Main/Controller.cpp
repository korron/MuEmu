#include "stdafx.h"
#include "Controller.h"
#include "Import.h"
#include "Interface.h"
#include "Camera.h"
#include "User.h"
#include "Glow.h"
#include "Fog.h"
#include "TrayMode.h"
// ----------------------------------------------------------------------------------------------

Controller	gController;
// ----------------------------------------------------------------------------------------------

bool Controller::Load()
{
	if( !this->MouseHook )
	{
		this->MouseHook = SetWindowsHookEx(WH_MOUSE, this->Mouse, gController.Instance, GetCurrentThreadId());
		// ----
		if( !this->MouseHook )
		{
			return false;
		}
	}
	// ----
	if( !this->KeyboardHook )
	{
		this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, this->Keyboard, gController.Instance, NULL);
		// ----
		if( !this->KeyboardHook )
		{
			return false;
		}
	}
	// ----
	return true;
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Mouse(int Code, WPARAM wParam, LPARAM lParam)
{
	if( GetForegroundWindow() != pGameWindow )
	{
		return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
	}
	// ----
	MOUSEHOOKSTRUCTEX * Mouse	= (MOUSEHOOKSTRUCTEX*)lParam;
	// ----
	gCamera.Run(Mouse, wParam);
	// ----
	switch(wParam)
	{
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
		{
			gInterface.EventCameraUI(wParam);
			gInterface.EventUsersPanelWindow_Main(wParam);
			gInterface.DrawPSHOP_Main(wParam);
			gInterface.DrawPSHOP_OFFMAIN(wParam);
		}
		break;
	}
	// ----
	return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Keyboard(int Code, WPARAM wParam, LPARAM lParam)
{
	if( (Code == HC_ACTION) && (wParam == WM_KEYDOWN))
	{
		KBDLLHOOKSTRUCT Hook = *((KBDLLHOOKSTRUCT*)lParam);
		// ----
		switch(Hook.vkCode)
		{
			// --
/*
		case VK_TAB:
		{
					   if (GetForegroundWindow() == pGameWindow)
					   {
						   if (gInterface.showMiniMap)
						   {
							   gInterface.showMiniMap = false;
						   }
						   else
						   {
							   gInterface.showMiniMap = true;
						   }
					   }
		}
			break;
			*/
			// --
	case VK_F11:
		{
					 if (GetForegroundWindow() == pGameWindow)
					 {
						 if (gInterface.CheckUsersPanelWindow())
						 {
							 gInterface.CloseUsersPanelWindow();
						 }
						 else
						 {
							 gInterface.OpenUsersPanelWindow();
						 }
					 }
		}
			break;	
			// --
		case VK_F12:
			{
				if( gTrayMode.TempWindowProc == NULL )
				{
					gTrayMode.TempWindowProc = SetWindowLong(pGameWindow, GWL_WNDPROC, (long)gController.Window);
				}
				// ----
				gTrayMode.SwitchState();
			}
			break;
			// ---

		case VK_ESCAPE:
			{
				gInterface.CloseUsersPanelWindow();
			}
			break;
			
		}
	} 
	return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------
LRESULT Controller::Window(HWND Window, DWORD Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case TRAYMODE_ICON_MESSAGE:
		{
			switch(lParam)
			{
			case WM_LBUTTONDBLCLK:
				{
					gTrayMode.SwitchState();
				}
				break;
			}
		}
		break;
	}
	// ----
	return CallWindowProc((WNDPROC)gTrayMode.TempWindowProc, Window, Message, wParam, lParam);
}