#include "StdAfx.h"
#include "Utils.h"

void HookBYTE(LPVOID Offset,BYTE value,bool bProtect)
{
	DWORD OldProtect;
	VirtualProtect(Offset,sizeof(BYTE),PAGE_EXECUTE_READWRITE,&OldProtect);
	*(BYTE*)(Offset) = value;
	
	if( bProtect )
	{
		VirtualProtect(Offset,1,PAGE_EXECUTE_READ,&OldProtect);
	}
}

void HookWORD(LPVOID Offset,WORD value,bool bProtect)
{
	DWORD OldProtect;
	VirtualProtect(Offset,sizeof(WORD),PAGE_EXECUTE_READWRITE,&OldProtect);
	*(WORD*)(Offset) = value;
	
	if( bProtect )
	{
		VirtualProtect(Offset,sizeof(WORD),PAGE_EXECUTE_READ,&OldProtect);
	}
}

void HookDWORD(LPVOID Offset,DWORD value,bool bProtect)
{
	DWORD OldProtect;
	VirtualProtect(Offset,sizeof(DWORD),PAGE_EXECUTE_READWRITE,&OldProtect);
	*(DWORD*)(Offset) = value;
	
	if( bProtect )
	{
		VirtualProtect(Offset,sizeof(DWORD),PAGE_EXECUTE_READ,&OldProtect);
	}
}

void HookSET(LPVOID Offset,BYTE value,int size,bool bProtect)
{
	DWORD OldProtect;
	VirtualProtect(Offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);
	memset(Offset,value,size);

	if( bProtect )
	{
		VirtualProtect(Offset,size,PAGE_EXECUTE_READ,&OldProtect);
	}
}

void HookBUFFER(LPVOID Offset,LPBYTE value,int size,bool bProtect)
{
	DWORD OldProtect;
	VirtualProtect(Offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);
	memcpy(Offset,value,size);

	if( bProtect )
	{
		VirtualProtect(Offset,size,PAGE_EXECUTE_READ,&OldProtect);
	}
}

void HookDWORD64(LPVOID Offset,DWORD64 value,bool bProtect)
{
	DWORD OldProtect;
	VirtualProtect(Offset,sizeof(DWORD64),PAGE_EXECUTE_READWRITE,&OldProtect);
	*(DWORD64*)(Offset) = value;

	if( bProtect )
	{
		VirtualProtect(Offset,sizeof(DWORD64),PAGE_EXECUTE_READ,&OldProtect);
	}
}

void HookNoAccess(LPVOID Offset,int size)
{
	DWORD OldProtect;
	VirtualProtect(Offset,size,PAGE_READONLY,&OldProtect);
}

//---------------------------------------------------------------------------

DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
	DWORD dwErrorCode   = 0;
	DWORD dwOldProtect  = 0;
	// ----
	int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);
	// ----
	if( iRes == 0 )
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	memcpy(lpAddress, lpBuf, uSize);
	// ----
	DWORD dwBytes   = 0;
	// ----
	iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);
	// ----
	if ( iRes == 0 )
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	return 0x00;
}
//---------------------------------------------------------------------------

DWORD ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize)
{
	DWORD dwErrorCode   = 0;
	DWORD dwOldProtect  = 0;
	// ----
	int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);
	// ----
	if ( iRes == 0 )
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	memcpy(lpBuf, lpAddress, uSize);
	// ----
	DWORD dwBytes   = 0;
	// ----
	iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);
	// ----
	if ( iRes == 0 )
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}
	// ----
	return 0x00;
}
//---------------------------------------------------------------------------

DWORD SetByte(const LPVOID dwOffset, const BYTE btValue)
{
	return WriteMemory(dwOffset, (LPVOID) & btValue, sizeof(BYTE));
}
//---------------------------------------------------------------------------

DWORD GetByte(const LPVOID dwOffset, BYTE & btValue)
{
	return ReadMemory(dwOffset, (LPVOID) btValue, sizeof(BYTE));
}
//---------------------------------------------------------------------------

DWORD SetWord(const LPVOID dwOffset, const WORD wValue)
{
	return WriteMemory(dwOffset, (LPVOID) & wValue, sizeof(WORD));
}
//---------------------------------------------------------------------------

DWORD GetWord(const LPVOID dwOffset, WORD & wValue)
{
	return ReadMemory(dwOffset, (LPVOID) wValue, sizeof(WORD));
}
//---------------------------------------------------------------------------

DWORD SetDword(const LPVOID dwOffset, const DWORD dwValue)
{
	return WriteMemory(dwOffset, (LPVOID) & dwValue, sizeof(DWORD));
}
//---------------------------------------------------------------------------

DWORD GetDword(const LPVOID dwOffset, DWORD & dwValue)
{
	return ReadMemory(dwOffset, (LPVOID) dwValue, sizeof(DWORD));
}
//---------------------------------------------------------------------------

DWORD SetFloat(const LPVOID dwOffset, float fValue)
{
	return WriteMemory(dwOffset, & fValue, sizeof(float));
}
//---------------------------------------------------------------------------

DWORD GetFloat(const LPVOID dwOffset, float & fValue)
{
	return ReadMemory(dwOffset, & fValue, sizeof(float));
}
//---------------------------------------------------------------------------

DWORD SetDouble(const LPVOID dwOffset, double dValue)
{
	return WriteMemory(dwOffset, & dValue, sizeof(double));
}
//---------------------------------------------------------------------------

DWORD SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[5];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ----
	btBuf[0]	= 0xE9;
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
	// ----
	btBuf[0]	= 0x0F;
	btBuf[1]	= 0x8F;
	memcpy( (LPVOID) & btBuf[2], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
	// ----
	btBuf[0]	= 0x0F;
	btBuf[1]	= 0x87;
	memcpy( (LPVOID) & btBuf[2], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ----
	btBuf[0]		= cmd;
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue)
{
	BYTE * lpBuf	= new BYTE[wCount];
	// ----
	memset(lpBuf, btValue, wCount);
	// ----
	return WriteMemory( dwAddress, (LPVOID) lpBuf, wCount);
}
//---------------------------------------------------------------------------

DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
{
	BYTE btBuf[5];
	// ----
	DWORD dwShift	= (ULONG_PTR)dwMyFuncOffset - ( (ULONG_PTR)dwJmpOffset + 5 );
	// ----
	btBuf[0] = cmd;
	// ----
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwJmpOffset, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset)
{
	*(DWORD*)(dwJmpOffset+1) = dwMyFuncOffset-(dwJmpOffset+5);
}
//---------------------------------------------------------------------------