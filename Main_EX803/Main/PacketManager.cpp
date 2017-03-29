// PacketManager.cpp: implementation of the CPacketManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PacketManager.h"

CPacketManager gPacketManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPacketManager::CPacketManager() // OK
{
	this->Init();
}

CPacketManager::~CPacketManager() // OK
{

}

void CPacketManager::Init() // OK
{
	BYTE DES_XEX3[24] = {0x0C,0xB0,0x66,0xCC,0xEF,0x92,0x8C,0x5C,0x65,0xF4,0xAC,0x3F,0x71,0xF2,0x7B,0xCE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	this->m_Encryption.SetKey(DES_XEX3,sizeof(DES_XEX3));
	this->m_Decryption.SetKey(DES_XEX3,sizeof(DES_XEX3));

	memset(this->m_buff,0,sizeof(this->m_buff));

	this->m_size = 0;

	this->m_XorFilter[0] = 0xAB;
	this->m_XorFilter[1] = 0x11;
	this->m_XorFilter[2] = 0xCD;
	this->m_XorFilter[3] = 0xFE;
	this->m_XorFilter[4] = 0x18;
	this->m_XorFilter[5] = 0x23;
	this->m_XorFilter[6] = 0xC5;
	this->m_XorFilter[7] = 0xA3;
	this->m_XorFilter[8] = 0xCA;
	this->m_XorFilter[9] = 0x33;
	this->m_XorFilter[10] = 0xC1;
	this->m_XorFilter[11] = 0xCC;
	this->m_XorFilter[12] = 0x66;
	this->m_XorFilter[13] = 0x67;
	this->m_XorFilter[14] = 0x21;
	this->m_XorFilter[15] = 0xF3;
	this->m_XorFilter[16] = 0x32;
	this->m_XorFilter[17] = 0x12;
	this->m_XorFilter[18] = 0x15;
	this->m_XorFilter[19] = 0x35;
	this->m_XorFilter[20] = 0x29;
	this->m_XorFilter[21] = 0xFF;
	this->m_XorFilter[22] = 0xFE;
	this->m_XorFilter[23] = 0x1D;
	this->m_XorFilter[24] = 0x44;
	this->m_XorFilter[25] = 0xEF;
	this->m_XorFilter[26] = 0xCD;
	this->m_XorFilter[27] = 0x41;
	this->m_XorFilter[28] = 0x26;
	this->m_XorFilter[29] = 0x3C;
	this->m_XorFilter[30] = 0x4E;
	this->m_XorFilter[31] = 0x4D;
}

int CPacketManager::Encrypt(BYTE* lpTarget,BYTE* lpSource,int size) // OK
{
	int OriSize = size;

	BYTE* lpTempSource = lpSource;
	BYTE* lpTempTarget = lpTarget;

	if((size%8) != 0)
	{
		size = (1+(size/8))*8;
	}

	this->m_Encryption.ProcessData(lpTempTarget,lpTempSource,size);

	lpTempTarget[size] = size-OriSize;

	return (++size);
}

int CPacketManager::Decrypt(BYTE* lpTarget,BYTE* lpSource,int size) // OK
{
	int OriSize = size;

	BYTE* lpTempSource = lpSource;
	BYTE* lpTempTarget = lpTarget;

	if(((--size)%8) != 0)
	{
		size = (1+(size/8))*8;
	}

	this->m_Decryption.ProcessData(lpTempTarget,lpTempSource,size);

	return (OriSize-lpTempSource[(OriSize-1)]);
}

bool CPacketManager::AddData(BYTE* lpBuff,int size) // OK
{
	if(size <= 0 || size >= 2048)
	{
		return 0;
	}

	memcpy(this->m_buff,lpBuff,size);
	this->m_size = size;
	return 1;
}

bool CPacketManager::ExtractPacket(BYTE* lpBuff) // OK
{
	int size,end;

	switch(this->m_buff[0])
	{
		case 0xC1:
		case 0xC3:
			size = this->m_buff[1];
			end = 2;
			break;
		case 0xC2:
		case 0xC4:
			size = MAKEWORD(this->m_buff[2],this->m_buff[1]);
			end = 3;
			break;
		default:
			return 0;
	}

	if(this->m_size < ((DWORD)size))
	{
		return 0;
	}

	this->XorData((end+1),size);

	memcpy(lpBuff,this->m_buff,size);

	return 1;
}

void CPacketManager::XorData(int start,int end) // OK
{
	if(start > end)
	{
		return;
	}

	for(int n=start;n < end;n++)
	{
		this->m_buff[n] ^= this->m_buff[n-1]^this->m_XorFilter[n%32];
	}
}
