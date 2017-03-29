#include "StdAfx.h"
#include "RegistryCheck.h"
#include "HackServerProtocol.h"
#include "ListManager.h"
#include "Util.h"

CRegistryCheck gRegistryCheck;

CRegistryCheck::CRegistryCheck()
{

}

CRegistryCheck::~CRegistryCheck()
{

}

void CRegistryCheck::Scan()
{
	for(std::vector<ITRN_LIST_INFO>::iterator it=gListManager.gInternalListInfo.begin();it != gListManager.gInternalListInfo.end();it++)
	{
		if(it->type != INTERN_REGISTRY)
		{
			continue;
		}

		HKEY KeyPointer = 0;

		RegOpenKey(HKEY_CURRENT_USER,it->value,&KeyPointer);

		if(KeyPointer != 0)
		{
			for(DWORD n=0;n < gListManager.gInternalListInfo.size();n++)
			{
				if(gListManager.gInternalListInfo[n].type == INTERN_REGISTRY)
				{
					SHDeleteKey(HKEY_CURRENT_USER,gListManager.gInternalListInfo[n].value);
				}
			}

			RegCloseKey(KeyPointer);
			CHClientDisconnectSend(CLIENT_DISCONNECT_REGISTRY_DETECTION,0,0);
			return;
		}
	}
}
