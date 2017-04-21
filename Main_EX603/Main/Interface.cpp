#include "stdafx.h"
#include "Interface.h"
#include "TMemory.h"
#include "Protocol.h"
#include "Offset.h"
#include "User.h"
#include "Import.h"
#include "Defines.h"
#include "Camera.h"
#include "Fog.h"
#include "Other.h"
#include "Graphics.h"
#include "Glow.h"
#include "ChatExpanded.h"
#include "Reconnect.h"
#include "Config.h"

Interface	gInterface;
DWORD		CharacterInfoExtern_Buff;
char		CharacterInfoExtern_LevelBuff[80];
DWORD		AddSomeShine_Buff;
DWORD		AddSomeShine_Pointer;
bool		Checkbox = true;

Interface::Interface()
{
	ZeroMemory(this->Data, sizeof(this->Data));
}

Naked(AddSomeShine)
{
	_asm
	{
		mov eax, dword ptr ds:[ecx + 0x30]
		mov AddSomeShine_Buff, eax
	}
	
	if( AddSomeShine_Buff == 349 || AddSomeShine_Buff == 406 || AddSomeShine_Buff == 407 || AddSomeShine_Buff == 408 )
	{
		_asm
		{
			mov AddSomeShine_Buff, 0x005E4979
			jmp AddSomeShine_Buff
		}
	}
	else
	{
		_asm
		{
			mov AddSomeShine_Buff, 0x005E4A3C
			jmp AddSomeShine_Buff
		}
	}
}

void Interface::Load()
{
	this->BindObject(eSAMPLEBUTTON, 0x7AA4, 16, 15, 175, 1);
	this->BindObject(eCheck, 0x9991, 15, 15, -1, -1);
	this->BindObject(eUnCheck, 0x9992, 15, 15, -1, -1);
	this->BindObject(eTIME, 0x787E, 73, 20, 174, 0);

	this->BindObject(eCAMERA_MAIN, 0x787A, 54, 18, 174, 0);
	this->BindObject(eCAMERA_BUTTON1, 0x787B, 16, 12, 175.5, 1);
	this->BindObject(eCAMERA_BUTTON2, 0x787C, 16, 12, 192.5, 1);
	this->BindObject(eLOGO, 0x9989, 63.3, 50, 192.5, 1);
	this->BindObject(eSHOP_WC, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_WP, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_GP, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_B, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_S, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_C, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_OFF, 0x7C04, 36, 27, -1, -1);

	this->BindObject(eOFFPANEL_MAIN, 0x7A5A, 222, 120, -1, -1);
	this->BindObject(eOFFPANEL_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eOFFPANEL_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eOFFPANEL_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eOFFPANEL_YES, 0x7B12, 54, 30, -1, -1);
	this->BindObject(eOFFPANEL_CANE, 0x7B0C, 54, 30, -1, -1);

	this->BindObject(eUSERSPANEL_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(eUSERSPANEL_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eUSERSPANEL_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eUSERSPANEL_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eUSERSPANEL_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eUSERSPANEL_OPTION, 0x7B68, 10, 10, -1, -1);
	this->BindObject(eUSERSPANEL_LINE, 0x7B67, 154, 2, -1, -1);
	this->BindObject(eUSERSPANEL_BUTTON, 0x9994, 40, 19, -1, -1);
	this->BindObject(eUSERSPANEL_BUTTON1, 0x9994, 40, 19, -1, -1);
	this->BindObject(eUSERSPANEL_BUTTON2, 0x9994, 40, 19, -1, -1);
	this->BindObject(eUSERSPANEL_FOG, 0x9991, 15, 15, -1, -1);
	this->BindObject(eUSERSPANEL_CLOSE, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eUSERSPANEL_HPBAR, 0x9991, 15, 15, -1, -1);
	this->BindObject(eUSERSPANEL_RANKHIDE, 0x9991, 15, 15, -1, -1);
	this->BindObject(eUSERSPANEL_TRONGLOW, 0x9991, 15, 15, -1, -1);
	this->BindObject(eUSERSPANEL_CHAT, 0x9991, 15, 15, -1, -1);
	this->BindObject(eUSERSPANEL_MINIMAP, 0x9991, 15, 15, -1, -1);
	this->BindObject(eUSERSPANEL_CAMERA, 0x9991, 15, 15, -1, -1);


	//Minimap
	this->BindObject(ePLAYER_POINT, 0x7883, 3, 3, -1, -1);
	this->BindObject(eNULL_MAP, 0x7884, 128, 128, -1, -1);
	this->BindObject(eLORENCIA_MAP, 0x7885, 128, 128, -1, -1);
	this->BindObject(eDUNGEON_MAP, 0x7886, 128, 128, -1, -1);
	this->BindObject(eDEVIAS_MAP, 0x7887, 128, 128, -1, -1);
	this->BindObject(eNORIA_MAP, 0x7888, 128, 128, -1, -1);
	this->BindObject(eLOSTTOWER_MAP, 0x7889, 128, 128, -1, -1);
	this->BindObject(eATLANS_MAP, 0x788C, 128, 128, -1, -1);
	this->BindObject(eTarkan_MAP, 0x7890, 128, 128, -1, -1);
	this->BindObject(eElbeland_MAP, 0x7891, 128, 128, -1, -1);
	this->BindObject(eICARUS_MAP, 0x7892, 128, 128, -1, -1);
	this->BindObject(eLANDOFTRIALS_MAP, 0x7893, 128, 128, -1, -1);
	this->BindObject(eAIDA_MAP, 0x7894, 128, 128, -1, -1);
	this->BindObject(eCRYWOLF_MAP, 0x7895, 128, 128, -1, -1);
	this->BindObject(eKANTRU_MAP, 0x7896, 128, 128, -1, -1);
	this->BindObject(eKANTRU3_MAP, 0x7897, 128, 128, -1, -1);
	this->BindObject(eBARRACKS_MAP, 0x7898, 128, 128, -1, -1);
	this->BindObject(eCALMNESS_MAP, 0x7899, 128, 128, -1, -1);
	this->BindObject(eRAKLION_MAP, 0x7900, 128, 128, -1, -1);
	this->BindObject(eVULCANUS_MAP, 0x7901, 128, 128, -1, -1);
	this->BindObject(eKALRUTAN_MAP, 0x7902, 128, 128, -1, -1);
	this->BindObject(eKALRUTAN2_MAP, 0x7903, 128, 128, -1, -1);
	//
	this->Data[eTIME].OnShow = true;
	//this->showMiniMap = false;

	//SetOp((LPVOID)oAllowGUI_Call1, this->AllowGUI, ASM::CALL);
	//SetOp((LPVOID)oAllowGUI_Call2, this->AllowGUI, ASM::CALL);
	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);
	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadImages, ASM::CALL);
	SetOp((LPVOID)0x00633FFB, this->LoadModels, ASM::CALL);
}

