#include "stdafx.h"
#include "GetHackList.h"
#include "CRC32.h"
#include "FileProtect.h"

CCRC32 CRCChecker;
FILE *DumpFile, *ChecksumFile;
char gCustomerName[32];

int main(int argc, _TCHAR* argv[])
{
	GetPrivateProfileString("GetHackList","CustomerName","",gCustomerName,sizeof(gCustomerName),".\\GetHackList.ini");

	gFileProtect.FindFile("Checksum_Protect\\");

	CRCChecker.Initialize();

	fopen_s(&DumpFile,"Dump.List.db","w");

	fopen_s(&ChecksumFile,"Checksum.List.db","w");

	GetHackList(L"Dump\\", TYPE_DUMP);

	GetHackList(L"Checksum\\", TYPE_CRC);

	GetHackList(L"Checksum_Protect\\", TYPE_CRC_PROTECT);

	fputs("end", DumpFile);

	fputs("end", ChecksumFile);

	fclose(DumpFile);

	fclose(ChecksumFile);

	return 0;
}

void GetHackList(wchar_t* Folder, int Type)
{
	wchar_t wildcard_path[256];

	wsprintfW(wildcard_path,L"%s*",Folder);

	WIN32_FIND_DATAW data;

	HANDLE file = FindFirstFileW(wildcard_path,&data);

	if(file == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		if((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
		{
			wchar_t file_name[256];

			wsprintfW(file_name,L"%s%s",Folder,data.cFileName);

			switch(Type)
			{
				case TYPE_DUMP:
					GetDump(file_name);
					break;
				case TYPE_CRC:
					GetChecksum(file_name,Type);
					break;
				case TYPE_CRC_PROTECT:
					GetChecksum(file_name,Type);
					break;
			}

			continue;
		}

		if(wcscmp(data.cFileName,L".") != 0 && wcscmp(data.cFileName,L"..") != 0)
		{
			wchar_t next_path[256];

			wsprintfW(next_path,L"%s%s\\",Folder,data.cFileName);

			GetHackList(next_path,Type);

			continue;
		}
	}
	while(FindNextFileW(file,&data) != 0);
}

bool FindEntryPointInfo(wchar_t* filename,DWORD* address,BYTE* dump) // OK
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

	IMAGE_NT_HEADERS* lpNtHeader = (IMAGE_NT_HEADERS32*)(lpBaseAddress+lpDosHeader->e_lfanew);

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

	IMAGE_SECTION_HEADER* lpSectionHeader = ImageRvaToSection(lpNtHeader,(PVOID)lpNtHeader->OptionalHeader.ImageBase,lpNtHeader->OptionalHeader.AddressOfEntryPoint);

	if(lpSectionHeader == 0)
	{
		UnmapViewOfFile((LPCVOID)lpBaseAddress);
		CloseHandle(mapping);
		CloseHandle(file);
		return 0;
	}

	if(SetFilePointer(file,((lpNtHeader->OptionalHeader.AddressOfEntryPoint-lpSectionHeader->VirtualAddress)+lpSectionHeader->PointerToRawData),0,FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		UnmapViewOfFile((LPCVOID)lpBaseAddress);
		CloseHandle(mapping);
		CloseHandle(file);
		return 0;
	}

	DWORD NumberOfBytesRead = 0;

	if(ReadFile(file,dump,32,&NumberOfBytesRead,0) == 0)
	{
		UnmapViewOfFile((LPCVOID)lpBaseAddress);
		CloseHandle(mapping);
		CloseHandle(file);
		return 0;
	}

	(*address) = lpNtHeader->OptionalHeader.ImageBase+lpNtHeader->OptionalHeader.AddressOfEntryPoint;

	UnmapViewOfFile((LPCVOID)lpBaseAddress);

	CloseHandle(mapping);

	CloseHandle(file);

	return 1;
}

void GetDump(wchar_t* filename)
{
	DWORD type = 0;
	DWORD address;
	BYTE dump[32];

	if(FindEntryPointInfo(filename,&address,dump) == 0)
	{
		type = 1;

		address = CRCChecker.FileCRC(filename);

		memset(dump,0,sizeof(dump));
	}

	char temp[256];

	wcscpy_s(filename,256,ConvertFileName(filename));

	filename[31] = ((wcslen(filename)>31)?0:filename[31]);

	wsprintf(temp,"%d	\"0x%.8X\"	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	\"%S\"\r\n",
	(DWORD)type, (DWORD)address, (BYTE)dump[0], (BYTE)dump[1], (BYTE)dump[2], (BYTE)dump[3], (BYTE)dump[4], (BYTE)dump[5], (BYTE)dump[6], (BYTE)dump[7], (BYTE)dump[8], (BYTE)dump[9], (BYTE)dump[10],
	(BYTE) dump[11], (BYTE)dump[12], (BYTE)dump[13], (BYTE)dump[14], (BYTE)dump[15], (BYTE)dump[16], (BYTE)dump[17], (BYTE)dump[18], (BYTE)dump[19], (BYTE)dump[20],
	(BYTE) dump[21], (BYTE)dump[22], (BYTE)dump[23], (BYTE)dump[24], (BYTE)dump[25], (BYTE)dump[26], (BYTE)dump[27], (BYTE)dump[28], (BYTE)dump[29], (BYTE)dump[30],
	(BYTE) dump[31], filename);

	WriteFile(temp,TYPE_DUMP);
}

void GetChecksum(wchar_t* filename, int type)
{
	DWORD checksum = CRCChecker.FileCRC(filename);

	char temp[256];

	if(type == TYPE_CRC)
	{
		RemovePath(filename,L"Checksum\\");
	}
	else
	{
		RemovePath(filename,L"Checksum_Protect\\");
	}

	wsprintf(temp,"\"%S\"			\"0x%X\"\r\n",filename,checksum);

	WriteFile(temp,type);
}

void WriteFile(char* text, int type)
{
	switch(type)
	{
		case TYPE_DUMP:
			fputs(text, DumpFile);
			break;
		case TYPE_CRC:
			fputs(text, ChecksumFile);
			break;
		case TYPE_CRC_PROTECT:
			fputs(text, ChecksumFile);
			break;
	}
}

wchar_t* ConvertFileName(wchar_t* path)
{
	wchar_t *filename = wcsrchr(path, L'\\');
	(filename == NULL) ? filename = path : filename++;
	return filename;
}

void RemovePath(wchar_t *s,const wchar_t *toremove)
{
	while(s=wcsstr(s,toremove))
	{
		wmemmove(s,s+wcslen(toremove),1+wcslen(s+wcslen(toremove)));
	}
}
