#pragma once

#define MAX_DUMP_COUNT 1000

struct DUMP_LIST_INFO
{
	BYTE type;
	DWORD offset;
	BYTE dump[32];
	char name[32];
};

class CReadFiles
{
public:
	CReadFiles();
	virtual ~CReadFiles();
	void DumpList(char* filename);
	bool CheckDumpList(DUMP_LIST_INFO info);
public:
	int m_TotalCount;
	std::vector<DUMP_LIST_INFO> gDumpListInfo;
};

extern CReadFiles gReadFiles;
