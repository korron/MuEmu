#include "stdafx.h"
#include "Item.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "CustomWingEffect.h"
#include "Util.h"

void InitItem() // OK
{
	SetCompleteHook(0xFF,0x0062D339,&ItemModelLoad);

	SetCompleteHook(0xFF,0x0062D33E,&ItemTextureLoad);

	SetCompleteHook(0xFF,0x00583F09,&GetItemColor);

	SetCompleteHook(0xFF,0x006036B8,&GetItemColor);

	SetCompleteHook(0xE9,0x005EF1EB,&ItemSocketName1);

	SetCompleteHook(0xE9,0x004F722D,&ItemSocketName2);

	SetCompleteHook(0xE9,0x00917459,&ItemExcellentSocket);
}

void InitJewel() // OK
{
	SetCompleteHook(0xE9,0x00594C7D,&JewelSetSalePrice);

	SetCompleteHook(0xE9,0x007C7C1A,&JewelCheckApplyItem);

	SetCompleteHook(0xE9,0x004E6F17,&JewelCheckIndex1);

	SetCompleteHook(0xE9,0x005EF320,&JewelCheckIndex2);

	SetCompleteHook(0xE9,0x09EA30A8,&JewelCheckIndex3);

	SetCompleteHook(0xE9,0x005EAF4B,&JewelCheckModelIndex1);
}

void InitWing() // OK
{
	SetCompleteHook(0xE9,0x00589583,&WingMakePreviewCharSet);

	SetCompleteHook(0xE9,0x0060576A,&WingDisableLevelGlow);

	SetCompleteHook(0xE9,0x007D1E43,&WingSetIncDamage);

	SetCompleteHook(0xE9,0x007D1EBE,&WingSetDecDamage);

	SetCompleteHook(0xE9,0x00916BE8,&WingSetOption);

	SetCompleteHook(0xE9,0x00592731,&WingSetModelType);

	SetCompleteHook(0xE9,0x0056CA92,&WingSetEffect);

	SetCompleteHook(0xE9,0x005BFDEE,&WingCheckIndex1);

	SetCompleteHook(0xE9,0x006058E5,&WingCheckModelIndex1);
}

void ItemModelLoad() // OK
{
	((void(*)())0x0061355D)();

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
	((void(*)())0x0061393F)();

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

	((void(*)(int,char*,char*,int))0x006112F7)(index,path,name,value);
}

void LoadItemTexture(int index,char* folder,char* name,int value) // OK
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,int,int,int))0x00610D61)(index,folder,0x2901,0x2600,0x01);
}

void GetItemColor(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(gCustomItem.GetCustomItemColor((a-ITEM_BASE_MODEL),(float*)d) == 0)
	{
		((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x005F0333)(a,b,c,d,e);
	}
}

BOOL CheckSocketItem(DWORD address) // OK
{
	if(*(DWORD*)(address+0x04) >= GET_ITEM(12,200) && *(DWORD*)(address+0x04) <= GET_ITEM(12,220)) // Pentagram Item
	{
		return 0;
	}

	if(*(DWORD*)(address+0x04) >= GET_ITEM(12,221) && *(DWORD*)(address+0x04) <= GET_ITEM(12,261)) // Pentagram Jewel
	{
		return 0;
	}

	if(*(DWORD*)(address+0x04) == GET_ITEM(12,144) || *(DWORD*)(address+0x04) == GET_ITEM(12,145) || *(DWORD*)(address+0x04) == GET_ITEM(12,148)) // Pentagram Mithril
	{
		return 0;
	}

	if(*(DWORD*)(address+0x04) == GET_ITEM(13,211)) // Evolution Stone
	{
		return 0;
	}

	for(int n=0;n < 5;n++)
	{
		if(*(BYTE*)(address+(0x59+n)) != 0xFF)
		{
			return 1;
		}
	}

	return 0;
}

__declspec(naked) void ItemSocketName1() // OK
{
	static DWORD ItemSocketNameAddress1 = 0x005EF1F1;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Mov Byte Ptr Ds:[Ecx+0x58],Al
		Push 0x05
		Mov Edx,Dword Ptr Ss:[Ebp+0x0C]
		Add Edx,0x07
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		Add Eax,0x59
		Push Eax
		Call [MemoryCpy]
		Add Esp,0x0C
		Jmp [ItemSocketNameAddress1]
	}
}

__declspec(naked) void ItemSocketName2() // OK
{
	static DWORD ItemSocketNameAddress1 = 0x004F7232;
	static DWORD ItemSocketNameAddress2 = 0x004F7238;

	_asm
	{
		Cmp Eax,Dword Ptr Ss:[Ebp+0x08]
		Je NEXT
		Cmp Dword Ptr Ss:[Ebp+0x08],0x02
		Jnz EXIT
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		Push Eax
		Call [CheckSocketItem]
		Add Esp,0x04
		Test Eax,Eax
		Je EXIT
		NEXT:
		Jmp [ItemSocketNameAddress1]
		EXIT:
		Jmp [ItemSocketNameAddress2]
	}
}

