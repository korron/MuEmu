#pragma once

#include "ServerDisplayer.h"

#define CRASH_APPLICATION_MACRO _asm _emit 0xFF _asm _emit 0x25 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00

enum eClientDisconnectType
{
	CLIENT_DISCONNECT_NONE = 0,
	CLIENT_DISCONNECT_DUMP_DETECTION = 1,
	CLIENT_DISCONNECT_EXECUTABLE_DETECTION = 2,
	CLIENT_DISCONNECT_FILE_DETECTION = 3,
	CLIENT_DISCONNECT_FILE_MAPPING_DETECTION = 4,
	CLIENT_DISCONNECT_LIBRARY_DETECTION = 5,
	CLIENT_DISCONNECT_REGISTRY_DETECTION = 6,
	CLIENT_DISCONNECT_MEMORY_DETECTION = 7,
	CLIENT_DISCONNECT_WINDOW_DETECTION = 8,
	CLIENT_DISCONNECT_MACRO_DETECTION = 9,
	CLIENT_DISCONNECT_DEBUGGER_DETECTION = 10,
};

void ErrorMessageBox(char* message,...);
void LogAdd(eLogColor color,char* text,...);
void TimeoutProc();
int GetUserCount();
int GetFreeClientIndex();
int SearchFreeClientIndex(int* index,int MinIndex,int MaxIndex,DWORD MinTime);
void PacketDecryptData(BYTE* lpMsg,int size,BYTE key);
void PacketEncryptData(BYTE* lpMsg,int size,BYTE key);
void GetHardwareId(char* hid);
char* RemoveCharacter(char* Input, char Character);
void AuthenticateError();
DWORD GetCurrentVersion();
DWORD ConvertHackVersion(char* version);

extern int gClientCount;
