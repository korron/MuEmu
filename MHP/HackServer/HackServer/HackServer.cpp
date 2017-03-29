#include "stdafx.h"
#include "resource.h"
#include "HackServer.h"
#include "MiniDump.h"
#include "ProcessManager.h"
#include "ServerDisplayer.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "ReadFiles.h"
#include "BlackList.h"
#include "Authenticate.h"
#include "Util.h"

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
HWND hWnd;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) // OK
{
	CMiniDump::Start();

	LoadString(hInstance,IDS_APP_TITLE,szTitle,MAX_LOADSTRING);
	LoadString(hInstance,IDC_HACKSERVER,szWindowClass,MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	if(InitInstance(hInstance,nCmdShow) == 0)
	{
		return 0;
	}

	gServerInfo.ReadStartupInfo("MHPServerInfo",".\\MHPServer.ini");

	#if(PROTECT_STATE == 1)

	gAuthenticate.Check();

	#endif

	char buff[256];

	wsprintf(buff,"[%s] MuEMU MHPServer (UserCount : %d)",HACKSERVER_VERSION,0);

	SetWindowText(hWnd,buff);

	gServerDisplayer.Init(hWnd);

	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,2),&wsa) == 0)
	{
		if(gSocketManager.Start(gServerInfo.m_HackServerPort) != 0)
		{
			gServerInfo.ReadInit();

			SetTimer(hWnd,TIMER_1000,1000,0);

			SetTimer(hWnd,TIMER_5000,5000,0);
		}
	}
	else
	{
		LogAdd(LOG_RED,"WSAStartup() failed with error: %d",WSAGetLastError());
	}

	gServerDisplayer.PaintAllInfo();

	SetTimer(hWnd,TIMER_2000,2000,0);

	HACCEL hAccelTable = LoadAccelerators(hInstance,(LPCTSTR)IDC_HACKSERVER);

	MSG msg;

	while(GetMessage(&msg,0,0,0) != 0)
	{
		if(TranslateAccelerator(msg.hwnd,hAccelTable,&msg) == 0)
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	CMiniDump::Clean();

	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) // OK
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance,(LPCTSTR)IDI_HACKSERVER);
	wcex.hCursor = LoadCursor(0,IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = (LPCSTR)IDC_HACKSERVER;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance,(LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance,int nCmdShow) // OK
{
	hInst = hInstance;

	hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPEDWINDOW | WS_THICKFRAME,CW_USEDEFAULT,0,600,600,0,0,hInstance,0);

	if(hWnd == 0)
	{
		return 0;
	}

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	return 1;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) // OK
{
	switch(message)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDM_ABOUT:
					DialogBox(hInst,(LPCTSTR)IDD_ABOUTBOX,hWnd,(DLGPROC)About);
					break;
				case IDM_EXIT:
					if(MessageBox(0,"Are you sure to terminate MHPServer?","Ask terminate server",MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				case IDM_RELOAD_CONFIG:
					gServerInfo.ReadConfig();
					break;
				case IDM_RELOAD_DUMP:
					gServerInfo.ReadDumpList();
					break;
				case IDM_RELOAD_CHECKSUM:
					gServerInfo.ReadChecksumList();
					break;
				case IDM_RELOAD_WINDOW:
					gServerInfo.ReadWindowList();
					break;
				case IDM_RELOAD_BLACKLIST:
					gServerInfo.ReadBlackList();
					break;
				case IDM_UPDATE:
					gReadFiles.UpdateInternalList();
					break;
				default:
					return DefWindowProc(hWnd,message,wParam,lParam);
			}
			break;
		case WM_TIMER:
			switch(wParam)
			{
				case TIMER_1000:
					gProcessManager.CheckProcess();
					break;
				case TIMER_2000:
					gServerDisplayer.Run();
					break;
				case TIMER_5000:
					TimeoutProc();
					gProcessManager.ClearProcessCache();
					break;
				default:
					break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd,message,wParam,lParam);
	}

	return 0;
}

LRESULT CALLBACK About(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam) // OK
{
	switch(message)
	{
		case WM_INITDIALOG:
			return 1;
		case WM_COMMAND:
			if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg,LOWORD(wParam));
				return 1;
			}
			break;
	}

	return 0;
}
