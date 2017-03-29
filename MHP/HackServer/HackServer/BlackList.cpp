#include "stdafx.h"
#include "BlackList.h"
#include "MemScript.h"
#include "Util.h"
#include "ServerInfo.h"

CBlackList gBlackList;

CBlackList::CBlackList()
{
}

CBlackList::~CBlackList()
{
}

void CBlackList::SetList(char* filename)
{
	CMemScript* lpScript = new CMemScript;

	if(lpScript == 0)
	{
		return;
	}
	
	if(lpScript->SetBuffer(filename,0) == 0)
	{
		delete lpScript;
		return;
	}
	
	gIpAddressBlackList.clear();
	gHardwareIdBlackList.clear();

	try
	{
		while(true)
		{
			if(lpScript->GetToken() == 2)
			{
				break;
			}

			int section = lpScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpScript->GetAsString()) == 0)
					{
						break;
					}

					BLACKLIST_IPADDR_INFO IpInfo;

					strcpy_s(IpInfo.IpAddress,lpScript->GetString());

					gIpAddressBlackList.push_back(IpInfo);

				}
				else if(section == 1)
				{
					if(strcmp("end",lpScript->GetAsString()) == 0)
					{
						break;
					}

					BLACKLIST_HARDID_INFO HidInfo;

					strcpy_s(HidInfo.HardwareId,lpScript->GetString());

					gHardwareIdBlackList.push_back(HidInfo);
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox("%s file read error",filename);
	}

	delete lpScript;
}

bool CBlackList::CheckIpAddress(char* IpAddress)
{
	if(gIpAddressBlackList.size() <= 0)
	{
		return 1;
	}

	for(DWORD i = 0; i < gIpAddressBlackList.size(); i++)
	{
		if(strcmp(gIpAddressBlackList[i].IpAddress, IpAddress) == 0)
		{
			return 0;
		}
	}

	return 1;
}

bool CBlackList::CheckHardwareId(char* HardwareId)
{
	if(gHardwareIdBlackList.size() <= 0)
	{
		return 1;
	}

	for(DWORD i = 0; i < gHardwareIdBlackList.size(); i++)
	{
		if(strcmp(gHardwareIdBlackList[i].HardwareId, HardwareId) == 0)
		{
			return 0;
		}
	}

	return 1;
}
