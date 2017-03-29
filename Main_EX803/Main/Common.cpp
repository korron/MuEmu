#include "stdafx.h"
#include "Common.h"
#include "Offset.h"
#include "Util.h"

BYTE GensBattleMapCount = 0;
BYTE GensMoveIndexCount = 0;
BYTE GensBattleMap[120];
BYTE GensMoveIndex[120];

void InitCommon() // OK
{
	SetCompleteHook(0xE9,0x0043E1F8,&LoginTab);

	SetCompleteHook(0xE9,0x004E1385,&CheckTickCount);

	SetCompleteHook(0xFF,0x00643C5E,&CheckMasterLevel); // C1:16

	SetCompleteHook(0xFF,0x00643D1E,&CheckMasterLevel); // C1:16

	SetCompleteHook(0xFF,0x00653C6F,&CheckMasterLevel); // C1:48

	SetCompleteHook(0xFF,0x00643FE4,&CheckMasterLevel); // C1:9C

	SetCompleteHook(0xFF,0x006440A4,&CheckMasterLevel); // C1:9C

	SetCompleteHook(0xFF,0x006367D7,&CheckMasterLevel); // C1:F3:03

	SetCompleteHook(0xFF,0x00636960,&CheckMasterLevel); // C1:F3:03

	SetCompleteHook(0xFF,0x0063765A,&CheckMasterLevel); // C1:F3:04

	SetCompleteHook(0xFF,0x006466EE,&CheckMasterLevel); // LevelUp

	SetCompleteHook(0xFF,0x0096FC3F,&CheckMasterLevel); // Print Level

	SetCompleteHook(0xFF,0x009948DC,&CheckMasterLevel); // Experience Bar

	SetCompleteHook(0xFF,0x00994971,&CheckMasterLevel); // Experience Bar

	SetCompleteHook(0xFF,0x004A6E0B,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x0059DFC7,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x0059F9D3,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x005A005C,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x005A50B9,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x005A54A1,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x005AA18C,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x00658E2F,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x00736BBC,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x00792B22,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x007C3A67,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x007C44DB,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x0097700D,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x00987D19,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x00998A4A,&CheckGensBattleMap);

	SetCompleteHook(0xE9,0x0099BD08,&CompareGensMoveIndex);
}

