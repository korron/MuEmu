#pragma once

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP

// System Include
#include <windows.h>
#include <winsock2.h>
#include <detours.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"detours.lib")
