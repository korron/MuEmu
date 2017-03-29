// CustomStore.cpp: implementation of the CCustomStore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomStore.h"
#include "CashShop.h"
#include "CommandManager.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "Log.h"
#include "Map.h"
#include "MasterSkillTree.h"
#include "Notice.h"
#include "PcPoint.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "Util.h"

CCustomStore gCustomStore;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomStore::CCustomStore() // OK
{

}

CCustomStore::~CCustomStore() // OK
{

}

void CCustomStore::ReadCustomStoreInfo(char* section,char* path) // OK
{
	this->m_CustomStoreSwitch = GetPrivateProfileInt(section,"CustomStoreSwitch",0,path);

	this->m_CustomStoreMapZone = GetPrivateProfileInt(section,"CustomStoreMapZone",0,path);

	this->m_CustomStoreEnable[0] = GetPrivateProfileInt(section,"CustomStoreEnable_AL0",0,path);

	this->m_CustomStoreEnable[1] = GetPrivateProfileInt(section,"CustomStoreEnable_AL1",0,path);

	this->m_CustomStoreEnable[2] = GetPrivateProfileInt(section,"CustomStoreEnable_AL2",0,path);

	this->m_CustomStoreEnable[3] = GetPrivateProfileInt(section,"CustomStoreEnable_AL3",0,path);

	this->m_CustomStoreRequireLevel[0] = GetPrivateProfileInt(section,"CustomStoreRequireLevel_AL0",0,path);

	this->m_CustomStoreRequireLevel[1] = GetPrivateProfileInt(section,"CustomStoreRequireLevel_AL1",0,path);

	this->m_CustomStoreRequireLevel[2] = GetPrivateProfileInt(section,"CustomStoreRequireLevel_AL2",0,path);

	this->m_CustomStoreRequireLevel[3] = GetPrivateProfileInt(section,"CustomStoreRequireLevel_AL3",0,path);

	this->m_CustomStoreRequireReset[0] = GetPrivateProfileInt(section,"CustomStoreRequireReset_AL0",0,path);

	this->m_CustomStoreRequireReset[1] = GetPrivateProfileInt(section,"CustomStoreRequireReset_AL1",0,path);

	this->m_CustomStoreRequireReset[2] = GetPrivateProfileInt(section,"CustomStoreRequireReset_AL2",0,path);

	this->m_CustomStoreRequireReset[3] = GetPrivateProfileInt(section,"CustomStoreRequireReset_AL3",0,path);

	GetPrivateProfileString(section,"CustomStoreCommandSyntax","",this->m_CustomStoreCommandSyntax,sizeof(this->m_CustomStoreCommandSyntax),path);

	GetPrivateProfileString(section,"CustomStoreCommandJoBSyntax","",this->m_CustomStoreCommandJoBSyntax,sizeof(this->m_CustomStoreCommandJoBSyntax),path);

	GetPrivateProfileString(section,"CustomStoreCommandJoSSyntax","",this->m_CustomStoreCommandJoSSyntax,sizeof(this->m_CustomStoreCommandJoSSyntax),path);

	GetPrivateProfileString(section,"CustomStoreCommandJoCSyntax","",this->m_CustomStoreCommandJoCSyntax,sizeof(this->m_CustomStoreCommandJoCSyntax),path);

	#if(GAMESERVER_UPDATE>=501)

	GetPrivateProfileString(section,"CustomStoreCommandWCCSyntax","",this->m_CustomStoreCommandWCCSyntax,sizeof(this->m_CustomStoreCommandWCCSyntax),path);

	GetPrivateProfileString(section,"CustomStoreCommandWCPSyntax","",this->m_CustomStoreCommandWCPSyntax,sizeof(this->m_CustomStoreCommandWCPSyntax),path);

	GetPrivateProfileString(section,"CustomStoreCommandWCGSyntax","",this->m_CustomStoreCommandWCGSyntax,sizeof(this->m_CustomStoreCommandWCGSyntax),path);

	#else

	GetPrivateProfileString(section,"CustomStoreCommandPCPSyntax","",this->m_CustomStoreCommandWCGSyntax,sizeof(this->m_CustomStoreCommandWCGSyntax),path);

	#endif

	GetPrivateProfileString(section,"CustomStoreJoBName","",this->m_CustomStoreJoBName,sizeof(this->m_CustomStoreJoBName),path);

	GetPrivateProfileString(section,"CustomStoreJoSName","",this->m_CustomStoreJoSName,sizeof(this->m_CustomStoreJoSName),path);

	GetPrivateProfileString(section,"CustomStoreJoCName","",this->m_CustomStoreJoCName,sizeof(this->m_CustomStoreJoCName),path);

	#if(GAMESERVER_UPDATE>=501)

	GetPrivateProfileString(section,"CustomStoreWCCName","",this->m_CustomStoreWCCName,sizeof(this->m_CustomStoreWCCName),path);

	GetPrivateProfileString(section,"CustomStoreWCPName","",this->m_CustomStoreWCPName,sizeof(this->m_CustomStoreWCPName),path);

	GetPrivateProfileString(section,"CustomStoreWCGName","",this->m_CustomStoreWCGName,sizeof(this->m_CustomStoreWCGName),path);

	#else

	GetPrivateProfileString(section,"CustomStorePCPName","",this->m_CustomStoreWCGName,sizeof(this->m_CustomStoreWCGName),path);

	#endif

	GetPrivateProfileString(section,"CustomStoreText1","",this->m_CustomStoreText1,sizeof(this->m_CustomStoreText1),path);

	GetPrivateProfileString(section,"CustomStoreText2","",this->m_CustomStoreText2,sizeof(this->m_CustomStoreText2),path);

	GetPrivateProfileString(section,"CustomStoreText3","",this->m_CustomStoreText3,sizeof(this->m_CustomStoreText3),path);

	GetPrivateProfileString(section,"CustomStoreText4","",this->m_CustomStoreText4,sizeof(this->m_CustomStoreText4),path);

	GetPrivateProfileString(section,"CustomStoreText5","",this->m_CustomStoreText5,sizeof(this->m_CustomStoreText5),path);

	GetPrivateProfileString(section,"CustomStoreText6","",this->m_CustomStoreText6,sizeof(this->m_CustomStoreText6),path);

	#if(GAMESERVER_UPDATE>=501)

	GetPrivateProfileString(section,"CustomStoreText7","",this->m_CustomStoreText7,sizeof(this->m_CustomStoreText7),path);

	GetPrivateProfileString(section,"CustomStoreText8","",this->m_CustomStoreText8,sizeof(this->m_CustomStoreText8),path);

	GetPrivateProfileString(section,"CustomStoreText9","",this->m_CustomStoreText9,sizeof(this->m_CustomStoreText9),path);

	GetPrivateProfileString(section,"CustomStoreText10","",this->m_CustomStoreText10,sizeof(this->m_CustomStoreText10),path);

	GetPrivateProfileString(section,"CustomStoreText11","",this->m_CustomStoreText11,sizeof(this->m_CustomStoreText11),path);

	#else

	GetPrivateProfileString(section,"CustomStoreText7","",this->m_CustomStoreText9,sizeof(this->m_CustomStoreText9),path);

	GetPrivateProfileString(section,"CustomStoreText8","",this->m_CustomStoreText10,sizeof(this->m_CustomStoreText10),path);

	GetPrivateProfileString(section,"CustomStoreText9","",this->m_CustomStoreText11,sizeof(this->m_CustomStoreText11),path);

	#endif

	this->m_CustomStoreOfflineSwitch = GetPrivateProfileInt(section,"CustomStoreOfflineSwitch",0,path);

	this->m_CustomStoreOfflineGPGain = GetPrivateProfileInt(section,"CustomStoreOfflineGPGain",0,path);

	this->m_CustomStoreOfflineMapZone = GetPrivateProfileInt(section,"CustomStoreOfflineMapZone",0,path);

	this->m_CustomStoreOfflineEnable[0] = GetPrivateProfileInt(section,"CustomStoreOfflineEnable_AL0",0,path);

	this->m_CustomStoreOfflineEnable[1] = GetPrivateProfileInt(section,"CustomStoreOfflineEnable_AL1",0,path);

	this->m_CustomStoreOfflineEnable[2] = GetPrivateProfileInt(section,"CustomStoreOfflineEnable_AL2",0,path);

	this->m_CustomStoreOfflineEnable[3] = GetPrivateProfileInt(section,"CustomStoreOfflineEnable_AL3",0,path);

	this->m_CustomStoreOfflineRequireLevel[0] = GetPrivateProfileInt(section,"CustomStoreOfflineRequireLevel_AL0",0,path);

	this->m_CustomStoreOfflineRequireLevel[1] = GetPrivateProfileInt(section,"CustomStoreOfflineRequireLevel_AL1",0,path);

	this->m_CustomStoreOfflineRequireLevel[2] = GetPrivateProfileInt(section,"CustomStoreOfflineRequireLevel_AL2",0,path);

	this->m_CustomStoreOfflineRequireLevel[3] = GetPrivateProfileInt(section,"CustomStoreOfflineRequireLevel_AL3",0,path);

	this->m_CustomStoreOfflineRequireReset[0] = GetPrivateProfileInt(section,"CustomStoreOfflineRequireReset_AL0",0,path);

	this->m_CustomStoreOfflineRequireReset[1] = GetPrivateProfileInt(section,"CustomStoreOfflineRequireReset_AL1",0,path);

	this->m_CustomStoreOfflineRequireReset[2] = GetPrivateProfileInt(section,"CustomStoreOfflineRequireReset_AL2",0,path);

	this->m_CustomStoreOfflineRequireReset[3] = GetPrivateProfileInt(section,"CustomStoreOfflineRequireReset_AL3",0,path);

	GetPrivateProfileString(section,"CustomStoreOfflineCommandSyntax","",this->m_CustomStoreOfflineCommandSyntax,sizeof(this->m_CustomStoreOfflineCommandSyntax),path);

	GetPrivateProfileString(section,"CustomStoreOfflineText1","",this->m_CustomStoreOfflineText1,sizeof(this->m_CustomStoreOfflineText1),path);

	GetPrivateProfileString(section,"CustomStoreOfflineText2","",this->m_CustomStoreOfflineText2,sizeof(this->m_CustomStoreOfflineText2),path);

	GetPrivateProfileString(section,"CustomStoreOfflineText3","",this->m_CustomStoreOfflineText3,sizeof(this->m_CustomStoreOfflineText3),path);

	GetPrivateProfileString(section,"CustomStoreOfflineText4","",this->m_CustomStoreOfflineText4,sizeof(this->m_CustomStoreOfflineText4),path);

	GetPrivateProfileString(section,"CustomStoreOfflineText5","",this->m_CustomStoreOfflineText5,sizeof(this->m_CustomStoreOfflineText5),path);
}

