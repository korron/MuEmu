// Camera.cpp: implementation of the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Camera.h"
#include "Offset.h"
#include "Util.h"

CCamera gCamera;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamera::CCamera() // OK
{
	this->m_Enable = 0;

	this->m_IsMove = 0;

	this->m_CursorX = 0;

	this->m_CursorY = 0;

	this->m_Zoom.MinPercent = 50.0;

	this->m_Zoom.MaxPercent = 130.0;

	this->m_Zoom.Precision = 2.0;

	this->m_Address.RotX = (float*)0x08B156B8;

	this->m_Address.RotY = (float*)0x01001BD0;

	this->m_Address.PosZ = (double*)0x00FFFA60;

	this->m_Address.ClipX[0] = (double*)0x01006BD0;

	this->m_Address.ClipX[1] = (double*)0x01006C00;

	this->m_Address.ClipY[0] = (float*)0x01001B88;

	this->m_Address.ClipY[1] = (float*)0x01006C10;

	this->m_Address.ClipGL = (float*)0x00FFFBD4;

	for(int n=0;n < MAX_SCREEN_STATE;n++){this->m_Default[n].IsLoad = 0;}
}

void CCamera::Init() // OK
{
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)CCamera::CheckCameraStateThread,this,0,0);
}

void CCamera::Toggle() // OK
{
	if(*(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_Enable ^= 1;
	}
}

void CCamera::Restore() // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->SetDefaultValue();
	}
}

void CCamera::SetIsMove(BOOL IsMove) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_IsMove = IsMove;
	}
}

void CCamera::SetCursorX(LONG CursorX) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorX = CursorX;
	}
}

void CCamera::SetCursorY(LONG CursorY) // OK
{
	if(this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorY = CursorY;
	}
}

void CCamera::Zoom(MOUSEHOOKSTRUCTEX* lpMouse) // OK
{
	if(this->m_Enable == 0 || this->m_IsMove != 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	this->m_Zoom.MinLimit = (this->m_Default[*(DWORD*)(MAIN_SCREEN_STATE)].Zoom/100)*this->m_Zoom.MinPercent;

	this->m_Zoom.MaxLimit = (this->m_Default[*(DWORD*)(MAIN_SCREEN_STATE)].Zoom/100)*this->m_Zoom.MaxPercent;

	if(((int)lpMouse->mouseData) > 0)
	{
		if((*this->m_Address.Zoom) >= this->m_Zoom.MinLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom,((*this->m_Address.Zoom)-this->m_Zoom.Precision));
		}
	}

	if(((int)lpMouse->mouseData) < 0)
	{
		if((*this->m_Address.Zoom) <= this->m_Zoom.MaxLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom,((*this->m_Address.Zoom)+this->m_Zoom.Precision));
		}
	}

	this->SetCurrentValue();
}

void CCamera::Move(MOUSEHOOKSTRUCTEX* lpMouse) // OK
{
	if(this->m_Enable == 0 || this->m_IsMove == 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if(this->m_CursorX < lpMouse->pt.x)
	{
		if((*this->m_Address.RotX) > 309.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX,-45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX,((*this->m_Address.RotX)+6.0f));
		}
	}
	
	if(this->m_CursorX > lpMouse->pt.x)
	{
		if((*this->m_Address.RotX) < -417.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX,-45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX,((*this->m_Address.RotX)-6.0f));
		}
	}

	if(this->m_CursorY < lpMouse->pt.y)
	{
		if((*this->m_Address.RotY) < -45.0f)
		{
			SetFloat((DWORD)this->m_Address.RotY,((*this->m_Address.RotY)+2.420f));
			SetDouble((DWORD)this->m_Address.PosZ,((*this->m_Address.PosZ)-44.0f));
		}
	}

	if(this->m_CursorY > lpMouse->pt.y)
	{
		if((*this->m_Address.RotY) > -90.0f)
		{
			SetFloat((DWORD)this->m_Address.RotY,((*this->m_Address.RotY)-2.420f));
			SetDouble((DWORD)this->m_Address.PosZ,((*this->m_Address.PosZ)+44.0f));
		}
	}

	this->m_CursorX = lpMouse->pt.x;

	this->m_CursorY = lpMouse->pt.y;

	this->SetCurrentValue();
}

