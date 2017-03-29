// SocketManager.cpp: implementation of the CSocketManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SocketServer.h"
#include "ClientManager.h"
#include "ProtocolCore.h"

CSocketManager gSocketManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketManager::CSocketManager() // OK
{
	this->m_listen = INVALID_SOCKET;

	this->m_CompletionPort = 0;

	this->m_port = 0;

	this->m_ServerAcceptThread = 0;

	for(int n=0;n < MAX_SERVER_WORKER_THREAD;n++)
	{
		this->m_ServerWorkerThread[n] = 0;
	}

	this->m_ServerWorkerThreadCount = 0;

	this->m_ServerQueue = 0;

	this->m_ServerQueueSemaphore = 0;

	this->m_ServerQueueThread = 0;
}

CSocketManager::~CSocketManager() // OK
{
	this->Clean();
}

bool CSocketManager::Start(WORD port) // OK
{
	this->m_port = port;

	if(this->CreateListenSocket() == 0)
	{
		this->Clean();
		return 0;
	}

	if(this->CreateCompletionPort() == 0)
	{
		this->Clean();
		return 0;
	}

	if(this->CreateAcceptThread() == 0)
	{
		this->Clean();
		return 0;
	}

	if(this->CreateWorkerThread() == 0)
	{
		this->Clean();
		return 0;
	}

	if(this->CreateServerQueue() == 0)
	{
		this->Clean();
		return 0;
	}

	printf("[SocketManager] Server started at port [%d]\n",this->m_port);
	return 1;
}

void CSocketManager::Clean() // OK
{
	if(this->m_ServerQueueThread != 0)
	{
		TerminateThread(this->m_ServerQueueThread,0);
		CloseHandle(this->m_ServerQueueThread);
		this->m_ServerQueueThread = 0;
	}

	if(this->m_ServerQueueSemaphore != 0)
	{
		CloseHandle(this->m_ServerQueueSemaphore);
		this->m_ServerQueueSemaphore = 0;
	}

	if(this->m_ServerQueue != 0)
	{
		delete this->m_ServerQueue;
		this->m_ServerQueue = 0;
	}

	for(DWORD n=0;n < MAX_SERVER_WORKER_THREAD;n++)
	{
		if(this->m_ServerWorkerThread[n] != 0)
		{
			TerminateThread(this->m_ServerWorkerThread[n],0);
			CloseHandle(this->m_ServerWorkerThread[n]);
			this->m_ServerWorkerThread[n] = 0;
		}
	}

	if(this->m_ServerAcceptThread != 0)
	{
		TerminateThread(this->m_ServerAcceptThread,0);
		CloseHandle(this->m_ServerAcceptThread);
		this->m_ServerAcceptThread = 0;
	}

	if(this->m_CompletionPort != 0)
	{
		CloseHandle(this->m_CompletionPort);
		this->m_CompletionPort = 0;
	}

	if(this->m_listen != INVALID_SOCKET)
	{
		closesocket(this->m_listen);
		this->m_listen = INVALID_SOCKET;
	}
}

