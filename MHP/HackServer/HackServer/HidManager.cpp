#include "StdAfx.h"
#include "HidManager.h"
#include "ServerInfo.h"

CHidManager gHidManager;

CHidManager::CHidManager()
{
}

CHidManager::~CHidManager()
{
}

bool CHidManager::CheckHardwareId(char HardwareId[36]) // OK
{
	if(gServerInfo.m_DetectionLockTime == 0)
	{
		return 1;
	}

	this->ClearHardwareId();

	for(DWORD i = 0; i < m_HardwareIdInfo.size(); i++)
	{
		if(memcmp(m_HardwareIdInfo[i].HardwareId, HardwareId,sizeof(m_HardwareIdInfo[i].HardwareId)) == 0)
		{
			return 0;
		}
	}

	return 1;
}

void CHidManager::InsertHardwareId(char HardwareId[36])
{
	HARDWARE_ID_INFO info;

	memcpy(info.HardwareId,HardwareId,sizeof(info.HardwareId));

	info.LastDetectionTime = GetTickCount();

	this->m_HardwareIdInfo.push_back(info);
}

void CHidManager::ClearHardwareId()
{
	for(std::vector<HARDWARE_ID_INFO>::iterator it=this->m_HardwareIdInfo.begin();it != this->m_HardwareIdInfo.end();it++)
	{
		if((GetTickCount()-it->LastDetectionTime) > (DWORD)(gServerInfo.m_DetectionLockTime*1000))
		{
			it = this->m_HardwareIdInfo.erase(it);
			break;
		}
	}
}
