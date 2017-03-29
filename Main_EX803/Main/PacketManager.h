// PacketManager.h: interface for the CPacketManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "..\\..\\Util\\cryptopp\\cryptlib.h"
#include "..\\..\\Util\\cryptopp\\modes.h"
#include "..\\..\\Util\\cryptopp\\des.h"

using namespace CryptoPP;

class CPacketManager
{
public:
	CPacketManager();
	virtual ~CPacketManager();
	void Init();
	int Encrypt(BYTE* lpTarget,BYTE* lpSource,int size);
	int Decrypt(BYTE* lpTarget,BYTE* lpSource,int size);
	bool AddData(BYTE* lpBuff,int size);
	bool ExtractPacket(BYTE* lpBuff);
	void XorData(int start,int end);
private:
	ECB_Mode<DES_XEX3>::Encryption m_Encryption;
	ECB_Mode<DES_XEX3>::Decryption m_Decryption;
	BYTE m_buff[2048];
	DWORD m_size;
	BYTE m_XorFilter[32];
};

extern CPacketManager gPacketManager;
