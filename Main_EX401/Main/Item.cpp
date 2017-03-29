#include "stdafx.h"
#include "Item.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "CustomWIngEffect.h"
#include "Offset.h"
#include "Util.h"

void InitItem() // OK
{
	SetCompleteHook(0xFF,0x005DBBF8,&ItemModelLoad);

	SetCompleteHook(0xFF,0x005DBC0D,&ItemTextureLoad);

	SetCompleteHook(0xFF,0x004F30A6,&GetItemColor);

	SetCompleteHook(0xFF,0x005BCCD1,&GetItemColor);

	SetCompleteHook(0xE9,0x005B2D62,&ItemSocketName1);

	SetCompleteHook(0xE9,0x004BD6F3,&ItemSocketName2);

	SetCompleteHook(0xE9,0x004BD70F,&ItemSocketName3);
}

void InitJewel() // OK
{
	SetCompleteHook(0xE9,0x0050597F,&JewelSetSalePrice);

	SetCompleteHook(0xE9,0x007148A7,&JewelCheckApplyItem);

	SetCompleteHook(0xE9,0x0058C745,&JewelCheckIndex1);

	SetCompleteHook(0xE9,0x005B2D6E,&JewelCheckIndex2);

	SetCompleteHook(0xE9,0x0060E1F5,&JewelCheckIndex3);

	SetCompleteHook(0xE9,0x0073649F,&JewelCheckIndex4);

	SetCompleteHook(0xE9,0x0058EB81,&JewelCheckModelIndex1);

	SetCompleteHook(0xE9,0x005BD867,&JewelCheckModelIndex2);
}

void InitWing() // OK
{
	SetCompleteHook(0xE9,0x004F7175,&WingMakePreviewCharSet);

	SetCompleteHook(0xE9,0x005BD6C7,&WingDisableLevelGlow);

	SetCompleteHook(0xE9,0x00589F7E,&WingSetIncDamage);

	SetCompleteHook(0xE9,0x00589FCD,&WingSetDecDamage);

	SetCompleteHook(0xE9,0x005033E0,&WingSetDefense);

	SetCompleteHook(0xE9,0x00503462,&WingSetExtraDefense);

	SetCompleteHook(0xE9,0x00504D2D,&WingSetOption);

	SetCompleteHook(0xE9,0x00503F5C,&WingSetNewOption);

	SetCompleteHook(0xE9,0x004FDED1,&WingSetModelType);

	SetCompleteHook(0xE9,0x004E4436,&WingSetEffect);

	SetCompleteHook(0xE9,0x004AEBB6,&WingCheckIndex1);

	SetCompleteHook(0xE9,0x004FD6F4,&WingCheckIndex2);

	SetCompleteHook(0xE9,0x00502C3A,&WingCheckIndex3);

	SetCompleteHook(0xE9,0x005036AF,&WingCheckIndex4);

	SetCompleteHook(0xE9,0x005041A1,&WingCheckIndex5);

	SetCompleteHook(0xE9,0x00505514,&WingCheckIndex6);

	SetCompleteHook(0xE9,0x0050658C,&WingCheckIndex7);

	SetCompleteHook(0xE9,0x005066F0,&WingCheckIndex8);

	SetCompleteHook(0xE9,0x005068CC,&WingCheckIndex9);

	SetCompleteHook(0xE9,0x00570793,&WingCheckIndex10);

	SetCompleteHook(0xE9,0x005843C2,&WingCheckIndex11);

	SetCompleteHook(0xE9,0x005853FA,&WingCheckIndex12);

	SetCompleteHook(0xE9,0x005862E7,&WingCheckIndex13);

	SetCompleteHook(0xE9,0x005871FB,&WingCheckIndex14);

	SetCompleteHook(0xE9,0x0058AAF5,&WingCheckIndex15);

	SetCompleteHook(0xE9,0x0058C7EE,&WingCheckIndex16);

	SetCompleteHook(0xE9,0x0058CB3C,&WingCheckIndex17);

	SetCompleteHook(0xE9,0x0059144F,&WingCheckIndex18);

	SetCompleteHook(0xE9,0x00591937,&WingCheckIndex19);

	SetCompleteHook(0xE9,0x006B6DE3,&WingCheckIndex20);

	SetCompleteHook(0xE9,0x0073122E,&WingCheckIndex21);

	SetCompleteHook(0xE9,0x00736550,&WingCheckIndex22);

	SetCompleteHook(0xE9,0x00752F01,&WingCheckIndex23);

	SetCompleteHook(0xE9,0x004E39BA,&WingCheckModelIndex1);

	SetCompleteHook(0xE9,0x00590101,&WingCheckModelIndex2);

	SetCompleteHook(0xE9,0x005C1D65,&WingCheckModelIndex3);
}

