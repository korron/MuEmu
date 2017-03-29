#pragma once

#include "Util.h"

class CWindowCheck
{
public:
	CWindowCheck();
	virtual ~CWindowCheck();
	void Scan();
};

extern CWindowCheck gWindowCheck;
