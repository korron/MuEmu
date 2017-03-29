#include "stdafx.h"
#include "Util.h"
#include "HackClient.h"
#include "HackServerProtocol.h"
#include "Log.h"
#include "SplashScreen.h"
#include "resource.h"
//Modules
#include "SimpleModules.h"
#include "ThreadCheck.h"

void SafeExitProcess()
{
	if(API_SCAN() == 0)
	{
		while(true)
		{
			memset(gThreadCheck.m_CheckThreadID,0,sizeof(gThreadCheck.m_CheckThreadID));
			CRASH_APPLICATION_MACRO
		}
	}
	else
	{
		while(true)
		{
			TerminateProcess(GetCurrentProcess(),0);
			CRASH_APPLICATION_MACRO
		}
	}
}

void SetByte(DWORD offset,BYTE value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,1,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(BYTE*)(offset) = value;

	VirtualProtect((void*)offset,1,OldProtect,&OldProtect);
}

void SetWord(DWORD offset,WORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,2,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(WORD*)(offset) = value;

	VirtualProtect((void*)offset,2,OldProtect,&OldProtect);
}

void SetDword(DWORD offset,DWORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetCompleteHook(BYTE head,DWORD offset,...) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,5,PAGE_EXECUTE_READWRITE,&OldProtect);

	if(head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset+1;

	*(DWORD*)(offset+1) = (*function)-(offset+5);

	VirtualProtect((void*)offset,5,OldProtect,&OldProtect);
}

void MemoryCpy(DWORD offset,void* value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memcpy((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void MemorySet(DWORD offset,DWORD value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memset((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void VirtualizeOffset(DWORD offset,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	DWORD HookAddr = (DWORD)malloc(size+5);

	memcpy((void*)HookAddr,(void*)offset,size);

	*(BYTE*)(HookAddr+size) = 0xE9;

	*(DWORD*)(HookAddr+size+1) = (offset+size)-((HookAddr+size)+5);

	*(BYTE*)(offset) = 0xE9;

	*(DWORD*)(offset+1) = HookAddr-(offset+5);

	memset((void*)(offset+5),0x90,(size-5));

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void ErrorMessageBox(char* message,...) // OK
{
	char buff[256];

	memset(buff,0,sizeof(buff));

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	MessageBox(0,buff,"Error",MB_OK | MB_ICONERROR);

	SafeExitProcess();
}

bool DelayMe(DWORD delay,DWORD value) // OK
{
	DWORD tick = GetTickCount();

	while(true)
	{
		if((GetTickCount()-tick) >= delay)
		{
			break;
		}
		else
		{
			Sleep(value);
		}
	}

	return 0;
}

bool ConvertProcessImageFileNameA(char* path,char* out_path,DWORD out_path_size) // OK
{
	char driver[512];
	char device[MAX_PATH];
	char search[3] = " :";

	if(GetLogicalDriveStrings((sizeof(driver)-1),driver) != 0)
	{
		char* fetch = driver;

		do
		{
			(*search) = (*fetch);

			if(QueryDosDevice(search,device,MAX_PATH) != 0)
			{
				std::string str = path;

				size_t index = str.find(device,0);

				if(index != std::string::npos)
				{
					str.replace(index,(std::string(device).length()+1),fetch);

					strcpy_s(out_path,out_path_size,str.data());

					return 1;
				}
			}

			while((*fetch++) != 0);
		}
		while((*fetch) != 0);
	}

	return 0;
}

bool ConvertProcessImageFileNameW(wchar_t* path,wchar_t* out_path,DWORD out_path_size) // OK
{
	wchar_t driver[512];
	wchar_t device[MAX_PATH];
	wchar_t search[3] = L" :";

	if(GetLogicalDriveStringsW((sizeof(driver)-1),driver) != 0)
	{
		wchar_t* fetch = driver;

		do
		{
			(*search) = (*fetch);

			if(QueryDosDeviceW(search,device,MAX_PATH) != 0)
			{
				std::wstring str = path;

				size_t index = str.find(device,0);

				if(index != std::wstring::npos)
				{
					str.replace(index,(std::wstring(device).length()+1),fetch);

					wcscpy_s(out_path,out_path_size,str.data());

					return 1;
				}
			}

			while((*fetch++) != 0);
		}
		while((*fetch) != 0);
	}

	return 0;
}

char* ConvertModuleFileName(char* name) // OK
{
	static char buff[MAX_PATH] = {0};

	for(int n=strlen(name);n > 0;n--)
	{
		if(name[n] == '\\')
		{
			strcpy_s(buff,sizeof(buff),&name[(n+1)]);
			break;
		}
	}

	return buff;
}

wchar_t* ConvertModuleFileName(wchar_t* name) // OK
{
	static wchar_t buff[MAX_PATH] = {0};

	for(int n=wcslen(name);n > 0;n--)
	{
		if(name[n] == '\\')
		{
			wcscpy_s(buff,sizeof(buff),&name[(n+1)]);
			break;
		}
	}

	return buff;
}

void PacketDecryptData(BYTE* lpMsg,int size,BYTE key) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]+key)^0xA0;
	}
}

void PacketEncryptData(BYTE* lpMsg,int size,BYTE key) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]^0xA0)-key;
	}
}