void ItemModelLoad() // OK
{
	((void(*)())0x005C7C75)();

	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		if(gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemModel((gCustomJewel.m_CustomJewelInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomJewel.m_CustomJewelInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemModel((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemModel((gCustomItem.m_CustomItemInfo[n].ItemIndex+ITEM_BASE_MODEL),((gCustomItem.m_CustomItemInfo[n].ItemIndex>=GET_ITEM(7,0)&&gCustomItem.m_CustomItemInfo[n].ItemIndex<GET_ITEM(12,0))?"Player\\":"Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName,-1);
		}
	}
}

void ItemTextureLoad() // OK
{
	((void(*)())0x005C94E2)();

	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		if(gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomJewel.m_CustomJewelInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomJewel.m_CustomJewelInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomItem.m_CustomItemInfo[n].ItemIndex+ITEM_BASE_MODEL),((gCustomItem.m_CustomItemInfo[n].ItemIndex>=GET_ITEM(7,0)&&gCustomItem.m_CustomItemInfo[n].ItemIndex<GET_ITEM(12,0))?"Player\\":"Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName,-1);
		}
	}
}

void LoadItemModel(int index,char* folder,char* name,int value) // OK
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,char*,int))0x005C5873)(index,path,name,value);
}

void LoadItemTexture(int index,char* folder,char* name,int value) // OK
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,int,int,int))0x005C51C0)(index,folder,0x2901,0x2600,0x01);
}

void GetItemColor(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(gCustomItem.GetCustomItemColor((a-ITEM_BASE_MODEL),(float*)d) == 0)
	{
		((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x005B3CCC)(a,b,c,d,e);
	}
}

BOOL CheckSocketItem(DWORD address,DWORD this_pointer) // OK
{
	for(int n=0;n < 5;n++)
	{
		if(*(BYTE*)(address+(0x42+n)) != 0xFF)
		{
			return 1;
		}
	}

	return ((BOOL(__thiscall*)(void*,WORD))0x004BD72A)((void*)this_pointer,(*(WORD*)(address+0x00)));
}

__declspec(naked) void ItemSocketName1() // OK
{
	static DWORD ItemSocketNameAddress1 = 0x005B2D68;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp-0x08]
		Mov Byte Ptr Ds:[Ecx+0x41],Al
		Push 0x05
		Mov Edx,Dword Ptr Ss:[Ebp+0x0C]
		Add Edx,0x07
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Add Eax,0x42
		Push Eax
		Call [MemoryCpy]
		Add Esp,0x0C
		Jmp [ItemSocketNameAddress1]
	}
}

__declspec(naked) void ItemSocketName2() // OK
{
	static DWORD ItemSocketNameAddress1 = 0x004BD702;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Push Ecx
		Call [CheckSocketItem]
		Add Esp,0x08
		Jmp [ItemSocketNameAddress1]
	}
}

__declspec(naked) void ItemSocketName3() // OK
{
	static DWORD ItemSocketNameAddress1 = 0x004BD724;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Sub Ecx,0x5E
		Push Ecx
		Call [CheckSocketItem]
		Add Esp,0x08
		Jmp [ItemSocketNameAddress1]
	}
}

