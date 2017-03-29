// ListManager.h: interface for the CListManager class.
//
//////////////////////////////////////////////////////////////////////

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

enum DUMP_LIST_TYPE
{
	TYPE_DUMP = 0,
	TYPE_AUX = 1,
};

enum INTERNAL_LIST_TYPE
{
	INTERN_MAPPING = 0,
	INTERN_LIBRARY = 1,
	INTERN_REGISTRY = 2,
};

enum WINDOW_LIST_TYPE
{
	WINDOW_NAME = 0,
	WINDOW_CLASS = 1,
};

class CListManager
{
public:
	CListManager();
	virtual ~CListManager();
public:
	std::vector<DUMP_LIST_INFO> gDumpListInfo;
	std::vector<CSUM_LIST_INFO> gChecksumListInfo;
	std::vector<ITRN_LIST_INFO> gInternalListInfo;
	std::vector<WNDW_LIST_INFO> gWindowListInfo;
};

extern CListManager gListManager;
