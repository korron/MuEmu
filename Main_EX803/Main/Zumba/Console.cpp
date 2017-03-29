#include "StdAfx.h"
//#include "Console.h"

#if (_DEBUG_CONSOLE == 1)

//teste meu
#define MAX_BUFF 1024
//teste meu


Logger cLog;
DWORD PiD;

Logger::Logger()
{
}

Logger::~Logger()
{
}

void closeMenu()
{
	char buf[MAX_BUFF];
	HWND hwnd = NULL;

	wsprintf(buf,(CONSOLETITLE));  //name
	SetConsoleTitle((LPCTSTR)buf);  //the window

	while(hwnd == NULL)
		hwnd = ::FindWindowEx(NULL, NULL, NULL, (LPCTSTR)buf);

	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);  //ok actually remove the close button
	//DeleteMenu(hmenu, SC_MINIMIZE, MF_BYCOMMAND);
	DeleteMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);
	DeleteMenu(hmenu, SC_MOUSEMENU, MF_BYCOMMAND);
	DeleteMenu(hmenu, SC_SIZE, MF_BYCOMMAND);
	DeleteMenu(hmenu, SC_MOVE, MF_BYCOMMAND);
	::SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME);
}  //end CloseMenu()
//fim teste meu
void __stdcall LoggerCore(PVOID pVoid)
{
	AllocConsole();
	closeMenu();
	SetConsoleTitleA(CONSOLETITLE);
	while(true)
		Sleep(1);
}


void Logger::InitCore()
{
	CreateThread( 0 , 0 , (LPTHREAD_START_ROUTINE) LoggerCore , 0 , 0 , &PiD ); 
	Sleep(100);

	this->ConsoleOutput("[ COMMON SERVER ] Console Loaded");
}

void Logger::ConsoleOutput(const char* Format, ...)
{
	FILE * file = fopen("ConsoleLog.txt","a");
	
	if (file == NULL)
	{
		MessageBoxA(NULL,"Error in Opening ConsoleLog.txt","ERROR",MB_ICONSTOP);
	}

	SYSTEMTIME t;
	GetLocalTime(&t);

	char Message[3072];
	DWORD dwBytesWritten;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message,Format, pArguments);
	va_end(pArguments);
	char currdate[11] = {0};
	sprintf(currdate, "(%02d:%02d:%02d)", t.wHour, t.wMinute, t.wSecond);
	char outputmsg[3072];
	sprintf(outputmsg,"%s %s\n", currdate,Message);
	WriteFile(Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);

	fprintf(file,outputmsg);

	fclose(file);
}
//teste meu

extern Logger cLog;

#endif