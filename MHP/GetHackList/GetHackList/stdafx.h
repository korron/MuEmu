#pragma once

// System Include
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <wchar.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <Dbghelp.h>

#pragma comment(lib,"Dbghelp.lib")
#pragma comment(lib,"psapi.lib")
#pragma comment(lib,"Shlwapi.lib")

extern char gCustomerName[32];
