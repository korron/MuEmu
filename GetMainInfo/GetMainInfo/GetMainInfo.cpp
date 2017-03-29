#include "stdafx.h"
#include "D:\MuDokumenty\x-team\pliki\SOURCE EDIT MUEMU\Util\CCRC32.H"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomWing.h"
#include "CustomWIngEffect.h"
#include "ThemidaSDK.h"

struct MAIN_FILE_INFO
{
	BYTE LauncherType; 
	char CustomerName[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[32];
	char ScreenShotPath[50];
	char ClientName[32];
	char PluginName[32];
	char CameraName[32];
	DWORD ClientCRC32;
	DWORD PluginCRC32;
	DWORD CameraCRC32;
	DWORD HelperActiveAlert;
	DWORD HelperActiveLevel;
	DWORD DWMaxAttackSpeed;
	DWORD DKMaxAttackSpeed;
	DWORD FEMaxAttackSpeed;
	DWORD MGMaxAttackSpeed;
	DWORD DLMaxAttackSpeed;
	DWORD SUMaxAttackSpeed;
	DWORD RFMaxAttackSpeed;
	DWORD ReconnectTime;
	CUSTOM_MESSAGE_INFO EngCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO PorCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO SpnCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_WING_EFFECT_INFO CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
};

int _tmain(int argc,_TCHAR* argv[]) // OK
{
	CLEAR_START

	ENCODE_START

	MAIN_FILE_INFO info;

	memset(&info,0,sizeof(info));

	info.LauncherType = GetPrivateProfileInt("MainInfo","LauncherType",0,".\\MainInfo.ini");

	info.IpAddressPort = GetPrivateProfileInt("MainInfo","IpAddressPort",44405,".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","CustomerName","",info.CustomerName,sizeof(info.CustomerName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","IpAddress","",info.IpAddress,sizeof(info.IpAddress),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientVersion","",info.ClientVersion,sizeof(info.ClientVersion),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientSerial","",info.ClientSerial,sizeof(info.ClientSerial),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","WindowName","",info.WindowName,sizeof(info.WindowName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ScreenShotPath","",info.ScreenShotPath,sizeof(info.ScreenShotPath),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","ClientName","",info.ClientName,sizeof(info.ClientName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","PluginName","",info.PluginName,sizeof(info.PluginName),".\\MainInfo.ini");

	GetPrivateProfileString("MainInfo","CameraName","",info.CameraName,sizeof(info.CameraName),".\\MainInfo.ini");

	info.HelperActiveAlert = GetPrivateProfileInt("HelperInfo","HelperActiveAlert",0,".\\MainInfo.ini");

	info.HelperActiveLevel = GetPrivateProfileInt("HelperInfo","HelperActiveLevel",80,".\\MainInfo.ini");

	info.DWMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DWMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.DKMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DKMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.FEMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","FEMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.MGMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","MGMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.DLMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","DLMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.SUMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","SUMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.RFMaxAttackSpeed = GetPrivateProfileInt("CharacterInfo","RFMaxAttackSpeed",65535,".\\MainInfo.ini");

	info.ReconnectTime = GetPrivateProfileInt("ReconnectInfo","ReconnectTime",0,".\\MainInfo.ini");

	gCustomMessage.Load("CustomMessage.txt");

	gCustomJewel.Load("CustomJewel.txt");

	gCustomWing.Load("CustomWing.txt");

	gCustomItem.Load("CustomItem.txt");

	gCustomWingEffect.Load("CustomWingEffect.txt");

	memcpy(info.EngCustomMessageInfo,gCustomMessage.m_EngCustomMessageInfo,sizeof(info.EngCustomMessageInfo));

	memcpy(info.PorCustomMessageInfo,gCustomMessage.m_PorCustomMessageInfo,sizeof(info.PorCustomMessageInfo));

	memcpy(info.SpnCustomMessageInfo,gCustomMessage.m_SpnCustomMessageInfo,sizeof(info.SpnCustomMessageInfo));

	memcpy(info.CustomJewelInfo,gCustomJewel.m_CustomJewelInfo,sizeof(info.CustomJewelInfo));

	memcpy(info.CustomWingInfo,gCustomWing.m_CustomWingInfo,sizeof(info.CustomWingInfo));

	memcpy(info.CustomItemInfo,gCustomItem.m_CustomItemInfo,sizeof(info.CustomItemInfo));

	memcpy(info.CustomWingEffectInfo,gCustomWingEffect.m_CustomWingEffectInfo,sizeof(info.CustomWingEffectInfo));

	CCRC32 CRC32;

	if(CRC32.FileCRC(info.ClientName,&info.ClientCRC32,1024) == 0)
	{
		info.ClientCRC32 = 0;
	}

	if(CRC32.FileCRC(info.PluginName,&info.PluginCRC32,1024) == 0)
	{
		info.PluginCRC32 = 0;
	}

	if(CRC32.FileCRC(info.CameraName,&info.CameraCRC32,1024) == 0)
	{
		info.CameraCRC32 = 0;
	}

	for(int n=0;n < sizeof(MAIN_FILE_INFO);n++)
	{
		((BYTE*)&info)[n] ^= (BYTE)(0xCA^LOBYTE(n));
		((BYTE*)&info)[n] -= (BYTE)(0x95^HIBYTE(n));
	}

	HANDLE file = CreateFile("main.emu",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);

	if(file == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD OutSize = 0;

	if(WriteFile(file,&info,sizeof(MAIN_FILE_INFO),&OutSize,0) == 0)
	{
		CloseHandle(file);
		return 0;
	}

	CloseHandle(file);

	ENCODE_END

	CLEAR_END

	return 0;
}
