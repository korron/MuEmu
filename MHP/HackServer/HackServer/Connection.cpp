// Connection.cpp: implementation of the CConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Connection.h"
#include "Util.h"

CConnection gConnection;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnection::CConnection() // OK
{
	this->m_socket = INVALID_SOCKET;

	this->m_event = WSA_INVALID_EVENT;
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

	if((this->m_socket=socket(PF_INET,SOCK_STREAM,0)) == INVALID_SOCKET)
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
			//gLog.Output(LOG_CONNECT,"[Connection] connect() failed with error: %d",WSAGetLastError());
			this->Disconnect();
			return 0;
		}
	}

	if(WSAEventSelect(this->m_socket,this->m_event,FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
	{
		//gLog.Output(LOG_CONNECT,"[Connection] WSAEventSelect() failed with error: %d",WSAGetLastError());
		this->Disconnect();
		return 0;
	}

	memset(this->m_RecvBuff,0,sizeof(this->m_RecvBuff));

	this->m_RecvSize = 0;

	memset(this->m_SendBuff,0,sizeof(this->m_SendBuff));

	this->m_SendSize = 0;

	CreateThread(0,0,(LPTHREAD_START_ROUTINE)this->ClientWorkerThread,this,0,0);

	return 1;
}

void CConnection::Disconnect() // OK
{
	if(this->m_socket != INVALID_SOCKET)
	{
		closesocket(this->m_socket);
		this->m_socket = INVALID_SOCKET;
	}
}

bool CConnection::CheckState() // OK
{
	return ((this->m_socket==INVALID_SOCKET)?0:1);
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
			//gLog.Output(LOG_CONNECT,"[Connection] recv() failed with error: %d",WSAGetLastError());
			this->Disconnect();
			return 0;
		}
	}

	this->m_RecvSize += result;

	if(this->m_RecvSize < 3)
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
			//gLog.Output(LOG_CONNECT,"[Connection] Protocol header error (header:%x)",this->m_RecvBuff[count]);
			this->Disconnect();
			return 0;
		}

		if(size <= 0 || size >= MAX_BUFF_SIZE)
		{
			//gLog.Output(LOG_CONNECT,"[Connection] Protocol size error (size:%d)",size);
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
			if(count > 0 && this->m_RecvSize > 0 && this->m_RecvSize < MAX_BUFF_SIZE)
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

	if(this->m_socket == INVALID_SOCKET)
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
		if((this->m_SendSize+size) >= MAX_BUFF_SIZE)
		{
			//gLog.Output(LOG_CONNECT,"[Connection] Max msg size (size:%d)",size);
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
				if((this->m_SendSize+size) >= MAX_BUFF_SIZE)
				{
					//gLog.Output(LOG_CONNECT,"[Connection] Max msg size (size:%d)",size);
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
				//gLog.Output(LOG_CONNECT,"[Connection] send() failed with error: %d",WSAGetLastError());
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
				//gLog.Output(LOG_CONNECT,"[Connection] send() failed with error: %d",WSAGetLastError());
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
		DWORD result = WSAWaitForMultipleEvents(1,&lpConnection->m_event,1,WSA_INFINITE,0);

		if((result == WSA_WAIT_FAILED) || (result == WSA_WAIT_TIMEOUT))
		{
			continue;
		}

		WSANETWORKEVENTS NetworkEvents;

		if(WSAEnumNetworkEvents(lpConnection->m_socket,lpConnection->m_event,&NetworkEvents) == SOCKET_ERROR)
		{
			lpConnection->m_critical.lock();
			lpConnection->Disconnect();
			lpConnection->m_critical.unlock();
			return 0;
		}

		if((NetworkEvents.lNetworkEvents & FD_READ) != 0)
		{
			if(NetworkEvents.iErrorCode[FD_READ_BIT] == 0)
			{
				gConnection.DataRecv();
			}
			else
			{
				//gLog.Output(LOG_CONNECT,"[Connection] FD_READ failed with error: %d",NetworkEvents.iErrorCode[FD_READ_BIT]);
			}
		}

		if((NetworkEvents.lNetworkEvents & FD_WRITE) != 0)
		{
			if(NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0)
			{
				gConnection.DataSendEx();
			}
			else
			{
				//gLog.Output(LOG_CONNECT,"[Connection] FD_WRITE failed with error: %d",NetworkEvents.iErrorCode[FD_WRITE_BIT]);
			}
		}

		if((NetworkEvents.lNetworkEvents & FD_CLOSE) != 0)
		{
			if(NetworkEvents.iErrorCode[FD_CLOSE_BIT] == 0)
			{
				gConnection.Disconnect();
			}
			else
			{
				//gLog.Output(LOG_CONNECT,"[Connection] FD_CLOSE failed with error: %d",NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
			}
		}
	}

	return 0;
}