__declspec(naked) void JewelSetSalePrice() // OK
{
	static DWORD JewelSetSalePriceAddress1 = 0x00506C42;
	static DWORD JewelSetSalePriceAddress2 = 0x00505985;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::GetCustomJewelSalePrice]
		Mov Dword Ptr Ss:[Ebp-0x08],Eax
		Mov Dword Ptr Ss:[Ebp-0x04],0x00
		Jmp [JewelSetSalePriceAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [JewelSetSalePriceAddress2]
	}
}

__declspec(naked) void JewelCheckApplyItem() // OK
{
	static DWORD JewelCheckApplyItemAddress1 = 0x007148B7;
	static DWORD JewelCheckApplyItemAddress2 = 0x007148B5;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp-0x70]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp-0x70]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Mov Eax,Dword Ptr Ss:[Ebp-0x94]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Push Edx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelApplyItem]
		Test Eax,Eax
		Je EXIT
		Mov Byte Ptr Ss:[Ebp-0x98],0x01
		Jmp [JewelCheckApplyItemAddress1]
		EXIT:
		Movzx Edx,Byte Ptr Ss:[Ebp-0x98]
		Test Edx,Edx
		Jmp [JewelCheckApplyItemAddress2]
	}
}

__declspec(naked) void JewelCheckIndex1() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x0058C7BE;
	static DWORD JewelCheckIndexAddress2 = 0x0058C74A;

	_asm
	{
		Movsx Edx,Dx
		Push Edx
		Push Edx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Pop Edx
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Pop Edx
		Cmp Edx,0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex2() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x005B2DA4;
	static DWORD JewelCheckIndexAddress2 = 0x005B2D75;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x04],0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex3() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x0060E25C;
	static DWORD JewelCheckIndexAddress2 = 0x0060E1FD;

	_asm
	{
		Pop Edi
		Pop Esi
		Pop Ebp
		Mov Edx,Eax
		Push Edx
		Push Edx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex4() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x007364EF;
	static DWORD JewelCheckIndexAddress2 = 0x007364A4;

	_asm
	{
		Mov Edx,Eax
		Push Edx
		Push Edx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckModelIndex1() // OK
{
	static DWORD JewelCheckModelIndexAddress1 = 0x00590512;
	static DWORD JewelCheckModelIndexAddress2 = 0x0058EB86;

	_asm
	{
		Mov Edx,Eax
		Mov Ecx,Edx
		Sub Ecx,ITEM_BASE_MODEL
		Push Edx
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [JewelCheckModelIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x1F40
		Jmp [JewelCheckModelIndexAddress2]
	}
}

__declspec(naked) void JewelCheckModelIndex2() // OK
{
	static DWORD JewelCheckModelIndexAddress1 = 0x005BDA5F;
	static DWORD JewelCheckModelIndexAddress2 = 0x005BD871;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x4CC]
		Sub Eax,ITEM_BASE_MODEL
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckModelIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x4CC],0x1F40
		Jmp [JewelCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingMakePreviewCharSet() // OK
{
	static DWORD WingMakePreviewCharSetAddress1 = 0x004F71DE;
	static DWORD WingMakePreviewCharSetAddress2 = 0x004F717D;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x10]
		Sar Edx,0x01
		And Edx,0x0F
		Test Edx,Edx
		Je EXIT
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Ecx,Byte Ptr Ds:[Eax+0x10]
		Sar Ecx,0x01
		And Ecx,0x0F
		Sub Ecx,0x01
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWing]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Eax,Byte Ptr Ds:[Edx+0x10]
		Sar Eax,0x01
		And Eax,0x0F
		Sub Eax,0x01
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingItem]
		Add Eax,ITEM_BASE_MODEL
		Mov Ecx,Dword Ptr Ss:[Ebp-0x08]
		Mov Word Ptr Ds:[Ecx+0x1C0],Ax
		Jmp [WingMakePreviewCharSetAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		And Eax,0xFF
		Jmp [WingMakePreviewCharSetAddress2]
	}
}

