#include "stdafx.h"
#include "LibraryCheck.h"
#include "HackServerProtocol.h"
#include "ListManager.h"
#include "Util.h"

CLibraryCheck gLibraryCheck;

CLibraryCheck::CLibraryCheck()
{

}

CLibraryCheck::~CLibraryCheck()
{

}

bool CLibraryCheck::Check(wchar_t* sTemp,char* CaptionName)
{
	wchar_t sTempNew[MAX_PATH], FinalPath[MAX_PATH*2];

	memcpy(sTempNew,sTemp,sizeof(sTempNew));

	PathRemoveFileSpecW(sTempNew);

	for(std::vector<ITRN_LIST_INFO>::iterator it=gListManager.gInternalListInfo.begin();it != gListManager.gInternalListInfo.end();it++)
	{
		if(it->type != INTERN_LIBRARY)
		{
			continue;
		}

		wsprintfW(FinalPath,L"%s\\%S",sTempNew,it->value);

		if((wcsstr(FinalPath,L":\\Windows\\")) || (wcsstr(FinalPath,L":\\SystemRoot\\")) || (wcsstr(FinalPath,L"\\System32\\")))
		{
			continue;
		}

		if(FileExists(FinalPath) == 1)
		{
			return 0;
		}
	}

	return 1;
}