void Interface::Work()
{
	gInterface.DrawTimeUI();
	gObjUser.Refresh();
	gCamera.Rotate();
	gCamera.Position();
	gInterface.DrawMiniMap();
	ReconnectMainProc();
	gInterface.DrawPSHOP();
	gInterface.DrawPSHOP_OFFMODE();
	gInterface.DrawUsersPanelWindow();
	gInterface.DrawCameraUI();
	pDrawInterface();
}

void Interface::LoadImages()
{
	pLoadImage("Custom\\Interface\\TimeBar.tga", 0x787E, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\CameraUI_BG.tga", 0x787A, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\CameraUI_Switch.tga", 0x787B, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\CameraUI_Reset.tga", 0x787C, 0x2601, 0x2900, 1, 0);
	// logo
	pLoadImage("Custom\\logo\\mwebgame.tga", 0x9989, 0x2601, 0x2900, 1, 0);
	// MiniMap
	pLoadImage("Custom\\Interface\\check.jpg", 0x9991, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\uncheck.jpg", 0x9992, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\button.tga", 0x9994, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\PlayerPoint.jpg", 0x7883, 0x2600, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\null.tga", 0x7884, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Lorencia.tga", 0x7885, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Dungeon.tga", 0x7886, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Devias.tga", 0x7887, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Noria.tga", 0x7888, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Losttower.tga", 0x7889, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Atlans.tga", 0x788C, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Tarkan.tga", 0x7890, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Elbeland.tga", 0x7891, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Icarus.tga", 0x7892, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\LandOfTrials.tga", 0x7893, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Aida.tga", 0x7894, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Crywolf.tga", 0x7895, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Kantru.tga", 0x7896, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Kantru3.tga", 0x7897, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Barracks.tga", 0x7898, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Calmness.tga", 0x7899, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Raklion.tga", 0x7900, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Vulcanus.tga", 0x7901, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Kalrutan.tga", 0x7902, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Kalrutan2.tga", 0x7903, 0x2601, 0x2900, 1, 0);
	// Danh Hieu
	pLoadImage("Custom\\Rank\\anhdungthienchien.tga", 0x9960, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\bantayvang.tga", 0x9961, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\binhmadainguyensoai.tga", 0x9962, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\chiengiapthanthanh.tga", 0x9963, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\chuyengiadaomo.tga", 0x9964, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\doccocaubai.tga", 0x9965, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\doitruongkybinh.tga", 0x9966, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\gianghohaohiep.tga", 0x9967, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\gianghoneso.tga", 0x9968, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\hoangthanhbachu.tga", 0x9969, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\toiactaytroi.tga", 0x9970, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\tiendechetnguoi.tga", 0x9971, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\nghiengnuocnghiengthanh.tga", 0x9972, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\phungvucuuthien.tga", 0x9973, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Rank\\suonglonghiepcot.tga", 0x9980, 0x2601, 0x2900, 1, 0);
		//Rank thuoc tinh
	pLoadImage("Custom\\element\\element_dark.tga", 0x9985, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\element\\element_fire.tga", 0x9984, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\element\\element_land.tga", 0x9986, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\element\\element_water.tga", 0x9987, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\element\\element_wind.tga", 0x9988, 0x2601, 0x2900, 1, 0);
	// ----
	pLoadSomeForm();
}

void Interface::LoadModels()
{
	pInitModelData2();
}


void Interface::BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[MonsterID].EventTick	= 0;
	this->Data[MonsterID].OnClick	= false;
	this->Data[MonsterID].OnShow	= false;
	this->Data[MonsterID].ModelID	= ModelID;
	this->Data[MonsterID].Width		= Width;
	this->Data[MonsterID].Height	= Height;
	this->Data[MonsterID].X			= X;
	this->Data[MonsterID].Y			= Y;
	this->Data[MonsterID].MaxX		= X + Width;
	this->Data[MonsterID].MaxY		= Y + Height;
	this->Data[MonsterID].Attribute	= 0;
}