__declspec(naked) void WingDisableLevelGlow() // OK
{
	static DWORD WingDisableLevelGlowAddress1 = 0x005BDC42;
	static DWORD WingDisableLevelGlowAddress2 = 0x005BD6D0;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		Mov Dword Ptr Ss:[Ebp-0x4CC],Ecx
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Dword Ptr Ss:[Ebp-0x08],0x00
		Jmp [WingDisableLevelGlowAddress1]
		EXIT:
		Jmp [WingDisableLevelGlowAddress2]
	}
}

__declspec(naked) void WingSetIncDamage() // OK
{
	static DWORD WingSetIncDamageAddress1 = 0x00589F8D;
	static DWORD WingSetIncDamageAddress2 = 0x00589F83;

	_asm
	{
		Movsx Edx,Cx
		Push Edx
		Push Ebp
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Ebp
		Pop Edx
		Push Ebp
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingIncDamage]
		Mov Esi,Eax
		Jmp [WingSetIncDamageAddress1]
		EXIT:
		Pop Ebp
		Pop Ecx
		Cmp Ecx,0x182B
		Jmp [WingSetIncDamageAddress2]
	}
}

__declspec(naked) void WingSetDecDamage() // OK
{
	static DWORD WingSetDecDamageAddress1 = 0x00589FE1;
	static DWORD WingSetDecDamageAddress2 = 0x00589FD7;

	_asm
	{
		Mov Dword Ptr Ds:[0x07B553F4],Eax
		Movsx Edx,Word Ptr Ds:[Edi]
		Push Edx
		Push Ebp
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Ebp
		Pop Edx
		Push Ebp
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingDecDamage]
		Mov Eax,Eax
		Jmp [WingSetDecDamageAddress1]
		EXIT:
		Pop Ebp
		Pop Edx
		Cmp Word Ptr Ds:[Edi],0x1828
		Jmp [WingSetDecDamageAddress2]
	}
}

__declspec(naked) void WingSetDefense() // OK
{
	static DWORD WingSetDefenseAddress1 = 0x00503447;
	static DWORD WingSetDefenseAddress2 = 0x005033E6;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Mov Eax,Dword Ptr Ss:[Ebp-0x28]
		Push Eax
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingDefense]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Word Ptr Ds:[Ecx+0x0E]
		Add Edx,Eax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Eax+0x0E],Dx
		Jmp [WingSetDefenseAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingSetDefenseAddress2]
	}
}

__declspec(naked) void WingSetExtraDefense() // OK
{
	static DWORD WingSetExtraDefenseAddress1 = 0x005034DA;
	static DWORD WingSetExtraDefenseAddress2 = 0x00503468;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp-0x28]
		Cmp Edx,0x0A
		Jnz NEXT1
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x01
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT1:
		Mov Edx,Dword Ptr Ss:[Ebp-0x28]
		Cmp Edx,0x0B
		Jnz NEXT2
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x03
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT2:
		Mov Edx,Dword Ptr Ss:[Ebp-0x28]
		Cmp Edx,0x0C
		Jnz NEXT3
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x06
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT3:
		Mov Edx,Dword Ptr Ss:[Ebp-0x28]
		Cmp Edx,0x0D
		Jnz NEXT4
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x0A
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT4:
		Mov Edx,Dword Ptr Ss:[Ebp-0x28]
		Cmp Edx,0x0E
		Jnz NEXT5
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x0F
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT5:
		Mov Edx,Dword Ptr Ss:[Ebp-0x28]
		Cmp Edx,0x0F
		Jnz NEXT6
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x15
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		NEXT6:
		Jmp [WingSetExtraDefenseAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingSetExtraDefenseAddress2]
	}
}

