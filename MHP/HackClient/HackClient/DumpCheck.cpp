#include "stdafx.h"
#include "DumpCheck.h"
#include "HackServerProtocol.h"
#include "ListManager.h"
#include "Util.h"

CDumpCheck gDumpCheck;

CDumpCheck::CDumpCheck()
{

}

CDumpCheck::~CDumpCheck()
{

}

bool CDumpCheck::Check(wchar_t* sTemp,char* CaptionName)
{
	bool load = 0;

	HANDLE file,mapping;
	BYTE* lpBaseAddress;
	IMAGE_NT_HEADERS32* lpNtHeader;

	for(std::vector<DUMP_LIST_INFO>::iterator it=gListManager.gDumpListInfo.begin();it != gListManager.gDumpListInfo.end();it++)
	{
		if(it->type != TYPE_DUMP)
		{
			continue;
		}

		if(load == 0)
		{
			if(this->GetProcessInfo(sTemp,&file,&mapping,&lpBaseAddress,&lpNtHeader) == 0)
			{
				break;
			}
			else
			{
				load = 1;
			}
		}

		BYTE dump[32];

		if(this->FindEntryPointInfo(sTemp,file,mapping,lpBaseAddress,lpNtHeader,it->offset,dump) == 0)
		{
			continue;
		}

		if(memcmp(it->dump,dump,sizeof(it->dump)) == 0)
		{
			memcpy(CaptionName,it->name,sizeof(it->name));
			UnmapViewOfFile((LPCVOID)lpBaseAddress);
			CloseHandle(mapping);
			CloseHandle(file);
			return 0;
		}
	}

	if(load != 0)
	{
		UnmapViewOfFile((LPCVOID)lpBaseAddress);

		CloseHandle(mapping);

		CloseHandle(file);
	}

	return 1;
}

bool CDumpCheck::GetProcessInfo(wchar_t* filename,HANDLE* file_out,HANDLE* mapping_out,BYTE** lpBaseAddress_out,IMAGE_NT_HEADERS32** lpNtHeader_out)
{
	HANDLE file = CreateFileW(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	BY_HANDLE_FILE_INFORMATION bhfi;

	if(GetFileInformationByHandle(file,&bhfi) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	HANDLE mapping = CreateFileMapping(file,0,PAGE_READONLY,bhfi.nFileSizeHigh,bhfi.nFileSizeLow,0);

	if(mapping == 0)
	{
		CloseHandle(file);
		return 0;
	}

	BYTE* lpBaseAddress = (BYTE*)MapViewOfFile(mapping,FILE_MAP_READ,0,0,bhfi.nFileSizeLow);

	if(lpBaseAddress == 0)
	{
		CloseHandle(mapping);
		CloseHandle(file);
		return 0;
	}

	IMAGE_DOS_HEADER* lpDosHeader = (IMAGE_DOS_HEADER*)lpBaseAddress;

	if(lpDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		UnmapViewOfFile((LPCVOID)lpBaseAddress);
		CloseHandle(mapping);
		CloseHandle(file);
		return 0;
	}

	IMAGE_NT_HEADERS32* lpNtHeader = (IMAGE_NT_HEADERS32*)(lpBaseAddress+lpDosHeader->e_lfanew);

	if(lpNtHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		UnmapViewOfFile((LPCVOID)lpBaseAddress);
		CloseHandle(mapping);
		CloseHandle(file);
		return 0;
	}

	if(lpNtHeader->FileHeader.Machine != IMAGE_FILE_MACHINE_I386)
	{
		UnmapViewOfFile((LPCVOID)lpBaseAddress);
		CloseHandle(mapping);
		CloseHandle(file);
		return 0;
	}

	(*file_out) = file;

	(*mapping_out) = mapping;

	(*lpBaseAddress_out) = lpBaseAddress;

	(*lpNtHeader_out) = lpNtHeader;

	return 1;
}

bool CDumpCheck::FindEntryPointInfo(wchar_t* filename, HANDLE file,HANDLE mapping,BYTE* lpBaseAddress,IMAGE_NT_HEADERS32* lpNtHeader,DWORD address,BYTE* dump) // OK
{
	IMAGE_SECTION_HEADER* lpSectionHeader = ImageRvaToSection(lpNtHeader,(PVOID)lpNtHeader->OptionalHeader.ImageBase,(address-lpNtHeader->OptionalHeader.ImageBase));

	if(lpSectionHeader == 0)
	{
		return 0;
	}

	if(SetFilePointer(file,(((address-lpNtHeader->OptionalHeader.ImageBase)-lpSectionHeader->VirtualAddress)+lpSectionHeader->PointerToRawData),0,FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		return 0;
	}

	DWORD NumberOfBytesRead = 0;

	if(ReadFile(file,dump,32,&NumberOfBytesRead,0) == 0)
	{
		return 0;
	}

	return 1;
}
