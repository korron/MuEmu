#pragma once

typedef unsigned __int64 QWORD;

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP

// System Include
#include <windows.h>
#include <iostream>
#include <map>
#include <math.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Mmsystem.h>
#include <detours.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"detours.lib")
#if(NDEBUG==0)
#pragma comment(lib,"..\\..\\Util\\cryptopp\\Debug\\cryptlib.lib")
#else
#pragma comment(lib,"..\\..\\Util\\cryptopp\\Release\\cryptlib.lib")
#endif
