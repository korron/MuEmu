#include "stdafx.h"
#include "Camera.h"
#include "Import.h"
#include "TMemory.h"
#include "Interface.h"
#include "User.h"
// ----------------------------------------------------------------------------------------------

Camera	gCamera;
// ----------------------------------------------------------------------------------------------

Camera::Camera()
{
	this->Default.Zoom = *(float*)oCam_Zoom;
	this->Default.RotationY = *(float*)oCam_RotY;
	this->Default.RotationZ = *(float*)oCam_RotZDef;
	this->Default.PositionZ = *(float*)oCam_PosZDef;
	this->Default.ClipX = *(double*)oCam_ClipX;
	this->Default.ClipY = *(float*)oCam_ClipY;
	this->Default.ClipZ = *(double*)oCam_ClipZ;
	this->Default.ClipX2 = *(double*)oCam_ClipX2;
	this->Default.ClipY2 = *(float*)oCam_ClipY2;
	this->Default.ClipZ2 = *(float*)oCam_ClipZ2;
	this->Default.ClipGL = *(float*)oCam_ClipGL;
	// ----
	this->InMove = 0;
	this->IsActive = 0;
	this->RotateMode = 2;
	this->ZoomPercent = 0.0;
	this->TempCursorX = 0;
	this->TempCursorY = 0;
	// ----
	this->ZoomPercent = this->Default.Zoom / ((float)ZOOM_MAX / 100.0f);
}
// ----------------------------------------------------------------------------------------------

Camera::~Camera()
{

}
// ----------------------------------------------------------------------------------------------

void Camera::Init()
{
	if (pPlayerState != GameProcess)
	{
		return;
	}
	// ----
	SetFloat((LPVOID)oCam_Zoom, this->Default.Zoom);
	SetFloat((LPVOID)oCam_RotY, this->Default.RotationY);
	SetFloat((LPVOID)oCam_RotZ, this->Default.RotationZ);
	SetDouble((LPVOID)oCam_PosZ, this->Default.PositionZ);

	SetDouble((LPVOID)oCam_ClipX, this->Default.ClipX + 800);
	SetFloat((LPVOID)oCam_ClipGL, this->Default.ClipGL + 500);

	SetFloat((LPVOID)oCam_ClipY, this->Default.ClipY);
	SetDouble((LPVOID)oCam_ClipZ, this->Default.ClipZ);
	SetDouble((LPVOID)oCam_ClipX2, this->Default.ClipX2);
	SetFloat((LPVOID)oCam_ClipY2, this->Default.ClipY2);
	SetFloat((LPVOID)oCam_ClipZ2, this->Default.ClipZ2);
	// ----
	this->ZoomPercent = *(float*)oCam_Zoom / ((float)ZOOM_MAX / 100.0f);
}
// ----------------------------------------------------------------------------------------------

void Camera::Switch()
{
	if (pPlayerState != GameProcess)
	{
		return;
	}
	// ----
	this->IsActive = !this->IsActive;
}
// ----------------------------------------------------------------------------------------------