void CCustomStore::CommandCustomStore(LPOBJ lpObj,char* arg) // OK
{
	if(this->m_CustomStoreSwitch == 0)
	{
		return;
	}

	if(this->m_CustomStoreEnable[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreText1);
		return;
	}

	if(((gMasterSkillTree.CheckMasterLevel(lpObj)==0)?lpObj->Level:(lpObj->Level+lpObj->MasterLevel)) < this->m_CustomStoreRequireLevel[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreText10,this->m_CustomStoreRequireLevel[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->Reset < this->m_CustomStoreRequireReset[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreText11,this->m_CustomStoreRequireReset[lpObj->AccountLevel]);
		return;
	}

	char mode[32] = {0};

	gCommandManager.GetString(arg,mode,sizeof(mode),0);

	if(strcmp(mode,"") != 0)
	{
		if(strcmp(mode,this->m_CustomStoreCommandJoBSyntax) == 0)
		{
			this->OpenCustomStore(lpObj,0);
		}
		else if(strcmp(mode,this->m_CustomStoreCommandJoSSyntax) == 0)
		{
			this->OpenCustomStore(lpObj,1);
		}
		else if(strcmp(mode,this->m_CustomStoreCommandJoCSyntax) == 0)
		{
			this->OpenCustomStore(lpObj,2);
		}
		else if(strcmp(mode,this->m_CustomStoreCommandWCCSyntax) == 0)
		{
			this->OpenCustomStore(lpObj,3);
		}
		else if(strcmp(mode,this->m_CustomStoreCommandWCPSyntax) == 0)
		{
			this->OpenCustomStore(lpObj,4);
		}
		else if(strcmp(mode,this->m_CustomStoreCommandWCGSyntax) == 0)
		{
			this->OpenCustomStore(lpObj,5);
		}
	}
}

void CCustomStore::CommandCustomStoreOffline(LPOBJ lpObj,char* arg) // OK
{
	if(this->m_CustomStoreOfflineSwitch == 0)
	{
		return;
	}

	if(this->m_CustomStoreOfflineEnable[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreOfflineText1);
		return;
	}

	if(((gMasterSkillTree.CheckMasterLevel(lpObj)==0)?lpObj->Level:(lpObj->Level+lpObj->MasterLevel)) < this->m_CustomStoreOfflineRequireLevel[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreOfflineText4,this->m_CustomStoreOfflineRequireLevel[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->Reset < this->m_CustomStoreOfflineRequireReset[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreOfflineText5,this->m_CustomStoreOfflineRequireReset[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->PShopOpen == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreOfflineText2);
		return;
	}

	if(gMap[lpObj->Map].CheckAttr(lpObj->X,lpObj->Y,1) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreOfflineText3);
		return;
	}

	if(CC_MAP_RANGE(lpObj->Map) != 0 || IT_MAP_RANGE(lpObj->Map) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreOfflineText3);
		return;
	}

	if(this->m_CustomStoreOfflineMapZone != -1 && this->m_CustomStoreOfflineMapZone != lpObj->Map)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreOfflineText3);
		return;
	}

	lpObj->Socket = INVALID_SOCKET;

	lpObj->PShopCustomOffline = 1;

	lpObj->PShopCustomOfflineTime = 0;

	closesocket(lpObj->PerSocketContext->Socket);
}

void CCustomStore::OpenCustomStore(LPOBJ lpObj,int type) // OK
{
	if(gServerInfo.m_PersonalShopSwitch == 0)
	{
		return;
	}

	if(lpObj->PShopOpen != 0)
	{
		gPersonalShop.GCPShopOpenSend(lpObj->Index,0);
		return;
	}

	if(gMap[lpObj->Map].CheckAttr(lpObj->X,lpObj->Y,1) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreText2);
		return;
	}

	if(CC_MAP_RANGE(lpObj->Map) != 0 || IT_MAP_RANGE(lpObj->Map) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreText2);
		return;
	}

	if(this->m_CustomStoreMapZone != -1 && this->m_CustomStoreMapZone != lpObj->Map)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreText2);
		return;
	}

	if(gPersonalShop.CheckPersonalShopOpen(lpObj->Index) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,this->m_CustomStoreText3);
		return;
	}

	if(lpObj->Level <= 5)
	{
		gPersonalShop.GCPShopOpenSend(lpObj->Index,2);
		return;
	}

	lpObj->PShopOpen = 1;

	lpObj->PShopCustom = 1;

	lpObj->PShopCustomType = type;

	lpObj->PShopCustomOffline = 0;

	lpObj->PShopCustomOfflineTime = 0;

	switch(type)
	{
		case 0:
			memcpy(lpObj->PShopText,this->m_CustomStoreJoBName,sizeof(lpObj->PShopText));
			break;
		case 1:
			memcpy(lpObj->PShopText,this->m_CustomStoreJoSName,sizeof(lpObj->PShopText));
			break;
		case 2:
			memcpy(lpObj->PShopText,this->m_CustomStoreJoCName,sizeof(lpObj->PShopText));
			break;
		case 3:
			memcpy(lpObj->PShopText,this->m_CustomStoreWCCName,sizeof(lpObj->PShopText));
			break;
		case 4:
			memcpy(lpObj->PShopText,this->m_CustomStoreWCPName,sizeof(lpObj->PShopText));
			break;
		case 5:
			memcpy(lpObj->PShopText,this->m_CustomStoreWCGName,sizeof(lpObj->PShopText));
			break;
	}

	gPersonalShop.GCPShopOpenSend(lpObj->Index,1);

	PMSG_PSHOP_TEXT_CHANGE_SEND pMsg;

	pMsg.header.set(0x3F,0x10,sizeof(pMsg));

	pMsg.index[0] = SET_NUMBERHB(lpObj->Index);

	pMsg.index[1] = SET_NUMBERLB(lpObj->Index);

	memcpy(pMsg.text,lpObj->PShopText,sizeof(pMsg.text));

	memcpy(pMsg.name,lpObj->Name,sizeof(pMsg.name));

	DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
}