bool CSocketManager::CreateListenSocket() // OK
{
	if((this->m_listen=WSASocket(AF_INET,SOCK_STREAM,0,0,0,WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("[SocketManager] WSASocket() failed with error: %d\n",WSAGetLastError());
		return 0;
	}

	SOCKADDR_IN SocketAddr;

	SocketAddr.sin_family = AF_INET;
	SocketAddr.sin_addr.s_addr = htonl(0);
	SocketAddr.sin_port = htons(this->m_port);

	if(bind(this->m_listen,(sockaddr*)&SocketAddr,sizeof(SocketAddr)) == SOCKET_ERROR)
	{
		printf("[SocketManager] bind() failed with error: %d\n",WSAGetLastError());
		return 0;
	}

	if(listen(this->m_listen,5) == SOCKET_ERROR)
	{
		printf("[SocketManager] listen() failed with error: %d\n",WSAGetLastError());
		return 0;
	}
	
	return 1;
}

bool CSocketManager::CreateCompletionPort() // OK
{
	SOCKET socket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_IP);

	if(socket == INVALID_SOCKET) 
	{
		printf("[SocketManager] socket() failed with error: %d\n",WSAGetLastError());
		return 0;
	}

	if((this->m_CompletionPort=CreateIoCompletionPort((HANDLE)socket,0,0,0)) == 0)
	{
		printf("[SocketManager] CreateIoCompletionPort() failed with error: %d\n",GetLastError());
		closesocket(socket);
		return 0;
	}

	closesocket(socket);
	return 1;
}

bool CSocketManager::CreateAcceptThread() // OK
{
	if((this->m_ServerAcceptThread=CreateThread(0,0,(LPTHREAD_START_ROUTINE)this->ServerAcceptThread,this,0,0)) == 0)
	{
		printf("[SocketManager] CreateThread() failed with error: %d\n",GetLastError());
		return 0;
	}

	return 1;
}

bool CSocketManager::CreateWorkerThread() // OK
{
	SYSTEM_INFO SystemInfo;

	GetSystemInfo(&SystemInfo);

	this->m_ServerWorkerThreadCount = ((SystemInfo.dwNumberOfProcessors>MAX_SERVER_WORKER_THREAD)?MAX_SERVER_WORKER_THREAD:SystemInfo.dwNumberOfProcessors);

	for(DWORD n=0;n < this->m_ServerWorkerThreadCount;n++)
	{
		if((this->m_ServerWorkerThread[n]=CreateThread(0,0,(LPTHREAD_START_ROUTINE)this->ServerWorkerThread,this,0,0)) == 0)
		{
			printf("[SocketManager] CreateThread() failed with error: %d\n",GetLastError());
			return 0;
		}

		if(SetThreadPriority(this->m_ServerWorkerThread[n],THREAD_PRIORITY_HIGHEST) == 0)
		{
			printf("[SocketManager] SetThreadPriority() failed with error: %d\n",GetLastError());
			return 0;
		}

		if(SetThreadAffinityMask(this->m_ServerWorkerThread[n],(1 << n)) == 0)
		{
			printf("[SocketManager] SetThreadAffinityMask() failed with error: %d\n",GetLastError());
			return 0;
		}
	}

	return 1;
}

bool CSocketManager::CreateServerQueue() // OK
{
	this->m_ServerQueue = new CQueue(MAX_QUEUE_SIZE);

	if(this->m_ServerQueue == 0)
	{
		return 0;
	}

	if((this->m_ServerQueueSemaphore=CreateSemaphore(0,0,MAX_QUEUE_SIZE,0)) == 0)
	{
		printf("[SocketManager] CreateSemaphore() failed with error: %d\n",GetLastError());
		return 0;
	}

	if((this->m_ServerQueueThread=CreateThread(0,0,(LPTHREAD_START_ROUTINE)this->ServerQueueThread,this,0,0)) == 0)
	{
		printf("[SocketManager] CreateThread() failed with error: %d\n",GetLastError());
		return 0;
	}

	return 1;
}

bool CSocketManager::DataRecv(int index,IO_BUFFER* lpIoBuffer) // OK
{
	if(lpIoBuffer->size < 3)
	{
		return 1;
	}

	BYTE* lpMsg = lpIoBuffer->buff;

	int count=0,size=0;
	BYTE header,head;
	
	while(true)
	{
		if(lpMsg[count] == 0xC1)
		{
			header = lpMsg[count];
			size = lpMsg[count+1];
			head = lpMsg[count+3];
		}
		else if(lpMsg[count] == 0xC2)
		{
			header = lpMsg[count];
			size = MAKEWORD(lpMsg[count+2],lpMsg[count+1]);
			head = lpMsg[count+4];
		}
		else
		{
			printf("[SocketManager] Protocol header error (index:%d, header:%x)\n",index,lpMsg[count]);
			return 0;
		}

		if(size < 3 || size >= MAX_PACKET_SIZE)
		{
			printf("[SocketManager] Protocol size error (index:%d, size:%d)\n",index,size);
			return 0;
		}

		if(size <= lpIoBuffer->size)
		{
			if(this->m_ServerQueue->AddToQueue(index,head,&lpMsg[count],size) != 0)
			{
				ReleaseSemaphore(this->m_ServerQueueSemaphore,1,0);
			}

			count += size;

			lpIoBuffer->size -= size;

			if(lpIoBuffer->size <= 0)
			{
				break;
			}
		}
		else
		{
			if(count > 0 && lpIoBuffer->size > 0 && lpIoBuffer->size < MAX_PACKET_SIZE)
			{
				memmove(lpMsg,&lpMsg[count],lpIoBuffer->size);
			}

			break;
		}
	}

	return 1;
}

bool CSocketManager::DataSend(int index,BYTE* lpMsg,int size) // OK
{
	this->m_critical.lock();

	if(CLIENT_RANGE(index) == 0)
	{
		this->m_critical.unlock();
		return 0;
	}

	CClientManager* lpClientManager = &gClientManager[index];

	if(lpClientManager->CheckState() == 0)
	{
		this->m_critical.unlock();
		return 0;
	}

	BYTE send[MAX_PACKET_SIZE];

	memcpy(send,lpMsg,size);

	if(size >= MAX_PACKET_SIZE)
	{
		printf("[SocketManager] Max msg size (type:1, index:%d, size:%d)\n",index,size);
		this->m_critical.unlock();
		return 0;
	}

	IO_CONTEXT* lpIoContext = &lpClientManager->m_IoContext[IO_SEND];

	if(lpIoContext->IoWait > 0)
	{
		if((lpIoContext->IoBuffer[1].size+size) >= MAX_PACKET_SIZE)
		{
			printf("[SocketManager] Max msg size (type:2, index:%d, size:%d)\n",index,lpIoContext->IoBuffer[1].size+size);
			this->Disconnect(index);
			this->m_critical.unlock();
			return 0;
		}

		memcpy(&lpIoContext->IoBuffer[1].buff[lpIoContext->IoBuffer[1].size],send,size);
		lpIoContext->IoBuffer[1].size += size;
		this->m_critical.unlock();
		return 1;
	}

	lpIoContext->IoSize = 0;

	if(lpIoContext->IoBuffer[1].size > 0)
	{
		memcpy(lpIoContext->IoBuffer[0].buff,lpIoContext->IoBuffer[1].buff,lpIoContext->IoBuffer[1].size);
		lpIoContext->IoSize = lpIoContext->IoBuffer[1].size;
		lpIoContext->IoBuffer[1].size = 0;
	}

	if((lpIoContext->IoSize+size) >= MAX_PACKET_SIZE)
	{
		printf("[SocketManager] Max msg size (type:3, index:%d, size:%d)\n",index,lpIoContext->IoSize+size);
		this->Disconnect(index);
		this->m_critical.unlock();
		return 0;
	}

	memcpy(&lpIoContext->IoBuffer[0].buff[lpIoContext->IoSize],send,size);

	lpIoContext->IoSize += size;

	lpIoContext->wsabuf.buf = (char*)lpIoContext->IoBuffer[0].buff;
	lpIoContext->wsabuf.len = lpIoContext->IoSize;

	lpIoContext->IoBuffer[0].size = 0;

	lpIoContext->IoType = IO_SEND;

	DWORD SendSize=0,Flags=0;
	
	if(WSASend(lpClientManager->m_socket,&lpIoContext->wsabuf,1,&SendSize,Flags,&lpIoContext->overlapped,0) == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("[SocketManager] WSASend() failed with error: %d\n",WSAGetLastError());
			this->Disconnect(index);
			this->m_critical.unlock();
			return 0;
		}
	}

	lpIoContext->IoWait = 1;

	this->m_critical.unlock();
	return 1;
}

