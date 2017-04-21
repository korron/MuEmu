#include "StdAfx.h"
#include "ToolKit.h"

ToolKitEx::ToolKitEx() {};

ToolKitEx::~ToolKitEx() {};

ToolKitEx ToolKit;

void ToolKitEx::Protect(DWORD dwSrcOffset, int Size, DWORD dwNewProtect)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, dwNewProtect, &OldProtect);
};

DWORD ToolKitEx::UnProtect(DWORD dwSrcOffset, int Size)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, PAGE_EXECUTE_READWRITE, &OldProtect);
	return OldProtect;
};

void ToolKitEx::SetNop(DWORD dwSrcOffset, int Size)
{
	for (int i = 0; i < Size; i++)
		*(BYTE*)(dwSrcOffset + i) = 0x90;
};

void ToolKitEx::SetByteP(DWORD dwSrcOffset, BYTE bOpCode)
{
	__try
	{
		DWORD dwProtect = this->UnProtect(dwSrcOffset, 1);
		*(BYTE*)(dwSrcOffset) = bOpCode;
		this->Protect(dwSrcOffset, 1, dwProtect);
	}
	__finally {}
}

void ToolKitEx::WriteJmp(DWORD dwSrcOffset, DWORD dwDstOffset)
{
	if (dwSrcOffset)
	{
		__try
		{
			DWORD dwOffset = UnProtect(dwSrcOffset, 10);
			SetByteP(dwSrcOffset, 0xE9);
			HookThis(dwDstOffset, dwSrcOffset);
			Protect(dwSrcOffset, 10, dwOffset);
		}
		__finally {}
	}
};

void ToolKitEx::HookThis(DWORD dwDstOffset, DWORD dwSrcOffset)
{
	*(DWORD*)(dwSrcOffset + 1) = dwDstOffset - (dwSrcOffset + 5);
};

void ToolKitEx::HookExactOffset(DWORD my, DWORD tohook, BYTE type)
{
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook + 1) = my;
};

void ToolKitEx::HookOffset(DWORD my, DWORD tohook, BYTE type)
{
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook + 1) = my - (tohook + 5);
};

void ToolKitEx::SetByteU(DWORD dwOffset, BYTE btValue)
{
	*(BYTE*)(dwOffset) = btValue;
};

bool ToolKitEx::FileExists(char * name)
{
	if (CreateFile(name, 0, 0, 0, OPEN_EXISTING, 0, 0) == INVALID_HANDLE_VALUE)
		return false;
	return true;
};