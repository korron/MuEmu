#pragma once

#define MIN_PORT 55901
#define MAX_PORT 55950

#define PORT_RANGE(x) (((x)<MIN_PORT)?0:((x)>MAX_PORT)?0:1)

void DecryptData(BYTE* lpMsg,int size);
void EncryptData(BYTE* lpMsg,int size);
bool CheckSocketPort(SOCKET s);
void CheckDetourIntegrity();
int WINAPI MyRecv(SOCKET s,char* buf,int len,int flags);
int WINAPI MySend(SOCKET s,char* buf,int len,int flags);
void InitHackCheck();
