#pragma once

class CFileMappingCheck
{
public:
	CFileMappingCheck();
	virtual ~CFileMappingCheck();
	void Scan();
};

extern CFileMappingCheck gFileMappingCheck;
