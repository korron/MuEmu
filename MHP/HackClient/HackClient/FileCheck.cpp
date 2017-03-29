#include "StdAfx.h"
#include "FileCheck.h"
#include "HackServerProtocol.h"
#include "ListManager.h"
#include "CCRC32.h"
#include "Util.h"

CFileCheck gFileCheck;

CFileCheck::CFileCheck()
{
	this->m_count = 0;
}

CFileCheck::~CFileCheck()
{
}

void CFileCheck::Scan()
{
	if((this->m_count++) < 12)
	{
		CCRC32 CRC32;

		for(std::vector<CSUM_LIST_INFO>::iterator it=gListManager.gChecksumListInfo.begin();it != gListManager.gChecksumListInfo.end();it++)
		{
			if(FileExists(it->path) == 1)
			{
				DWORD FileHash;

				if(CRC32.FileCRC(it->path,&FileHash,1024) == 0)
				{
					CHClientDisconnectSend(CLIENT_DISCONNECT_FILE_DETECTION,it->path,0);
					return;
				}

				if(it->checksum != FileHash)
				{
					CHClientDisconnectSend(CLIENT_DISCONNECT_FILE_DETECTION,it->path,0);
					return;
				}
			}
			else
			{
				CHClientDisconnectSend(CLIENT_DISCONNECT_FILE_DETECTION,it->path,0);
				return;
			}
		}
	}
}