__declspec(naked) void WingSetOption() // OK
{
	static DWORD WingSetOptionAddress1 = 0x00504DF4;
	static DWORD WingSetOptionAddress2 = 0x00504D33;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Sar Eax,0x04
		And Eax,0x01
		Je NEXT1
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push 1
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x10]
		Imul Eax,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr DS:[Edx+Ecx+0x2E],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 1
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Byte Ptr Ds:[Ecx+Edx+0x26],Al
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		Jmp [WingSetOptionAddress1]
		NEXT1:
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Sar Eax,0x05
		And Eax,0x01
		Je NEXT2
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push 2
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x10]
		Imul Eax,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr DS:[Edx+Ecx+0x2E],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 2
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Byte Ptr Ds:[Ecx+Edx+0x26],Al
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		Jmp [WingSetOptionAddress1]
		NEXT2:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push 0
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x10]
		Imul Eax,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr DS:[Edx+Ecx+0x2E],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 0
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Byte Ptr Ds:[Ecx+Edx+0x26],Al
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		Jmp [WingSetOptionAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingSetOptionAddress2]
	}
}

__declspec(naked) void WingSetNewOption() // OK
{
	static DWORD WingSetNewOptionAddress1 = 0x00504059;
	static DWORD WingSetNewOptionAddress2 = 0x00503F62;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		And Edx,1
		Je NEXT1
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push 0
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr Ds:[Edx+Ecx+0x2E],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 0
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Byte Ptr Ds:[Ecx+Edx+0x26],Al
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		NEXT1:
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		Sar Edx,1
		And Edx,1
		Je NEXT2
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push 1
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr Ds:[Edx+Ecx+0x2E],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 1
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Byte Ptr Ds:[Ecx+Edx+0x26],Al
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		NEXT2:
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		Sar Edx,2
		And Edx,1
		Je NEXT3
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push 2
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr Ds:[Edx+Ecx+0x2E],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 2
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Byte Ptr Ds:[Ecx+Edx+0x26],Al
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		NEXT3:
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		Sar Edx,3
		And Edx,1
		Je NEXT4
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push 3
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr Ds:[Edx+Ecx+0x2E],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 3
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Byte Ptr Ds:[Ecx+Edx+0x26],Al
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		NEXT4:
		Jmp [WingSetNewOptionAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingSetNewOptionAddress2]
	}
}

__declspec(naked) void WingSetModelType() // OK
{
	static DWORD WingSetModelTypeAddress1 = 0x004FDEDF;
	static DWORD WingSetModelTypeAddress2 = 0x004FDEDB;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp-0xA4]
		Sub Edx,ITEM_BASE_MODEL
		Push 1
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByModelType]
		Test Eax,Eax
		Je EXIT
		Jmp [WingSetModelTypeAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0xA4],0x1B5B
		Jmp [WingSetModelTypeAddress2]
	}
}

__declspec(naked) void WingSetEffect() // OK
{
	static DWORD WingSetColorAddress1 = 0x004EA2FD;
	static DWORD WingSetColorAddress2 = 0x004E4440;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x74]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x48]
		Push Ecx
		Lea Edx,Dword Ptr Ss:[Ebp-0x10]
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x44]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x300]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWingEffect
		Call [CCustomWingEffect::SetWingEffect]
		Test Eax,Eax
		Je EXIT
		Jmp [WingSetColorAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x300],0x73A
		Jmp [WingSetColorAddress2]
	}
}

