// Connection.h: interface for the CConnection class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CriticalSection.h"
#include "HackServerProtocol.h"

#define MAX_BUFF_SIZE	8192
#define AUTH_ADDRESS_A	"muemu.pl"
#define AUTH_ADDRESS_B	"muemu.pl"
#define AUTH_ADDRESS_C	"muemu.pl"
#define AUTH_PORT		19448

struct PMSG_AUTH_INFO_RECV
{
	PBMSG_HEAD header;
	BYTE result;
	BYTE status;
	DWORD version;
};

struct PMSG_AUTH_INFO_SEND
{
	PBMSG_HEAD header;
	char CustomerName[32];
	char HardwareId[36];
};

class CAuthenticate
{
public:
	CAuthenticate();
	virtual ~CAuthenticate();
	bool Init(void* function);
	void Check();
	bool Connect(char* IpAddress,WORD port);
	void Disconnect();
	bool CheckState();
	bool DataRecv();
	bool DataSend(BYTE* lpMsg,int size);
	bool DataSendEx();
	static DWORD WINAPI ClientWorkerThread(CAuthenticate* lpConnection);
	static void ProtocolCore(BYTE head,BYTE* lpMsg,int size);
	void AuthInfoRecv(PMSG_AUTH_INFO_RECV* lpMsg);
	void RequestInfoSend();
private:
	SOCKET m_socket;
	WSAEVENT m_event;
	BYTE m_RecvBuff[MAX_BUFF_SIZE];
	int m_RecvSize;
	BYTE m_SendBuff[MAX_BUFF_SIZE];
	int m_SendSize;
	void (*wsProtocolCore)(BYTE,BYTE*,int);
	CCriticalSection m_critical;
	bool m_AuthReceived;
};

extern CAuthenticate gAuthenticate;