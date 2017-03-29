#pragma once

class CExecutableCheck
{
public:
	CExecutableCheck();
	virtual ~CExecutableCheck();
	bool Check(wchar_t* sTemp,char* CaptionName);
};

extern CExecutableCheck gExecutableCheck;