bool FileExists(char* filename)
{
	FILE *FileToFind;

	fopen_s(&FileToFind,filename,"r");

	if(!FileToFind)
	{
		return 0;
	}
	else
	{
		fclose(FileToFind);
		return 1;
	}
}

bool FileExists(wchar_t* filename)
{
	FILE *FileToFind;

	_wfopen_s(&FileToFind,filename,L"r");

	if(!FileToFind)
	{
		return 0;
	}
	else
	{
		fclose(FileToFind);
		return 1;
	}
}

DWORD WINAPI SplashThread(CSplash* lpSplash) // OK
{
	lpSplash->ShowSplash();

	SetEvent(lpSplash->m_SplashEvent);

	MSG msg;

	while(GetMessage(&msg,0,0,0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}

void SplashScreen(CSplash* ClassInst, int SplashType, bool TextSwitch, char DisplayText[255], int CloseTime)
{
	gLog.Output(LOG_DEBUG,GetEncryptedString(42),SplashType,TextSwitch,DisplayText);

	int ResId;

	COLORREF TextColor;

	SplashInit.CloseSplash();
	SplashAlert.CloseSplash();
	SplashError.CloseSplash();

	switch(SplashType)
	{
		case 0:
			ResId = IDB_BITMAP1;
			TextColor = RGB(118,164,156);
			break;
		case 1:
			ResId = IDB_BITMAP2;
			TextColor = RGB(150,104,17);
			break;
		case 2:
			ResId = IDB_BITMAP3;
			TextColor = RGB(185,43,43);
			break;
	}

	if(TextSwitch)
		ClassInst->Start(ResId, hins, RGB(128, 128, 128), 1, DisplayText, TextColor);
	else
		ClassInst->Start(ResId, hins, RGB(128, 128, 128));

	ClassInst->m_SplashEvent = CreateEvent(0,0,0,0);

	CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)SplashThread,ClassInst,0,0);

	WaitForSingleObject(ClassInst->m_SplashEvent,INFINITE);

	CloseHandle(ClassInst->m_SplashEvent);

	if(CloseTime > 0)
	{
		Sleep(CloseTime);

		if(SplashType != 0)
		{
			ClassInst->CloseSplash();
			SafeExitProcess();
		}
	}
}

char* GetHardwareId() //OK
{
	char PhysicalDriveSerial[256];

	memset(PhysicalDriveSerial,0,sizeof(PhysicalDriveSerial));

	for(int n=0;n < 5;n++)
	{
		if(GetPhysicalDriveSerialNumber(n,PhysicalDriveSerial,sizeof(PhysicalDriveSerial)) != 0)
		{
			break;
		}
	}

	DWORD ComputerHardwareId1 = *(DWORD*)(&PhysicalDriveSerial[0x00]) ^ *(DWORD*)(&PhysicalDriveSerial[0x10]) ^ 0x3AD3B74A;

	DWORD ComputerHardwareId2 = *(DWORD*)(&PhysicalDriveSerial[0x04]) ^ *(DWORD*)(&PhysicalDriveSerial[0x14]) ^ 0x94FDC685;

	DWORD ComputerHardwareId3 = *(DWORD*)(&PhysicalDriveSerial[0x08]) ^ *(DWORD*)(&PhysicalDriveSerial[0x18]) ^ 0xF45BBF4C;

	DWORD ComputerHardwareId4 = *(DWORD*)(&PhysicalDriveSerial[0x0C]) ^ *(DWORD*)(&PhysicalDriveSerial[0x1C]) ^ 0x8941D8E7;

	static char HardwareId[36];

	wsprintf(HardwareId,"%08X-%08X-%08X-%08X",ComputerHardwareId1,ComputerHardwareId2,ComputerHardwareId3,ComputerHardwareId4);

	return HardwareId;
}

char* HardIdParse(char* Input, char Character) //OK
{
	for(DWORD i=0; i<=strlen(Input); i++)
	{
		if(Input[i] == Character)
		{
			for(DWORD n=i; n<=strlen(Input); n++)
			{
				Input[n] = Input[n+1];
			}
		}
	}
	return Input;
}

char* GetEncryptedString(int index) // OK
{
	static char buff[256];

	memset(buff,0,sizeof(buff));

	for(int n=0;n < sizeof(gProtectString[index]);n++)
	{
		buff[n] = (gProtectString[index][n]-0x1B)^0x0C;
	}

	return buff;
}

bool SetAdminPrivilege(char* PrivilegeName) // OK
{
	HANDLE TokenHandle;

	if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&TokenHandle) == 0)
	{
		return 0;
	}

	LUID luid;

	if(LookupPrivilegeValue(0,PrivilegeName,&luid) == 0)
	{
		return 0;
	}

	TOKEN_PRIVILEGES tp;

	memset(&tp,0,sizeof(tp));

	tp.PrivilegeCount = 1;

	tp.Privileges[0].Luid = luid;

	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if(AdjustTokenPrivileges(TokenHandle,0,&tp,sizeof(tp),0,0) == 0)
	{
		return 0;
	}

	return 1;
}
