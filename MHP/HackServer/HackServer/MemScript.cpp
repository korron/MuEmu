// MemScript.cpp: implementation of the CMemScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemScript.h"
#include "Util.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemScript::CMemScript()
{
    this->m_buff = 0;
	this->m_size = 0;
}

CMemScript::~CMemScript()
{
    if(this->m_buff != 0)
	{
        delete[] this->m_buff;
	}

	this->m_size = 0;
}

bool CMemScript::SetBuffer(char* filename,int CryptSwitch)
{
    if(this->m_buff != 0)
	{
	    delete[] this->m_buff;
	    this->m_buff = 0;
	}

	char NewFileName[MAX_PATH];
	sprintf_s(NewFileName,"%s",filename);
    HANDLE file = CreateFile(NewFileName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
 
	if(file == INVALID_HANDLE_VALUE)
	{
		ErrorMessageBox("%s file not found",filename);
	    return 0;
	}

	this->m_size = GetFileSize(file,0);

	this->m_buff = new char[this->m_size];

	if(this->m_buff == 0)
	{
	    return 0;
	}

	DWORD BytesRead = 0;
    
	if(ReadFile(file,this->m_buff,this->m_size,&BytesRead,NULL) == 0)
	{
	    CloseHandle(file);
	    return 0;
	}

	CloseHandle(file);

	if(CryptSwitch != 0)
	{
		for(DWORD n=0; n < this->m_size; n++)
		{
			this->m_buff[n] += 0x95;
			this->m_buff[n] ^= 0xCA;
		}
	}

	this->m_count = 0;

	this->m_tick = GetTickCount();

    return 1;
}

void CMemScript::GetWzAgInfo(char* buff,DWORD* size)
{
    memcpy(buff,this->m_buff,this->m_size);

	*size = this->m_size;
}

int CMemScript::GetChar()
{
    if(this->m_count >= (int)this->m_size)
	{
        return -1;
	}
    else
	{
        return this->m_buff[this->m_count++];
	}
}

void CMemScript::UnGetChar(int ch)
{
    if(this->m_count <= 0)
	{
        return;
	}
    else
	{
        this->m_count--;
        this->m_buff[this->m_count] = ch;
	}
}

int CMemScript::GetToken()
{
    if((GetTickCount()-this->m_tick) > 1000)
	{
        throw 1;
	}

    this->m_string[0] = 0;
	this->m_number = 0;

    char ch;

    while(true)
	{
	    ch = this->GetChar();

        if(ch == -1)
		{
            return 2;
		}

		if(isspace(ch) != 0)
		{
		    continue;
		}

	    if(ch == '/' && (ch = this->GetChar()) == '/')
		{
            while(true)
			{
		        ch = this->GetChar();

				if(ch == -1)
				{
				    return 2;
				}

			    if(ch == '\n')
				{
			       break;
				}
			}
		}
		else
		{
		    break;
		}
	}

	char* lpBuff;
	char TempString[100] = {0};

    switch(ch)
	{
        case 0x23:	// #
        case 0x3B:	// ;
	    case 0x2C:	// ,
	    case 0x7B:	// {
        case 0x7D:	// }
		    return ch;
	    case 0x2D:	//-
	    case 0x2E:	//.
	    case 0x30:	//0
	    case 0x31:	//1
	    case 0x32:	//2
	    case 0x33:	//3
	    case 0x34:	//4		
	    case 0x35:	//5
	    case 0x36:	//6
	    case 0x37:	//7
	    case 0x38:	//8
	    case 0x39:	//9
		case '*':
	        this->UnGetChar(ch);

		    lpBuff = TempString;
		
		    while(((ch = this->GetChar()) != -1) && (ch == 0x2E) || (ch == '*') || ((isdigit(ch) != 0) || (ch == 0x2D))) 
			{
			    *lpBuff = ch;
			    lpBuff++;
			}
			
		    *lpBuff = 0;
			if(strcmp(TempString,"*") == 0)
			{
				this->m_number = -1;
			}
			else
			{
				this->m_number = (float)atof(TempString);
			}
		    return 1;
	    case 0x22:	// "	
	        lpBuff = &this->m_string[0];
		
		    while(((ch = this->GetChar()) != -1) && (ch != 0x22))	
			{
			    *lpBuff = ch;
			    lpBuff++;
			}

		    if(ch != 0x22 )
			{
			    this->UnGetChar(ch);
			}

		    *lpBuff = 0;
		    return 0;
        default:	
		    if(isalpha(ch))
			{
			    lpBuff = &this->m_string[0];
			    *lpBuff=ch;
			    lpBuff++;

			    while(((ch = this->GetChar()) != -1) && ((ch == 0x2E) || (ch == 0x5F) || (isalnum(ch) != 0)))
				{
				    *lpBuff = ch;
				    lpBuff++;
				
				}

			    this->UnGetChar(ch);
			    *lpBuff=0;
			    return 0;
			}
		    else
			{
			    return 0x3C;
			}
		    break;
	}
}

int CMemScript::GetNumber()
{
    return (int)this->m_number;
}

DWORD CMemScript::GetDword()
{
	DWORD HexResult;

	char TempHex[11];

	strcpy_s(TempHex,&this->m_string[0]);

	sscanf_s(TempHex,"%X",&HexResult);

	return HexResult;
}

DWORD CMemScript::GetAsDword()
{
	this->GetToken();

	DWORD HexResult;

	char TempHex[11];

	strcpy_s(TempHex,&this->m_string[0]);

	sscanf_s(TempHex,"%X",&HexResult);

	return HexResult;
}

int CMemScript::GetAsNumber()
{
	this->GetToken();

    return (int)this->m_number;
}

char* CMemScript::GetString()
{
    return &this->m_string[0];
}

char* CMemScript::GetAsString()
{
    this->GetToken();

	return &this->m_string[0];
}

double CMemScript::GetFloat()
{
	return (double)this->m_number;
}

double CMemScript::GetAsFloat()
{
	this->GetToken();
    return (double)this->m_number;
}