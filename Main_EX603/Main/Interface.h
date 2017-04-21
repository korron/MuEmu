#pragma once


#include "Offset.h"
#include "Import.h"
#include "Defines.h"

#define INTERFACE_DEBUG		1


#define MAX_OBJECT			250
#define MAX_WIN_WIDTH		640
#define MAX_WIN_HEIGHT		480

enum ObjectID
{
	eSAMPLEBUTTON = 1,
	eRANK_MAIN,
	eRANK_TITLE,
	eRANK_FRAME,
	eRANK_FOOTER,
	eRANK_DIV,
	eRANK_BUTTON,
	eRANK_TAB1,
	eRANK_TAB2,
	eRANK_TAB3,
	eRANK_TAB4,
	//
	eCAMERA_MAIN,
	eCAMERA_BUTTON1,
	eCAMERA_BUTTON2,
	eLOGO,

	eOFFPANEL_MAIN,
	eOFFPANEL_TITLE,
	eOFFPANEL_FRAME,
	eOFFPANEL_FOOTER,
	eOFFPANEL_YES,
	eOFFPANEL_CANE,
	//
	eCheck,
	eUnCheck,
	//
	eUSERSPANEL_MAIN,
	eUSERSPANEL_TITLE,
	eUSERSPANEL_FRAME,
	eUSERSPANEL_FOOTER,
	eUSERSPANEL_DIV,
	eUSERSPANEL_OPTION,
	eUSERSPANEL_LINE,
	eUSERSPANEL_CLOSE,
	eUSERSPANEL_HPBAR,
	eUSERSPANEL_RANKHIDE,
	eUSERSPANEL_TRONGLOW,
	eUSERSPANEL_FOG,
	eUSERSPANEL_AUTOATACK,
	eUSERSPANEL_AUTOPARTY,
	eUSERSPANEL_BUTTON,
	eUSERSPANEL_BUTTON1,
	eUSERSPANEL_BUTTON2,
	eUSERSPANEL_CHAT,
	eUSERSPANEL_MINIMAP,
	eUSERSPANEL_CAMERA,
	//
	eTIME,
	//
	eSHOP_WC,
	eSHOP_B,
	eSHOP_WP,
	eSHOP_S,
	eSHOP_GP,
	eSHOP_C,
	eSHOP_OFF,
	eSHOP_OFFMAIN,
	eSHOP_OFFOK,
	eSHOP_OFFNO,
	//
	ePLAYER_POINT,
	eNULL_MAP,
	eLORENCIA_MAP,
	eDUNGEON_MAP,
	eDEVIAS_MAP,
	eNORIA_MAP,
	eLOSTTOWER_MAP,
	eATLANS_MAP,
	eTarkan_MAP,
	eElbeland_MAP,
	eICARUS_MAP,
	eLANDOFTRIALS_MAP,
	eAIDA_MAP,
	eCRYWOLF_MAP,
	eKANTRU_MAP,
	eKANTRU3_MAP,
	eBARRACKS_MAP,
	eCALMNESS_MAP,
	eRAKLION_MAP,
	eVULCANUS_MAP,
	eKALRUTAN_MAP,
	eKALRUTAN2_MAP,
	//
};


enum ColorMacro
{
	eShinyGreen		= Color4f(172, 255, 56, 255),
	eGold			= Color4f(255, 189, 25, 255),
	eWhite			= Color4f(255, 255, 255, 255),
	eWhite1			= Color4f(201, 201, 201, 201),
	eWhite180		= Color4f(255, 255, 255, 180),
	eOrange			= Color4f(255, 105, 25, 255),
	eGray100		= Color4f(50, 50, 50, 100),
	eGray150		= Color4f(50, 50, 50, 150),
	eBlowPink		= Color4f(220, 20, 60, 255),
	eRed			= Color4f(225, 0, 0, 255),
	eExcellent		= Color4f(0, 225, 139, 255),
	eAncient		= Color4f(1, 223, 119, 255),
	eSocket			= Color4f(153, 102, 204, 255),
	eBlue			= Color4f(36, 242, 252, 255),
	eBlue1			= Color4f(0, 0, 255, 255),
	eYellow			= Color4f(255, 255, 0, 255),
	eBrown			= Color4f(69, 39, 18, 255),
};


