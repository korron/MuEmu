#pragma once

enum eProtectType
{
	TYPE_DUMP = 0,
	TYPE_CRC = 1,
	TYPE_CRC_PROTECT = 2,
};

void GetHackList(wchar_t* Folder, int Type);
void GetDump(wchar_t *exeFile);
void GetChecksum(wchar_t* filename, int type);
void WriteFile(char* text, int type);
wchar_t* ConvertFileName(wchar_t* path);
void RemovePath(wchar_t *s,const wchar_t *toremove);
