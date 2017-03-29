// QueryManager.cpp: implementation of the CQueryManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QueryManager.h"

CQueryManager gDatabase;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CQueryManager::CQueryManager()
{
	this->m_RowCount = -1;
    this->m_ColCount = -1;
	this->m_SQLConnection = SQL_NULL_HANDLE;
	this->m_SQLEnvironment = SQL_NULL_HANDLE;
	this->m_STMT = SQL_NULL_HANDLE;

	memset(this->m_SQLColName,0,sizeof(this->m_SQLColName));
	memset(this->m_SQLData,0,sizeof(this->m_SQLData));

	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&this->m_SQLEnvironment);
	SQLSetEnvAttr(this->m_SQLEnvironment,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
}

CQueryManager::~CQueryManager()
{
	this->Disconnect();
}

bool CQueryManager::Connect(char* dns) // OK
{
	strcpy_s(this->m_dns,dns);

	if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC,this->m_SQLEnvironment,&this->m_SQLConnection)) == 0)
	{
		return 0;
	}
 
	if(SQL_SUCCEEDED(SQLConnect(this->m_SQLConnection,(SQLCHAR*)this->m_dns,SQL_NTS,0,SQL_NTS,0,SQL_NTS)) == 0)
	{
		return 0;
	}

	if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT,this->m_SQLConnection,&this->m_STMT)) == 0)
	{
		return 0;
	}
 
	return 1;
}

void CQueryManager::Disconnect()
{
    if(this->m_STMT != SQL_NULL_HANDLE)
	{
		SQLFreeHandle(SQL_HANDLE_STMT,this->m_STMT);
	}

	if(this->m_SQLConnection != SQL_NULL_HANDLE)
	{
		SQLFreeHandle(SQL_HANDLE_DBC,this->m_SQLConnection);
	}

	if(this->m_SQLEnvironment != SQL_NULL_HANDLE)
	{
		SQLFreeHandle(SQL_HANDLE_ENV,this->m_SQLEnvironment);
	}

	this->m_SQLConnection = SQL_NULL_HANDLE;
	this->m_SQLEnvironment = SQL_NULL_HANDLE;
	this->m_STMT = SQL_NULL_HANDLE;
}

void CQueryManager::Diagnostic(char* query)
{
	SQLSMALLINT count=1,MsgLen;
	SQLCHAR SqlState[6],SQLMsgError[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER NativeError;

	printf("%s",query);

    while(SQLGetDiagRec(SQL_HANDLE_STMT,this->m_STMT,count,SqlState,&NativeError,SQLMsgError,sizeof(SQLMsgError),&MsgLen) != SQL_NO_DATA)
	{
	    printf("[Query Manager] State (%s), Diagnostic: %s\n",SqlState,SQLMsgError);
	    count++;
	}

    if(strcmp((char*)SqlState,"08S01") == 0)
	{
	    this->Connect(this->m_dns);
	}
}

bool CQueryManager::ExecQuery(char* query,...)
{
	char buff[4096];

	va_list arg;
	va_start(arg,query);
	vsprintf(buff,query,arg);
	va_end(arg);

	SQLRETURN result = SQLExecDirect(this->m_STMT,(SQLCHAR*)buff,SQL_NTS);

	if(result != SQL_SUCCESS && result != SQL_SUCCESS_WITH_INFO && result != SQL_NO_DATA)
	{
		this->Diagnostic(buff);
		return 0;
	}

	SQLRowCount(this->m_STMT,&this->m_RowCount);

	if(this->m_RowCount == 0)
	{
		return 1;
	}

	SQLNumResultCols(this->m_STMT,&this->m_ColCount);

	if(this->m_ColCount >= MAX_COLUMNS)
	{
	    return 0;
	}

	if(this->m_ColCount == 0)
	{
		return 1;
	}

	memset(this->m_SQLData,0,sizeof(this->m_SQLData));

	for(int n=0;n < this->m_ColCount;n++)
	{
		SQLBindCol(this->m_STMT,n+1,SQL_C_CHAR,this->m_SQLData[n],sizeof(this->m_SQLData[0]),&this->m_SQLDataLen[n]);
		SQLDescribeCol(this->m_STMT,n+1,this->m_SQLColName[n],sizeof(this->m_SQLColName[n]),0,0,0,0,0);
	}

	return 1;
}

void CQueryManager::Close()
{
	SQLCloseCursor(this->m_STMT);
	SQLFreeStmt(this->m_STMT,SQL_UNBIND);
}

SQLRETURN CQueryManager::Fetch()
{
	return SQLFetch(this->m_STMT);
}

int CQueryManager::FindIndex(char* ColName)
{
    for(int n=0;n < this->m_ColCount;n++)
	{
		if(stricmp(ColName,(char*)this->m_SQLColName[n]) == 0)
		{
			return n;
		}
	}

	return -1;
}

void CQueryManager::GetAsString(char* ColName,char* OutBuffer)
{
    int index = this->FindIndex(ColName);

	if(index != -1)
	{
        strcpy(OutBuffer,this->m_SQLData[index]);
	}
	else
	{
	    OutBuffer[0] = 0;
	}
}

int CQueryManager::GetAsInteger(char* ColName)
{
    int index = this->FindIndex(ColName);

	if(index != -1)
	{
	    return atoi(this->m_SQLData[index]);
	}

    return -1;
}

__int64 CQueryManager::GetAsInteger64(char* ColName)
{
    int index = this->FindIndex(ColName);

	if(index != -1)
	{
	    return _atoi64(this->m_SQLData[index]);
	}

	return -1;
}

float CQueryManager::GetAsFloat(char* ColName)
{
    int index = this->FindIndex(ColName);

	if(index != -1)
	{
	    return atof(this->m_SQLData[index]);
	}

	return -1;
}

int CQueryManager::GetResult(int index)
{
    return atoi(this->m_SQLData[index]);
}

bool CQueryManager::GetAsBinary(BYTE* OutBuffer,DWORD size,char* query,...)
{
    char buff[4096];

	va_list arg;
	va_start(arg,query);
	vsprintf(buff,query,arg);
	va_end(arg);

	if(SQL_SUCCEEDED(SQLExecDirect(this->m_STMT,(SQLCHAR*)buff,SQL_NTS)) == 0)
	{
	    this->Diagnostic(buff);
	    return 0;
	}

    if(SQLFetch(this->m_STMT) == SQL_NO_DATA)
	{
	    return 0;
	}

	SQLINTEGER SQLSize;

	if(SQL_SUCCEEDED(SQLGetData(this->m_STMT,1,SQL_C_BINARY,OutBuffer,size,&SQLSize)) == 0)
	{
	    return 0;
	}

    return 1;
}

void CQueryManager::SetAsBinary(BYTE* InBuffer,DWORD size,char* query,...)
{
    char buff[4096];

	va_list arg;
	va_start(arg,query);
	vsprintf(buff,query,arg);
	va_end(arg);

	SQLINTEGER ValueSize = (size+100)*-1;

	SQLBindParameter(this->m_STMT,1,SQL_PARAM_INPUT,SQL_C_BINARY,SQL_LONGVARBINARY,size,0,(SQLPOINTER)1,0,&ValueSize);

	SQLExecDirect(this->m_STMT,(SQLCHAR*)buff,SQL_NTS);

	SQLPOINTER pointer;
	SQLRETURN result = SQLParamData(this->m_STMT,&pointer);

	while(result == SQL_NEED_DATA)
	{
	    result = SQLPutData(this->m_STMT,InBuffer,size);
		result = SQLParamData(this->m_STMT,&pointer);
	}
	
	SQLParamData(this->m_STMT,&pointer);
}