__declspec(naked) void ItemExcellentSocket() // OK
{
	static DWORD ItemExcellentSocketAddress1 = 0x004F7201;
	static DWORD ItemExcellentSocketAddress2 = 0x0091745E;
	static DWORD ItemExcellentSocketAddress3 = 0x0091749D;

	_asm
	{
		Push 0x02
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Call [ItemExcellentSocketAddress1]
		Movzx Eax,Al
		Test Eax,Eax
		Jne EXIT
		Push 0x01
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Jmp [ItemExcellentSocketAddress2]
		EXIT:
		Jmp [ItemExcellentSocketAddress3]
	}
}

__declspec(naked) void JewelSetSalePrice() // OK
{
	static DWORD JewelSetSalePriceAddress1 = 0x005963F4;
	static DWORD JewelSetSalePriceAddress2 = 0x00594C87;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::GetCustomJewelSalePrice]
		Mov Dword Ptr Ss:[Ebp-0x10],Eax
		Mov Dword Ptr Ss:[Ebp-0x0C],0x00
		Jmp [JewelSetSalePriceAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Cmp Dword Ptr Ds:[Eax+0x04],0x1C0D
		Jmp [JewelSetSalePriceAddress2]
	}
}

__declspec(naked) void JewelCheckApplyItem() // OK
{
	static DWORD JewelCheckApplyItemAddress1 = 0x007C7C25;
	static DWORD JewelCheckApplyItemAddress2 = 0x007C7C21;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x6C]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Mov Eax,Dword Ptr Ss:[Ebp-0x6C]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Mov Edx,Dword Ptr Ss:[Ebp-0x98]
		Mov Eax,Dword Ptr Ds:[Edx+0x04]
		Push Eax
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelApplyItem]
		Test Eax,Eax
		Je EXIT
		Mov Byte Ptr Ss:[Ebp-0x99],0x01
		Jmp [JewelCheckApplyItemAddress1]
		EXIT:
		Movzx Eax,Byte Ptr Ss:[Ebp-0x99]
		Jmp [JewelCheckApplyItemAddress2]
	}
}

__declspec(naked) void JewelCheckIndex1() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x004E6F20;
	static DWORD JewelCheckIndexAddress2 = 0x004E6F1E;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp+0x08],0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex2() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x005EF356;
	static DWORD JewelCheckIndexAddress2 = 0x005EF327;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x08],0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex3() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x00644CDD;
	static DWORD JewelCheckIndexAddress2 = 0x09EA30AF;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x14],0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckModelIndex1() // OK
{
	static DWORD JewelCheckModelIndexAddress1 = 0x005EB366;
	static DWORD JewelCheckModelIndexAddress2 = 0x005EAF52;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x0C]
		Mov Ecx,Dword Ptr Ds:[Eax+0x40]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckModelIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp-0x0C]
		Cmp Dword Ptr Ds:[Eax+0x40],0x20F3
		Jmp [JewelCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingMakePreviewCharSet() // OK
{
	static DWORD WingMakePreviewCharSetAddress1 = 0x005895DA;
	static DWORD WingMakePreviewCharSetAddress2 = 0x0058958A;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Ecx,Byte Ptr Ds:[Eax+0x10]
		Sar Ecx,0x01
		And Ecx,0x0F
		Test Ecx,Ecx
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
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Ecx,Byte Ptr Ds:[Eax+0x10]
		Sar Ecx,0x01
		And Ecx,0x0F
		Sub Ecx,0x01
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingItem]
		Add Eax,ITEM_BASE_MODEL
		Mov Ecx,Dword Ptr Ss:[Ebp-0x10]
		Mov Word Ptr Ds:[Ecx+0x218],Ax
		Jmp [WingMakePreviewCharSetAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Eax,Byte Ptr Ds:[Eax+0x10]
		Jmp [WingMakePreviewCharSetAddress2]
	}
}

__declspec(naked) void WingDisableLevelGlow() // OK
{
	static DWORD WingDisableLevelGlowAddress1 = 0x00605D0F;
	static DWORD WingDisableLevelGlowAddress2 = 0x00605773;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Sub Eax,ITEM_BASE_MODEL
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Dword Ptr Ss:[Ebp-0x04],0x00
		Jmp [WingDisableLevelGlowAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Mov Dword Ptr Ss:[Ebp-0x768],Eax
		Jmp [WingDisableLevelGlowAddress2]
	}
}

__declspec(naked) void WingSetIncDamage() // OK
{
	static DWORD WingSetIncDamageAddress1 = 0x007D1E4A;
	static DWORD WingSetIncDamageAddress2 = 0x007D1E4A;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x1C]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp+0x1C]
		Mov Eax,Dword Ptr Ds:[Edx+0x04]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x20]
		Push Ecx
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingIncDamage]
		Push Eax
		Jmp [WingSetIncDamageAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x20]
		Add Eax,0x20
		Push Eax
		Jmp [WingSetIncDamageAddress2]
	}
}

