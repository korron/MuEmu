#ifndef _QUERYMANAGER_H_
#define _QUERYMANAGER_H_

#pragma once


#define MAX_COLUMNS	100

class CQueryManager  
{
public:

	CQueryManager ();
	virtual ~CQueryManager();

    bool Connect(char* dns);
	void Disconnect();
	void Diagnostic(char* query);

	bool ExecQuery(char* query,...);
	void Close();
	SQLRETURN Fetch();
	int FindIndex(char* ColName);

	void GetAsString(char* ColName,char* OutBuffer);
	int GetAsInteger(char* ColName);
	__int64 GetAsInteger64(char* ColName);
	float GetAsFloat(char* ColName);
	int GetResult(int index);
	bool GetAsBinary(BYTE* OutBuffer,DWORD size,char* query,...);
	void SetAsBinary(BYTE* InBuffer,DWORD size,char* query,...);
private:
    SQLHANDLE m_SQLEnvironment;
	SQLHANDLE m_SQLConnection;
	SQLHANDLE m_STMT;
	char m_dns[64];
	long  m_RowCount;
	short m_ColCount;
	SQLCHAR m_SQLColName[MAX_COLUMNS][30];
	char m_SQLData[MAX_COLUMNS][256];
	long m_SQLDataLen[MAX_COLUMNS];
};

extern CQueryManager gDatabase;

#endif