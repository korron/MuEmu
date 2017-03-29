#include "stdafx.h"
#include "resource.h"
#include "Main.h"
#include "..\\..\\Util\\CCRC32.H"
#include "Common.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "CustomWingEffect.h"
#include "HackCheck.h"
#include "HealthBar.h"
#include "Item.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Resolution.h"
#include "Util.h"

HINSTANCE hins;

extern "C" _declspec(dllexport) void EntryProc() // OK
{
	if(gProtect.ReadMainFile("main.emu") == 0)
	{
		ExitProcess(0);
	}

	SetByte(0x00E61144,0xA0); // Accent
	SetByte(0x004D1E69,0xEB); // Crack (mu.exe)
	SetByte(0x004D228D,0xE9); // Crack (GameGuard)
	SetByte(0x004D228E,0x8B); // Crack (GameGuard)
	SetByte(0x004D228F,0x00); // Crack (GameGuard)
	SetByte(0x004D2290,0x00); // Crack (GameGuard)
	SetByte(0x004D2291,0x00); // Crack (GameGuard)
	SetByte(0x004D559C,0xEB); // Crack (ResourceGuard)
	SetByte(0x00633F7A,0xEB); // Crack (ResourceGuard)
	SetByte(0x00634403,0xEB); // Crack (ResourceGuard)
	SetByte(0x0063E6C4,0xEB); // Crack (ResourceGuard)
	SetByte(0x004D2246,0xEB); // Crack (ResourceGuard)
	SetByte(0x00501163,0xEB); // Crack (ResourceGuard)
	SetByte(0x0040AF0A,0x00); // Crack (ResourceGuard)
	SetByte(0x0040B4BC,0x50); // Login Screen
	SetByte(0x0040B4C5,0x50); // Login Screen
	SetByte(0x0040B4CF,0x18); // Login Screen
	SetByte(0x0040AF0A,0x00); // Login Screen
	SetByte(0x0040AFD5,0xEB); // Login Screen
	SetByte(0x00777FD6,0x70); // Item Text Limit
	SetByte(0x00777FD7,0x17); // Item Text Limit
	SetByte(0x004EBEC7,0x3C); // Item Text Limit
	SetByte(0x005C4004,0x3C); // Item Text Limit
	SetByte(0x007E40BB,0x3C); // Item Text Limit
	SetByte(0x0081B546,0x3C); // Item Text Limit
	SetByte(0x0081B58D,0x3C); // Item Text Limit
	SetByte(0x0086E284,0x3C); // Item Text Limit
	SetByte(0x0086E44C,0x3C); // Item Text Limit
	SetByte(0x0086E573,0x3C); // Item Text Limit
	SetByte(0x0086F8FC,0x3C); // Item Text Limit
	SetByte(0x007DA373,0xB7); // Item Type Limit
	SetByte(0x007E1C44,0xB7); // Item Type Limit
	SetByte(0x0052100D,0xEB); // Ctrl Fix
	SetByte(0x009543C4,0x00); // Move Vulcanus
	SetByte(0x0064CBD1,((gProtect.m_MainInfo.HelperActiveAlert==0)?0xEB:0x75)); // Helper Message Box
	SetByte(0x0064CBD0,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
	SetByte(0x0095CEEF,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
	SetByte(0x0095CF14,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
	SetByte(0x00E61F68,(gProtect.m_MainInfo.ClientVersion[0]+1)); // Version
	SetByte(0x00E61F69,(gProtect.m_MainInfo.ClientVersion[2]+2)); // Version
	SetByte(0x00E61F6A,(gProtect.m_MainInfo.ClientVersion[3]+3)); // Version
	SetByte(0x00E61F6B,(gProtect.m_MainInfo.ClientVersion[5]+4)); // Version
	SetByte(0x00E61F6C,(gProtect.m_MainInfo.ClientVersion[6]+5)); // Version
	SetWord(0x00E609E4,(gProtect.m_MainInfo.IpAddressPort)); // IpAddressPort
	SetDword(0x004D9D3B,(DWORD)&FrameValue);
	SetDword(0x004DAC60,(DWORD)&FrameValue);
	SetDword(0x004D597B,(DWORD)&MainTickCount);
	SetDword(0x004DA289,(DWORD)&MainTickCount);
	SetDword(0x004DA297,(DWORD)&MainTickCount);
	SetDword(0x004DA3A2,(DWORD)&MainTickCount);
	SetDword(0x004DA3CE,(DWORD)&MainTickCount);
	SetDword(0x004DA3D9,(DWORD)&MainTickCount);
	SetDword(0x0063D326,(DWORD)&MainTickCount);
	SetDword(0x00642112,(DWORD)&MainTickCount);
	SetDword(0x004D0E09,(DWORD)gProtect.m_MainInfo.WindowName);
	SetDword(0x004D9F55,(DWORD)gProtect.m_MainInfo.ScreenShotPath);

	MemorySet(0x0063E908,0x90,20); // C1:F3:04

	MemoryCpy(0x00E611B2,gProtect.m_MainInfo.IpAddress,sizeof(gProtect.m_MainInfo.IpAddress)); // IpAddress

	MemoryCpy(0x00E61F70,gProtect.m_MainInfo.ClientSerial,sizeof(gProtect.m_MainInfo.ClientSerial)); // ClientSerial

	SetCompleteHook(0xFF,0x0065FD79,&ProtocolCoreEx);

	SetCompleteHook(0xE9,0x004DA280,&CheckTickCount1);

	SetCompleteHook(0xE9,0x004DA3A1,&CheckTickCount2);

	SetCompleteHook(0xE8,0x005B96E8,&DrawNewHealthBar);

	VirtualizeOffset(0x004D9D39,12);

	VirtualizeOffset(0x004D9D45,7);

	VirtualizeOffset(0x004D9EFC,15);

	VirtualizeOffset(0x004DAC5C,8);

	VirtualizeOffset(0x005451F7,5);

	VirtualizeOffset(0x00545230,8);

	VirtualizeOffset(0x005A52E9,8);

	LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN1),(DWORD)&NewAddressData1);

	LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN2),(DWORD)&NewAddressData2);

	LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN3),(DWORD)&NewAddressData3);

	gCustomMessage.LoadEng(gProtect.m_MainInfo.EngCustomMessageInfo);

	gCustomMessage.LoadPor(gProtect.m_MainInfo.PorCustomMessageInfo);

	gCustomMessage.LoadSpn(gProtect.m_MainInfo.SpnCustomMessageInfo);

	gCustomJewel.Load(gProtect.m_MainInfo.CustomJewelInfo);

	gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);

	gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);

	gCustomWingEffect.Load(gProtect.m_MainInfo.CustomWingEffectInfo);

	gPacketManager.LoadEncryptionKey("Data\\Enc1.dat");

	gPacketManager.LoadDecryptionKey("Data\\Dec2.dat");

	InitCommon();

	//InitHackCheck();

	InitItem();

	InitJewel();

	InitPrintPlayer();

	InitReconnect();

	InitResolution();

	InitWing();

	gProtect.CheckLauncher();

	gProtect.CheckInstance();

	gProtect.CheckClientFile();

	gProtect.CheckPluginFile();

	gProtect.CheckCameraFile();
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hins = (HINSTANCE)hModule;
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}