void InitMemoryProtection() // OK
{
	SetByte(0x006D0AB9,0xC3); // Character Disappear
	SetByte(0x006D0BB3,0xC3); // Character Disappear
	SetByte(0x006D0CCD,0xC3); // Character Disappear
	SetByte(0x006D0DC3,0xC3); // Character Disappear
	SetByte(0x006D0EE0,0xC3); // Character Disappear
	SetByte(0x006D101A,0xC3); // Character Disappear
	SetByte(0x006D138F,0xC3); // Character Disappear
	SetByte(0x006D14AC,0xC3); // Character Disappear
	SetByte(0x006D15EA,0xC3); // Character Disappear
	SetByte(0x006D172B,0xC3); // Character Disappear
	SetByte(0x006D188C,0xC3); // Character Disappear
	SetByte(0x006D1A19,0xC3); // Character Disappear
	SetByte(0x006D1BAE,0xC3); // Character Disappear
	SetByte(0x006D1D44,0xC3); // Character Disappear
	SetByte(0x006D211E,0xC3); // Character Disappear
	SetByte(0x006D225A,0xC3); // Character Disappear
	SetByte(0x006D2396,0xC3); // Character Disappear
	SetByte(0x006D24E0,0xC3); // Character Disappear
	SetByte(0x006D2638,0xC3); // Character Disappear
	SetByte(0x006D2711,0xC3); // Character Disappear
	SetByte(0x006D2869,0xC3); // Character Disappear

	MemorySet(0x004D6942,0x90,7); // Memory Trap
	MemorySet(0x006D292F,0x90,7); // Memory Trap
	MemorySet(0x0AD19BAF,0x90,7); // Memory Trap

	SetCompleteHook(0xFF,0x004E0A7C,0x0A2A86EF);
	SetCompleteHook(0xFF,0x004DE068,0x0A2A86EF);
	SetCompleteHook(0xFF,0x004DE767,0x0A2A86EF);
	SetCompleteHook(0xFF,0x004DE479,0x0A61CF19);
	SetCompleteHook(0xFF,0x004DDBE2,0x0A61CF19);
	SetCompleteHook(0xFF,0x004E05FB,0x0A61CF19);
	SetCompleteHook(0xFF,0x00638032,0x0A2A2C77);
	SetCompleteHook(0xFF,0x00644F3D,0x0A2A2C77);
	SetCompleteHook(0xFF,0x005A0DB9,0x0A5D51B8);
	SetCompleteHook(0xFF,0x005A0DE7,0x0A5D51B8);
	SetCompleteHook(0xFF,0x004E1293,0x09D67F23);
	SetCompleteHook(0xFF,0x00664B56,0x0A2DE6EF);
	SetCompleteHook(0xFF,0x004E0600,0x0A273D1E);
	SetCompleteHook(0xFF,0x008FC0B0,0x0ACBDA84);
	SetCompleteHook(0xFF,0x004E12A7,0x0A571AD3);
	SetCompleteHook(0xFF,0x00664B48,0x09E57A4B);
	SetCompleteHook(0xFF,0x0066672E,0x09CFBA90);
	SetCompleteHook(0xFF,0x00664975,0x0A714401);
	SetCompleteHook(0xFF,0x0066495B,0x0ACBCE0D);
	SetCompleteHook(0xFF,0x004E03F0,0x0A713AF4);
	SetCompleteHook(0xFF,0x006658C5,0x0A443DF0);
	SetCompleteHook(0xFF,0x006660B8,0x0ADD3732);
	SetCompleteHook(0xFF,0x00664E28,0x0A789228);
	SetCompleteHook(0xFF,0x0098226C,0x09D6996B);
	SetCompleteHook(0xFF,0x006646BF,0x0A48D5E5);
	SetCompleteHook(0xFF,0x008FC088,0x0A78A8D5);
	SetCompleteHook(0xFF,0x00666E34,0x0A6DDF0D);
	SetCompleteHook(0xFF,0x006668EB,0x0A732638);
	SetCompleteHook(0xFF,0x00665A31,0x0A064795);
	SetCompleteHook(0xFF,0x00665A4D,0x09D5429D);
	SetCompleteHook(0xFF,0x00665A3F,0x0AE589A9);
	SetCompleteHook(0xFF,0x008FC0E2,0x0A4DB895);
	SetCompleteHook(0xFF,0x008FC0C9,0x0A81D205);
	SetCompleteHook(0xFF,0x008FC0FB,0x0A99CCDC);
	SetCompleteHook(0xFF,0x0066493C,0x0AD4461B);
	SetCompleteHook(0xFF,0x0066494A,0x0A391923);
	SetCompleteHook(0xFF,0x006658D0,0x0A278CD5);
	SetCompleteHook(0xFF,0x00666E0A,0x0ADD670D);
	SetCompleteHook(0xFF,0x00666E26,0x0A29B623);
	SetCompleteHook(0xFF,0x006665B2,0x09E5091D);
	SetCompleteHook(0xFF,0x00666610,0x0A6E491C);
	SetCompleteHook(0xFF,0x006666BD,0x09E22B98);
	SetCompleteHook(0xFF,0x00665639,0x0AE5881C);
	SetCompleteHook(0xFF,0x0066656D,0x0ABF83FB);
	SetCompleteHook(0xFF,0x006665C8,0x0A425DAA);
	SetCompleteHook(0xFF,0x006664E1,0x0ADD76E0);
	SetCompleteHook(0xFF,0x00666AE9,0x0A7368DF);
	SetCompleteHook(0xFF,0x00666B15,0x0A6E56BA);
	SetCompleteHook(0xFF,0x00666B0A,0x0AA1C555);
	SetCompleteHook(0xFF,0x00666AF4,0x0ABCFA67);
	SetCompleteHook(0xFF,0x006668A9,0x09D738A3);
	SetCompleteHook(0xFF,0x006668B4,0x0AB847B3);
	SetCompleteHook(0xFF,0x006668D5,0x09D4AEF5);
	SetCompleteHook(0xFF,0x006668E0,0x0A78C9D2);
	SetCompleteHook(0xFF,0x006668BF,0x0AA1A247);
	SetCompleteHook(0xFF,0x006668CA,0x0ABC703A);
	SetCompleteHook(0xFF,0x006664D3,0x0A2ED520);
	SetCompleteHook(0xFF,0x00666602,0x0A986173);
	SetCompleteHook(0xFF,0x006664FD,0x0A1C8C3E);
	SetCompleteHook(0xFF,0x00666519,0x09E43F3B);
	SetCompleteHook(0xFF,0x006666C8,0x09E24FF3);
	SetCompleteHook(0xFF,0x0066657B,0x0A6DB4F0);
	SetCompleteHook(0xFF,0x0066662C,0x0A4302F3);
	SetCompleteHook(0xFF,0x006665D3,0x09D64540);
	SetCompleteHook(0xFF,0x006665E9,0x0ACBD4E0);
	SetCompleteHook(0xFF,0x006665A7,0x0A570A4E);
	SetCompleteHook(0xFF,0x0066659C,0x0A61B78E);
	SetCompleteHook(0xFF,0x006665BD,0x0AEABAC4);
	SetCompleteHook(0xFF,0x0066650B,0x0A425197);
	SetCompleteHook(0xFF,0x0066655F,0x0AB86794);
	SetCompleteHook(0xFF,0x0066661E,0x09CF818C);
	SetCompleteHook(0xFF,0x006664EF,0x0A56E08B);
	SetCompleteHook(0xFF,0x006667AF,0x0A2A2B15);
}

