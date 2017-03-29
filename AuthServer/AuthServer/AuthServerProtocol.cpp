#include "stdafx.h"
#include "AuthServerProtocol.h"
#include "ClientManager.h"
#include "QueryManager.h"
#include "SocketManager.h"
#include "ServerDisplayer.h"
#include "Util.h"

void AuthServerProtocolCore(int index,BYTE head,BYTE* lpMsg,int size) // OK
{
	gClientManager[index].m_PacketTime = GetTickCount();

	switch(head)
	{
		case 0x00:
			AGAuthServerDataRecv((SDHP_AUTH_SERVER_DATA_RECV*)lpMsg,index);
			break;
		default:
			gSocketManager.Disconnect(index);
			break;
	}
}

void AGAuthServerDataRecv(SDHP_AUTH_SERVER_DATA_RECV* lpMsg,int index) // OK
{
	SDHP_AUTH_SERVER_DATA_SEND pMsg;

	pMsg.type = 0xC1;

	pMsg.size = sizeof(pMsg);

	pMsg.head = 0x00;

	pMsg.EncKey = lpMsg->EncKey;

	pMsg.ServerType = lpMsg->ServerType;

	pMsg.Status = AUTH_SERVER_STATUS_NONE;

	pMsg.PackageType = 0;

	pMsg.PlanType = 0;

	memset(pMsg.CustomerName,0,sizeof(pMsg.CustomerName));

	memset(pMsg.CustomerHardwareId,0,sizeof(pMsg.CustomerHardwareId));

	gQueryManager.BindParameterAsString(1,lpMsg->CustomerName,sizeof(lpMsg->CustomerName));

	if(gQueryManager.ExecQuery("SELECT Id FROM [User] WHERE Name=?") == 0 || gQueryManager.Fetch() == SQL_NO_DATA)
	{
		gQueryManager.Close();

		pMsg.Status = AUTH_SERVER_STATUS_NONE;

		pMsg.PackageType = 0;

		pMsg.PlanType = 0;

		memset(pMsg.CustomerName,0,sizeof(pMsg.CustomerName));

		memset(pMsg.CustomerHardwareId,0,sizeof(pMsg.CustomerHardwareId));
	}
	else
	{
		int UserId = gQueryManager.GetAsInteger("Id");

		gQueryManager.Close();

		if(gQueryManager.ExecQuery("SELECT ProductId,Information1,Information2,Status,PackageIndex,PlanIndex FROM License WHERE UserId=%d",UserId) != 0)
		{
			while(gQueryManager.Fetch() != SQL_NO_DATA)
			{
				char IpAddress[16] = {0};

				char HardwareId[36] = {0};

				int ProductId = gQueryManager.GetAsInteger("ProductId");

				gQueryManager.GetAsString("Information1",IpAddress,sizeof(IpAddress));

				gQueryManager.GetAsString("Information2",HardwareId,sizeof(HardwareId));

				if(GetDatabaseProductId(lpMsg->ServerType) == ProductId && strcmp(gClientManager[index].m_IpAddr,IpAddress) == 0 && strcmp(lpMsg->CustomerHardwareId,HardwareId) == 0)
				{
					pMsg.Status = (BYTE)gQueryManager.GetAsInteger("Status");

					pMsg.PackageType = (BYTE)gQueryManager.GetAsInteger("PackageIndex")+1;

					pMsg.PlanType = (BYTE)gQueryManager.GetAsInteger("PlanIndex")+1;

					memcpy(pMsg.CustomerName,lpMsg->CustomerName,sizeof(pMsg.CustomerName));

					memcpy(pMsg.CustomerHardwareId,lpMsg->CustomerHardwareId,sizeof(pMsg.CustomerHardwareId));

					break;
				}
			}
		}

		gQueryManager.Close();
	}

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.size);

	gQueryManager.ExecQuery("INSERT INTO AuthLog (IpAddress,CustomerName,HardwareId,Type,Version,Status,Date) VALUES ('%s','%s','%s',%d,%d,%d,getdate())",gClientManager[index].m_IpAddr,lpMsg->CustomerName,lpMsg->CustomerHardwareId,lpMsg->ServerType,0,pMsg.Status);

	gQueryManager.Close();
}
