#pragma once

void HookBYTE(LPVOID Offset,BYTE value,bool bProtect=true);
void HookWORD(LPVOID Offset,WORD value,bool bProtect=true);
void HookDWORD(LPVOID Offset,DWORD value,bool bProtect=true);
void HookDWORD64(LPVOID Offset,DWORD64 value,bool bProtect=true);
void HookSET(LPVOID Offset,BYTE value,int size,bool bProtect=true);
void HookBUFFER(LPVOID Offset,LPBYTE value,int size,bool bProtect=true);

//
DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize);
DWORD SetByte(const LPVOID dwOffset, const BYTE btValue);
DWORD GetByte(const LPVOID dwOffset, BYTE & btValue);
DWORD SetWord(const LPVOID dwOffset, const WORD wValue);
DWORD GetWord(const LPVOID dwOffset, WORD & wValue);
DWORD SetDword(const LPVOID dwOffset, const DWORD dwValue);
DWORD GetDword(const LPVOID dwOffset, DWORD & dwValue);
DWORD SetFloat(const LPVOID dwOffset, const float fValue);
DWORD GetFloat(const LPVOID dwOffset, float & fValue);
DWORD SetDouble(const LPVOID dwOffset, double dValue);
DWORD SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, BYTE cmd);
DWORD SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue);