#include "StdAfx.h"
#include "QueryManager.h"
#include "SocketServer.h"
#include "MiniDump.h"
#include "ClientManager.h"

int main(int argv, char** argc)
{
	CMiniDump::Start();

	if(gDatabase.Connect("XTeam") != 1)
	{
	    printf("Could not connect to database",WSAGetLastError());
		return 0;
	}

	printf("Authenticate Server\n");

	printf("Product: HackServer\n\n");

	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,2),&wsa) == 0)
	{
		if(gSocketManager.Start(AUTH_PORT) == 0)
		{
			printf("[SocketManager] Start failed\n");
			return 0;
		}
	}
	else
	{
		printf("WSAStartup() failed with error: %d\n",WSAGetLastError());
		return 0;
	}
	
	while(true)
	{
		Sleep(1500);
	};

	CMiniDump::Clean();
}

void TimeoutProc() // OK
{
	for(int n=0;n < MAX_CLIENT;n++)
	{
		if(gClientManager[n].CheckState() != 0)
		{
			if((GetTickCount()-gClientManager[n].m_ConnectionTime) > 10000)
			{
				gSocketManager.Disconnect(gClientManager[n].m_index);
			}
		}
	}
}