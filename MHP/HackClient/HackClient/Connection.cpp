// Connection.cpp: implementation of the CConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Connection.h"
#include "Log.h"
#include "Util.h"
//Modules
#include "ThreadCheck.h"

CConnection gConnection;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnection::CConnection() // OK
{
	this->m_socket = INVALID_SOCKET;

	this->m_event = WSA_INVALID_EVENT;

	this->m_WorkerThread = 0;

	this->m_active = 0;
}

CConnection::~CConnection() // OK
{
	this->Disconnect();
}

bool CConnection::Init(void* function) // OK
{
	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		return 0;
	}

	if((this->m_socket=socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET)
	{
		return 0;
	}

	if((this->m_event=WSACreateEvent()) == WSA_INVALID_EVENT)
	{
		return 0;
	}

	this->wsProtocolCore = (void(*)(BYTE,BYTE*,int))function;

	return 1;
}

bool CConnection::Connect(char* IpAddress,WORD port) // OK
{
	if(this->m_socket == INVALID_SOCKET)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(1));
		return 0;
	}
	
	SOCKADDR_IN target;

	target.sin_family = AF_INET;
	target.sin_port = htons(port);
	target.sin_addr.s_addr = inet_addr(IpAddress);
	
	if(target.sin_addr.s_addr == INADDR_NONE)
	{
		HOSTENT* host = gethostbyname(IpAddress);

		if(host != 0)
		{
			memcpy(&target.sin_addr.s_addr,(*host->h_addr_list),host->h_length);
		}
	}

	if(connect(this->m_socket,(SOCKADDR*)&target,sizeof(target)) == SOCKET_ERROR)
	{
		if(WSAGetLastError() != WSAEWOULDBLOCK)
		{
			gLog.Output(LOG_DEBUG,GetEncryptedString(2),WSAGetLastError());
			this->Disconnect();
			return 0;
		}
	}

	if(WSAEventSelect(this->m_socket,this->m_event,FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
	{
		gLog.Output(LOG_DEBUG,GetEncryptedString(3),WSAGetLastError());
		this->Disconnect();
		return 0;
	}

	memset(this->m_RecvBuff,0,sizeof(this->m_RecvBuff));

	this->m_RecvSize = 0;

	memset(this->m_SendBuff,0,sizeof(this->m_SendBuff));

	this->m_SendSize = 0;

	this->m_WorkerThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)this->ClientWorkerThread,this,0,&gThreadCheck.m_CheckThreadID[0]);

	this->m_active = 1;

	return 1;
}

void CConnection::Disconnect() // OK
{
	if(this->m_WorkerThread != 0)
	{
		gThreadCheck.m_CheckThreadID[0] = (DWORD)INVALID_HANDLE_VALUE;
		TerminateThread(this->m_WorkerThread,0);
		CloseHandle(this->m_WorkerThread);
		this->m_WorkerThread = 0;
	}

	if(this->m_socket != INVALID_SOCKET)
	{
		closesocket(this->m_socket);
		this->m_socket = INVALID_SOCKET;
	}

	if(this->m_event != WSA_INVALID_EVENT)
	{
		WSACloseEvent(this->m_event);
		this->m_event = WSA_INVALID_EVENT;
	}

	this->m_active = 0;
}

bool CConnection::CheckState() // OK
{
	if(this->m_socket == INVALID_SOCKET)
	{
		return 0;
	}

	if(this->m_active == 0)
	{
		return 0;
	}

	return 1;
}

bool CConnection::DataRecv() // OK
{
	int count=0,size=0,result=0;

	if((result=recv(this->m_socket,(char*)&this->m_RecvBuff[this->m_RecvSize],(MAX_BUFF_SIZE-this->m_RecvSize),0)) == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEWOULDBLOCK)
		{
			return 1;
		}
		else
		{
			gLog.Output(LOG_DEBUG,GetEncryptedString(4),WSAGetLastError());
			this->Disconnect();
			return 0;
		}
	}

	this->m_RecvSize += result;

	if(this->m_RecvSize < 4)
	{
		return 1;
	}

	BYTE header,head;

	while(true)
	{
		if(this->m_RecvBuff[count] == 0xC1)
		{
			header = this->m_RecvBuff[count];
			size = this->m_RecvBuff[count+1];
			head = this->m_RecvBuff[count+3];
		}
		else if(this->m_RecvBuff[count] == 0xC2)
		{
			header = this->m_RecvBuff[count];
			size = MAKEWORD(this->m_RecvBuff[count+2],this->m_RecvBuff[count+1]);
			head = this->m_RecvBuff[count+4];
		}
		else
		{
			gLog.Output(LOG_DEBUG,GetEncryptedString(5),this->m_RecvBuff[count]);
			this->Disconnect();
			return 0;
		}

		if(size < 4 || size > MAX_BUFF_SIZE)
		{
			gLog.Output(LOG_DEBUG,GetEncryptedString(6),header,size,head);
			this->Disconnect();
			return 0;
		}

		if(size <= this->m_RecvSize)
		{
			if(header == 0xC1)
			{
				PacketDecryptData(&this->m_RecvBuff[count+3],(size-3),this->m_RecvBuff[count+2]);
				head = this->m_RecvBuff[count+3];
			}
			else
			{
				PacketDecryptData(&this->m_RecvBuff[count+4],(size-4),this->m_RecvBuff[count+3]);
				head = this->m_RecvBuff[count+4];
			}

			this->wsProtocolCore(head,&this->m_RecvBuff[count],size);

			count += size;
			this->m_RecvSize -= size;

			if(this->m_RecvSize <= 0)
			{
				break;
			}
		}
		else
		{
			if(count > 0 && this->m_RecvSize > 0 && this->m_RecvSize <= (MAX_BUFF_SIZE-count))
			{
				memmove(this->m_RecvBuff,&this->m_RecvBuff[count],this->m_RecvSize);
			}

			break;
		}
	}

	return 1;
}

