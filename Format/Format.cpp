// Format.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MemScript.h"

struct COL_INFO
{
	eTokenResult token;
	int number;
	float float_number;
	char string[100];
	int LinePos;
};

struct ROW_INFO
{
	std::vector<COL_INFO> ColInfo;
};

std::vector<ROW_INFO> RowInfo;

std::vector<int> HeaderInfo;

int HeaderCount = 0;

bool ParseHeader(char* buff)
{
	if(buff == 0)
	{
		return 0;
	}

	bool ColLock = 0;

	int CommentFixer = 0;

	for(int n=0;n < 1024;n++)
	{
		if(buff[n] == '\n')
		{
			break;
		}

		if(buff[n] == '/')
		{
			CommentFixer++;
			continue;
		}

		if(buff[n] == 0x09 || buff[n] == 0x20)
		{
			ColLock = 0;
			CommentFixer = 0;
		}
		else
		{
			if(ColLock == 0)
			{
				HeaderInfo.push_back(n-CommentFixer);
				HeaderCount++;
				ColLock = 1;
				CommentFixer = 0;
			}
		}
	}

	return 1;
}

bool Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return 0;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
	}

	if(ParseHeader(lpMemScript->GetBuffer()) == 0)
	{
		printf("PARSE ERROR\n");
		delete lpMemScript;
		return 0;
	}

	try
	{
		while(true)
		{
			eTokenResult FirstToken = lpMemScript->GetToken();

			if(FirstToken == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			ROW_INFO r_info;

			int CurHeaderCount = 0;

			for(std::vector<int>::iterator header=HeaderInfo.begin();header != HeaderInfo.end();header++)
			{
				COL_INFO c_info;

				if(header == HeaderInfo.begin())
				{
					c_info.token = FirstToken;
				}
				else
				{
					c_info.token = lpMemScript->GetToken();
				}

				c_info.number = lpMemScript->GetNumber();

				c_info.float_number = lpMemScript->GetFloatNumber();

				strcpy_s(c_info.string,lpMemScript->GetString());

				c_info.LinePos = *header;

				//HeaderCount = 21;

				//if(CurHeaderCount < HeaderCount)
				//if(CurHeaderCount != 4 && CurHeaderCount != 8)
				//{
					r_info.ColInfo.push_back(c_info);
				//}

				CurHeaderCount++;
			}

			RowInfo.push_back(r_info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
	}

	delete lpMemScript;
	return 1;
}

bool Save(char* path)
{
	HANDLE file = CreateFile(path,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		printf("[%s] Could not create file",path);
		return 0;
	}

	for(std::vector<ROW_INFO>::iterator row=RowInfo.begin();row != RowInfo.end();row++)
	{
		char line[1024] = {0};

		memset(line,0x20,sizeof(line));

		int LastSize = 0;

		int CurHeaderCount = 0;

		for(std::vector<COL_INFO>::iterator col=row->ColInfo.begin();col != row->ColInfo.end();col++)
		{
			char temp[100] = {0};

			if(col->token == TOKEN_NUMBER)
			{
				if(strcmp(col->string,"*") == 0)
				{
					wsprintf(temp,"%s",col->string);
				}
				else
				{
					if((float)col->number == col->float_number)
					{
						if(CurHeaderCount == 0)
						{
							//col->number /= 10;

							wsprintf(temp,"%d",col->number);
						}
						else
						{
							//sprintf(temp,"%.2f",col->float_number);
							wsprintf(temp,"%d",col->number);
						}
					}
					else
					{
						wsprintf(temp,"%.2f",col->float_number);
					}
				}

				memcpy(&line[col->LinePos],temp,strlen(temp));
			}

			if(col->token == TOKEN_STRING)
			{
				wsprintf(temp,"\"%s\"",col->string);
			}

			memcpy(&line[col->LinePos],temp,strlen(temp));

			LastSize = col->LinePos+strlen(temp);

			CurHeaderCount++;
		}

		memset(&line[LastSize],0,(sizeof(line)-LastSize));

		line[LastSize+0] = 0x0D;
		line[LastSize+1] = 0x0A;

		DWORD size;

		if(WriteFile(file,&line,(LastSize+2),&size,0) == 0)
		{
			CloseHandle(file);
			printf("[%s] Could not write file",path);
			return 0;
		}
	}

	CloseHandle(file);
	return 1;
}

struct MOB_NAME
{
	int Index;
	int Type;
	char Name[32];
};

MOB_NAME gMobName[1000];

void LoadMobName(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(lpMemScript->GetLastError());
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	for(int n=0;n < 1000;n++)
	{
		gMobName[n].Index = -1;
	}

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			MOB_NAME info;

			memset(&info,0,sizeof(info));

			info.Index = lpMemScript->GetNumber();

			info.Type = lpMemScript->GetAsNumber();

			char temp[100];

			strcpy_s(temp,lpMemScript->GetAsString());

			memcpy(info.Name,temp,32);

			info.Name[31] = 0;

			if(gMobName[info.Index].Index == -1)
			{
				memcpy(&gMobName[info.Index],&info,sizeof(gMobName[info.Index]));
			}
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

struct SORT_INFO
{
	bool Active;
	std::vector<COL_INFO> ColInfo;
};

SORT_INFO SortInfo[1000];

void FixMob()
{
	for(int n=0;n < 1000;n++)
	{
		SortInfo[n].Active = 0;
	}

	for(std::vector<ROW_INFO>::iterator row=RowInfo.begin();row != RowInfo.end();row++)
	{
		int ColCount = 0;
		int ColIndex = -1;

		for(std::vector<COL_INFO>::iterator col=row->ColInfo.begin();col != row->ColInfo.end();col++)
		{
			if(ColCount == 0)
			{
				ColIndex = col->number;
			}
			else
			{
				/*
				if(ColCount == 2 && gMobName[ColIndex].Index == ColIndex)
				{
					memset(col->string,0,sizeof(col->string));

					strcpy_s(col->string,gMobName[ColIndex].Name);
				}
				*/
			}

			ColCount++;
		}

		if(ColIndex != -1 && SortInfo[ColIndex].Active == 0)
		{
			SortInfo[ColIndex].Active = 1;
			SortInfo[ColIndex].ColInfo = row->ColInfo;
		}
	}

	RowInfo.clear();

	for(int n=0;n < 1000;n++)
	{
		if(SortInfo[n].Active != 0)
		{
			ROW_INFO info;

			info.ColInfo = SortInfo[n].ColInfo;

			RowInfo.push_back(info);
		}
	}
}

void FixOrder()
{
	COL_INFO new_c[6];
	int new_LinePos[7];

	for(std::vector<ROW_INFO>::iterator row=RowInfo.begin();row != RowInfo.end();row++)
	{
		int ColCount = 0;
		int ColIndex = -1;

		for(std::vector<COL_INFO>::iterator col=row->ColInfo.begin();col != row->ColInfo.end();col++)
		{
			new_LinePos[ColCount] = col->LinePos;

			switch(ColCount)
			{
			case 0:
				break;
			case 1:
				new_c[1] = *col;
				break;
			case 2:
				new_c[2] = *col;
				break;
			case 3:
				new_c[0] = *col;
				new_c[0].LinePos = new_LinePos[0];
				break;
			case 4:
				new_c[3] = *col;
				new_c[3].LinePos = new_LinePos[3];
				break;
			case 5:
				new_c[4] = *col;
				new_c[4].LinePos = new_LinePos[4];
				break;
			case 6:
				new_c[5] = *col;
				new_c[5].LinePos = new_LinePos[5];
				break;
			default:
				new_c[ColCount] = *col;
				break;
			}

			ColCount++;
		}

		row->ColInfo.clear();

		for(int n=0;n < _countof(new_c);n++)
		{
			row->ColInfo.push_back(new_c[n]);
		}
	}
}

int main(int argc, char* argv[])
{
	//LoadMobName("mob.txt");

	if(Load("in.txt") != 0)
	{
		//FixMob();
		FixOrder();

		if(Save("out.txt") != 0)
		{
			printf("Operation Successful!\n");
		}
	}

	while(true){Sleep(100);}

	return 0;
}

