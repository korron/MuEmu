#pragma once

class CRegistryCheck
{
public:
	CRegistryCheck();
	virtual ~CRegistryCheck();
	void Scan();
};

extern CRegistryCheck gRegistryCheck;
