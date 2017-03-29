// GetInternalList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char* DecodedPath  = ".\\Decoded.txt";
	char* EncodedPath  = ".\\Internal.List.db";

	FILE *decFile, *encFile;
	fopen_s(&decFile, DecodedPath,"rb");
	fopen_s(&encFile, EncodedPath,"wb");

	fseek(decFile, 0, SEEK_END);
	int decSize = ftell(decFile);
	rewind(decFile);

	char* buffer;
	buffer = (char*)malloc(sizeof(char)*decSize);
	fread(buffer,1,decSize,decFile);

	for(int n=0; n < decSize; n++)
	{
		buffer[n] ^= 0xCA;
		buffer[n] -= 0x95;
	}

	fwrite(buffer, decSize, 1, encFile);

	fclose(decFile);
	fclose(encFile);
	return 0;
}