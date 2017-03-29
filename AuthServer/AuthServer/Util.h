#pragma once

#include "ServerDisplayer.h"

#define CRASH_APPLICATION_MACRO _asm _emit 0xFF _asm _emit 0x25 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00 _asm _emit 0x00

void ErrorMessageBox(char* message,...);
void LogAdd(eLogColor color,char* text,...);
void PacketDecryptData(BYTE* lpMsg,int size,BYTE key);
void PacketEncryptData(BYTE* lpMsg,int size,BYTE key);
void CheckComputerHardwareId();
void AuthServerTimeoutProc();
int GetDatabaseProductId(int ProductId);
