#include "stdafx.h"
#include "resource.h"
#include "Main.h"
#include "..\\..\\Util\\CCRC32.H"
#include "Common.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomWing.h"
#include "CustomWingEffect.h"
#include "HackCheck.h"
#include "Item.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Resolution.h"
#include "Util.h"
//ZUMBA
#include "Zumba\\Stack.h"
#include "Zumba\\ProtectionWarn.h"

DWORD state;
HINSTANCE hins;
KERNELGETSTARTUPINFO HookGetStartupInfo;

static const char* LogPath1 = "Logs\\stack_%s.txt";
static const char* LogPath2 = "Logs\\crash_%04d%02d%02d_%02d%02d.dmp";
static const char* LogPath3 = "Logs\\stack_%04d%02d%02d_%02d%02d.txt";
static const char* LogPath4 = "Logs\\CrashLog.txt";
static const char* LogPath5 = "Logs\\CrashLog_%d.txt";
static const char* LogPath6 = "Logs\\Error.log";
static const char* LogPath7 = "Logs\\Error_%d.log";

void EntryProc() // OK
{
	if(gProtect.ReadMainFile("main.emu") == 0)
	{
		ExitProcess(0);
		return;
	}

	SetByte(0x004D9556,0xE9); // Crack (GameGuard)
	SetByte(0x004D9557,0x8B); // Crack (GameGuard)
	SetByte(0x004D9558,0x00); // Crack (GameGuard)
	SetByte(0x004D9559,0x00); // Crack (GameGuard)
	SetByte(0x004D955A,0x00); // Crack (GameGuard)
	SetByte(0x004D9176,0xEB); // Crack (ResourceGuard)
	SetByte(0x004D9513,0x75); // Crack (ResourceGuard)
	SetByte(0x0043E510,0x50); // Login Screen
	SetByte(0x0043E519,0x50); // Login Screen
	SetByte(0x0043E521,0x18); // Login Screen
	SetByte(0x0043DFD9,0x00); // Login Screen
	SetByte(0x0043E098,0xEB); // Login Screen
	SetByte(0x0043EC4B,0xB0); // Web Check
	SetByte(0x0043EC4C,0x01); // Web Check
	SetByte(0x0043EC4D,0x90); // Web Check
	SetByte(0x009CDF5A,0x07); // Jewel of Life
	SetByte(0x0052AB21,0xEB); // Ctrl Fix
	SetByte(0x009D20DF,0x00); // Move Vulcanus
	SetByte(0x0118EF48,(gProtect.m_MainInfo.ClientVersion[0]+1)); // Version
	SetByte(0x0118EF49,(gProtect.m_MainInfo.ClientVersion[2]+2)); // Version
	SetByte(0x0118EF4A,(gProtect.m_MainInfo.ClientVersion[3]+3)); // Version
	SetByte(0x0118EF4B,(gProtect.m_MainInfo.ClientVersion[5]+4)); // Version
	SetByte(0x0118EF4C,(gProtect.m_MainInfo.ClientVersion[6]+5)); // Version
	SetWord(0x0118D31C,(gProtect.m_MainInfo.IpAddressPort)); // IpAddressPort
	SetDword(0x004D7FBF,(DWORD)gProtect.m_MainInfo.WindowName);
	SetDword(0x004E0F40,(DWORD)gProtect.m_MainInfo.ScreenShotPath);
	SetDword(0x009F3CDB,(DWORD)LogPath1);
	SetDword(0x009F3D25,(DWORD)LogPath2);
	SetDword(0x009F3D59,(DWORD)LogPath3);
	SetDword(0x009F6B95,(DWORD)LogPath4);
	SetDword(0x009F6BE2,(DWORD)LogPath5);
	SetDword(0x009F1668,(DWORD)LogPath6);
	SetDword(0x009F1758,(DWORD)LogPath7);

	MemorySet(0x006CCCAA,0x90,2); // Remove Packet Twist

	MemorySet(0x0A6FBFD9,0x90,3); // Remove Packet Twist

	MemorySet(0x0A702AFA,0x90,3); // Remove Packet Twist

	MemoryCpy(0x0118DB1A,gProtect.m_MainInfo.IpAddress,sizeof(gProtect.m_MainInfo.IpAddress)); // IpAddres

	MemoryCpy(0x0118EF50,gProtect.m_MainInfo.ClientSerial,sizeof(gProtect.m_MainInfo.ClientSerial)); // ClientSerial

	SetCompleteHook(0xFF,0x0065E94C,&ProtocolCoreEx);

	gCustomMessage.LoadEng(gProtect.m_MainInfo.EngCustomMessageInfo);

	gCustomMessage.LoadPor(gProtect.m_MainInfo.PorCustomMessageInfo);

	gCustomMessage.LoadSpn(gProtect.m_MainInfo.SpnCustomMessageInfo);

	gCustomJewel.Load(gProtect.m_MainInfo.CustomJewelInfo);

	gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);

	gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);

	gCustomWingEffect.Load(gProtect.m_MainInfo.CustomWingEffectInfo);

	InitCommon();

	InitHackCheck();

	InitItem();

	InitJewel();

	InitMemoryProtection();

	InitPrintPlayer();

	InitReconnect();

	InitResolution();

	InitWing();

	gProtect.CheckLauncher();

	gProtect.CheckInstance();

	gProtect.CheckClientFile();

	gProtect.CheckPluginFile();

	gProtect.CheckCameraFile();

	CreateDirectory("Logs",0);

	//ZUMBA
	StartStackLogging();
	ProtectionWarnStart();
}

void WINAPI MyGetStartupInfo(LPSTARTUPINFO lpStartupInfo) // OK
{
	if((state++) == 0)
	{
		EntryProc();
	}

	HookGetStartupInfo(lpStartupInfo);
}

void InitEntryProc() // OK
{
	state = 0;

	HookGetStartupInfo = (KERNELGETSTARTUPINFO)GetProcAddress(GetModuleHandle("Kernel32.dll"),"GetStartupInfoA");

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)HookGetStartupInfo,MyGetStartupInfo);
	DetourTransactionCommit();
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hins = (HINSTANCE)hModule;
			InitEntryProc();
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
