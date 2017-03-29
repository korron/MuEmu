#include "stdafx.h"
#include "ProtocolCore.h"
#include "QueryManager.h"
#include "SocketServer.h"
#include "ClientManager.h"
#include "Util.h"

void ProtocolCore(int index, BYTE head, BYTE* lpMsg, int size)
{
	switch(head)
	{
		case 0x00:
			RequestInfoRecv((PMSG_AUTH_INFO_RECV*)lpMsg,index);
			break;
	}
}

void RequestInfoRecv(PMSG_AUTH_INFO_RECV* lpInfo, int index)
{
	PMSG_AUTHENTICATE_SEND pMsg;

	pMsg.header.set(0x00,sizeof(pMsg));

	pMsg.result = 0;

	pMsg.status = 0;

	pMsg.version = 0;

	if(CheckTextSyntax(lpInfo->CustomerName,sizeof(lpInfo->CustomerName)) == 0)
	{
		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
		return;
	}

	if(CheckTextSyntax(lpInfo->HardwareId,sizeof(lpInfo->HardwareId)) == 0)
	{
		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
		return;
	}

	if(gDatabase.ExecQuery("SELECT Id FROM [User] WHERE Name='%s'",lpInfo->CustomerName) == 0 || gDatabase.Fetch() == SQL_NO_DATA)
	{
		gDatabase.Close();
		gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
		return;
	}

	int user_idx = gDatabase.GetAsInteger("Id");

	gDatabase.Close();

	if(gDatabase.ExecQuery("SELECT Information1,Status,UpdateIndex FROM License WHERE UserId=%d AND ProductId=%d AND Information2='%s' AND Status=1",user_idx,4,lpInfo->HardwareId) != 0)
	{
		while(gDatabase.Fetch() != SQL_NO_DATA)
		{
			char TempAddr[50];

			memset(TempAddr,0,sizeof(TempAddr));

			gDatabase.GetAsString("Information1",TempAddr);

			if(strcmp(TempAddr, gClientManager[index].m_IpAddr) != 0)
			{
				continue;
			}

			pMsg.status = (BYTE)gDatabase.GetAsInteger("Status");

			pMsg.version = (DWORD)gDatabase.GetAsInteger("UpdateIndex");

			break;
		}
	}

	gDatabase.Close();

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}