void CSocketManager::Disconnect(int index) // OK
{
	this->m_critical.lock();

	if(CLIENT_RANGE(index) == 0)
	{
		this->m_critical.unlock();
		return;
	}

	CClientManager* lpClientManager = &gClientManager[index];

	if(lpClientManager->CheckState() == 0)
	{
		this->m_critical.unlock();
		return;
	}

	if(lpClientManager->m_socket != INVALID_SOCKET)
	{
		if(closesocket(lpClientManager->m_socket) == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSAENOTSOCK)
			{
				printf("[SocketManager] closesocket() failed with error: %d\n",WSAGetLastError());
				this->m_critical.unlock();
				return;
			}
		}
	}

	lpClientManager->DelClient();

	this->m_critical.unlock();
}

void CSocketManager::OnRecv(int index,DWORD IoSize,IO_CONTEXT* lpIoContext) // OK
{
	this->m_critical.lock();

	if(CLIENT_RANGE(index) == 0)
	{
		this->m_critical.unlock();
		return;
	}

	CClientManager* lpClientManager = &gClientManager[index];

	lpIoContext->IoBuffer[0].size += IoSize;

	if(this->DataRecv(index,&lpIoContext->IoBuffer[0]) == 0)
	{
		this->Disconnect(index);
		this->m_critical.unlock();
		return;
	}

	lpIoContext->wsabuf.buf = (char*)&lpIoContext->IoBuffer[0].buff[lpIoContext->IoBuffer[0].size];
	lpIoContext->wsabuf.len = MAX_PACKET_SIZE-lpIoContext->IoBuffer[0].size;

	lpIoContext->IoType = IO_RECV;

	DWORD RecvSize=0,Flags=0;

	if(WSARecv(lpClientManager->m_socket,&lpIoContext->wsabuf,1,&RecvSize,&Flags,&lpIoContext->overlapped,0) == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("[SocketManager] WSARecv() failed with error: %d\n",WSAGetLastError());
			this->Disconnect(index);
			this->m_critical.unlock();
			return;
		}
	}

	lpIoContext->IoWait = 1;

	this->m_critical.unlock();
}