void Interface::DrawSampleButton()
{
	float PosX = this->GetResizeX(eSAMPLEBUTTON);
	
	if( this->CheckWindow(ObjWindow::CashShop)
			|| this->CheckWindow(ObjWindow::FullMap)
			|| this->CheckWindow(ObjWindow::SkillTree)
			|| this->CheckWindow(MoveList) )
	{
		return;
	}
	
	this->DrawGUI(eSAMPLEBUTTON, PosX, 1);
	
	if( !IsWorkZone(eSAMPLEBUTTON) )
	{
		return;
	}
	
	this->DrawToolTip(PosX - 5, 31, "Button tooltip");
	
	if( this->Data[eSAMPLEBUTTON].OnClick )
	{
		this->DrawColoredGUI(eSAMPLEBUTTON, PosX, 1, pMakeColor(40, 20, 3, 130));
		return;
	}
	
	this->DrawColoredGUI(eSAMPLEBUTTON, PosX, 1, pMakeColor(255, 204, 20, 130));
}


void Interface::EventSampleButton(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eSAMPLEBUTTON].EventTick);
	
	if( this->CheckWindow(CashShop) || this->CheckWindow(FullMap)
			|| this->CheckWindow(SkillTree) || this->CheckWindow(MoveList)
			|| !IsWorkZone(eSAMPLEBUTTON) )
	{
		return;
	}
	
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eSAMPLEBUTTON].OnClick = true;
		return;
	}
	
	this->Data[eSAMPLEBUTTON].OnClick = false;
	
	if( Delay < 500 )
	{
		return;
	}
	
	this->Data[eSAMPLEBUTTON].EventTick = GetTickCount();
	
	if( !this->Data[eRANK_MAIN].OnShow )
	{
		this->Data[eRANK_MAIN].OnShow = true;
	}
	else
	{
		this->Data[eRANK_MAIN].OnShow = false;
	}
}
void Interface::DrawCameraUI()
{
	float PosX = this->GetResizeX(eCAMERA_MAIN);
	// ----
	if (this->CheckWindow(CashShop)
		|| this->CheckWindow(SkillTree)
		|| this->CheckWindow(FullMap)
		|| this->CheckWindow(MoveList)
		|| (this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store))
		|| (this->CheckWindow(Inventory)
		&& this->CheckWindow(Warehouse)
		&& this->CheckWindow(ExpandWarehouse)))
	{
		return;
	}
	// ----
	this->DrawGUI(eCAMERA_MAIN, PosX, 0);
	this->DrawGUI(eCAMERA_BUTTON1, PosX + 0.5, 1);
	this->DrawGUI(eCAMERA_BUTTON2, PosX + 18.5, 1);
	this->DrawGUI(eLOGO, PosX + 370, 20);
	// ----
	if (gCamera.IsActive)
	{
		this->DrawColoredGUI(eCAMERA_BUTTON1, PosX + 0.5, 1, eShinyGreen);
	}
	// ----
	if (IsWorkZone(eCAMERA_BUTTON1))
	{
		if (gCamera.IsActive)
		{
			this->DrawToolTip(PosX + 0.5 - 5, 25, "Zoom: %02.f%%", gCamera.ZoomPercent);
		}
		else
		{
			this->DrawToolTip(PosX + 0.5 - 5, 25, "3D Camera [On|Off]");
		}
		// ----
		if (this->Data[eCAMERA_BUTTON1].OnClick)
		{
			this->DrawColoredGUI(eCAMERA_BUTTON1, PosX + 0.5, 1, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		this->DrawColoredGUI(eCAMERA_BUTTON1, PosX + 0.5, 1, pMakeColor(255, 204, 20, 200));
	}
	else if (IsWorkZone(eCAMERA_BUTTON2))
	{
		this->DrawToolTip(PosX + 18.5 - 5, 25, "3D Camera [Reset]");
		// ----
		if (this->Data[eCAMERA_BUTTON2].OnClick)
		{
			this->DrawColoredGUI(eCAMERA_BUTTON2, PosX + 18.5, 1, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		this->DrawColoredGUI(eCAMERA_BUTTON2, PosX + 18.5, 1, pMakeColor(255, 204, 20, 200));
	}
}
// ----------------------------------------------------------------------------------------------

void Interface::EventCameraUI(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	// ----
	if (this->CheckWindow(CashShop)
		|| this->CheckWindow(SkillTree)
		|| this->CheckWindow(FullMap)
		|| this->CheckWindow(MoveList)
		|| (this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store))
		|| (this->CheckWindow(Inventory)
		&& this->CheckWindow(Warehouse)
		&& this->CheckWindow(ExpandWarehouse)))
	{
		return;
	}
	// ----
	if (IsWorkZone(eCAMERA_BUTTON1))
	{
		DWORD Delay = (CurrentTick - this->Data[eCAMERA_BUTTON1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCAMERA_BUTTON1].OnClick = true;
			return;
		}
		// ----
		this->Data[eCAMERA_BUTTON1].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCAMERA_BUTTON1].EventTick = GetTickCount();
		// ----
		gCamera.Switch();
	}
	else if (IsWorkZone(eCAMERA_BUTTON2))
	{
		DWORD Delay = (CurrentTick - this->Data[eCAMERA_BUTTON2].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCAMERA_BUTTON2].OnClick = true;
			return;
		}
		// ----
		this->Data[eCAMERA_BUTTON2].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCAMERA_BUTTON2].EventTick = GetTickCount();
		// ----
		gCamera.Init();
	}
}
// ----------------------------------------------------------------------------------------------


bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}
int Interface::CloseWindow(int WindowID)
{
	return pCloseWindow(pWindowThis(), WindowID);
}
int Interface::OpenWindow(int WindowID)
{
	return pOpenWindow(pWindowThis(), WindowID);
}

void Interface::DrawTimeUI()
{
	if (!this->Data[eTIME].OnShow)
	{
		return;
	}
	// ----
	if (this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree)
		|| this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::ChatWindow))
	{
		return;
	}
	// ----
	this->DrawGUI(eTIME, 0.0f, 412.0f);
	// -----
	time_t TimeLocal;
	struct tm * LocalT;
	time(&TimeLocal);
	LocalT = localtime(&TimeLocal);
	char LocalTime[30];
	sprintf(LocalTime, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);
	this->DrawFormat(eWhite, 25.0f, 418.0f, 100.0f, 1.0f, LocalTime);
}

/*
bool Interface::AllowGUI()
{
	if( gInterface.CheckResetWindow())
	{
		return false;
	}
	
	return pAllowGUI();
}
*/

void Interface::SetTextColor(BYTE Red, BYTE Green, BYTE Blue, BYTE Opacity)
{
	pSetTextColor(pTextThis(), Red, Green, Blue, Opacity);
}
void Interface::DrawText(int X, int Y, LPCTSTR Text)
{
	pDrawText(pTextThis(), X, Y, Text, 0, 0, (LPINT)1, 0);
}
int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	int LineCount = 0;
	
	char * Line = strtok(Buff, "\n");
	
	while( Line != NULL )
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
	
	return PosY;
}
void Interface::DrawFormatEx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	pDrawColorText(Buff, PosX, PosY, Width, 0, Color, 0, Align);
}
float Interface::DrawRepeatGUI(short MonsterID, float X, float Y, int Count)
{
	float StartY = Y;
	
	for( int i = 0; i < Count; i++ )
	{
		pDrawGUI(this->Data[MonsterID].ModelID, X, StartY,this->Data[MonsterID].Width, this->Data[MonsterID].Height);
		
		StartY += this->Data[MonsterID].Height;
	}
	
	return StartY;
}
void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}
void Interface::DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= X;
		this->Data[ObjectID].Y		= Y;
		this->Data[ObjectID].MaxX	= X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= Y + this->Data[ObjectID].Height;
	}

	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y,this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}
int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	return pDrawToolTip(X, Y, Buff);
}
int Interface::DrawToolTipEx(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	int LineCount = 0;
	
	char * Line = strtok(Buff, "\n");
	
	while( Line != NULL )
	{
		pDrawToolTip(X, Y, Line);
		Y += 10;
		Line = strtok(NULL, "\n");
	}
	
	return Y;
}
int Interface::DrawMessage(int Mode, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	return pDrawMessage(Buff, Mode);
}
bool Interface::IsWorkZone(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;

	if( ObjectID == eSAMPLEBUTTON )
	{
		PosX = this->GetResizeX(ObjectID);
		MaxX = PosX + this->Data[ObjectID].Width;
	}

	if( (gObjUser.m_CursorX < PosX || gObjUser.m_CursorX > MaxX) || (gObjUser.m_CursorY < this->Data[ObjectID].Y || gObjUser.m_CursorY > this->Data[ObjectID].MaxY) )
		return false;

	return true;
}
bool Interface::IsWorkZone(float X, float Y, float MaxX, float MaxY)
{
	if( (gObjUser.m_CursorX < X || gObjUser.m_CursorX > MaxX) || (gObjUser.m_CursorY < Y || gObjUser.m_CursorY > MaxY) )
		return false;
	
	return true;
}
float Interface::GetResizeX(short ObjectID)
{
	if( pWinWidth == 800 )
	{
		return this->Data[ObjectID].X + 16.0;
	}
	else if( pWinWidth != 1024 )
	{
		return this->Data[ObjectID].X - 16.0;
	}
	
	return this->Data[ObjectID].X;
}

float Interface::GetResizeY(short ObjectID)
{
	
	return this->Data[ObjectID].Y;
}

