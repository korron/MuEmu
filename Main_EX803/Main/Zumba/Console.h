#ifndef Logger_H
#define Logger_H

#include "StdAfx.h"

#define _DEBUG_CONSOLE TRUE

#if (_DEBUG_CONSOLE == 1)

#define CONSOLETITLE "[ DEBUG MODE ] CODED BY WILLERSON "

class Logger
{
public:
	Logger();
	~Logger();
	void InitCore();
	void ConsoleOutput(const char* Format, ...);
	void closeMenu();
};
extern Logger cLog;
//void __stdcall LoggerCore();

#endif

#endif