void Camera::Run(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam)
{
	if (pMapNumber == 30 || pMapNumber == 31)
	{
		this->IsActive = false;
		this->Init();
	}
	// ----
	switch (wParam)
	{
	case WM_MOUSEWHEEL:
	{
						  if (!this->IsActive || gInterface.CheckWindow(MoveList))
						  {
							  return;
						  }
						  // ----
						  if ((int)Mouse->mouseData > 0)
						  {
							  if (*(float*)oCam_Zoom < ZOOM_MAX)
							  {
								  SetFloat((LPVOID)oCam_Zoom, *(float*)oCam_Zoom + ZOOM_INTER);
							  }
							  else
							  {
								  SetFloat((LPVOID)oCam_Zoom, (float)ZOOM_MAX);
							  }
						  }
						  else if ((int)Mouse->mouseData < 0)
						  {
							  if (*(float*)oCam_Zoom > ZOOM_MIN)
							  {
								  SetFloat((LPVOID)oCam_Zoom, *(float*)oCam_Zoom - ZOOM_INTER);
							  }
							  else
							  {
								  SetFloat((LPVOID)oCam_Zoom, (float)ZOOM_MIN);
							  }
						  }
						  // ----
						  this->ZoomPercent = *(float*)oCam_Zoom / ((float)ZOOM_MAX / 100.0f);
						  // ----
						  SetDouble((LPVOID)oCam_ClipX, PERCF(PERCF(this->Default.ClipX, 800), this->ZoomPercent));
						  SetFloat((LPVOID)oCam_ClipY, PERCF(PERCF(this->Default.ClipY, 285), this->ZoomPercent));
						  SetDouble((LPVOID)oCam_ClipZ, PERCF(PERCF(this->Default.ClipZ, -395), this->ZoomPercent));
						  SetDouble((LPVOID)oCam_ClipX2, PERCF(PERCF(this->Default.ClipX2, 235), this->ZoomPercent));
						  SetFloat((LPVOID)oCam_ClipY2, PERCF(PERCF(this->Default.ClipY2, 195), this->ZoomPercent));
						  SetFloat((LPVOID)oCam_ClipZ2, PERCF(PERCF(this->Default.ClipZ2, -4000), this->ZoomPercent));
						  SetFloat((LPVOID)oCam_ClipGL, PERCF(PERCF(this->Default.ClipGL, 450), this->ZoomPercent));
	}
		break;
		// --
	case WM_MBUTTONDOWN:
	{
						   this->InMove = true;
	}
		break;
		// --
	case WM_MBUTTONUP:
	{
						 this->InMove = false;
	}
		break;
	}
}
// ----------------------------------------------------------------------------------------------

void Camera::Rotate()
{
	if (!this->IsActive)
	{
		return;
	}
	// ----
	if (this->RotateMode == 1) //-> Auto rotation
	{
		if (gObjUser.m_CursorX <= 150)
		{
			SetFloat((LPVOID)oCam_RotZ, *(float*)oCam_RotZ - ROTATION_SENS);
		}
		else if (gObjUser.m_CursorX >= 500)
		{
			SetFloat((LPVOID)oCam_RotZ, *(float*)oCam_RotZ + ROTATION_SENS);
		}
	}
	else if (this->RotateMode == 2 && this->InMove) //-> Manual rotation
	{
		if (this->TempCursorX < gObjUser.m_CursorX)
		{
			SetFloat((LPVOID)oCam_RotZ, *(float*)oCam_RotZ + ROTATION_SENS);
		}
		else if (this->TempCursorX > gObjUser.m_CursorX)
		{
			SetFloat((LPVOID)oCam_RotZ, *(float*)oCam_RotZ - ROTATION_SENS);
		}
		// ----
		this->TempCursorX = gObjUser.m_CursorX;
	}
}
// ----------------------------------------------------------------------------------------------

void Camera::Position()
{
	if (!this->IsActive)
	{
		return;
	}
	// ----
	if (this->InMove)
	{
		if (this->TempCursorY < gObjUser.m_CursorY)
		{
			if (*(float*)oCam_RotY < -45)
			{
				SetDouble((LPVOID)oCam_PosZ, *(double*)oCam_PosZ - 44);
				SetFloat((LPVOID)oCam_RotY, *(float*)oCam_RotY + (double)2.42);
			}
		}
		else if (this->TempCursorY > gObjUser.m_CursorY)
		{
			if (*(float*)oCam_RotY > -90)
			{
				SetDouble((LPVOID)oCam_PosZ, *(double*)oCam_PosZ + 44);
				SetFloat((LPVOID)oCam_RotY, *(float*)oCam_RotY - (double)2.42);
			}
		}
		// ----
		this->TempCursorY = gObjUser.m_CursorY;
	}
}