// Connection.h: interface for the CConnection class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CriticalSection.h"

#define MAX_BUFF_SIZE 8192

class CConnection
{
public:
	CConnection();
	virtual ~CConnection();
	bool Init(void* function);
	bool Connect(char* IpAddress,WORD port);
	void Disconnect();
	bool CheckState();
	bool DataRecv();
	bool DataSend(BYTE* lpMsg,int size);
	bool DataSendEx();
	static DWORD WINAPI ClientWorkerThread(CConnection* lpConnection);
private:
	SOCKET m_socket;
	WSAEVENT m_event;
	BYTE m_RecvBuff[MAX_BUFF_SIZE];
	int m_RecvSize;
	BYTE m_SendBuff[MAX_BUFF_SIZE];
	int m_SendSize;
	void (*wsProtocolCore)(BYTE,BYTE*,int);
	CCriticalSection m_critical;
};

extern CConnection gConnection;