// ----------------------------------------------------------------------------------------------
bool Interface::MiniMapCheck()
{
	if (this->CheckWindow(Inventory) ||
		this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(Character) ||
		this->CheckWindow(CommandWindow) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(GensInfo) ||
		this->CheckWindow(Guild) ||
		this->CheckWindow(NPC_Dialog) ||
		this->CheckWindow(NPC_Julia) ||
		this->CheckWindow(NPC_Titus) ||
		this->CheckWindow(OtherStore) ||
		this->CheckWindow(Party) ||
		this->CheckWindow(PetInfo) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Store) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(FriendList) ||
		this->CheckWindow(FastMenu) ||
		this->CheckWindow(MuHelper) ||
		this->CheckWindow(Quest) ||
		this->CheckWindow(Warehouse))
		return true;
	return false;
}

bool Interface::CombinedChecks()
{
	if ((this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store)) ||
		(this->CheckWindow(Inventory)
		&& this->CheckWindow(Warehouse)
		&& this->CheckWindow(ExpandWarehouse)) ||
		(this->CheckWindow(Inventory)
		&& this->CheckWindow(Character)
		&& this->CheckWindow(Store)))
		return true;
	return false;
}

void Interface::DrawMiniMap()
{
	if (gInterface.showMiniMap)
	{
		float MainWidth = 138.0;
		float MainHeight = 265.0;
		float StartY = 264.0;
		float StartX = 512.0;
		// ----
		if (this->MiniMapCheck() || this->CombinedChecks())
		{
			return;
		}
		// ----
		switch (gObjUser.m_MapNumber)
		{
		case 0:    //Lorencia
		{
					   this->DrawGUI(eLORENCIA_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 1:    //Dungeon
		{
					   this->DrawGUI(eDUNGEON_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 2:    //Devias
		{
					   this->DrawGUI(eDEVIAS_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 3:    //Noria
		{
					   this->DrawGUI(eNORIA_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 4:    //LostTower
		{
					   this->DrawGUI(eLOSTTOWER_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 5:    //Exile (disabled)
		{
					   return;
		}
			break;
			// --
			// --
		case 7:    //Atlans
		{
					   this->DrawGUI(eATLANS_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 8:    //Tarkan
		{
					   this->DrawGUI(eTarkan_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 10:    //Icarus
		{
						this->DrawGUI(eICARUS_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 31:    //Land of Trials
		{
						this->DrawGUI(eLANDOFTRIALS_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 33:    //Aida
		{
						this->DrawGUI(eAIDA_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 34:    //Crywolf Fortress
		{
						this->DrawGUI(eCRYWOLF_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 37:    //Kantru
		{
						this->DrawGUI(eKANTRU_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 38:    //Kantru 3
		{
						this->DrawGUI(eKANTRU3_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 41:    //Barracks
		{
						this->DrawGUI(eBARRACKS_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 51:    //Elbeland
		{
						this->DrawGUI(eElbeland_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 56:    //Swamp of Calmness
		{
						this->DrawGUI(eCALMNESS_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 57:    //Raklion
		{
						this->DrawGUI(eRAKLION_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 63:    //Vulcanus
		{
						this->DrawGUI(eVULCANUS_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 80:    //Kalrutan
		{
						this->DrawGUI(eKALRUTAN_MAP, StartX, StartY + 30);
		}
			break;
			// --
		case 81:    //Kalrutan 2
		{
						this->DrawGUI(eKALRUTAN2_MAP, StartX, StartY + 30);
		}
			break;

			// --
		default: //Default
		{
					 this->DrawGUI(eNULL_MAP, StartX, StartY + 30);
		}
			break;
		}
		// ----
		this->DrawGUI(ePLAYER_POINT, (float)(StartX - 1 + gObjUser.lpViewPlayer->MapPosX / 2), (float)(294 - 1 + (255 - gObjUser.lpViewPlayer->MapPosY) / 2));
	}
}
// ----------------------------------------------------------------------------------------------
void Interface::DrawUsersPanelWindow()
{
	if( !this->Data[eUSERSPANEL_MAIN].OnShow )
	{
		return;
	}
	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	
	this->DrawGUI(eUSERSPANEL_MAIN, StartX, StartY + 2);
	this->DrawGUI(eUSERSPANEL_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eUSERSPANEL_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eUSERSPANEL_FOOTER, StartX, StartY);
	// ----
		if( IsWorkZone(eUSERSPANEL_CLOSE) )
		{
			DWORD Color = eGray100;
			
			if( this->Data[eUSERSPANEL_CLOSE].OnClick )
			{
				Color = eGray150;
			}
			
			this->DrawColoredGUI(eUSERSPANEL_CLOSE, this->Data[eUSERSPANEL_CLOSE].X, this->Data[eUSERSPANEL_CLOSE].Y, Color);
		}
	// ----
	this->DrawGUI(eUSERSPANEL_CLOSE, ButtonX, this->Data[eUSERSPANEL_FOOTER].Y + 10);
	this->DrawFormat(eWhite, StartX + 8, this->Data[eUSERSPANEL_FOOTER].Y + 20, 210, 3, "Close");
	this->DrawGUI(eUSERSPANEL_DIV, StartX, this->Data[eUSERSPANEL_FOOTER].Y - 10);
	// ----
	this->DrawGUI(eUnCheck, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 37);

	this->DrawGUI(eUSERSPANEL_OPTION, StartX + 35, this->Data[eUSERSPANEL_MAIN].Y + 38);
	this->DrawGUI(eUSERSPANEL_LINE, StartX + 30, this->Data[eUSERSPANEL_MAIN].Y + 55);

	this->DrawFormat(eWhite, StartX + 20, this->Data[eUSERSPANEL_MAIN].Y + 40, +125, 3, Config.msg);
	{
	if(lifebar)
		{
		}
	else
		{
			this->DrawGUI(eUSERSPANEL_HPBAR, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 37);
		}
		// ----
	}
	// ----
	    this->DrawGUI(eUSERSPANEL_RANKHIDE, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 62);
	    this->DrawGUI(eUSERSPANEL_OPTION, StartX + 35, this->Data[eUSERSPANEL_MAIN].Y + 63);
	    this->DrawGUI(eUSERSPANEL_LINE, StartX + 30, this->Data[eUSERSPANEL_MAIN].Y + 80);
		this->DrawFormat(eWhite, StartX + 20, this->Data[eUSERSPANEL_MAIN].Y + 65, +125, 3, Config.msg2);
	{
	if(rankbar)
		{
		}
	else
		{
			this->DrawGUI(eUnCheck, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 62);
		}
		// ----
	}

	// ----
	    this->DrawGUI(eUSERSPANEL_TRONGLOW, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 87);
	    this->DrawGUI(eUSERSPANEL_OPTION, StartX + 35, this->Data[eUSERSPANEL_MAIN].Y + 88);
	    this->DrawGUI(eUSERSPANEL_LINE, StartX + 30, this->Data[eUSERSPANEL_MAIN].Y + 105);
		this->DrawFormat(eWhite, StartX + 20, this->Data[eUSERSPANEL_MAIN].Y + 90, +135, 3, Config.msg3);
		{
	if(g_bEnabled)
		{
		}
	else
		{
			this->DrawGUI(eUnCheck, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 87);
		}
		// ----
	}
	// ----
		this->DrawGUI(eUSERSPANEL_FOG, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 112);
	    this->DrawGUI(eUSERSPANEL_OPTION, StartX + 35, this->Data[eUSERSPANEL_MAIN].Y + 113);
	    this->DrawGUI(eUSERSPANEL_LINE, StartX + 30, this->Data[eUSERSPANEL_MAIN].Y + 130);
		this->DrawFormat(eWhite, StartX + 20, this->Data[eUSERSPANEL_MAIN].Y + 115, +125, 3, Config.msg4);
		{
	if(gFog.EnableFog)
		{
		}
	else
		{
			this->DrawGUI(eUnCheck, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 112);
		}
		// ----
	}
	// ----
		this->DrawGUI(eUnCheck, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 137);
	    this->DrawGUI(eUSERSPANEL_OPTION, StartX + 35, this->Data[eUSERSPANEL_MAIN].Y + 138);
	    this->DrawGUI(eUSERSPANEL_LINE, StartX + 30, this->Data[eUSERSPANEL_MAIN].Y + 155);
		this->DrawFormat(eWhite, StartX + 20, this->Data[eUSERSPANEL_MAIN].Y + 140, +125, 3, Config.msg5);
		{
	if (!gChatExpanded.IsActive)
        {
		}
	else
		{
			this->DrawGUI(eUSERSPANEL_CHAT, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 137);
		}
		// ----
	}
		// ----
		this->DrawGUI(eUSERSPANEL_MINIMAP, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 164);
	    this->DrawGUI(eUSERSPANEL_OPTION, StartX + 35, this->Data[eUSERSPANEL_MAIN].Y + 165);
	    this->DrawGUI(eUSERSPANEL_LINE, StartX + 30, this->Data[eUSERSPANEL_MAIN].Y + 182);
		this->DrawFormat(eWhite, StartX + 20, this->Data[eUSERSPANEL_MAIN].Y + 167, +120, 3, Config.msg6);
		{
	if (showMiniMap)
        {
		}
	else
		{
			this->DrawGUI(eUnCheck, ButtonX + 100, this->Data[eUSERSPANEL_MAIN].Y + 164);
		}
		// ----
	}
		// ----

		

		

}
bool Interface::EventUsersPanelWindow_Main(DWORD Event)
{
	this->EventUsersPanelWindow_Close(Event);
	this->EventUsersPanelWindow_HPBAR(Event);
	this->EventUsersPanelWindow_RANKHIDE(Event);
	this->EventUsersPanelWindow_TRONGLOW(Event);
	this->EventUsersPanelWindow_FOG(Event);
	this->EventUsersPanelWindow_CHAT(Event);
	this->EventUsersPanelWindow_MINIMAP(Event);

	
	return true;
}
bool Interface::EventUsersPanelWindow_Close(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eUSERSPANEL_CLOSE].EventTick);
	// ----
	if( !this->Data[eUSERSPANEL_MAIN].OnShow || !IsWorkZone(eUSERSPANEL_CLOSE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eUSERSPANEL_CLOSE].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eUSERSPANEL_CLOSE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eUSERSPANEL_CLOSE].EventTick = GetTickCount();
	this->CloseUsersPanelWindow();
	// ----
	return false;
}
bool Interface::EventUsersPanelWindow_HPBAR(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eUSERSPANEL_HPBAR].EventTick);
	// ----
	if( !this->Data[eUSERSPANEL_MAIN].OnShow || !IsWorkZone(eUSERSPANEL_HPBAR) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eUSERSPANEL_HPBAR].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eUSERSPANEL_HPBAR].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eUSERSPANEL_HPBAR].EventTick = GetTickCount();
	if(lifebar)
	{
	lifebar = false;
	}
	else
	{
	lifebar = true;
	}
}
bool Interface::EventUsersPanelWindow_RANKHIDE(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eUSERSPANEL_RANKHIDE].EventTick);
	// ----
	if( !this->Data[eUSERSPANEL_MAIN].OnShow || !IsWorkZone(eUSERSPANEL_RANKHIDE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eUSERSPANEL_RANKHIDE].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eUSERSPANEL_RANKHIDE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eUSERSPANEL_RANKHIDE].EventTick = GetTickCount();
	if(rankbar)
	{
	rankbar = false;
	}
	else
	{
	rankbar = true;
	}
}
bool Interface::EventUsersPanelWindow_TRONGLOW(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eUSERSPANEL_TRONGLOW].EventTick);
	// ----
	if( !this->Data[eUSERSPANEL_MAIN].OnShow || !IsWorkZone(eUSERSPANEL_TRONGLOW) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eUSERSPANEL_TRONGLOW].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eUSERSPANEL_TRONGLOW].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eUSERSPANEL_TRONGLOW].EventTick = GetTickCount();
	if(g_bEnabled) //Effects
	{
		g_bEnabled = false;
	}
	else
	{
		g_bEnabled = true;
	}
}
bool Interface::EventUsersPanelWindow_FOG(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eUSERSPANEL_FOG].EventTick);
	// ----
	if( !this->Data[eUSERSPANEL_MAIN].OnShow || !IsWorkZone(eUSERSPANEL_FOG) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eUSERSPANEL_FOG].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eUSERSPANEL_FOG].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eUSERSPANEL_FOG].EventTick = GetTickCount();
	if(gFog.EnableFog) //Fog
	{
		gFog.EnableFog = false;
	}
    else
	{
		gFog.EnableFog = true;
	}
}
bool Interface::EventUsersPanelWindow_CHAT(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eUSERSPANEL_CHAT].EventTick);
	// ----
	if( !this->Data[eUSERSPANEL_MAIN].OnShow || !IsWorkZone(eUSERSPANEL_CHAT) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eUSERSPANEL_CHAT].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eUSERSPANEL_CHAT].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eUSERSPANEL_CHAT].EventTick = GetTickCount();
	gChatExpanded.Switch();
}
bool Interface::EventUsersPanelWindow_MINIMAP(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eUSERSPANEL_MINIMAP].EventTick);
	// ----
	if( !this->Data[eUSERSPANEL_MAIN].OnShow || !IsWorkZone(eUSERSPANEL_MINIMAP) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eUSERSPANEL_MINIMAP].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eUSERSPANEL_MINIMAP].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eUSERSPANEL_MINIMAP].EventTick = GetTickCount();
	if(showMiniMap) //Fog
	{
		gInterface.showMiniMap = false;
	}
    else
	{
		gInterface.showMiniMap = true;
	}
}

void Interface::DrawPSHOP()
{
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	if (this->CheckWindow(ObjWindow::Store))
	{
	this->DrawFormat(eRed, StartX + 35, StartY + 76, +125, 3, "Custom Store:");

	this->DrawGUI(eSHOP_WC, StartX + 70, StartY + 90);
	this->DrawFormat(eWhite, StartX + 80, StartY + 97, 100.0f, 1.0f, "WCoinC");


	this->DrawGUI(eSHOP_B, StartX + 70, StartY + 120);
	this->DrawFormat(eYellow, StartX + 85, StartY + 127, 100.0f, 1.0f, "Bless");

	this->DrawGUI(eSHOP_WP, StartX + 125, StartY + 90);
	this->DrawFormat(eWhite, StartX + 135, StartY + 97, 100.0f, 1.0f, "WCoinP");

	this->DrawGUI(eSHOP_S, StartX + 125, StartY + 120);
	this->DrawFormat(eYellow, StartX + 140, StartY + 127, 100.0f, 1.0f, "Soul");

	this->DrawGUI(eSHOP_GP, StartX + 180, StartY + 90);
	this->DrawFormat(eWhite, StartX + 187, StartY + 97, 100.0f, 1.0f, "GoblinPoint");

	this->DrawGUI(eSHOP_C, StartX + 180, StartY + 120);
	this->DrawFormat(eYellow, StartX + 195, StartY + 127, 100.0f, 1.0f, "Chaos");

	this->DrawGUI(eSHOP_OFF, StartX + 190, StartY + 291);
	if( IsWorkZone(eSHOP_OFF) )
	{
		this->DrawToolTip(StartX + 190, StartY + 275, "OFFSTORE System, click to active!");
	}
	}
	// ----
}
bool Interface::DrawPSHOP_Main(DWORD Event)
{
	this->DrawPSHOP_BLESS(Event);
	this->DrawPSHOP_SOUL(Event);
	this->DrawPSHOP_CHAOS(Event);
	this->DrawPSHOP_WCOINC(Event);
	this->DrawPSHOP_WCOINP(Event);
	this->DrawPSHOP_COINTP(Event);
	this->DrawPSHOP_OFFBUTTON(Event);
	return true;
}
bool Interface::DrawPSHOP_BLESS(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eSHOP_B].EventTick);
	// ----
	if( !this->CheckWindow(ObjWindow::Store) || !IsWorkZone(eSHOP_B) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eSHOP_B].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eSHOP_B].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eSHOP_B].EventTick = GetTickCount();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFF,0x01,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}
bool Interface::DrawPSHOP_SOUL(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eSHOP_S].EventTick);
	// ----
	if( !this->CheckWindow(ObjWindow::Store) || !IsWorkZone(eSHOP_S) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eSHOP_S].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eSHOP_S].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eSHOP_S].EventTick = GetTickCount();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFF,0x02,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}
bool Interface::DrawPSHOP_CHAOS(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eSHOP_C].EventTick);
	// ----
	if( !this->CheckWindow(ObjWindow::Store) || !IsWorkZone(eSHOP_C) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eSHOP_C].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eSHOP_C].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eSHOP_C].EventTick = GetTickCount();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFF,0x03,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}
