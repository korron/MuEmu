// Queue.h: interface for the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "CriticalSection.h"

struct QUEUE_INFO
{
	WORD index;
	BYTE head;
	BYTE* buff;
	DWORD size;
	QUEUE_INFO* QueueNext;
};

class CQueue
{
public:
	CQueue(int size);
	virtual ~CQueue();
	DWORD GetQueueSize();
	bool AddQueueTail(QUEUE_INFO* lpInfo);
	QUEUE_INFO* GetQueueHead();
	bool AddToQueue(WORD index,BYTE head,BYTE* lpMsg,DWORD size);
	bool GetFromQueue(WORD* index,BYTE* head,BYTE* lpMsg,DWORD* size);
	void ClearQueue();
private:
	DWORD m_QueueSize;
	DWORD m_QueueMaxSize;
	QUEUE_INFO* m_QueueHead;
	QUEUE_INFO* m_QueueTail;
	CCriticalSection m_critical;
};
