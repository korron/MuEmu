// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_SCREEN_STATE 6

struct CAMERA_ZOOM
{
	float MinPercent;
	float MaxPercent;
	float MinLimit;
	float MaxLimit;
	float Precision;
};

struct CAMERA_ADDR
{
	float* Zoom;
	float* RotX;
	float* RotY;
	double* PosZ;
	double* ClipX[2];
	float* ClipY[2];
	float* ClipGL;
};

struct CAMERA_INFO
{
	int IsLoad;
	float Zoom;
	float RotX;
	float RotY;
	double PosZ;
	double ClipX[2];
	float ClipY[2];
	float ClipGL;
};

class CCamera
{
public:
	CCamera();
	void Init();
	void Toggle();
	void Restore();
	void SetIsMove(BOOL IsMove);
	void SetCursorX(LONG CursorX);
	void SetCursorY(LONG CursorY);
	void Zoom(MOUSEHOOKSTRUCTEX* lpMouse);
	void Move(MOUSEHOOKSTRUCTEX* lpMouse);
	void SetCurrentValue();
	void SetDefaultValue();
	static DWORD WINAPI CheckCameraStateThread(CCamera* lpCamera);
private:
	BOOL m_Enable;
	BOOL m_IsMove;
	LONG m_CursorX;
	LONG m_CursorY;
	CAMERA_ZOOM m_Zoom;
	CAMERA_ADDR m_Address;
	CAMERA_INFO m_Default[MAX_SCREEN_STATE];
};

extern CCamera gCamera;
