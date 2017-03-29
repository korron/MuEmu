#include "stdafx.h"
#include "HackCheck.h"
#include "CCRC32.h"
#include "HackServerProtocol.h"
#include "Log.h"
#include "Protect.h"
#include "Util.h"

typedef int(WINAPI*WSRECV)(SOCKET,char*,int,int);
typedef int(WINAPI*WSSEND)(SOCKET,char*,int,int);
typedef DWORD(WINAPI*KERNELGETTICKCOUNT)();

WSRECV HookRecv;
WSSEND HookSend;
KERNELGETTICKCOUNT HookGetTickCount;
BYTE EncDecKey1;
BYTE EncDecKey2;
BYTE recvTable[5];
BYTE sendTable[5];
BYTE GetTickCountTable[5];
BYTE* recvAddress;
BYTE* sendAddress;
BYTE* GetTickCountAddress;

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

void CheckDetourIntegrity() // OK
{
	if(recvAddress != 0 && memcmp(recvAddress,recvTable,sizeof(recvTable)) != 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(15));
		SafeExitProcess();
		return;
	}

	if(sendAddress != 0 && memcmp(sendAddress,sendTable,sizeof(sendTable)) != 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(16));
		SafeExitProcess();
		return;
	}

	if(GetTickCountAddress != 0 && memcmp(GetTickCountAddress,GetTickCountTable,sizeof(GetTickCountTable)) != 0)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(17));
		SafeExitProcess();
		return;
	}
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
		EncDecKey += gProtect.m_MainInfo.CustomerName[n];
	}

	EncDecKey1 = (BYTE)gEncDecKey1;
	EncDecKey2 = (BYTE)gEncDecKey2;

	EncDecKey1 += LOBYTE(EncDecKey);
	EncDecKey2 += HIBYTE(EncDecKey);

	recvAddress = (BYTE*)GetProcAddress(GetModuleHandle("Ws2_32.dll"),"recv");
	sendAddress = (BYTE*)GetProcAddress(GetModuleHandle("Ws2_32.dll"),"send");
	GetTickCountAddress = (BYTE*)GetProcAddress(GetModuleHandle("Kernel32.dll"),"GetTickCount");

	HookRecv = (WSRECV)recvAddress;
	HookSend = (WSSEND)sendAddress;
	HookGetTickCount = (KERNELGETTICKCOUNT)GetTickCountAddress;

	memcpy(recvTable,(void*)recvAddress,sizeof(recvTable));

	memcpy(sendTable,(void*)sendAddress,sizeof(sendTable));

	memcpy(GetTickCountTable,(void*)GetTickCountAddress,sizeof(GetTickCountTable));

	if(gEncDecKey1 != 0 || gEncDecKey2 != 0)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)HookRecv,MyRecv);
		DetourTransactionCommit();

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)HookSend,MySend);
		DetourTransactionCommit();

		memcpy(recvTable,(void*)recvAddress,sizeof(recvTable));

		memcpy(sendTable,(void*)sendAddress,sizeof(sendTable));
	}
}
