#include "StdAfx.h"
#include "StackWalker.h"
#include <tchar.h>
#include <time.h>


static TCHAR s_szExceptionLogFileName[_MAX_PATH] = _T("\\exceptions.log");  // default
static BOOL s_bUnhandledExeptionFilterSet = FALSE;

// Log Set Internals
int LogMDay;
int LogMonth;
int LogMYear;
BOOL GetTime = 0;

class StackWalkerToConsole : public StackWalker
{
private:
	FILE * file;
	char szFile[256];
	struct tm *today;
	time_t ltime;

public:
	StackWalkerToConsole()
	{
		if(GetTime == FALSE)
		{
			time(&ltime);
			today = new tm;
			localtime_s(today,&ltime);
			today->tm_year=today->tm_year + 1900;
			LogMYear=today->tm_year;
			LogMonth=today->tm_mon+1;
			LogMDay=today->tm_mday;
			wsprintf(szFile,"stack_%02d%02d%02d_%02d%02d.log",LogMYear, LogMonth, LogMDay, today->tm_hour, today->tm_min);
			GetTime = TRUE;
		}
		fopen_s(&file,szFile,"w");
	}

	~StackWalkerToConsole()
	{
		fclose(file);
	}
	char * GetStackLogFileName()
	{
		return szFile;
	}
protected:
	virtual void OnOutput(LPCTSTR szText)
	{
		char szMsg[512]; memset(szMsg,0,512);
		//base64.Encrypt(szText,strlen(szText),szMsg);
		wsprintf(szMsg,"%s",szText);
		fprintf(file,szMsg);
		fprintf(file,"\n");
	}
};

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	return NULL;
}

BOOL PreventSetUnhandledExceptionFilter()
{
	HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));
	if (hKernel32 == NULL)
	{
		return FALSE;
	}

	void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
	if(pOrgEntry == NULL)
	{
		return FALSE;
	}

	DWORD dwOldProtect = 0;
	SIZE_T jmpSize = 5;
#ifdef _M_X64
	jmpSize = 13;
#endif
	BOOL bProt = VirtualProtect(pOrgEntry, jmpSize, 
		PAGE_EXECUTE_READWRITE, &dwOldProtect);
	BYTE newJump[20];
	void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
#ifdef _M_IX86
	DWORD dwOrgEntryAddr = (DWORD) pOrgEntry;
	dwOrgEntryAddr += jmpSize; // add 5 for 5 op-codes for jmp rel32
	DWORD dwNewEntryAddr = (DWORD) pNewFunc;
	DWORD dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;
	// JMP rel32: Jump near, relative, displacement relative to next instruction.
	newJump[0] = 0xE9;  // JMP rel32
	memcpy(&newJump[1], &dwRelativeAddr, sizeof(pNewFunc));
#elif _M_X64
	newJump[0] = 0x49;  // MOV R15, ...
	newJump[1] = 0xBF;  // ...
	memcpy(&newJump[2], &pNewFunc, sizeof (pNewFunc));
	//pCur += sizeof (ULONG_PTR);
	newJump[10] = 0x41;  // JMP R15, ...
	newJump[11] = 0xFF;  // ...
	newJump[12] = 0xE7;  // ...
#endif
	SIZE_T bytesWritten;
	BOOL bRet = WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, jmpSize, &bytesWritten);

	if (bProt != FALSE)
	{
		DWORD dwBuf;
		VirtualProtect(pOrgEntry, jmpSize, dwOldProtect, &dwBuf);
	}
	return bRet;
}

static LONG __stdcall CrashHandlerExceptionFilter(EXCEPTION_POINTERS* pExPtrs)
{
#ifdef _M_IX86
	if (pExPtrs->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
	{
		static char MyStack[1024*128];  // be sure that we have enought space...
		// it assumes that DS and SS are the same!!! (this is the case for Win32)
		// change the stack only if the selectors are the same (this is the case for Win32)
		//__asm push offset MyStack[1024*128];
		//__asm pop esp;
		__asm mov eax,offset MyStack[1024*128];
		__asm mov esp,eax;
	}
#endif

	StackWalkerToConsole sw;  // output to console
	sw.ShowCallstack(GetCurrentThread(), pExPtrs->ContextRecord);
	TCHAR lString[500];
	/*_stprintf_s(lString,
		_T("*** Unhandled Exception! See console output for more infos!\n")
		_T("   ExpCode: 0x%8.8X\n")
		_T("   ExpFlags: %d\n")
		_T("   ExpAddress: 0x%8.8X\n")
		_T("   Please report!"),
		pExPtrs->ExceptionRecord->ExceptionCode,
		pExPtrs->ExceptionRecord->ExceptionFlags,
		pExPtrs->ExceptionRecord->ExceptionAddress);*/

	_stprintf_s(lString,"*** Please Send %s to Server Admin! ***",sw.GetStackLogFileName());
	FatalAppExit(-1, lString);
	return EXCEPTION_CONTINUE_SEARCH;
}

static void InitUnhandledExceptionFilter()
{
	TCHAR szModName[_MAX_PATH];
	if (GetModuleFileName(NULL, szModName, sizeof(szModName)/sizeof(TCHAR)) != 0)
	{
		_tcscpy_s(s_szExceptionLogFileName, szModName);
		_tcscat_s(s_szExceptionLogFileName, _T(".exp.log"));
	}
	if (s_bUnhandledExeptionFilterSet == FALSE)
	{
		// set global exception handler (for handling all unhandled exceptions)
		SetUnhandledExceptionFilter(CrashHandlerExceptionFilter);
#if defined _M_X64 || defined _M_IX86
		PreventSetUnhandledExceptionFilter();
#endif
		s_bUnhandledExeptionFilterSet = TRUE;
	}
}

void StartStackLogging()
{
	InitUnhandledExceptionFilter();
}