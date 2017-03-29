#include "StdAfx.h"
#include "ExecutableCheck.h"
#include "CCRC32.h"
#include "HackServerProtocol.h"
#include "ListManager.h"
#include "Util.h"

CExecutableCheck gExecutableCheck;

CExecutableCheck::CExecutableCheck()
{

}

CExecutableCheck::~CExecutableCheck()
{

}

bool CExecutableCheck::Check(wchar_t* sTemp,char* CaptionName)
{
	bool load = 0;

	CCRC32 CRC32;

	DWORD FileHash;

	for(std::vector<DUMP_LIST_INFO>::iterator it=gListManager.gDumpListInfo.begin();it != gListManager.gDumpListInfo.end();it++)
	{
		if(it->type != TYPE_AUX)
		{
			continue;
		}

		if(load == 0)
		{
			if(CRC32.FileCRC(sTemp,&FileHash,1024) == 0)
			{
				break;
			}
			else
			{
				load = 1;
			}
		}

		if(it->offset == FileHash)
		{
			memcpy(CaptionName,it->name,sizeof(it->name));
			return 0;
		}
	}

	return 1;
}
