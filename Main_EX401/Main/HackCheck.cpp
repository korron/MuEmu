#include "stdafx.h"
#include "HackCheck.h"
#include "Protect.h"
#include "Util.h"

typedef int(WINAPI*WSRECV)(SOCKET,char*,int,int);
typedef int(WINAPI*WSSEND)(SOCKET,char*,int,int);

WSRECV HookRecv;
WSSEND HookSend;
BYTE EncDecKey1;
BYTE EncDecKey2;

void DecryptData(BYTE* lpMsg,int size) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]^EncDecKey1)-EncDecKey2;
	}
}

void EncryptData(BYTE* lpMsg,int size) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]+EncDecKey2)^EncDecKey1;
	}
}

bool CheckSocketPort(SOCKET s) // OK
{
	SOCKADDR_IN addr;
	int addr_len = sizeof(addr);

	if(getpeername(s,(SOCKADDR*)&addr,&addr_len) == SOCKET_ERROR)
	{
		return 0;
	}

	if(PORT_RANGE(ntohs(addr.sin_port)) == 0)
	{
		return 0;
	}

	return 1;
}

int WINAPI MyRecv(SOCKET s,char* buf,int len,int flags) // OK
{
	int result = HookRecv(s,(char*)buf,len,flags);

	if(result == SOCKET_ERROR || result == 0)
	{
		return result;
	}

	if(CheckSocketPort(s) != 0)
	{
		DecryptData((BYTE*)buf,result);
	}

	return result;
}

int WINAPI MySend(SOCKET s,char* buf,int len,int flags) // OK
{
	if(CheckSocketPort(s) != 0)
	{
		EncryptData((BYTE*)buf,len);
	}

	return HookSend(s,buf,len,flags);
}

void InitHackCheck() // OK
{
	WORD EncDecKey = 0;

	for(int n=0;n < sizeof(gProtect.m_MainInfo.CustomerName);n++)
	{
		EncDecKey += (BYTE)(gProtect.m_MainInfo.CustomerName[n]^gProtect.m_MainInfo.ClientSerial[(n%sizeof(gProtect.m_MainInfo.ClientSerial))]);
	}

	EncDecKey1 = (BYTE)0xE2;
	EncDecKey2 = (BYTE)0x76;

	EncDecKey1 += LOBYTE(EncDecKey);
	EncDecKey2 += HIBYTE(EncDecKey);

	HookRecv = *(WSRECV*)(0x008125E8);

	HookSend = *(WSSEND*)(0x008125F8);

	SetDword(0x008125E8,(DWORD)&MyRecv);

	SetDword(0x008125F8,(DWORD)&MySend);
}
