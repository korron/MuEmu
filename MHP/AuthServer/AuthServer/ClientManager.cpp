// ClientManager.cpp: implementation of the CClientManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClientManager.h"

CClientManager gClientManager[MAX_CLIENT];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientManager::CClientManager() // OK
{
	this->m_index = -1;

	this->m_state = CLIENT_OFFLINE;

	this->m_socket = INVALID_SOCKET;
}

CClientManager::~CClientManager() // OK
{

}

bool CClientManager::CheckState() // OK
{
	if(CLIENT_RANGE(this->m_index) == 0 || this->m_state == CLIENT_OFFLINE || this->m_socket == INVALID_SOCKET)
	{
		return 0;
	}

	return 1;
}

void CClientManager::AddClient(int index,char* ip,SOCKET socket) // OK
{
	this->m_index = index;

	this->m_state = CLIENT_ONLINE;

	strcpy_s(this->m_IpAddr,ip);

	this->m_socket = socket;

	memset(&this->m_IoContext[IO_RECV].overlapped,0,sizeof(this->m_IoContext[IO_RECV].overlapped));

	this->m_IoContext[IO_RECV].wsabuf.buf = (char*)this->m_IoContext[IO_RECV].IoBuffer[0].buff;
	this->m_IoContext[IO_RECV].wsabuf.len = MAX_PACKET_SIZE;
	this->m_IoContext[IO_RECV].IoBuffer[0].size = 0;
	this->m_IoContext[IO_RECV].IoBuffer[1].size = 0;
	this->m_IoContext[IO_RECV].IoSize = 0;
	this->m_IoContext[IO_RECV].IoType = IO_RECV;
	this->m_IoContext[IO_RECV].IoWait = 0;

	memset(&this->m_IoContext[IO_SEND].overlapped,0,sizeof(this->m_IoContext[IO_SEND].overlapped));

	this->m_IoContext[IO_SEND].wsabuf.buf = (char*)this->m_IoContext[IO_SEND].IoBuffer[0].buff;
	this->m_IoContext[IO_SEND].wsabuf.len = MAX_PACKET_SIZE;
	this->m_IoContext[IO_SEND].IoBuffer[0].size = 0;
	this->m_IoContext[IO_SEND].IoBuffer[1].size = 0;
	this->m_IoContext[IO_SEND].IoSize = 0;
	this->m_IoContext[IO_SEND].IoType = IO_SEND;
	this->m_IoContext[IO_SEND].IoWait = 0;

	memset(this->m_HardwareId,0,sizeof(this->m_HardwareId));

	this->m_ConnectionTime = GetTickCount();

	this->m_PacketTime = 0;


	//printf("[ClientManager][%d] AddClient (%s)",this->m_index,this->m_IpAddr);
}

void CClientManager::DelClient() // OK
{
	//printf("[ClientManager][%d] DelClient (%s)",this->m_index,this->m_IpAddr);

	this->m_index = -1;

	this->m_state = CLIENT_OFFLINE;

	memset(this->m_IpAddr,0,sizeof(this->m_IpAddr));

	this->m_socket = INVALID_SOCKET;

	memset(this->m_HardwareId,0,sizeof(this->m_HardwareId));

	this->m_ConnectionTime = 0;

	this->m_PacketTime = 0;
}

void CClientManager::SetClientInfo(char* HardwareId) // OK
{
	memcpy(this->m_HardwareId,HardwareId,sizeof(this->m_HardwareId));

	printf("[ClientManager][%d] ClientInfo (HardwareId: %s)",this->m_index,this->m_HardwareId);
}
