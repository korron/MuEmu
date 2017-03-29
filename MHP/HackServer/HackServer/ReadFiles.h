#pragma once

struct DUMP_LIST_INFO
{
	BYTE type;
	DWORD offset;
	BYTE dump[32];
	char name[32];
};

struct CSUM_LIST_INFO
{
	char path[MAX_PATH];
	DWORD checksum;
};

struct ITRN_LIST_INFO
{
	BYTE type;
	char value[MAX_PATH];
};

struct WNDW_LIST_INFO
{
	BYTE type;
	char text[64];
};

class CReadFiles
{
public:
	CReadFiles();
	virtual ~CReadFiles();
	void DumpList(char* filename);
	void ChecksumList(char* filename);
	void InternalList(char* filename);
	void WindowList(char* filename);
	void UpdateInternalList();
public:
	bool ReloadSwitch;
	bool UpdateSwitch;
	std::vector<DUMP_LIST_INFO> gDumpListInfo;
	std::vector<CSUM_LIST_INFO> gChecksumListInfo;
	std::vector<ITRN_LIST_INFO> gInternalListInfo;
	std::vector<WNDW_LIST_INFO> gWindowListInfo;
};

extern CReadFiles gReadFiles;
