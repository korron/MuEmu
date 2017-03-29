// CustomItem.h: interface for the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_ITEM 2000

struct CUSTOM_ITEM_INFO
{
	int Index;
	int ItemIndex;
	int ColorR;
	int ColorG;
	int ColorB;
	char ModelName[32];
};

class CCustomItem
{
public:
	CCustomItem();
	virtual ~CCustomItem();
	void Init();
	void Load(char* path);
	void SetInfo(CUSTOM_ITEM_INFO info);
public:
	CUSTOM_ITEM_INFO m_CustomItemInfo[MAX_CUSTOM_ITEM];
};

extern CCustomItem gCustomItem;