void CSocketManager::OnSend(int index,DWORD IoSize,IO_CONTEXT* lpIoContext) // OK
{
	this->m_critical.lock();

	if(CLIENT_RANGE(index) == 0)
	{
		this->m_critical.unlock();
		return;
	}

	CClientManager* lpClientManager = &gClientManager[index];

	lpIoContext->IoBuffer[0].size += IoSize;

	if(lpIoContext->IoBuffer[0].size >= lpIoContext->IoSize)
	{
		lpIoContext->IoWait = 0;

		if(lpIoContext->IoBuffer[1].size <= 0)
		{
			this->m_critical.unlock();
			return;
		}

		lpIoContext->IoSize = 0;

		memcpy(lpIoContext->IoBuffer[0].buff,lpIoContext->IoBuffer[1].buff,lpIoContext->IoBuffer[1].size);

		lpIoContext->IoSize = lpIoContext->IoBuffer[1].size;
		lpIoContext->IoBuffer[1].size = 0;

		lpIoContext->wsabuf.buf = (char*)lpIoContext->IoBuffer[0].buff;
		lpIoContext->wsabuf.len = lpIoContext->IoSize;

		lpIoContext->IoBuffer[0].size = 0;
	}
	else
	{
		if((lpIoContext->IoSize-lpIoContext->IoBuffer[0].size) < 0)
		{
			this->m_critical.unlock();
			return;
		}

		lpIoContext->wsabuf.buf = (char*)&lpIoContext->IoBuffer[0].buff[lpIoContext->IoBuffer[0].size];
		lpIoContext->wsabuf.len = lpIoContext->IoSize-lpIoContext->IoBuffer[0].size;
	}

	lpIoContext->IoType = IO_SEND;

	DWORD SendSize=0,Flags=0;

	if(WSASend(lpClientManager->m_socket,&lpIoContext->wsabuf,1,&SendSize,Flags,&lpIoContext->overlapped,0) == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("[SocketManager] WSASend() failed with error: %d\n",WSAGetLastError());
			this->Disconnect(index);
			this->m_critical.unlock();
			return;
		}
	}

	lpIoContext->IoWait = 1;

	this->m_critical.unlock();
}

int CALLBACK CSocketManager::ServerAcceptCondition(IN LPWSABUF lpCallerId,IN LPWSABUF lpCallerData,IN OUT LPQOS lpSQOS,IN OUT LPQOS lpGQOS,IN LPWSABUF lpCalleeId,OUT LPWSABUF lpCalleeData,OUT GROUP FAR* g,CSocketManager* lpSocketManager) // OK
{
	SOCKADDR_IN* SocketAddr = (SOCKADDR_IN*)lpCallerId->buf;

	/*if(gIpManager.CheckIpAddress(inet_ntoa(SocketAddr->sin_addr)) == 0)
	{
		return CF_REJECT;
	}*/

	return CF_ACCEPT;
}