bool CCustomStore::OnPShopOpen(LPOBJ lpObj) // OK
{
	return ((lpObj->PShopCustom==0)?0:1);
}

void CCustomStore::OnPShopClose(LPOBJ lpObj) // OK
{
	if(lpObj->PShopCustom != 0)
	{
		lpObj->PShopCustom = 0;
		lpObj->PShopCustomType = 0;
	}

	if(lpObj->PShopCustomOffline == 1)
	{
		lpObj->PShopCustomOffline = 2;
		lpObj->PShopCustomOfflineTime = 5;
	}
}

void CCustomStore::OnPShopSecondProc(LPOBJ lpObj) // OK
{
	if(lpObj->PShopCustomOffline != 0)
	{
		if(lpObj->PShopCustomOffline == 2)
		{
			if((--lpObj->PShopCustomOfflineTime) == 0)
			{
				gObjDel(lpObj->Index);
				lpObj->PShopCustomOffline = 0;
				lpObj->PShopCustomOfflineTime = 0;
			}
		}

		lpObj->CheckSumTime = GetTickCount();
		lpObj->ConnectTickCount = GetTickCount();
		lpObj->PcPointPointTime = ((this->m_CustomStoreOfflineGPGain==0)?GetTickCount():lpObj->PcPointPointTime);
		lpObj->CashShopGoblinPointTime = ((this->m_CustomStoreOfflineGPGain==0)?GetTickCount():lpObj->CashShopGoblinPointTime);
	}
}

