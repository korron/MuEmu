#include "StdAfx.h"
#include "CRC32.h"

void CCRC32::Initialize(void)
{
	memset(&this->ulTable, 0, sizeof(this->ulTable));

	for(int iCodes = 0; iCodes <= 0xFF; iCodes++)
	{
		this->ulTable[iCodes] = this->Reflect(iCodes, 8) << 24;

		for(int iPos = 0; iPos < 8; iPos++)
		{
			this->ulTable[iCodes] = (this->ulTable[iCodes] << 1) ^ (this->ulTable[iCodes] & (1 << 31) ? CRC32_POLYNOMIAL : 0);
		}

		this->ulTable[iCodes] = this->Reflect(this->ulTable[iCodes], 32);
	}
}

unsigned long CCRC32::Reflect(unsigned long ulReflect, char cChar)
{
	unsigned long ulValue = 0;

	for(int iPos = 1; iPos < (cChar + 1); iPos++)
	{
		if(ulReflect & 1)
		{
			ulValue |= 1 << (cChar - iPos);
		}
		ulReflect >>= 1;
	}

	return ulValue;
}

unsigned long CCRC32::FileCRC(const wchar_t *sFileName)
{
	unsigned long ulCRC = 0xFFFFFFFF;

	FILE *fSource = NULL;
	unsigned char sBuf[CRC32BUFSZ];
	int iBytesRead = 0;

	if(_wfopen_s(&fSource, sFileName, L"rb") != NULL)
	{
		return 0xFFFFFFFF;
	}

	do
	{
		iBytesRead = fread(sBuf, sizeof(char), CRC32BUFSZ, fSource);
		this->PartialCRC(&ulCRC, sBuf, iBytesRead);
	} while(iBytesRead == CRC32BUFSZ);

	fclose(fSource);

	return(ulCRC ^ 0xFFFFFFFF);
}

unsigned long CCRC32::FullCRC(unsigned char *sData, unsigned long ulLength)
{
	unsigned long ulCRC = 0xFFFFFFFF;
	this->PartialCRC(&ulCRC, sData, ulLength);
	return ulCRC ^ 0xFFFFFFFF;
}

void CCRC32::PartialCRC(unsigned long *ulInCRC, unsigned char *sData, unsigned long ulLength)
{
	while(ulLength--)
	{
		*ulInCRC = (*ulInCRC >> 8) ^ this->ulTable[(*ulInCRC & 0xFF) ^ *sData++];
	}
}