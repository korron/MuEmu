#include "stdafx.h"
#include "Util.h"

char* GetRealIpAddress(char* IpAddress) // OK
{
	static SOCKADDR_IN target;

	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr(IpAddress);
 
	if(target.sin_addr.s_addr == INADDR_NONE)
	{
		HOSTENT* host = gethostbyname(IpAddress);

		if(host != 0)
		{
			memcpy(&target.sin_addr.s_addr,*host->h_addr_list,host->h_length);
		}
	}

	return inet_ntoa(target.sin_addr);
}

bool CheckTextSyntax(char* text,int size) // OK
{
	for(int n=0;n < size;n++)
	{
		if(text[n] == 0x22 || text[n] == 0x27)
		{
			return 0;
		}
	}

	return 1;
}
