#pragma once

class CDumpCheck
{
public:
	CDumpCheck();
	virtual ~CDumpCheck();
	bool Check(wchar_t* sTemp,char* CaptionName);
	bool GetProcessInfo(wchar_t* filename,HANDLE* file_out,HANDLE* mapping_out,BYTE** lpBaseAddress_out,IMAGE_NT_HEADERS32** lpNtHeader_out);
	bool FindEntryPointInfo(wchar_t* filename, HANDLE file,HANDLE mapping,BYTE* lpBaseAddress,IMAGE_NT_HEADERS32* lpNtHeader,DWORD address,BYTE* dump);
};

extern CDumpCheck gDumpCheck;
