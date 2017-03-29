#include "stdafx.h"
#include "ThemidaSDK.h"

int _tmain(int argc,_TCHAR* argv[]) // OK
{
	CLEAR_START

	VM_START

	DWORD VolumeSerialNumber;

	if(GetVolumeInformation("C:\\",0,0,&VolumeSerialNumber,0,0,0,0) == 0)
	{
		return 0;
	}

	UUID uuid;

	UuidCreateSequential(&uuid);

	SYSTEM_INFO SystemInfo;

	GetSystemInfo(&SystemInfo);

	DWORD ComputerHardwareId1 = VolumeSerialNumber ^ 0x12B586FE;

	DWORD ComputerHardwareId2 = *(DWORD*)(&uuid.Data4[2]) ^ 0x5D78A569;

	DWORD ComputerHardwareId3 = ((*(WORD*)(&uuid.Data4[6]) & 0xFFFF) | (SystemInfo.wProcessorArchitecture << 16)) ^ 0xF45BC123;

	DWORD ComputerHardwareId4 = ((SystemInfo.wProcessorLevel & 0xFFFF) | (SystemInfo.wProcessorRevision << 16)) ^ 0xB542D8E1;

	FILE* file;

	if(fopen_s(&file,"HardwareId.txt","w") != 0)
	{
		return 0;
	}

	fprintf(file,"%08X-%08X-%08X-%08X\n",ComputerHardwareId1,ComputerHardwareId2,ComputerHardwareId3,ComputerHardwareId4);

	fclose(file);

	VM_END

	CLEAR_END

	return 0;
}
