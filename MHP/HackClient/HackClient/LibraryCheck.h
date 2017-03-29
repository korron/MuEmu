#pragma once

class CLibraryCheck
{
public:
	CLibraryCheck();
	virtual ~CLibraryCheck();
	bool Check(wchar_t* sTemp,char* CaptionName);
};

extern CLibraryCheck gLibraryCheck;
