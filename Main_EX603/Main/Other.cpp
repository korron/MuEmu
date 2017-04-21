#include "stdafx.h"
#include "Other.h"
#include "Fog.h"
#include "Offset.h"
#include "Import.h"
#include "Defines.h"
#include "Interface.h"
#include "TMemory.h"

DWORD		Test_Buff;
char		Test_LevelBuff[40];

int InGameEffects		= GetPrivateProfileIntA("Setting","FixGraphics",1,".\\Settings.ini");
int Anisotropy			= GetPrivateProfileIntA("Setting","Anisotropy",1,".\\Settings.ini");
int MaxAnisotropy		= GetPrivateProfileIntA("Setting","MaxAnisotropy",1,".\\Settings.ini");
int Linear				= GetPrivateProfileIntA("Setting","Linear",1,".\\Settings.ini");
// ----------------------------------------------------------------------------------------------
//OGL Function Prototypes
void (WINAPI *glEnable_original)(GLenum cap) = glEnable;
void (WINAPI *glClearColor_original)(GLclampf r,GLclampf g,GLclampf b,GLclampf a) = glClearColor;
int g_nMaxAnisotropy = MaxAnisotropy;
// ----------------------------------------------------------------------------------------------

void WINAPI glEnable_hook(GLenum mode)
{
	// ---
	if(InGameEffects != 0)
	{
		if(Anisotropy != 0)
		{
			glGetIntegerv(0x84FF,&g_nMaxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy-0.1);
		}
		if(Linear != 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	else
	{
		if(Anisotropy != 0)
		{
			glGetIntegerv(0x84FF,&g_nMaxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy-0.1);
		}
		if(Linear != 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	
	float rgba[4] = {gFog.gColor[pMapNumber].red,gFog.gColor[pMapNumber].green,gFog.gColor[pMapNumber].blue,1.0f}; gFog.toRGB(rgba);
					
		if (mode == GL_BLEND || mode == GL_TEXTURE_2D || mode == GL_DEPTH_TEST)
			glDisable(GL_FOG);

		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_DENSITY, 0.25f);
		glFogfv(GL_FOG_COLOR, rgba);
		if(pMapNumber==74)
		{
			glFogf(GL_FOG_START, 4050);
			glFogf(GL_FOG_END, 4850);
		}
		else
		{
			glFogf(GL_FOG_START, 1650.0f);
			glFogf(GL_FOG_END, 2100.0f);
		}
		glHint(GL_FOG_HINT, GL_NICEST);
			 
		glEnable_original(GL_FOG);

		if (mode == GL_BLEND || mode == GL_TEXTURE_2D || mode == GL_DEPTH_TEST) 
			glDisable(GL_FOG);  
	if(!gFog.EnableFog)
	{
		glDisable(GL_FOG);
	}
	glEnable_original(mode);
}

void WINAPI glClearColor_hook(GLclampf r,GLclampf g,GLclampf b,GLclampf a)
{
	if(gFog.EnableFog)
	{
	float rgba[4];
	rgba[0] = gFog.gColor[pMapNumber].red;
	rgba[1] = gFog.gColor[pMapNumber].green;
	rgba[2] = gFog.gColor[pMapNumber].blue;
	rgba[3] = 1.0;
	gFog.toRGB(rgba);		

	glClearColor_original(rgba[0],rgba[1],rgba[2],rgba[3]);
	}
}

void InitOGLHook()
{	
	//---- glEnable
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID &)glEnable_original,glEnable_hook);
	DetourTransactionCommit();

	//---- glClearColor
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID &)glClearColor_original,glClearColor_hook);
	DetourTransactionCommit();
}

Naked(Credit)
{
	 gInterface.DrawFormat(eOrange, (MAX_WIN_WIDTH / 2) - 74, 470, 150, 3, "(c) 2016. All right reserved.");
	 //gInterface.DrawFormat(eSocket, (MAX_WIN_WIDTH / 2) + 240, 470, 100, 3, "iKENNYLEE.NET");
	_asm
	{
		lea eax, Test_LevelBuff
		push eax
	//	// ----
	}
	_asm
	{
		mov Test_Buff, 0x004D7D1D
		jmp Test_Buff
	}
}

void LoadCustom()
{
	static char* LogName	= "Logs\\Error.log";
	static char* LogName2	= "Logs\\Error_%d.log";
	static char* DumpName	= "Logs\\Error.dmp";
	// ----
	SetDword((PVOID)(0x0096AA48+1), (DWORD)LogName);
	SetDword((PVOID)(0x0096AACF+1), (DWORD)LogName);
	SetDword((PVOID)(0x0096AB5B+1), (DWORD)LogName2);
	SetDword((PVOID)(0x004D1D0B+1), (DWORD)DumpName);
	SetByte((PVOID)(0x007AF175 + 1), 9);
	SetByte((PVOID)(0x007AF415 + 1), 9);
	SetByte((PVOID)(0x007AF795 + 1), 9);
	SetByte((PVOID)(0x007B0315 + 1), 9);
	//
	SetByte((PVOID)0x0062EBF8,0xEB);
	SetByte((PVOID)0x0062EBFE,0xEB);
	SetByte((PVOID)0x0062EE42,0xEB);
	SetByte((PVOID)0x0062EE48,0xEB);
	SetByte((PVOID)0x0062EEE5,0xEB);
	SetByte((PVOID)0x0062EEEB,0xEB);	
	//Increase terrains amount
	SetByte((PVOID)0x0062EBF7,0x69);
	SetByte((PVOID)0x0062EE41,0x69);
	SetByte((PVOID)0x0062EEE4,0x69);
	//
	SetRange((PVOID)0x004D7DAD, 0x0f, ASM::NOP);
	SetOp((LPVOID)0x004D7D13, (LPVOID)Credit, ASM::JMP);
}