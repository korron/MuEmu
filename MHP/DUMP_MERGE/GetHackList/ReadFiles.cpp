// ReadFiles.cpp: implementation of the CReadFiles class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReadFiles.h"
#include "MemScript.h"

CReadFiles gReadFiles;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadFiles::CReadFiles()
{
	this->m_TotalCount = 0;

	this->gDumpListInfo.clear();
}

CReadFiles::~CReadFiles()
{
}

void CReadFiles::DumpList(char* filename)
{
	CMemScript* lpScript = new CMemScript;

	if(lpScript == 0)
	{
		return;
	}

	if(lpScript->SetBuffer(filename,0) == 0)
	{
		delete lpScript;
		return;
	}

	try
	{
		while(true)
		{
			if(lpScript->GetToken() == 2)
			{
				break;
			}

			if(strcmp("end",lpScript->GetString()) == 0)
			{
				break;
			}

			DUMP_LIST_INFO TempList;

			TempList.type = lpScript->GetNumber();

			char TempHex[11];

			strcpy_s(TempHex,lpScript->GetAsString());

			sscanf_s(TempHex,"%X",&TempList.offset);

			for(int i=0; i<32; i++)
			{
				TempList.dump[i] = lpScript->GetAsNumber();
			}

			char TempName[255];

			strcpy_s(TempName,lpScript->GetAsString());

			TempName[31] = ((strlen(TempName)>31)?0:TempName[31]);

			strcpy_s(TempList.name,TempName);

			this->m_TotalCount++;

			if(this->CheckDumpList(TempList) != 0)
			{
				this->gDumpListInfo.push_back(TempList);
			}
		}
	}
	catch(...)
	{
		printf("%s file read error\n",filename);
	}

	delete lpScript;
}

bool CReadFiles::CheckDumpList(DUMP_LIST_INFO info)
{
	for(std::vector<DUMP_LIST_INFO>::iterator it=this->gDumpListInfo.begin();it != this->gDumpListInfo.end();it++)
	{
		if(it->offset == info.offset && memcmp(it->dump,info.dump,sizeof(it->dump)) == 0)
		{
			return 0;
		}
	}

	return 1;
}