bool Interface::DrawPSHOP_WCOINC(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eSHOP_WC].EventTick);
	// ----
	if( !this->CheckWindow(ObjWindow::Store) || !IsWorkZone(eSHOP_WC) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eSHOP_WC].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eSHOP_WC].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eSHOP_WC].EventTick = GetTickCount();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFF,0x04,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}
bool Interface::DrawPSHOP_WCOINP(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eSHOP_WP].EventTick);
	// ----
	if( !this->CheckWindow(ObjWindow::Store) || !IsWorkZone(eSHOP_WP) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eSHOP_WP].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eSHOP_WP].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eSHOP_WP].EventTick = GetTickCount();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFF,0x05,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}
bool Interface::DrawPSHOP_COINTP(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eSHOP_GP].EventTick);
	// ----
	if( !this->CheckWindow(ObjWindow::Store) || !IsWorkZone(eSHOP_GP) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eSHOP_GP].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eSHOP_GP].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eSHOP_GP].EventTick = GetTickCount();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFF,0x06,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.header.size);
}

bool Interface::DrawPSHOP_OFFBUTTON(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eSHOP_OFF].EventTick);
	// ----
	if( !this->CheckWindow(ObjWindow::Store) || !IsWorkZone(eSHOP_OFF) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eSHOP_OFF].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eSHOP_OFF].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eSHOP_OFF].EventTick = GetTickCount();
	gInterface.OpenOffWindow();
}

