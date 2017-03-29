// FileProtect.cpp: implementation of the CFileProtect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileProtect.h"

CFileProtect gFileProtect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileProtect::CFileProtect() // OK
{
	this->m_buff = 0;

	this->m_size = 0;

	memset(this->m_path,0,sizeof(this->m_path));
}

CFileProtect::~CFileProtect() // OK
{

}

bool CFileProtect::LoadFile(char* path) // OK
{
	HANDLE file = CreateFile(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	this->m_size = GetFileSize(file,0);

	if(this->m_buff != 0)
	{
		delete[] this->m_buff;
		this->m_buff = 0;
	}

	this->m_buff = new char[this->m_size];

	if(this->m_buff == 0)
	{
		CloseHandle(file);
		return 0;
	}

	DWORD OutSize = 0;

	if(ReadFile(file,this->m_buff,this->m_size,&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);
	return 1;
}

void CFileProtect::FindFile(char* path) // OK
{
	char wildcard_path[256];

	wsprintf(wildcard_path,"%s*",path);

	WIN32_FIND_DATA data;

	HANDLE file = FindFirstFile(wildcard_path,&data);

	if(file == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		if((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
		{
			char file_name[256];
			wsprintf(file_name,"%s%s",path,data.cFileName);
			this->EncryptFile(file_name);
			continue;
		}

		if(strcmp(data.cFileName,".") != 0 && strcmp(data.cFileName,"..") != 0)
		{
			char next_path[256];
			wsprintf(next_path,"%s%s\\",path,data.cFileName);
			this->FindFile(next_path);
			continue;
		}
	}
	while(FindNextFile(file,&data) != 0);
}

bool CFileProtect::EncryptFile(char* path) // OK
{
	if(this->LoadFile(path) == 0)
	{
		return 0;
	}

	if(this->m_size >= sizeof(gFileProtectHeader) && memcmp(this->m_buff,gFileProtectHeader,sizeof(gFileProtectHeader)) == 0)
	{
		return 0;
	}

	HANDLE file = CreateFile(path,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	char* buff = new char[this->m_size+sizeof(gFileProtectHeader)];

	memcpy(&buff[0],gFileProtectHeader,sizeof(gFileProtectHeader));

	memcpy(&buff[sizeof(gFileProtectHeader)],this->m_buff,this->m_size);

	for(int n=0;n < ((int)this->m_size);n++)
	{
		buff[sizeof(gFileProtectHeader)+n] ^= gFileProtectXorTable[n%sizeof(gFileProtectXorTable)];
		buff[sizeof(gFileProtectHeader)+n] += gFileProtectXorTable[gCustomerName[n%sizeof(gCustomerName)]%sizeof(gFileProtectXorTable)];
	}

	DWORD OutSize = 0;

	if(WriteFile(file,buff,(this->m_size+sizeof(gFileProtectHeader)),&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);
	return 1;
}

bool CFileProtect::DecryptFile(char* path) // OK
{
	if(this->LoadFile(path) == 0)
	{
		return 0;
	}

	if(this->m_size < sizeof(gFileProtectHeader))
	{
		return 0;
	}

	if(memcmp(this->m_buff,gFileProtectHeader,sizeof(gFileProtectHeader)) != 0)
	{
		return 0;
	}

	for(int n=0;n < ((int)(this->m_size-sizeof(gFileProtectHeader)));n++)
	{
		this->m_buff[sizeof(gFileProtectHeader)+n] -= gFileProtectXorTable[gCustomerName[n%sizeof(gCustomerName)]%sizeof(gFileProtectXorTable)];
		this->m_buff[sizeof(gFileProtectHeader)+n] ^= gFileProtectXorTable[n%sizeof(gFileProtectXorTable)];
	}

	return this->CreateTemporaryFile();
}

bool CFileProtect::CreateTemporaryFile() // OK
{
	wsprintf(this->m_path,"Data\\t%d.bmd",rand()%1000);

	HANDLE file = CreateFile(this->m_path,GENERIC_WRITE,FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,0,CREATE_ALWAYS,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_TEMPORARY,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if(WriteFile(file,&this->m_buff[sizeof(gFileProtectHeader)],(this->m_size-sizeof(gFileProtectHeader)),&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);
	return 1;
}

void CFileProtect::DeleteTemporaryFile() // OK
{
	if(strcmp(this->m_path,"") == 0)
	{
		return;
	}

	if(DeleteFile(this->m_path) == 0)
	{
		return;
	}

	delete[] this->m_buff;

	this->m_buff = 0;

	this->m_size = 0;

	memset(this->m_path,0,sizeof(this->m_path));
}

void CFileProtect::ConvertMainFilePath(char* path) // OK
{
	if(this->DecryptFile(path) == 0)
	{
		return;
	}

	memset(path,0,strlen(path));

	memcpy(path,this->m_path,strlen(this->m_path));
}