void CCustomStore::OnPShopAlreadyConnected(LPOBJ lpObj) // OK
{
	if(lpObj->PShopCustomOffline != 0)
	{
		gObjDel(lpObj->Index);
		lpObj->PShopCustomOffline = 0;
		lpObj->PShopCustomOfflineTime = 0;
	}
}

void CCustomStore::OnPShopItemList(LPOBJ lpObj,LPOBJ lpTarget) // OK
{
	if(lpTarget->PShopCustom != 0)
	{
		switch(lpTarget->PShopCustomType)
		{
			case 0:
				gNotice.GCNoticeSend(lpObj->Index,0,0,0,0,0,0,this->m_CustomStoreText4);
				break;
			case 1:
				gNotice.GCNoticeSend(lpObj->Index,0,0,0,0,0,0,this->m_CustomStoreText5);
				break;
			case 2:
				gNotice.GCNoticeSend(lpObj->Index,0,0,0,0,0,0,this->m_CustomStoreText6);
				break;
			case 3:
				gNotice.GCNoticeSend(lpObj->Index,0,0,0,0,0,0,this->m_CustomStoreText7);
				break;
			case 4:
				gNotice.GCNoticeSend(lpObj->Index,0,0,0,0,0,0,this->m_CustomStoreText8);
				break;
			case 5:
				gNotice.GCNoticeSend(lpObj->Index,0,0,0,0,0,0,this->m_CustomStoreText9);
				break;
		}
	}
}

