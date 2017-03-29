#include "StdAfx.h"

char* RemoveChar(char* Input, char Character) //OK
{
	for(int i=0; i<=strlen(Input); i++)
	{
		if(Input[i] == Character)
		{
			for(int n=i; n<=strlen(Input); n++)
			{
				Input[n] = Input[n+1];
			}
		}
	}
	return Input;
}

void GetHID()
{
	HW_PROFILE_INFO hwProfileInfo;
	DWORD HDSerial;
	char HardID[50];
	TCHAR DriverLetterBuf[30];
	char DriverName[5];

    GetSystemWindowsDirectory(DriverLetterBuf,30);
	sprintf(DriverName,"%c://",DriverLetterBuf[0]);
	GetVolumeInformationA(DriverName, NULL, 12, &HDSerial, NULL, NULL, NULL, 10);

	if(GetCurrentHwProfile(&hwProfileInfo) != NULL)
	{
		sprintf(HardID,"%S",hwProfileInfo.szHwProfileGuid);
		strcpy(HardID,RemoveChar(HardID,'{'));
		strcpy(HardID,RemoveChar(HardID,'}'));
		strcpy(HardID,RemoveChar(HardID,'-'));
		
		for(int i=0;i<=strlen(HardID);i++)
		{
			HardID[i] = toupper(HardID[i]);
		}
		sprintf(HardID,"%c%c%c%c%c%c%c%c-%c%c%c%c%c%c%c%c-%c%c%c%c%c%c%c%c-%.08X",HardID[0],HardID[1],HardID[2],HardID[3],HardID[4],HardID[5],HardID[6],
			HardID[7],HardID[8],HardID[9],HardID[10],HardID[11],HardID[12],HardID[13],HardID[14],HardID[15],HardID[16],HardID[17],HardID[18],HardID[19],HardID[20],
			HardID[21],HardID[22],HardID[23],HDSerial);
	}
	if(strlen(HardID)<20)
	{
		sprintf(HardID,"%.08X-%.08X-%.08X-%.08X",HDSerial,HDSerial/2,HDSerial*2,HDSerial*3);
	}

	FILE * pFile;

	fopen_s(&pFile,".\\HardwareId.txt","w");

	if (pFile!=NULL)
	{
		fputs (HardID,pFile);
		fclose (pFile);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{	
	GetHID();
	return 0;
}

