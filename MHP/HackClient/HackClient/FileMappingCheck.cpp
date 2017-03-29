#include "StdAfx.h"
#include "FileMappingCheck.h"
#include "HackServerProtocol.h"
#include "ListManager.h"
#include "Util.h"

CFileMappingCheck gFileMappingCheck;

CFileMappingCheck::CFileMappingCheck()
{
}

CFileMappingCheck::~CFileMappingCheck()
{
}

void CFileMappingCheck::Scan()
{
	for(std::vector<ITRN_LIST_INFO>::iterator it=gListManager.gInternalListInfo.begin();it != gListManager.gInternalListInfo.end();it++)
	{
		if(it->type != INTERN_MAPPING)
		{
			continue;
		}

		if((OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, it->value) != NULL))
		{
			CHClientDisconnectSend(CLIENT_DISCONNECT_FILE_MAPPING_DETECTION,0,0);
			return;
		}
	}
}