DWORD WINAPI CSocketManager::ServerAcceptThread(CSocketManager* lpSocketManager) // OK
{
	SOCKADDR_IN SocketAddr;
	int SocketAddrSize = sizeof(SocketAddr);

	while(true)
	{
		SOCKET socket = WSAAccept(lpSocketManager->m_listen,(sockaddr*)&SocketAddr,&SocketAddrSize,(LPCONDITIONPROC)&lpSocketManager->ServerAcceptCondition,(DWORD)lpSocketManager);

		if(socket == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		{
			lpSocketManager->m_critical.lock();
			printf("[SocketManager] WSAAccept() failed with error: %d\n",WSAGetLastError());
			lpSocketManager->m_critical.unlock();
			continue;
		}

		lpSocketManager->m_critical.lock();

		int index = -1;

		for(int n=0;n < MAX_CLIENT;n++)
		{
			if(gClientManager[n].CheckState() == 0)
			{
				index = n;
				break;
			}
		}

		if(index == -1)
		{
			closesocket(socket);
			lpSocketManager->m_critical.unlock();
			continue;
		}

		if(CreateIoCompletionPort((HANDLE)socket,lpSocketManager->m_CompletionPort,index,0) == 0)
		{
			printf("[SocketManager] CreateIoCompletionPort() failed with error: %d\n",GetLastError());
			closesocket(socket);
			lpSocketManager->m_critical.unlock();
			continue;
		}

		CClientManager* lpClientManager = &gClientManager[index];

		lpClientManager->AddClient(index,inet_ntoa(SocketAddr.sin_addr),socket);

		DWORD RecvSize=0,Flags=0;

		if(WSARecv(socket,&lpClientManager->m_IoContext[IO_RECV].wsabuf,1,&RecvSize,&Flags,&lpClientManager->m_IoContext[IO_RECV].overlapped,0) == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSA_IO_PENDING)
			{
				printf("[SocketManager] WSARecv() failed with error: %d\n",WSAGetLastError());
				lpSocketManager->Disconnect(index);
				lpSocketManager->m_critical.unlock();
				continue;
			}
		}

		lpSocketManager->m_critical.unlock();
	}

	return 0;
}

DWORD WINAPI CSocketManager::ServerWorkerThread(CSocketManager* lpSocketManager) // OK
{
	DWORD IoSize;
	DWORD index;
	LPOVERLAPPED lpOverlapped;

	while(true)
	{
		if(GetQueuedCompletionStatus(lpSocketManager->m_CompletionPort,&IoSize,&index,&lpOverlapped,INFINITE) == 0)
		{
			if(GetLastError() != ERROR_NETNAME_DELETED && GetLastError() != ERROR_CONNECTION_ABORTED && GetLastError() != ERROR_OPERATION_ABORTED && GetLastError() != ERROR_SEM_TIMEOUT)
			{
				lpSocketManager->m_critical.lock();
				printf("[SocketManager] GetQueuedCompletionStatus() failed with error: %d\n",GetLastError());
				lpSocketManager->Disconnect(index);
				lpSocketManager->m_critical.unlock();
				continue;
			}
		}

		lpSocketManager->m_critical.lock();

		if(IoSize == 0)
		{
			lpSocketManager->Disconnect(index);
			lpSocketManager->m_critical.unlock();
			continue;
		}

		IO_CONTEXT* lpIoContext = (IO_CONTEXT*)lpOverlapped;

		switch(lpIoContext->IoType)
		{
			case IO_RECV:
				lpSocketManager->OnRecv(index,IoSize,lpIoContext);
				break;
			case IO_SEND:
				lpSocketManager->OnSend(index,IoSize,lpIoContext);
				break;
		}

		lpSocketManager->m_critical.unlock();
	}

	return 0;
}

DWORD WINAPI CSocketManager::ServerQueueThread(CSocketManager* lpSocketManager) // OK
{
	WORD index;
	BYTE head;
	BYTE buff[MAX_PACKET_SIZE];
	DWORD size;

	while(true)
	{
		if(WaitForSingleObject(lpSocketManager->m_ServerQueueSemaphore,INFINITE) == WAIT_FAILED)
		{
			printf("[SocketManager] WaitForSingleObject() failed with error: %d\n",GetLastError());
			break;
		}

		if(lpSocketManager->m_ServerQueue->GetFromQueue(&index,&head,buff,&size) != 0)
		{
			if(CLIENT_RANGE(index) != 0 && gClientManager[index].CheckState() != 0)
			{
				ProtocolCore(index,head,buff,size);
			}
		}
	}

	return 0;
}

DWORD CSocketManager::GetQueueSize() // OK
{
	if(this->m_ServerQueue == 0)
	{
		return 0;
	}

	return this->m_ServerQueue->GetQueueSize();
}
