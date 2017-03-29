#ifndef _HIDMANAGER_H_
#define _HIDMANAGER_H_
#pragma once

struct HARDWARE_ID_INFO
{
	char HardwareId[36];
	DWORD LastDetectionTime;
};

class CHidManager
{
public:
	CHidManager();
	virtual ~CHidManager();
	bool CheckHardwareId(char HardwareId[36]);
	void InsertHardwareId(char HardwareId[36]);
	void ClearHardwareId();
private:
	std::vector<HARDWARE_ID_INFO> m_HardwareIdInfo;
};

extern CHidManager gHidManager;
#endif