bool CCustomStore::OnPShopBuyItemRecv(PMSG_PSHOP_BUY_ITEM_RECV* lpMsg,int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return 1;
	}

	int bIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);

	if(gObjIsConnectedGP(bIndex) == 0)
	{
		return 1;
	}

	LPOBJ lpTarget = &gObj[bIndex];

	if(lpTarget->PShopOpen == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,3);
		return 1;
	}

	if(lpTarget->PShopCustom == 0)
	{
		return 0;
	}

	if(lpTarget->PShopTransaction != 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,4);
		return 1;
	}

	if(INVENTORY_SHOP_RANGE(lpMsg->slot) == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,5);
		return 1;
	}

	gObjFixInventoryPointer(aIndex);

	if(lpObj->Transaction == 1)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,6);
		return 1;
	}

	char name[11] = {0};

	memcpy(name,lpMsg->name,sizeof(lpMsg->name));
	
	if(strcmp(name,lpTarget->Name) != 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,6);
		return 1;
	}

	if(lpTarget->Inventory[lpMsg->slot].IsItem() == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,6);
		return 1;
	}

	if(lpTarget->Inventory[lpMsg->slot].m_PShopValue <= 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,6);
		return 1;
	}

	#if(GAMESERVER_UPDATE>=501)

	if(lpTarget->PShopCustomType == 3 || lpTarget->PShopCustomType == 4 || lpTarget->PShopCustomType == 5)
	{
		gCashShop.GDCashShopRecievePointSend(aIndex,(DWORD)&CCustomStore::OnPShopBuyItemCallbackRecv,(DWORD)&gObj[bIndex],lpMsg->slot);
		return 1;
	}

	#else

	if(lpTarget->PShopCustomType == 3 || lpTarget->PShopCustomType == 4 || lpTarget->PShopCustomType == 5)
	{
		gPcPoint.GDPcPointRecievePointSend(aIndex,(DWORD)&CCustomStore::OnPShopBuyItemCallbackRecv,(DWORD)&gObj[bIndex],lpMsg->slot);
		return 1;
	}

	#endif

	int PShopJoBValue = ((lpTarget->PShopCustomType==0)?lpTarget->Inventory[lpMsg->slot].m_PShopValue:0);

	int PShopJoSValue = ((lpTarget->PShopCustomType==1)?lpTarget->Inventory[lpMsg->slot].m_PShopValue:0);

	int PShopJoCValue = ((lpTarget->PShopCustomType==2)?lpTarget->Inventory[lpMsg->slot].m_PShopValue:0);

	int RequireJewelCount[3] = {0};

	int PaymentJewelCount[3] = {0};

	int RequireJewelTable[3][4] = {0};

	int PaymentJewelTable[3][4] = {0};

	gPersonalShop.GetRequireJewelCount(lpObj,&RequireJewelCount[0],RequireJewelTable[0],0,PShopJoBValue);

	gPersonalShop.GetRequireJewelCount(lpObj,&RequireJewelCount[1],RequireJewelTable[1],1,PShopJoSValue);

	gPersonalShop.GetRequireJewelCount(lpObj,&RequireJewelCount[2],RequireJewelTable[2],2,PShopJoCValue);

	gPersonalShop.GetPaymentJewelCount(lpTarget,&PaymentJewelCount[0],PaymentJewelTable[0],0,PShopJoBValue);

	gPersonalShop.GetPaymentJewelCount(lpTarget,&PaymentJewelCount[1],PaymentJewelTable[1],1,PShopJoSValue);

	gPersonalShop.GetPaymentJewelCount(lpTarget,&PaymentJewelCount[2],PaymentJewelTable[2],2,PShopJoCValue);

	if(RequireJewelCount[0] < PShopJoBValue)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,7);
		return 1;
	}

	if(RequireJewelCount[1] < PShopJoSValue)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,7);
		return 1;
	}

	if(RequireJewelCount[2] < PShopJoCValue)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,7);
		return 1;
	}

	if(PShopJoBValue > 0 && RequireJewelTable[0][0] == 0 && RequireJewelTable[0][1] == 0 && RequireJewelTable[0][2] == 0 && RequireJewelTable[0][3] == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,7);
		return 1;
	}

	if(PShopJoSValue > 0 && RequireJewelTable[1][0] == 0 && RequireJewelTable[1][1] == 0 && RequireJewelTable[1][2] == 0 && RequireJewelTable[1][3] == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,7);
		return 1;
	}

	if(PShopJoCValue > 0 && RequireJewelTable[2][0] == 0 && RequireJewelTable[2][1] == 0 && RequireJewelTable[2][2] == 0 && RequireJewelTable[2][3] == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,7);
		return 1;
	}

	if(gItemManager.GetInventoryEmptySlotCount(lpTarget) < (PaymentJewelCount[0]+PaymentJewelCount[1]+PaymentJewelCount[2]))
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,7);
		return 1;
	}

	lpTarget->PShopTransaction = 1;

	BYTE result = gItemManager.InventoryInsertItem(aIndex,lpTarget->Inventory[lpMsg->slot]);

	if(result == 0xFF)
	{
		gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,0,8);
		return 1;
	}

	gLog.Output(LOG_TRADE,"[SellPesonalShopItem][%s][%s] - (Account: %s, Name: %s, Value: %d, JoBValue: %d, JoSValue: %d, JoCValue: %d, Index: %04d, Level: %02d, Serial: %08X, Option1: %01d, Option2: %01d, Option3: %01d, NewOption: %03d, JewelOfHarmonyOption: %03d, ItemOptionEx: %03d, SocketOption: %03d, %03d, %03d, %03d, %03d)",lpTarget->Account,lpTarget->Name,lpObj->Account,0,PShopJoBValue,PShopJoSValue,PShopJoCValue,lpTarget->Inventory[lpMsg->slot].m_Index,lpTarget->Inventory[lpMsg->slot].m_Level,lpTarget->Inventory[lpMsg->slot].m_Serial,lpTarget->Inventory[lpMsg->slot].m_Option1,lpTarget->Inventory[lpMsg->slot].m_Option2,lpTarget->Inventory[lpMsg->slot].m_Option3,lpTarget->Inventory[lpMsg->slot].m_NewOption,lpTarget->Inventory[lpMsg->slot].m_JewelOfHarmonyOption,lpTarget->Inventory[lpMsg->slot].m_ItemOptionEx,lpTarget->Inventory[lpMsg->slot].m_SocketOption[0],lpTarget->Inventory[lpMsg->slot].m_SocketOption[1],lpTarget->Inventory[lpMsg->slot].m_SocketOption[2],lpTarget->Inventory[lpMsg->slot].m_SocketOption[3],lpTarget->Inventory[lpMsg->slot].m_SocketOption[4]);

	gPersonalShop.SetRequireJewelCount(lpObj,RequireJewelTable[0],0);

	gPersonalShop.SetRequireJewelCount(lpObj,RequireJewelTable[1],1);

	gPersonalShop.SetRequireJewelCount(lpObj,RequireJewelTable[2],2);

	gPersonalShop.GCPShopBuyItemSend(aIndex,bIndex,result,1);

	GDCharacterInfoSaveSend(aIndex);

	gPersonalShop.SetPaymentJewelCount(lpTarget,PaymentJewelTable[0],0);

	gPersonalShop.SetPaymentJewelCount(lpTarget,PaymentJewelTable[1],1);

	gPersonalShop.SetPaymentJewelCount(lpTarget,PaymentJewelTable[2],2);

	gPersonalShop.GCPShopSellItemSend(bIndex,aIndex,lpMsg->slot);

	gItemManager.InventoryDelItem(bIndex,lpMsg->slot);
	gItemManager.GCItemDeleteSend(bIndex,lpMsg->slot,1);

	GDCharacterInfoSaveSend(bIndex);

	if(gPersonalShop.CheckPersonalShop(bIndex) == 0)
	{
		lpTarget->PShopItemChange = 1;
	}
	else
	{
		lpTarget->PShopOpen = 0;
		memset(lpTarget->PShopText,0,sizeof(lpTarget->PShopText));
		gPersonalShop.GCPShopCloseSend(bIndex,1);
		this->OnPShopClose(lpTarget);
	}

	lpTarget->PShopTransaction = 0;

	return 1;
}

