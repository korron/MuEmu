#include "stdafx.h"
#include "Camera.h"
#include "ChatWindow.h"
#include "Minimap.h"
#include "Offset.h"
#include "TrayMode.h"

HHOOK HookKB;
HHOOK HookMS;
BOOL VKF9_State = 0;
BYTE MainChecksum[5] = {0x8B,0x4D,0xF8,0x88,0x41};

LRESULT CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam) // OK
{
	if(nCode == HC_ACTION)
	{
		if(((DWORD)lParam & (1 << 30)) != 0 && ((DWORD)lParam & (1 << 31)) != 0)
		{
			switch(wParam)
			{
				case VK_F9:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						VKF9_State ^= 1;
						SendMessage(*(HWND*)(MAIN_WINDOW),WM_RBUTTONUP,VK_F9,MK_RBUTTON);
					}
					break;
				case VK_F10:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						gCamera.Toggle();
					}
					break;
				case VK_F11:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						gCamera.Restore();
					}
					break;
				case VK_F12:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						gTrayMode.Toggle();
					}
					break;
				default:
					break;
			}
		}
	}

	return CallNextHookEx(HookKB,nCode,wParam,lParam);
}

LRESULT CALLBACK MouseProc(int nCode,WPARAM wParam,LPARAM lParam) // OK
{
	if(nCode == HC_ACTION)
	{
		MOUSEHOOKSTRUCTEX* HookStruct = (MOUSEHOOKSTRUCTEX*)lParam;

		switch(wParam)
		{
			case WM_MOUSEMOVE:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					gCamera.Move(HookStruct);
				}
				break;
			case WM_MBUTTONDOWN:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					gCamera.SetIsMove(1);
					gCamera.SetCursorX(HookStruct->pt.x);
					gCamera.SetCursorY(HookStruct->pt.y);
				}
				break;
			case WM_MBUTTONUP:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					gCamera.SetIsMove(0);
				}
				break;
			case WM_MOUSEWHEEL:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					gCamera.Zoom(HookStruct);
				}
				break;
			default:
				break;
		}
	}

	return CallNextHookEx(HookMS,nCode,wParam,lParam);
}

LONG WINAPI CheckMacroThread() // OK
{
	while(!SleepEx(1000,0))
	{
		if(VKF9_State != 0)
		{
			SendMessage(*(HWND*)(MAIN_WINDOW),WM_RBUTTONDOWN,VK_F9,MK_RBUTTON);
		}
	}

	return 0;
}

void EntryProc(HINSTANCE hins) // OK
{
	if(memcmp((void*)0x005B2D62,MainChecksum,sizeof(MainChecksum)) != 0)
	{
		HookKB = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,hins,GetCurrentThreadId());

		HookMS = SetWindowsHookEx(WH_MOUSE,MouseProc,hins,GetCurrentThreadId());

		CreateThread(0,0,(LPTHREAD_START_ROUTINE)CheckMacroThread,0,0,0);

		InitChatWindow();

		InitMiniMap();

		gTrayMode.Init(hins);
	}
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			EntryProc((HINSTANCE)hModule);
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}