__declspec(naked) void WingCheckIndex1() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x004AEBE2;
	static DWORD WingCheckIndexAddress2 = 0x004AEBBD;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x14],0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex2() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x004FD710;
	static DWORD WingCheckIndexAddress2 = 0x004FD6FA;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex3() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00502C8A;
	static DWORD WingCheckIndexAddress2 = 0x00502C40;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex4() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005036CB;
	static DWORD WingCheckIndexAddress2 = 0x005036B5;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex5() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005041AF;
	static DWORD WingCheckIndexAddress2 = 0x005041A7;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex6() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00505522;
	static DWORD WingCheckIndexAddress2 = 0x0050551A;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex7() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0050659A;
	static DWORD WingCheckIndexAddress2 = 0x00506592;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex8() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005066FE;
	static DWORD WingCheckIndexAddress2 = 0x005066F6;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex9() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005068DD;
	static DWORD WingCheckIndexAddress2 = 0x005068D2;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex10() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00570AE7;
	static DWORD WingCheckIndexAddress2 = 0x0057079A;

	_asm
	{
		Mov Edx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Movsx Ecx,Word Ptr Ds:[Edx+0x13C8]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Movsx Ecx,Word Ptr Ds:[Edx+0x13C8]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex11() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005843D8;
	static DWORD WingCheckIndexAddress2 = 0x005843C7;

	_asm
	{
		Movsx Edx,Dx
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Edx
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Edx
		Cmp Edx,0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex12() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00585401;
	static DWORD WingCheckIndexAddress2 = 0x005853FF;

	_asm
	{
		Mov Edx,Eax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex13() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005862ED;
	static DWORD WingCheckIndexAddress2 = 0x00586308;

	_asm
	{
		Movsx Edx,Ax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x182B
		Jg NEXT
		Jmp [WingCheckIndexAddress1]
		NEXT:
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex14() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00587201;
	static DWORD WingCheckIndexAddress2 = 0x00587225;

	_asm
	{
		Movsx Edx,Ax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x182B
		Jg NEXT
		Jmp [WingCheckIndexAddress1]
		NEXT:
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex15() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058AAFB;
	static DWORD WingCheckIndexAddress2 = 0x0058AB02;

	_asm
	{
		Movsx Edx,Ax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x182B
		Jg NEXT
		Jmp [WingCheckIndexAddress1]
		NEXT:
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex16() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058C7F4;
	static DWORD WingCheckIndexAddress2 = 0x0058C80F;

	_asm
	{
		Movsx Edx,Ax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x182B
		Jg NEXT
		Jmp [WingCheckIndexAddress1]
		NEXT:
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex17() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058CC47;
	static DWORD WingCheckIndexAddress2 = 0x0058CB41;

	_asm
	{
		Movsx Edx,Cx
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Ecx
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Ecx
		Cmp Ecx,0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex18() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005914DE;
	static DWORD WingCheckIndexAddress2 = 0x00591459;

	_asm
	{
		Movsx Edx,Ax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x182B
		Jle NEXT
		Jmp [WingCheckIndexAddress2]
		NEXT:
		Jmp [WingCheckIndexAddress1]
	}
}

__declspec(naked) void WingCheckIndex19() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00591960;
	static DWORD WingCheckIndexAddress2 = 0x0059193C;

	_asm
	{
		Mov Edx,Eax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex20() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x006B6E30;
	static DWORD WingCheckIndexAddress2 = 0x006B6DE9;

	_asm
	{
		Mov Edx,Edx
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Edx
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Edx
		Cmp Edx,0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex21() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00731251;
	static DWORD WingCheckIndexAddress2 = 0x00731233;

	_asm
	{
		Mov Edx,Eax
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex22() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0073655D;
	static DWORD WingCheckIndexAddress2 = 0x00736557;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp-0x30]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x30],0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex23() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00752F48;
	static DWORD WingCheckIndexAddress2 = 0x00752F07;

	_asm
	{
		Mov Edx,Ecx
		Push Edx
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Ecx
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Pop Ecx
		Cmp Ecx,0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex1() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x004E39C8;
	static DWORD WingCheckModelIndexAddress2 = 0x004E39C1;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x1C]
		Sub Eax,ITEM_BASE_MODEL
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp+0x1C],0x1B5E
		Jmp [WingCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex2() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x00590124;
	static DWORD WingCheckModelIndexAddress2 = 0x00590106;

	_asm
	{
		Mov Edx,Eax
		Mov Ecx,Edx
		Sub Ecx,ITEM_BASE_MODEL
		Push Edx
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Pop Eax
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Pop Eax
		Cmp Eax,0x1B5E
		Jmp [WingCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex3() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x005C1EB0;
	static DWORD WingCheckModelIndexAddress2 = 0x005C1D6F;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Ecx,Dword Ptr Ds:[Eax+0x30]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Cmp Dword Ptr Ds:[Edx+0x30],0x1B5E
		Jmp [WingCheckModelIndexAddress2]
	}
}