void CCustomStore::OnPShopBuyItemCallbackRecv(LPOBJ lpObj,LPOBJ lpTarget,DWORD slot,DWORD WCoinC,DWORD WCoinP,DWORD GoblinPoint) // OK
{
	if(gObjIsConnectedGP(lpTarget->Index) == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,0,3);
		return;
	}

	if(lpTarget->PShopOpen == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,0,3);
		return;
	}

	if(lpTarget->PShopTransaction != 0)
	{
		gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,0,4);
		return;
	}

	if(lpTarget->Inventory[slot].IsItem() == 0)
	{
		gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,0,6);
		return;
	}

	DWORD PShopWCCValue = ((lpTarget->PShopCustomType==3)?lpTarget->Inventory[slot].m_PShopValue:0);

	DWORD PShopWCPValue = ((lpTarget->PShopCustomType==4)?lpTarget->Inventory[slot].m_PShopValue:0);

	DWORD PShopWGPValue = ((lpTarget->PShopCustomType==5)?lpTarget->Inventory[slot].m_PShopValue:0);

	if(WCoinC < PShopWCCValue)
	{
		gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,0,7);
		return;
	}

	if(WCoinP < PShopWCPValue)
	{
		gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,0,7);
		return;
	}

	if(GoblinPoint < PShopWGPValue)
	{
		gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,0,7);
		return;
	}

	lpTarget->PShopTransaction = 1;

	BYTE result = gItemManager.InventoryInsertItem(lpObj->Index,lpTarget->Inventory[slot]);

	if(result == 0xFF)
	{
		gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,0,8);
		return;
	}

	gLog.Output(LOG_TRADE,"[SellPesonalShopItem][%s][%s] - (Account: %s, Name: %s, Value: %d, WCCValue: %d, WCPValue: %d, WGPValue: %d, Index: %04d, Level: %02d, Serial: %08X, Option1: %01d, Option2: %01d, Option3: %01d, NewOption: %03d, JewelOfHarmonyOption: %03d, ItemOptionEx: %03d, SocketOption: %03d, %03d, %03d, %03d, %03d)",lpTarget->Account,lpTarget->Name,lpObj->Account,0,PShopWCCValue,PShopWCPValue,PShopWGPValue,lpTarget->Inventory[slot].m_Index,lpTarget->Inventory[slot].m_Level,lpTarget->Inventory[slot].m_Serial,lpTarget->Inventory[slot].m_Option1,lpTarget->Inventory[slot].m_Option2,lpTarget->Inventory[slot].m_Option3,lpTarget->Inventory[slot].m_NewOption,lpTarget->Inventory[slot].m_JewelOfHarmonyOption,lpTarget->Inventory[slot].m_ItemOptionEx,lpTarget->Inventory[slot].m_SocketOption[0],lpTarget->Inventory[slot].m_SocketOption[1],lpTarget->Inventory[slot].m_SocketOption[2],lpTarget->Inventory[slot].m_SocketOption[3],lpTarget->Inventory[slot].m_SocketOption[4]);

	#if(GAMESERVER_UPDATE>=501)

	gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,PShopWCCValue,PShopWCPValue,PShopWGPValue);

	#else

	gPcPoint.GDPcPointSubPointSaveSend(lpObj->Index,PShopWGPValue);

	gPcPoint.GDPcPointPointSend(lpObj->Index);

	#endif

	gPersonalShop.GCPShopBuyItemSend(lpObj->Index,lpTarget->Index,result,1);

	GDCharacterInfoSaveSend(lpObj->Index);

	#if(GAMESERVER_UPDATE>=501)

	gCashShop.GDCashShopAddPointSaveSend(lpTarget->Index,0,PShopWCCValue,PShopWCPValue,PShopWGPValue);

	#else

	gPcPoint.GDPcPointAddPointSaveSend(lpTarget->Index,PShopWGPValue);

	gPcPoint.GDPcPointPointSend(lpTarget->Index);

	#endif

	gPersonalShop.GCPShopSellItemSend(lpTarget->Index,lpObj->Index,slot);

	gItemManager.InventoryDelItem(lpTarget->Index,(BYTE)slot);
	gItemManager.GCItemDeleteSend(lpTarget->Index,(BYTE)slot,1);

	GDCharacterInfoSaveSend(lpTarget->Index);

	if(gPersonalShop.CheckPersonalShop(lpTarget->Index) == 0)
	{
		lpTarget->PShopItemChange = 1;
	}
	else
	{
		lpTarget->PShopOpen = 0;
		memset(lpTarget->PShopText,0,sizeof(lpTarget->PShopText));
		gPersonalShop.GCPShopCloseSend(lpTarget->Index,1);
		gCustomStore.OnPShopClose(lpTarget);
	}

	lpTarget->PShopTransaction = 0;
}
