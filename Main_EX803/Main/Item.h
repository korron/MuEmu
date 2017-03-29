#pragma once

#define MAX_ITEM_SECTION 16
#define MAX_ITEM_TYPE 512
#define MAX_ITEM (MAX_ITEM_SECTION*MAX_ITEM_TYPE)
#define ITEM_BASE_MODEL 1254

#define GET_ITEM(x,y) (((x)*MAX_ITEM_TYPE)+(y))
#define GET_ITEM_MODEL(x,y) ((((x)*MAX_ITEM_TYPE)+(y))+ITEM_BASE_MODEL)

void InitItem();
void InitJewel();
void InitWing();
void ItemModelLoad();
void ItemTextureLoad();
void LoadItemModel(int index,char* folder,char* name,int value);
void LoadItemTexture(int index,char* folder,char* name,int value);
void GetItemColor(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e);
BOOL CheckSocketItem(DWORD address);
void ItemSocketName1();
void ItemSocketName2();
void ItemExcellentSocket();
void JewelSetSalePrice();
void JewelCheckApplyItem();
void JewelCheckIndex1();
void JewelCheckIndex2();
void JewelCheckIndex3();
void JewelCheckModelIndex1();
void WingMakePreviewCharSet();
void WingDisableLevelGlow();
void WingSetIncDamage();
void WingSetDecDamage();
void WingSetOption();
void WingSetModelType();
void WingSetEffect();
void WingCheckIndex1();
void WingCheckModelIndex1();
