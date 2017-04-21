#pragma once
#include <windows.h>
//
#define pInitGraphics		((void(__cdecl*)()) 0x00777590)//0071F6F1
#define oInitGraphics_Call		0x00776EAE//0071F0AC

#define pSelectDraw	((int(__cdecl*)(DWORD)) 0x0041FE10)//00420BD4)
#define oSelectDraw_Call		0x00405A32//00407436

#define pWinWidth				*(GLsizei*)0x0E61E58
#define pWinHeight				*(GLsizei*)0x0E61E5C

class Graphics
{
public:
	Graphics();
	// ----
	void		Load();
	static void	InitGraphics();
	static void	InterfaceDraw();
	static int  SelectDraw(int value);
}; extern Graphics gGraphics;