bool CConnection::DataSend(BYTE* lpMsg,int size) // OK
{
	this->m_critical.lock();

	if(this->CheckState() == 0)
	{
		this->m_critical.unlock();
		return 0;
	}

	BYTE buff[MAX_BUFF_SIZE];

	memcpy(buff,lpMsg,size);

	if(buff[0] == 0xC1)
	{
		PacketEncryptData(&buff[3],(size-3),buff[2]);
	}
	else
	{
		PacketEncryptData(&buff[4],(size-4),buff[3]);
	}

	if(this->m_SendSize > 0)
	{
		if((this->m_SendSize+size) > MAX_BUFF_SIZE)
		{
			gLog.Output(LOG_DEBUG,GetEncryptedString(7),(this->m_SendSize+size));
			this->Disconnect();
			this->m_critical.unlock();
			return 0;
		}
		else
		{
			memcpy(&this->m_SendBuff[this->m_SendSize],buff,size);
			this->m_SendSize += size;
			this->m_critical.unlock();
			return 1;
		}
	}

	int count=0,result=0;

	while(size > 0)
	{
		if((result=send(this->m_socket,(char*)&buff[count],size,0)) == SOCKET_ERROR)
		{
			if(WSAGetLastError() == WSAEWOULDBLOCK)
			{
				if((this->m_SendSize+size) > MAX_BUFF_SIZE)
				{
					gLog.Output(LOG_DEBUG,GetEncryptedString(8),(this->m_SendSize+size));
					this->Disconnect();
					this->m_critical.unlock();
					return 0;
				}
				else
				{
					memcpy(&this->m_SendBuff[this->m_SendSize],&buff[count],size);
					this->m_SendSize += size;
					this->m_critical.unlock();
					return 1;
				}
			}
			else
			{
				gLog.Output(LOG_DEBUG,GetEncryptedString(9),WSAGetLastError());
				this->Disconnect();
				this->m_critical.unlock();
				return 0;
			}
		}
		else
		{
			count += result;
			size -= result;
		}
	}

	this->m_critical.unlock();
	return 1;
}

bool CConnection::DataSendEx() // OK
{
	this->m_critical.lock();

	int count=0,result=0;

	while(this->m_SendSize > 0)
	{
		if((result=send(this->m_socket,(char*)&this->m_SendBuff[count],this->m_SendSize,0)) == SOCKET_ERROR)
		{
			if(WSAGetLastError() == WSAEWOULDBLOCK)
			{
				memmove(this->m_SendBuff,&this->m_SendBuff[count],this->m_SendSize);
				this->m_critical.unlock();
				return 1;
			}
			else
			{
				gLog.Output(LOG_DEBUG,GetEncryptedString(10),WSAGetLastError());
				this->Disconnect();
				this->m_critical.unlock();
				return 0;
			}
		}
		else
		{
			count += result;
			this->m_SendSize -= result;
		}
	}

	this->m_critical.unlock();
	return 1;
}

DWORD WINAPI CConnection::ClientWorkerThread(CConnection* lpConnection) // OK
{
	while(true)
	{
		DWORD result = WSAWaitForMultipleEvents(1,&lpConnection->m_event,0,WSA_INFINITE,0);

		if(result != WSA_WAIT_FAILED && result != WSA_WAIT_TIMEOUT)
		{
			WSANETWORKEVENTS NetworkEvents;

			if(WSAEnumNetworkEvents(lpConnection->m_socket,lpConnection->m_event,&NetworkEvents) == SOCKET_ERROR)
			{
				gLog.Output(LOG_DEBUG,GetEncryptedString(11),WSAGetLastError());
				lpConnection->Disconnect();
				return 0;
			}

			if((NetworkEvents.lNetworkEvents & FD_READ) == FD_READ)
			{
				if(NetworkEvents.iErrorCode[FD_READ_BIT] == 0)
				{
					lpConnection->DataRecv();
				}
				else
				{
					gLog.Output(LOG_DEBUG,GetEncryptedString(12),NetworkEvents.iErrorCode[FD_READ_BIT]);
					lpConnection->Disconnect();
					return 0;
				}
			}

			if((NetworkEvents.lNetworkEvents & FD_WRITE) == FD_WRITE)
			{
				if(NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0)
				{
					lpConnection->DataSendEx();
				}
				else
				{
					gLog.Output(LOG_DEBUG,GetEncryptedString(13),NetworkEvents.iErrorCode[FD_WRITE_BIT]);
					lpConnection->Disconnect();
					return 0;
				}
			}

			if((NetworkEvents.lNetworkEvents & FD_CLOSE) == FD_CLOSE)
			{
				if(NetworkEvents.iErrorCode[FD_CLOSE_BIT] == 0)
				{
					lpConnection->Disconnect();
				}
				else
				{
					gLog.Output(LOG_DEBUG,GetEncryptedString(14),NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
					lpConnection->Disconnect();
					return 0;
				}
			}
		}
	}

	return 0;
}
