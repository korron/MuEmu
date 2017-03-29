// ReadFiles.cpp: implementation of the CReadFiles class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReadFiles.h"
#include "ClientManager.h"
#include "HackServerProtocol.h"
#include "MemScript.h"
#include "ServerInfo.h"
#include "Util.h"
#include "FileDownloadURL.h"
#include "FileDownloadHTTP.h"

CReadFiles gReadFiles;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadFiles::CReadFiles()
{
	this->ReloadSwitch = 0;
	this->UpdateSwitch = 0;
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

	gDumpListInfo.clear();

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

			gDumpListInfo.push_back(TempList);
		}
	}
	catch(...)
	{
		ErrorMessageBox("%s file read error",filename);
	}

	delete lpScript;
}

void CReadFiles::ChecksumList(char* filename)
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

	gChecksumListInfo.clear();

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

			CSUM_LIST_INFO TempList;

			strcpy_s(TempList.path,lpScript->GetString());

			TempList.checksum = lpScript->GetAsDword();

			gChecksumListInfo.push_back(TempList);
		}
	}
	catch(...)
	{
		ErrorMessageBox("%s file read error",filename);
	}

	delete lpScript;
}

void CReadFiles::InternalList(char* filename)
{
	CMemScript* lpScript = new CMemScript;

	if(lpScript == 0)
	{
		return;
	}
	
	if(lpScript->SetBuffer(filename,1) == 0)
	{
		delete lpScript;
		return;
	}
	
	gInternalListInfo.clear();

	try
	{
		while(true)
		{
			if(lpScript->GetToken() == 2)
			{
				break;
			}

			int section = lpScript->GetNumber();

			while(true)
			{
				if(strcmp("end",lpScript->GetAsString()) == 0)
				{
					break;
				}

				ITRN_LIST_INFO TempList;

				memset(&TempList,0,sizeof(TempList));

				TempList.type = section;

				strcpy_s(TempList.value,lpScript->GetString());

				gInternalListInfo.push_back(TempList);
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox("%s file read error",filename);
	}

	delete lpScript;
}

void CReadFiles::WindowList(char* filename)
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
	
	gWindowListInfo.clear();

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

			WNDW_LIST_INFO TempList;

			TempList.type = lpScript->GetNumber();

			strcpy_s(TempList.text,lpScript->GetAsString());

			gWindowListInfo.push_back(TempList);
		}
	}
	catch(...)
	{
		ErrorMessageBox("%s file read error",filename);
	}

	delete lpScript;
}

void CReadFiles::UpdateInternalList()
{
	if(this->UpdateSwitch != 0)
	{
		LogAdd(LOG_BLACK,"[Database] Please wait for the current list update");
		return;
	}

	if(this->ReloadSwitch != 0)
	{
		LogAdd(LOG_BLACK,"[Database] Please wait for the current list reload");
		return;
	}

	this->UpdateSwitch = 1;

	char UpdateFileURL[MAX_PATH];

	sprintf_s(UpdateFileURL,"", HACKSERVER_VERSION);

	char NewFilePath[MAX_PATH] = ".\\Data\\Internal.List.part.db";

	char OldFilePath[MAX_PATH] = ".\\Data\\Internal.List.db";

	char buffer[0xFFFF];

	char address[1024];

	char request[1024];

	URLPARTS_T url;

	memset(&url, 0, sizeof(url));

	url.address = address;

	url.request = request;

	url.addressLen = sizeof(address);

	url.requestLen = sizeof(request);

	breakUrl(UpdateFileURL, &url);

	int Downloader = httpGet(address, url.port, request);

	if(Downloader)
	{
		FILE* NewFile;

		fopen_s(&NewFile, NewFilePath, "wb");

		int size;

		while((size = httpRecv(Downloader, buffer, sizeof(buffer))) > 0)
		{
			fwrite(buffer, size, 1, NewFile);
		}

		fclose(NewFile);

		httpClose(Downloader);

	}
	else
	{
		DeleteFile(NewFilePath);

		this->UpdateSwitch = 0;

		LogAdd(LOG_RED,"[Database] Could not update list (Error: %i)", httpLastError());

		return;
	}

	DeleteFile(OldFilePath);

	Sleep(500);

	rename(NewFilePath,OldFilePath);

	this->UpdateSwitch = 0;

	LogAdd(LOG_GREEN,"[Database] Updated successfully");

	gServerInfo.ReadInternalList();
}
