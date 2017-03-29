// FileProtect.h: interface for the CFileProtect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CFileProtect
{
public:
	CFileProtect();
	virtual ~CFileProtect();
	bool LoadFile(char* path);
	void FindFile(char* path);
	bool EncryptFile(char* path);
	bool DecryptFile(char* path);
	bool CreateTemporaryFile();
	void DeleteTemporaryFile();
	void ConvertMainFilePath(char* path);
private:
	char* m_buff;
	DWORD m_size;
	char m_path[256];
};

extern CFileProtect gFileProtect;

static const BYTE gFileProtectHeader[8] = {0x98,0xAD,0xF1,0x11,0x46,0x87,0xC5,0x27};

static const BYTE gFileProtectXorTable[16] = {0x58,0xA1,0x10,0xFA,0x85,0xDE,0xB1,0x56,0xC1,0x15,0x90,0x8A,0x12,0xDE,0x67,0x44};
