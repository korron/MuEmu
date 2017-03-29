// ClientManager.h: interface for the CClientManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "SocketServer.h"

#define MAX_CLIENT 1000

#define CLIENT_RANGE(x) (((x)<0)?0:((x)>=MAX_CLIENT)?0:1)

enum eClientState
{
	CLIENT_OFFLINE = 0,
	CLIENT_ONLINE = 1,
};

class CClientManager
{
public:
	CClientManager();
	virtual ~CClientManager();
	bool CheckState();
	void AddClient(int index,char* ip,SOCKET socket);
	void DelClient();
	void SetClientInfo(char* HardwareId);
public:
	int m_index;
	eClientState m_state;
	char m_IpAddr[16];
	SOCKET m_socket;
	IO_CONTEXT m_IoContext[MAX_IO_OPERATION];
	char m_HardwareId[35];
	DWORD m_ConnectionTime;
	DWORD m_PacketTime;
};

extern CClientManager gClientManager[MAX_CLIENT];
