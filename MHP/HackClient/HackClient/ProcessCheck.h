#pragma once

#include "CriticalSection.h"
#include "Util.h"

class CProcessCheck
{
public:
	CProcessCheck();
	virtual ~CProcessCheck();
	bool CheckProcess(DWORD processID,DWORD flag);
};

extern CProcessCheck gProcessCheck;
