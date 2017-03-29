#pragma once

#define MAX_ITEM_SECTION 16
#define MAX_ITEM_TYPE 512
#define MAX_ITEM (MAX_ITEM_SECTION*MAX_ITEM_TYPE)
#define ITEM_BASE_MODEL 1171

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
BOOL CheckSocketItem(DWORD address,DWORD this_pointer);
void ItemTextZeroMemory();
void ItemSocketName1();
void ItemSocketName2();
void ItemSocketName3();
void JewelSetSalePrice();
void JewelCheckApplyItem();
void JewelCheckIndex1();
void JewelCheckIndex2();
void JewelCheckIndex3();
void JewelCheckIndex4();
void JewelCheckModelIndex1();
void JewelCheckModelIndex2();
void WingMakePreviewCharSet();
void WingDisableLevelGlow();
void WingSetIncDamage();
void WingSetDecDamage();
void WingSetDefense();
void WingSetExtraDefense();
void WingSetOption();
void WingSetNewOption();
void WingSetModelType();
void WingSetEffect();
void WingCheckIndex1();
void WingCheckIndex2();
void WingCheckIndex3();
void WingCheckIndex4();
void WingCheckIndex5();
void WingCheckIndex6();
void WingCheckIndex7();
void WingCheckIndex8();
void WingCheckIndex9();
void WingCheckIndex10();
void WingCheckIndex11();
void WingCheckIndex12();
void WingCheckIndex13();
void WingCheckIndex14();
void WingCheckIndex15();
void WingCheckIndex16();
void WingCheckIndex17();
void WingCheckIndex18();
void WingCheckIndex19();
void WingCheckIndex20();
void WingCheckIndex21();
void WingCheckModelIndex1();
void WingCheckModelIndex2();
void WingCheckModelIndex3();