struct InterfaceObject
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	BYTE	Attribute;
};


class Interface
{
public:
	Interface();
	
	void		Load();
	static void TakeFPS();
	static void	Work();
	static void	LoadImages();
	static void LoadModels();
	void		BindObject(short ObjectID, DWORD ModelID, float Width, float Height, float X, float Y);
	
	void		DrawSampleButton();
	void		EventSampleButton(DWORD Event);
	void		DrawCameraUI();
	void		EventCameraUI(DWORD Event);
	void		DrawTimeUI();

	bool		MiniMapCheck();
	bool		CombinedChecks();
	void		DrawMiniMap();
	bool        showMiniMap;
	
	bool		CheckWindow(int WindowID);
	int			CloseWindow(int WindowID);
	int			OpenWindow(int WindowID);
	//static bool	AllowGUI();
	
	void		SetTextColor(BYTE Red, BYTE Greed, BYTE Blue, BYTE Opacity);
	void		DrawText(int X, int Y, LPCTSTR Text);
	int			DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void		DrawFormatEx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void		DrawGUI(short ObjectID, float X, float Y);
	float		DrawRepeatGUI(short ObjectID, float X, float Y, int Count);
	void		DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color);
	int			DrawToolTip(int X, int Y, LPCSTR Text, ...);
	int			DrawToolTipEx(int X, int Y, LPCSTR Text, ...);
	int			DrawMessage(int Mode, LPCSTR Text, ...);

	void		OpenOffWindow() { this->Data[eOFFPANEL_MAIN].OnShow = true; pSetCursorFocus = true; };
	void		CloseOffWindow() { this->Data[eOFFPANEL_MAIN].OnShow = false; pSetCursorFocus = false; };
	bool		CheckOffWindow() { return this->Data[eOFFPANEL_MAIN].OnShow; };
	void		DrawPSHOP();
	bool		DrawPSHOP_Main(DWORD Event);
	bool		DrawPSHOP_BLESS(DWORD Event);
	bool		DrawPSHOP_SOUL(DWORD Event);
	bool		DrawPSHOP_CHAOS(DWORD Event);
	bool		DrawPSHOP_WCOINC(DWORD Event);
	bool		DrawPSHOP_WCOINP(DWORD Event);
	bool		DrawPSHOP_COINTP(DWORD Event);
	bool		DrawPSHOP_OFFBUTTON(DWORD Event);
	void		DrawPSHOP_OFFMODE();
	bool		DrawPSHOP_OFFMAIN(DWORD Event);
	bool		DrawPSHOP_OFFYES(DWORD Event);
	bool		DrawPSHOP_OFFCANE(DWORD Event);
	//
	void		OpenUsersPanelWindow() { this->Data[eUSERSPANEL_MAIN].OnShow = true; pSetCursorFocus = true; };
	void		CloseUsersPanelWindow() { this->Data[eUSERSPANEL_MAIN].OnShow = false; pSetCursorFocus = false; };
	bool		CheckUsersPanelWindow() { return this->Data[eUSERSPANEL_MAIN].OnShow; };
	void		DrawUsersPanelWindow();
	bool		EventUsersPanelWindow_Main(DWORD Event);
	bool		EventUsersPanelWindow_Close(DWORD Event);
	bool		EventUsersPanelWindow_HPBAR(DWORD Event);
	bool		EventUsersPanelWindow_RANKHIDE(DWORD Event);
	bool		EventUsersPanelWindow_TRONGLOW(DWORD Event);
	bool		EventUsersPanelWindow_FOG(DWORD Event);
	bool		EventUsersPanelWindow_CHAT(DWORD Event);
	bool		EventUsersPanelWindow_MINIMAP(DWORD Event);

	
	bool		IsWorkZone(short ObjectID);
	bool		IsWorkZone(float X, float Y, float MaxX, float MaxY);
	float		GetResizeX(short ObjectID);
	float		GetResizeY(short ObjectID);


	InterfaceObject Data[MAX_OBJECT];
private:
	
};
extern Interface gInterface;
