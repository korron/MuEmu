// CustomJewel.cpp: implementation of the CCustomJewel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomJewel.h"
#include "MemScript.h"

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

void CCustomJewel::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}
		
			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_JEWEL_INFO info;

					memset(&info,0,sizeof(info));

					info.Index = lpMemScript->GetNumber();

					info.ItemIndex = lpMemScript->GetAsNumber();

					info.MinItemLevel = lpMemScript->GetAsNumber();

					info.MaxItemLevel = lpMemScript->GetAsNumber();

					info.MaxItemOption1 = lpMemScript->GetAsNumber();

					info.MaxItemOption2 = lpMemScript->GetAsNumber();

					info.MinItemOption3 = lpMemScript->GetAsNumber();

					info.MaxItemOption3 = lpMemScript->GetAsNumber();

					info.MinItemNewOption = lpMemScript->GetAsNumber();

					info.MaxItemNewOption = lpMemScript->GetAsNumber();

					info.MaxItemSetOption = lpMemScript->GetAsNumber();

					info.MinItemSocketOption = lpMemScript->GetAsNumber();

					info.MaxItemSocketOption = lpMemScript->GetAsNumber();

					info.EnableSlotWeapon = lpMemScript->GetAsNumber();

					info.EnableSlotArmor = lpMemScript->GetAsNumber();

					info.EnableSlotWing = lpMemScript->GetAsNumber();

					info.SuccessRate[0] = lpMemScript->GetAsNumber();

					info.SuccessRate[1] = lpMemScript->GetAsNumber();

					info.SuccessRate[2] = lpMemScript->GetAsNumber();

					info.SuccessRate[3] = lpMemScript->GetAsNumber();

					info.SalePrice = lpMemScript->GetAsNumber();

					strcpy_s(info.ModelName,lpMemScript->GetAsString());

					this->SetInfo(info);
				}
				else if(section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_JEWEL_SUCCESS_INFO info;

					memset(&info,0,sizeof(info));

					info.Index = lpMemScript->GetNumber();

					info.Level = lpMemScript->GetAsNumber();

					info.Option1 = lpMemScript->GetAsNumber();

					info.Option2 = lpMemScript->GetAsNumber();

					info.Option3 = lpMemScript->GetAsNumber();

					info.NewOption = lpMemScript->GetAsNumber();

					info.SetOption = lpMemScript->GetAsNumber();

					info.SocketOption = lpMemScript->GetAsNumber();
				}
				else if(section == 2)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_JEWEL_FAILURE_INFO info;

					memset(&info,0,sizeof(info));

					info.Index = lpMemScript->GetNumber();

					info.Level = lpMemScript->GetAsNumber();

					info.Option1 = lpMemScript->GetAsNumber();

					info.Option2 = lpMemScript->GetAsNumber();

					info.Option3 = lpMemScript->GetAsNumber();

					info.NewOption = lpMemScript->GetAsNumber();

					info.SetOption = lpMemScript->GetAsNumber();

					info.SocketOption = lpMemScript->GetAsNumber();
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomJewel::SetInfo(CUSTOM_JEWEL_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_JEWEL)
	{
		return;
	}

	this->m_CustomJewelInfo[info.Index] = info;
}