BOOL CheckGensBattleMap(int map) // OK
{
	for(int n=0;n < GensBattleMapCount;n++)
	{
		if(GensBattleMap[n] == map)
		{
			return 1;
		}
	}

	return 0;
}

BOOL CheckGensMoveIndex(int idx) // OK
{
	for(int n=0;n < GensMoveIndexCount;n++)
	{
		if(GensMoveIndex[n] == idx)
		{
			return 1;
		}
	}

	return 0;
}

__declspec(naked) void LoginTab() // OK
{
	static DWORD LoginTabAddress1 = 0x0043E211;

	__asm
	{
		Push 0
		Mov Eax,Dword Ptr Ss:[Ebp-0x38]
		Mov Ecx,Dword Ptr Ds:[Eax+0x350]
		Mov Edx,Dword Ptr Ss:[Ebp-0x38]
		Mov Eax,Dword Ptr Ds:[Edx+0x350]
		Mov Edx,Dword Ptr Ds:[Eax]
		Call Dword Ptr Ds:[Edx+0x30]
		Mov Eax,Dword Ptr Ss:[Ebp-0x38]
		Mov Ecx,Dword Ptr Ds:[Eax+0x354]
		Push Ecx
		Mov Edx,Dword Ptr Ss:[Ebp-0x38]
		Mov Ecx,Dword Ptr Ds:[Edx+0x350]
		Mov Eax,Dword Ptr Ss:[Ebp-0x38]
		Mov Edx,Dword Ptr Ds:[Eax+0x350]
		Mov Eax,Dword Ptr Ds:[Edx]
		Call Dword Ptr Ds:[Eax+0x58]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x38]
		Mov Edx,Dword Ptr Ds:[Ecx+0x350]
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x38]
		Mov Ecx,Dword Ptr Ds:[Eax+0x354]
		Mov Edx,Dword Ptr Ss:[Ebp-0x38]
		Mov Eax,Dword Ptr Ds:[Edx+0x354]
		Mov Edx,Dword Ptr Ds:[Eax]
		Call Dword Ptr Ds:[Edx+0x58]
		Jmp [LoginTabAddress1]
	}
}

__declspec(naked) void CheckTickCount() // OK
{
	static DWORD CheckTickCountAddress1 = 0x004E1391;

	_asm
	{
		NEXT:
		Push 1
		Call Dword Ptr Ds:[Sleep]
		Call Dword Ptr Ds:[GetTickCount]
		Sub Eax,Dword Ptr Ss:[Ebp-0x074]
		Cmp Eax,Dword Ptr Ss:[Ebp-0x18C]
		Jl NEXT
		Jmp [CheckTickCountAddress1]
	}
}

__declspec(naked) void CheckMasterLevel() // OK
{
	static DWORD CheckMasterLevelAddress1 = 0x0059182A;

	_asm
	{
		Push Ebp
		Mov Ebp,Esp
		Mov Eax,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Xor Ecx,Ecx
		Mov Cx,Word Ptr Ds:[Eax+0x0E]
		Cmp Ecx,0x190
		Je NEXT
		Xor Eax,Eax
		Jmp EXIT
		NEXT:
		Xor Edx,Edx
		Mov Dl,Byte Ptr Ss:[Ebp+0x08]
		Push Edx
		Call [CheckMasterLevelAddress1]
		Add Esp,0x04
		EXIT:
		Pop Ebp
		Retn
	}
}

__declspec(naked) void CompareGensMoveIndex() // OK
{
	static DWORD CheckGensMoveIndexAddress1 = 0x00525C24;
	static DWORD CheckGensMoveIndexAddress2 = 0x0099BD42;
	static DWORD CheckGensMoveIndexAddress3 = 0x0099BD30;

	__asm
	{
		Lea Ecx,Dword Ptr Ss:[Ebp-0x08]
		Call [CheckGensMoveIndexAddress1]
		Mov Ecx,Dword Ptr Ds:[Eax]
		Mov Edx,Dword Ptr Ds:[Ecx]
		Push Edx
		Call [CheckGensMoveIndex]
		Add Esp,0x04
		Test Eax,Eax
		Jnz EXIT
		Jmp [CheckGensMoveIndexAddress2]
		EXIT:
		Jmp [CheckGensMoveIndexAddress3]
	}
}
