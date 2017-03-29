// CustomJewel.h: interface for the CCustomJewel class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_JEWEL 15

struct CUSTOM_JEWEL_SUCCESS_INFO
{
	int Index;
	int Level;
	int Option1;
	int Option2;
	int Option3;
	int NewOption;
	int SetOption;
	int SocketOption;
};

struct CUSTOM_JEWEL_FAILURE_INFO
{
	int Index;
	int Level;
	int Option1;
	int Option2;
	int Option3;
	int NewOption;
	int SetOption;
	int SocketOption;
};

struct CUSTOM_JEWEL_INFO
{
	int Index;
	int ItemIndex;
	int MinItemLevel;
	int MaxItemLevel;
	int MaxItemOption1;
	int MaxItemOption2;
	int MinItemOption3;
	int MaxItemOption3;
	int MinItemNewOption;
	int MaxItemNewOption;
	int MaxItemSetOption;
	int MinItemSocketOption;
	int MaxItemSocketOption;
	int EnableSlotWeapon;
	int EnableSlotArmor;
	int EnableSlotWing;
	int SuccessRate[4];
	int SalePrice;
	char ModelName[32];
	CUSTOM_JEWEL_SUCCESS_INFO SuccessInfo;
	CUSTOM_JEWEL_FAILURE_INFO FailureInfo;
};

class CCustomJewel
{
public:
	CCustomJewel();
	virtual ~CCustomJewel();
	void Init();
	void Load(CUSTOM_JEWEL_INFO* info);
	void SetInfo(CUSTOM_JEWEL_INFO info);
	CUSTOM_JEWEL_INFO* GetInfo(int index);
	CUSTOM_JEWEL_INFO* GetInfoByItem(int ItemIndex);
	BOOL CheckCustomJewel(int index);
	BOOL CheckCustomJewelByItem(int ItemIndex);
	BOOL CheckCustomJewelApplyItem(int ItemIndex,int TargetItemIndex);
	int GetCustomJewelSuccessRate(int ItemIndex,int AccountLevel);
	int GetCustomJewelSalePrice(int ItemIndex);
public:
	CUSTOM_JEWEL_INFO m_CustomJewelInfo[MAX_CUSTOM_JEWEL];
};

extern CCustomJewel gCustomJewel;
