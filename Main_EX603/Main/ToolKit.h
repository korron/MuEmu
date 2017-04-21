#pragma once

#include "StdAfx.h"

class ToolKitEx
{
public:
	ToolKitEx();
	virtual ~ToolKitEx();

	bool FileExists(char * name);
	void SetNop(DWORD dwSrcOffset, int Size);
	void SetByteP(DWORD dwSrcOffset, BYTE bOpCode);
	void SetByteU(DWORD dwOffset, BYTE btValue);
	void WriteJmp(DWORD dwSrcOffset, DWORD dwDstOffset);
	void HookThis(DWORD dwDstOffset, DWORD dwSrcOffset);
	void HookOffset(DWORD my, DWORD tohook, BYTE type);
	void HookExactOffset(DWORD my, DWORD tohook, BYTE type);
	void Protect(DWORD dwSrcOffset, int Size, DWORD dwNewProtect);
	DWORD UnProtect(DWORD dwSrcOffset, int Size);

private:

protected:
};
extern ToolKitEx ToolKit;