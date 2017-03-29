#pragma once
#define WIN32_LEAN_AND_MEAN

#define AUTH_PORT	19448

#include "targetver.h"
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <dbghelp.h>
#include <commctrl.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"dbghelp.lib")
#pragma comment(lib,"comctl32.lib")