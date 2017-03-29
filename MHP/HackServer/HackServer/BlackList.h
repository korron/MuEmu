#pragma once

struct BLACKLIST_IPADDR_INFO
{
	char IpAddress[17];
};

struct BLACKLIST_HARDID_INFO
{
	char HardwareId[36];
};


class CBlackList
{
public:
	CBlackList();
	virtual ~CBlackList();
	void SetList(char* filename);
	bool CheckIpAddress(char* IpAddress);
	bool CheckHardwareId(char* HardwareId);

public:
	std::vector<BLACKLIST_IPADDR_INFO> gIpAddressBlackList;
	std::vector<BLACKLIST_HARDID_INFO> gHardwareIdBlackList;
};

extern CBlackList gBlackList;