void Interface::DrawPSHOP_OFFMODE()
{
	if( !this->Data[eOFFPANEL_MAIN].OnShow )
	{
		return;
	}
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 80.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	this->DrawGUI(eOFFPANEL_MAIN, StartX, StartY + 2);
	this->DrawGUI(eOFFPANEL_TITLE, StartX, StartY);
	//StartY = this->DrawRepeatGUI(eOFFPANEL_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eOFFPANEL_FOOTER, StartX, StartY + 75);

	this->DrawFormat(eGold, StartX + 10, 90, 210, 3, "Offline Shop System");
	this->DrawFormat(eWhite, StartX + 10, 130, 210, 3, "Leave your Character in OFFSTORE mode?");
	this->DrawGUI(eOFFPANEL_YES, StartX + 30, StartY + 75);
	this->DrawGUI(eOFFPANEL_CANE, StartX + 140, StartY + 75);

}

bool Interface::DrawPSHOP_OFFMAIN(DWORD Event)
{
	this->DrawPSHOP_OFFYES(Event);
	this->DrawPSHOP_OFFCANE(Event);
	return true;
}

bool Interface::DrawPSHOP_OFFYES(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eOFFPANEL_YES].EventTick);
	// ----
	if( !this->Data[eOFFPANEL_MAIN].OnShow || !IsWorkZone(eOFFPANEL_YES) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eOFFPANEL_YES].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eOFFPANEL_YES].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eOFFPANEL_YES].EventTick = GetTickCount();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFF,0x07,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,pMsg.header.size);
	this->CloseOffWindow();
}
bool Interface::DrawPSHOP_OFFCANE(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eOFFPANEL_CANE].EventTick);
	// ----
	if( !this->Data[eOFFPANEL_MAIN].OnShow || !IsWorkZone(eOFFPANEL_CANE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eOFFPANEL_CANE].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eOFFPANEL_CANE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	// ----
	this->Data[eOFFPANEL_CANE].EventTick = GetTickCount();
	this->CloseOffWindow();
}