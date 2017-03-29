// CustomItem.cpp: implementation of the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomItem.h"

CCustomItem gCustomItem;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomItem::CCustomItem() // OK
{
	this->Init();
}

CCustomItem::~CCustomItem() // OK
{

}

void CCustomItem::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		this->m_CustomItemInfo[n].Index = -1;
	}
}

void CCustomItem::Load(CUSTOM_ITEM_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomItem::SetInfo(CUSTOM_ITEM_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_ITEM)
	{
		return;
	}

	this->m_CustomItemInfo[info.Index] = info;
}

CUSTOM_ITEM_INFO* CCustomItem::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_ITEM)
	{
		return 0;
	}

	if(this->m_CustomItemInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomItemInfo[index];
}

CUSTOM_ITEM_INFO* CCustomItem::GetInfoByItem(int ItemIndex) // OK
{
	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		CUSTOM_ITEM_INFO* lpInfo = this->GetInfo(n);

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

bool CCustomItem::GetCustomItemColor(int ItemIndex,float* ItemColor) // OK
{
	CUSTOM_ITEM_INFO* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	ItemColor[0] = (float)(lpInfo->ColorR/255.0f);
	ItemColor[1] = (float)(lpInfo->ColorG/255.0f);
	ItemColor[2] = (float)(lpInfo->ColorB/255.0f);
	return 1;
}
