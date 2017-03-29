#pragma once

class CFileCheck
{
public:
	CFileCheck();
	virtual ~CFileCheck();
	void Scan();
private:
	int m_count;
};

extern CFileCheck gFileCheck;