void CCamera::SetCurrentValue() // OK
{
	SetDouble((DWORD)this->m_Address.ClipX[0],(4190.0f+(abs(((*this->m_Address.PosZ)-150.0f))*3.0f)));

	SetDouble((DWORD)this->m_Address.ClipX[1],(4190.0f+(abs(((*this->m_Address.PosZ)-150.0f))*3.0f)));

	SetFloat((DWORD)this->m_Address.ClipY[0],(5400.0f+(((float)abs(((*this->m_Address.PosZ)-150.0f)))*3.0f)));

	SetFloat((DWORD)this->m_Address.ClipY[1],(5400.0f+(((float)abs(((*this->m_Address.PosZ)-150.0f)))*3.0f)));

	SetFloat((DWORD)this->m_Address.ClipGL,(2100.0f+(((float)abs(((*this->m_Address.PosZ)-150.0f)))*3.0f)));
}

void CCamera::SetDefaultValue() // OK
{
	if(*(DWORD*)(MAIN_SCREEN_STATE) < MAX_SCREEN_STATE)
	{
		if(this->m_Default[*(DWORD*)(MAIN_SCREEN_STATE)].IsLoad != 0)
		{
			CAMERA_INFO* lpInfo = &this->m_Default[*(DWORD*)(MAIN_SCREEN_STATE)];

			SetFloat((DWORD)this->m_Address.Zoom,lpInfo->Zoom);

			SetFloat((DWORD)this->m_Address.RotX,lpInfo->RotX);

			SetFloat((DWORD)this->m_Address.RotY,lpInfo->RotY);

			SetDouble((DWORD)this->m_Address.PosZ,lpInfo->PosZ);

			SetDouble((DWORD)this->m_Address.ClipX[0],lpInfo->ClipX[0]);

			SetDouble((DWORD)this->m_Address.ClipX[1],lpInfo->ClipX[1]);

			SetFloat((DWORD)this->m_Address.ClipY[0],lpInfo->ClipY[0]);

			SetFloat((DWORD)this->m_Address.ClipY[1],lpInfo->ClipY[1]);

			SetFloat((DWORD)this->m_Address.ClipGL,lpInfo->ClipGL);
		}
	}
}

DWORD WINAPI CCamera::CheckCameraStateThread(CCamera* lpCamera) // OK
{
	DWORD CurrentScreenState = 0;

	while(!SleepEx(500,0))
	{
		if(*(DWORD*)(MAIN_SCREEN_STATE) < MAX_SCREEN_STATE)
		{
			if(lpCamera->m_Default[*(DWORD*)(MAIN_SCREEN_STATE)].IsLoad == 0)
			{
				lpCamera->m_Address.Zoom = (float*)(((DWORD(*)())0x004E2379)()+0x20);

				CAMERA_INFO* lpInfo = &lpCamera->m_Default[*(DWORD*)(MAIN_SCREEN_STATE)];

				lpInfo->IsLoad = 1;

				lpInfo->Zoom = (*lpCamera->m_Address.Zoom);

				lpInfo->RotX = (*lpCamera->m_Address.RotX);

				lpInfo->RotY = (*lpCamera->m_Address.RotY);

				lpInfo->PosZ = (*lpCamera->m_Address.PosZ);

				lpInfo->ClipX[0] = (*lpCamera->m_Address.ClipX[0]);

				lpInfo->ClipX[1] = (*lpCamera->m_Address.ClipX[1]);

				lpInfo->ClipY[0] = (*lpCamera->m_Address.ClipY[0]);

				lpInfo->ClipY[1] = (*lpCamera->m_Address.ClipY[1]);

				lpInfo->ClipGL = (*lpCamera->m_Address.ClipGL);
			}

			if(*(DWORD*)(MAIN_SCREEN_STATE) != CurrentScreenState)
			{
				lpCamera->m_Enable = 0;

				lpCamera->m_IsMove = 0;

				lpCamera->m_CursorX = 0;

				lpCamera->m_CursorY = 0;

				lpCamera->SetDefaultValue();

				SetDword((DWORD)&CurrentScreenState,*(DWORD*)(MAIN_SCREEN_STATE));
			}
		}
	}

	return 0;
}
