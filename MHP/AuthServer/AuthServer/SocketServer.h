// SocketManager.h: interface for the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CriticalSection.h"
#include "Queue.h"

#define MAX_PACKET_SIZE 8192
#define MAX_SERVER_WORKER_THREAD 8
#define MAX_QUEUE_SIZE 2048
#define MAX_IO_OPERATION 2
#define IO_RECV 0
#define IO_SEND 1

struct IO_BUFFER
{
	BYTE buff[MAX_PACKET_SIZE];
	int size;
};

struct IO_CONTEXT
{
	WSAOVERLAPPED overlapped;
	WSABUF wsabuf;
	IO_BUFFER IoBuffer[2];
	int IoSize;
	BYTE IoType;
	BYTE IoWait;
};

class CSocketManager
{
public:
	CSocketManager();
	virtual ~CSocketManager();
	bool Start(WORD port);
	void Clean();
	bool CreateListenSocket();
	bool CreateCompletionPort();
	bool CreateAcceptThread();
	bool CreateWorkerThread();
	bool CreateServerQueue();
	bool DataRecv(int index,IO_BUFFER* lpIoBuffer);
	bool DataSend(int index,BYTE* lpMsg,int size);
	void Disconnect(int index);
	void OnRecv(int index,DWORD IoSize,IO_CONTEXT* lpIoContext);
	void OnSend(int index,DWORD IoSize,IO_CONTEXT* lpIoContext);
	static int CALLBACK ServerAcceptCondition(IN LPWSABUF lpCallerId,IN LPWSABUF lpCallerData,IN OUT LPQOS lpSQOS,IN OUT LPQOS lpGQOS,IN LPWSABUF lpCalleeId,OUT LPWSABUF lpCalleeData,OUT GROUP FAR* g,CSocketManager* lpSocketManager);
	static DWORD WINAPI ServerAcceptThread(CSocketManager* lpSocketManager);
	static DWORD WINAPI ServerWorkerThread(CSocketManager* lpSocketManager);
	static DWORD WINAPI ServerQueueThread(CSocketManager* lpSocketManager);
	DWORD GetQueueSize();
private:
	SOCKET m_listen;
	HANDLE m_CompletionPort;
	WORD m_port;
	HANDLE m_ServerAcceptThread;
	HANDLE m_ServerWorkerThread[MAX_SERVER_WORKER_THREAD];
	DWORD m_ServerWorkerThreadCount;
	CQueue* m_ServerQueue;
	HANDLE m_ServerQueueSemaphore;
	HANDLE m_ServerQueueThread;
	CCriticalSection m_critical;
};

extern CSocketManager gSocketManager;
