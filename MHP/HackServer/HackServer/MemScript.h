// MemScript.h: interface for the CMemScript class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CMemScript
{
public:
	CMemScript();
	virtual ~CMemScript();

    bool SetBuffer(char* filename, int CryptSwitch);
	void GetWzAgInfo(char* buff,DWORD* size);
    int GetChar();
    void UnGetChar(int ch);
    int GetToken();
    int GetNumber();
	int GetAsNumber();
	DWORD GetDword();
	DWORD GetAsDword();
	double GetFloat();
	double GetAsFloat();
    char* GetString();
	char* GetAsString();
	void DataCrypt(char** content);
private:
	char* m_buff;
	DWORD m_size;
	int m_count;
    float m_number;
	DWORD m_dword;
    char m_string[100];
	DWORD m_tick;

};
