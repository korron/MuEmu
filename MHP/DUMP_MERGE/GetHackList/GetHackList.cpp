#include "stdafx.h"
#include "GetHackList.h"
#include "ReadFiles.h"

FILE *DumpFile;

int main(int argc, _TCHAR* argv[])
{
	printf("MERGE START\n");

	MergeDumpList("MERGE\\");

	fopen_s(&DumpFile,"Dump.List.db","w");

	MakeDumpList();

	fputs("end", DumpFile);

	fclose(DumpFile);

	printf("MERGE END [%d]/[%d]\n",gReadFiles.gDumpListInfo.size(),gReadFiles.m_TotalCount);

	Sleep(5000);

	return 0;
}

void MergeDumpList(char* Folder)
{
	char wildcard_path[256];

	wsprintf(wildcard_path,"%s*",Folder);

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

			wsprintf(file_name,"%s%s",Folder,data.cFileName);

			gReadFiles.DumpList(file_name);

			continue;
		}

		if(strcmp(data.cFileName,".") != 0 && strcmp(data.cFileName,"..") != 0)
		{
			char next_path[256];

			wsprintf(next_path,"%s%s\\",Folder,data.cFileName);

			MergeDumpList(next_path);

			continue;
		}
	}
	while(FindNextFile(file,&data) != 0);
}

void MakeDumpList()
{
	DWORD address;
	BYTE dump[32];

	for(std::vector<DUMP_LIST_INFO>::iterator it=gReadFiles.gDumpListInfo.begin();it != gReadFiles.gDumpListInfo.end();it++)
	{
		address = it->offset;

		memcpy(dump,it->dump,sizeof(dump));

		char temp[256],filename[256];

		strcpy(filename,it->name);

		filename[31] = ((strlen(filename)>31)?0:filename[31]);

		wsprintf(temp,"0	\"0x%.8X\"	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	%.3d	\"%s\"\r\n",
		(DWORD)address, (BYTE)dump[0], (BYTE)dump[1], (BYTE)dump[2], (BYTE)dump[3], (BYTE)dump[4], (BYTE)dump[5], (BYTE)dump[6], (BYTE)dump[7], (BYTE)dump[8], (BYTE)dump[9], (BYTE)dump[10],
		(BYTE) dump[11], (BYTE)dump[12], (BYTE)dump[13], (BYTE)dump[14], (BYTE)dump[15], (BYTE)dump[16], (BYTE)dump[17], (BYTE)dump[18], (BYTE)dump[19], (BYTE)dump[20],
		(BYTE) dump[21], (BYTE)dump[22], (BYTE)dump[23], (BYTE)dump[24], (BYTE)dump[25], (BYTE)dump[26], (BYTE)dump[27], (BYTE)dump[28], (BYTE)dump[29], (BYTE)dump[30],
		(BYTE) dump[31], filename);

		fputs(temp, DumpFile);
	}
}
