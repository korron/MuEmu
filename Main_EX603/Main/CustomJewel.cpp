// CustomJewel.cpp: implementation of the CCustomJewel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "Item.h"

CCustomJewel gCustomJewel;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomJewel::CCustomJewel() // OK
{
	this->Init();
}

CCustomJewel::~CCustomJewel() // OK
{

}

void CCustomJewel::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		this->m_CustomJewelInfo[n].Index = -1;
	}
}

void CCustomJewel::Load(CUSTOM_JEWEL_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomJewel::SetInfo(CUSTOM_JEWEL_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_JEWEL)
	{
		return;
	}

	this->m_CustomJewelInfo[info.Index] = info;
}

CUSTOM_JEWEL_INFO* CCustomJewel::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_JEWEL)
	{
		return 0;
	}

	if(this->m_CustomJewelInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomJewelInfo[index];
}

CUSTOM_JEWEL_INFO* CCustomJewel::GetInfoByItem(int ItemIndex) // OK
{
	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		CUSTOM_JEWEL_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->ItemIndex == ItemIndex)
		{
			return lpInfo;
		}
	}

	return 0;
}

BOOL CCustomJewel::CheckCustomJewel(int index) // OK
{
	if(this->GetInfo(index) != 0)
	{
		return 1;
	}

	return 0;
}

BOOL CCustomJewel::CheckCustomJewelByItem(int ItemIndex) // OK
{
	if(this->GetInfoByItem(ItemIndex) != 0)
	{
		return 1;
	}

	return 0;
}

BOOL CCustomJewel::CheckCustomJewelApplyItem(int ItemIndex,int TargetItemIndex) // OK
{
	CUSTOM_JEWEL_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	if((TargetItemIndex/MAX_ITEM_TYPE) >= 7 && (TargetItemIndex/MAX_ITEM_TYPE) <= 11 && (TargetItemIndex%MAX_ITEM_TYPE) >= 62 && (TargetItemIndex%MAX_ITEM_TYPE) <= 72)
	{
		return 0;
	}

	if(TargetItemIndex > GET_ITEM(12,6) && (TargetItemIndex < GET_ITEM(12,36) || TargetItemIndex > GET_ITEM(12,43)) && TargetItemIndex != GET_ITEM(12,49) && TargetItemIndex != GET_ITEM(12,50) && (TargetItemIndex < GET_ITEM(12,262) || TargetItemIndex > GET_ITEM(12,265)) && TargetItemIndex != GET_ITEM(13,30) && gCustomWing.CheckCustomWingByItem(TargetItemIndex) == 0)
	{
		return 0;
	}

	if(lpInfo->EnableSlotWeapon == 0 && (TargetItemIndex >= GET_ITEM(0,0) && TargetItemIndex < GET_ITEM(6,0)))
	{
		return 0;
	}

	if(lpInfo->EnableSlotArmor == 0 && (TargetItemIndex >= GET_ITEM(6,0) && TargetItemIndex < GET_ITEM(12,0)))
	{
		return 0;
	}

	if(lpInfo->EnableSlotWing == 0 && ((TargetItemIndex >= GET_ITEM(12,0) && TargetItemIndex <= GET_ITEM(12,6)) || (TargetItemIndex >= GET_ITEM(12,36) && TargetItemIndex <= GET_ITEM(12,43)) || TargetItemIndex == GET_ITEM(12,49) || TargetItemIndex == GET_ITEM(12,50) || (TargetItemIndex >= GET_ITEM(12,262) && TargetItemIndex <= GET_ITEM(12,265)) || TargetItemIndex == GET_ITEM(13,30) || gCustomWing.CheckCustomWingByItem(TargetItemIndex) != 0))
	{
		return 0;
	}

	return 1;
}

int CCustomJewel::GetCustomJewelSuccessRate(int ItemIndex,int AccountLevel) // OK
{
	CUSTOM_JEWEL_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	return lpInfo->SuccessRate[AccountLevel];
}

int CCustomJewel::GetCustomJewelSalePrice(int ItemIndex) // OK
{
	CUSTOM_JEWEL_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	return lpInfo->SalePrice;
}