__declspec(naked) void WingSetDecDamage() // OK
{
	static DWORD WingSetDecDamageAddress1 = 0x007D1EC6;
	static DWORD WingSetDecDamageAddress2 = 0x007D1EC6;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x1C]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp+0x1C]
		Mov Eax,Dword Ptr Ds:[Edx+0x04]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x20]
		Push Ecx
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingDecDamage]
		Push Eax
		Jmp [WingSetDecDamageAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x20]
		Lea Eax,Dword Ptr Ds:[Eax+Eax+0x19]
		Push Eax
		Jmp [WingSetDecDamageAddress2]
	}
}

__declspec(naked) void WingSetOption() // OK
{
	static DWORD WingOptionIndex,WingOptionValue;
	static DWORD WingSetOptionAddress1 = 0x00916E58;
	static DWORD WingSetOptionAddress2 = 0x00916C49;
	static DWORD WingSetOptionAddress3 = 0x00916BF2;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x20]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Eax,Dword Ptr Ss:[Ebp-0x0C]
		Sar Eax,0x04
		And Eax,0x01
		Je NEXT1
		Mov Eax,Dword Ptr Ss:[Ebp-0x0C]
		And Eax,0xFFFFFFEF
		Mov Dword Ptr Ss:[Ebp-0x0C],Eax
		Mov Eax,Dword Ptr Ss:[Ebp-0x20]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push 1
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov WingOptionIndex,Eax
		Mov Eax,Dword Ptr Ss:[Ebp-0x20]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push 1
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Imul Eax,Edx
		Mov WingOptionValue,Eax
		Push WingOptionValue
		Push WingOptionIndex
		Mov Ecx,Dword Ptr Ss:[Ebp-0x20]
		Call [WingSetOptionAddress1]
		Jmp [WingSetOptionAddress2]
		NEXT1:
		Mov Eax,Dword Ptr Ss:[Ebp-0x0C]
		Sar Eax,0x05
		And Eax,0x01
		Je NEXT2
		Mov Eax,Dword Ptr Ss:[Ebp-0x0C]
		And Eax,0xFFFFFFDF
		Mov Dword Ptr Ss:[Ebp-0x0C],Eax
		Mov Eax,Dword Ptr Ss:[Ebp-0x20]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push 2
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov WingOptionIndex,Eax
		Mov Eax,Dword Ptr Ss:[Ebp-0x20]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push 2
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Imul Eax,Edx
		Mov WingOptionValue,Eax
		Push WingOptionValue
		Push WingOptionIndex
		Mov Ecx,Dword Ptr Ss:[Ebp-0x20]
		Call [WingSetOptionAddress1]
		Jmp [WingSetOptionAddress2]
		NEXT2:
		Mov Eax,Dword Ptr Ss:[Ebp-0x20]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push 0
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov WingOptionIndex,Eax
		Mov Eax,Dword Ptr Ss:[Ebp-0x20]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push 0
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Imul Eax,Edx
		Mov WingOptionValue,Eax
		Push WingOptionValue
		Push WingOptionIndex
		Mov Ecx,Dword Ptr Ss:[Ebp-0x20]
		Call [WingSetOptionAddress1]
		Jmp [WingSetOptionAddress2]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp-0x20]
		Cmp Dword Ptr Ds:[Eax+0x04],0x182B
		Jmp [WingSetOptionAddress3]
	}
}

__declspec(naked) void WingSetModelType() // OK
{
	static DWORD WingSetModelTypeAddress1 = 0x00592763;
	static DWORD WingSetModelTypeAddress2 = 0x0059273D;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x74]
		Movsx Eax,Word Ptr Ds:[Eax]
		Mov Dword Ptr Ss:[Ebp-0xB8],Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0xB8]
		Sub Ecx,ITEM_BASE_MODEL
		Push 1
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByModelType]
		Test Eax,Eax
		Je EXIT
		Jmp [WingSetModelTypeAddress1]
		EXIT:
		Jmp [WingSetModelTypeAddress2]
	}
}

__declspec(naked) void WingSetEffect() // OK
{
	static DWORD WingSetColorAddress1 = 0x00576DC9;
	static DWORD WingSetColorAddress2 = 0x0056CA9C;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x70]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x6C]
		Push Ecx
		Lea Edx,Dword Ptr Ss:[Ebp-0x18]
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x68]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x720]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWingEffect
		Call [CCustomWingEffect::SetWingEffect]
		Test Eax,Eax
		Je EXIT
		Jmp [WingSetColorAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x720],0xCEC
		Jmp [WingSetColorAddress2]
	}
}

__declspec(naked) void WingCheckIndex1() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005BFE0B;
	static DWORD WingCheckIndexAddress2 = 0x005BFDF8;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Mov Ecx,Dword Ptr Ds:[Eax+0x04]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Cmp Dword Ptr Ds:[Eax+0x04],0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex1() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x00605B55;
	static DWORD WingCheckModelIndexAddress2 = 0x006058EF;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x768]
		Sub Eax,ITEM_BASE_MODEL
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x768],0x1D11
		Jmp [WingCheckModelIndexAddress2]
	}
}
