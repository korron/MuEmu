#include "stdafx.h"
#include "resource.h"
#include "Main.h"
#include "..\\..\\Util\\CCRC32.H"
#include "Common.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "CustomWIngEffect.h"
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

	SetByte(0x0083FB1C,0xA0); // Accent
	SetByte(0x005E5200,0xEB); // Crack (mu.exe)
	SetByte(0x005E551A,0xEB); // Crack (GameGuard)
	SetByte(0x005E5563,0xE9); // Crack (GameGuard)
	SetByte(0x005E5564,0x8A); // Crack (GameGuard)
	SetByte(0x005E5565,0x00); // Crack (GameGuard)
	SetByte(0x005E5566,0x00); // Crack (GameGuard)
	SetByte(0x005E5567,0x00); // Crack (GameGuard)
	SetByte(0x0060112F,0xEB); // Crack (ResourceGuard)
	SetByte(0x005ECAEB,0xE9); // Website
	SetByte(0x005ECAEC,0xA7); // Website
	SetByte(0x005ECAED,0x00); // Website
	SetByte(0x0049E1C7,0xE9); // Age Image
	SetByte(0x0049E1C8,0x02); // Age Image
	SetByte(0x0049E1C9,0x01); // Age Image
	SetByte(0x0049E1CA,0x00); // Age Image
	SetByte(0x0049E1CB,0x00); // Age Image
	SetByte(0x0049E31E,0xC3); // Age Image
	SetByte(0x005008E6,0xEB); // Corrupted Filter.bmd
	SetByte(0x0048FC6A,0xEB); // Corrupted ItemSetType.bmd
	SetByte(0x0048FE9F,0xEB); // Corrupted ItemSetOption.bmd
	SetByte(0x004B832B,0xEB); // Ctrl Fix
	SetByte(0x005E516D,0xEB); // Multi Instance
	SetByte(0x00853FF4,(gProtect.m_MainInfo.ClientVersion[0]+1)); // Version
	SetByte(0x00853FF5,(gProtect.m_MainInfo.ClientVersion[2]+2)); // Version
	SetByte(0x00853FF6,(gProtect.m_MainInfo.ClientVersion[3]+3)); // Version
	SetByte(0x00853FF7,(gProtect.m_MainInfo.ClientVersion[5]+4)); // Version
	SetByte(0x00853FF8,(gProtect.m_MainInfo.ClientVersion[6]+5)); // Version
	SetWord(0x00853430,(gProtect.m_MainInfo.IpAddressPort)); // IpAddressPort
	SetDword(0x005E41CC,(DWORD)gProtect.m_MainInfo.WindowName);
	SetDword(0x005ECCB2,(DWORD)gProtect.m_MainInfo.ScreenShotPath);

	MemorySet(0x0060144B,0x90,10); // C1:F3:04

	MemoryCpy(0x0083FB5C,gProtect.m_MainInfo.IpAddress,sizeof(gProtect.m_MainInfo.IpAddress)); // IpAddress

	MemoryCpy(0x00853FFC,gProtect.m_MainInfo.ClientSerial,sizeof(gProtect.m_MainInfo.ClientSerial)); // ClientSerial

	SetCompleteHook(0xFF,0x0062B9A3,&ProtocolCoreEx);

	SetCompleteHook(0xE8,0x00575F55,&DrawNewHealthBar);

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

	InitHackCheck();

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
