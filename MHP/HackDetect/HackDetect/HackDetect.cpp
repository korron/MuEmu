#include "stdafx.h"

#define MIN_PORT 55901
#define MAX_PORT 55950
#define MAX_IO_BUFFER_SIZE 6000
#define IO_RECV 0
#define IO_SEND 1

#define PORT_RANGE(x) (((x)<MIN_PORT)?0:((x)>MAX_PORT)?0:1)

struct PER_IO_CONTEXT
{
	WSAOVERLAPPED Overlapped;
	WSABUF wsabuf;
	BYTE Buffer[MAX_IO_BUFFER_SIZE];
	BYTE BufferSecond[MAX_IO_BUFFER_SIZE];
	int SecondOfs;
	int TotalBytes;
	int SentBytes;
	int IoOperation;
	int WaitIO;
};

typedef int (WINAPI*WSASEND)(SOCKET,LPWSABUF,DWORD,LPDWORD,DWORD,LPWSAOVERLAPPED,LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef BOOL (WINAPI*GETQUEUEDCOMPLETIONSTATUS)(HANDLE,LPDWORD,LPDWORD,LPOVERLAPPED*,DWORD);

WSASEND HookWSASend;
GETQUEUEDCOMPLETIONSTATUS HookGetQueuedCompletionStatus;

char CustomerName[32];
BYTE EncDecKey1;
BYTE EncDecKey2;
BYTE InternalVersion;

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

	if(getsockname(s,(SOCKADDR*)&addr,&addr_len) == SOCKET_ERROR)
	{
		return 0;
	}

	if(PORT_RANGE(ntohs(addr.sin_port)) == 0)
	{
		return 0;
	}

	return 1;
}

int WINAPI MyWSASend(SOCKET s,LPWSABUF lpBuffers,DWORD dwBufferCount,LPDWORD lpNumberOfBytesSent,DWORD dwFlags,LPWSAOVERLAPPED lpOverlapped,LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) // OK
{
	if(CheckSocketPort(s) != 0)
	{
		EncryptData((BYTE*)lpBuffers->buf,lpBuffers->len);
	}

	return HookWSASend(s,lpBuffers,dwBufferCount,lpNumberOfBytesSent,dwFlags,lpOverlapped,lpCompletionRoutine);
}

BOOL WINAPI MyGetQueuedCompletionStatus(HANDLE CompletionPort,LPDWORD lpNumberOfBytes,LPDWORD lpCompletionKey,LPOVERLAPPED* lpOverlapped,DWORD dwMilliseconds) // OK
{
	BOOL result = 0;

	if((result=HookGetQueuedCompletionStatus(CompletionPort,lpNumberOfBytes,lpCompletionKey,lpOverlapped,dwMilliseconds)) == 0)
	{
		if(lpOverlapped == 0 || (GetLastError() != ERROR_NETNAME_DELETED && GetLastError() != ERROR_CONNECTION_ABORTED && GetLastError() != ERROR_OPERATION_ABORTED && GetLastError() != ERROR_SEM_TIMEOUT))
		{
			return result;
		}
	}

	if((*lpNumberOfBytes) == 0 && (*lpCompletionKey) == 0 && (*lpOverlapped) == 0)
	{
		return result;
	}

	PER_IO_CONTEXT* lpIoRecvContext;
	PER_IO_CONTEXT* lpIoSendContext;

	switch(((PER_IO_CONTEXT*)(*lpOverlapped))->IoOperation)
	{
		case IO_RECV:
			lpIoRecvContext = (PER_IO_CONTEXT*)(*lpOverlapped);
			DecryptData(&lpIoRecvContext->Buffer[lpIoRecvContext->SentBytes],(*lpNumberOfBytes));
			break;
		case IO_SEND:
			lpIoSendContext = (PER_IO_CONTEXT*)(*lpOverlapped);
			if((lpIoSendContext->SentBytes+(*lpNumberOfBytes)) < ((DWORD)lpIoSendContext->TotalBytes)){DecryptData(&lpIoSendContext->Buffer[(lpIoSendContext->SentBytes+(*lpNumberOfBytes))],(lpIoSendContext->TotalBytes-(lpIoSendContext->SentBytes+(*lpNumberOfBytes))));}
			break;
	}

	return result;
}

char* ConvertModuleFileName(char* name) // OK
{
	static char buff[MAX_PATH] = {0};

	for(int n=strlen(name);n > 0;n--)
	{
		if(name[n] == '\\')
		{
			memcpy(buff,name,n);
			break;
		}
	}

	return buff;
}

void EntryProc(HINSTANCE hins) // OK
{
	char MutexName[64];

	wsprintf(MutexName,"XTMPID%d",GetCurrentProcessId());

	HANDLE Mutex = CreateMutex(0,0,MutexName);

	if(Mutex == 0){return;}

	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		char name[MAX_PATH],path[MAX_PATH];

		GetModuleFileName(hins,name,sizeof(name));

		wsprintf(path,"%s\\MHPServer.ini",ConvertModuleFileName(name));

		GetPrivateProfileString("MHPServerInfo","CustomerName","",CustomerName,sizeof(CustomerName),path);

		EncDecKey1 = GetPrivateProfileInt("MHPServerInfo","EncDecKey1",0,path);

		EncDecKey2 = GetPrivateProfileInt("MHPServerInfo","EncDecKey2",0,path);

		InternalVersion = GetPrivateProfileInt("MHPServerInfo","InternalVersion",0,path);

		HookWSASend = (WSASEND)GetProcAddress(GetModuleHandle("Ws2_32.dll"),"WSASend");

		HookGetQueuedCompletionStatus = (GETQUEUEDCOMPLETIONSTATUS)GetProcAddress(GetModuleHandle("kernel32.dll"),"GetQueuedCompletionStatus");

		if(EncDecKey1 != 0 || EncDecKey2 != 0)
		{
			WORD EncDecKey = 0;

			for(int n=0;n < sizeof(CustomerName);n++)
			{
				EncDecKey += CustomerName[n];
			}

			EncDecKey1 += LOBYTE(EncDecKey);
			EncDecKey2 += HIBYTE(EncDecKey);

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach(&(PVOID&)HookWSASend,MyWSASend);
			DetourTransactionCommit();

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach(&(PVOID&)HookGetQueuedCompletionStatus,MyGetQueuedCompletionStatus);
			DetourTransactionCommit();
		}
	}

	CloseHandle(Mutex);
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			EntryProc((HINSTANCE)hModule);
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}
