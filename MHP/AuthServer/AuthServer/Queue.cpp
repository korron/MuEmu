// Queue.cpp: implementation of the CQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Queue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueue::CQueue(int size) // OK
{
	this->m_QueueSize = 0;
	this->m_QueueMaxSize = size;
	this->m_QueueHead = 0;
	this->m_QueueTail = 0;
}

CQueue::~CQueue() // OK
{
	this->ClearQueue();
}

DWORD CQueue::GetQueueSize() // OK
{
	DWORD size = 0;

	this->m_critical.lock();

	size = this->m_QueueSize;

	this->m_critical.unlock();

	return size;
}

bool CQueue::AddQueueTail(QUEUE_INFO* lpInfo) // OK
{
	bool result = 0;

	this->m_critical.lock();

	if(this->m_QueueSize < this->m_QueueMaxSize)
	{
		lpInfo->QueueNext = 0;

		if(this->m_QueueHead == 0)
		{
			this->m_QueueHead = lpInfo;
		}
		else
		{
			this->m_QueueTail->QueueNext = lpInfo;
		}

		this->m_QueueTail = lpInfo;
		this->m_QueueSize++;
		result = 1;
	}

	this->m_critical.unlock();

	return result;
}

QUEUE_INFO* CQueue::GetQueueHead() // OK
{
	QUEUE_INFO* lpInfo = 0;

	this->m_critical.lock();

	if(this->m_QueueHead != 0)
	{
		lpInfo = this->m_QueueHead;

		if(this->m_QueueHead->QueueNext != 0)
		{
			this->m_QueueHead = this->m_QueueHead->QueueNext;
		}
		else
		{
			this->m_QueueHead = 0;
			this->m_QueueTail = 0;
		}

		this->m_QueueSize--;
	}

	this->m_critical.unlock();

	return lpInfo;
}

bool CQueue::AddToQueue(WORD index,BYTE head,BYTE* lpMsg,DWORD size) // OK
{
	bool result = 0;

	this->m_critical.lock();

	QUEUE_INFO* lpInfo = (QUEUE_INFO*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(QUEUE_INFO));

	if(lpInfo != 0)
	{
		BYTE* buff = (BYTE*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,size);

		if(buff != 0)
		{
			memcpy(buff,lpMsg,size);

			lpInfo->index = index;
			lpInfo->head = head;
			lpInfo->buff = buff;
			lpInfo->size = size;

			if(this->AddQueueTail(lpInfo) != 0)
			{
				result = 1;
			}
		}
		else
		{
			HeapFree(GetProcessHeap(),0,buff);
			HeapFree(GetProcessHeap(),0,lpInfo);
		}
	}
	else
	{
		HeapFree(GetProcessHeap(),0,lpInfo);
	}

	this->m_critical.unlock();

	return result;
}

bool CQueue::GetFromQueue(WORD* index,BYTE* head,BYTE* lpMsg,DWORD* size) // OK
{
	bool result = 0;

	this->m_critical.lock();
	
	QUEUE_INFO* lpInfo = this->GetQueueHead();

	if(lpInfo != 0)
	{
		(*index) = lpInfo->index;

		(*head) = lpInfo->head;

		memcpy(lpMsg,lpInfo->buff,lpInfo->size);

		(*size) = lpInfo->size;

		HeapFree(GetProcessHeap(),0,lpInfo->buff);
		HeapFree(GetProcessHeap(),0,lpInfo);

		result = 1;
	}

	this->m_critical.unlock();

	return result;
}

void CQueue::ClearQueue() // OK
{
	this->m_critical.lock();

	while(true)
	{
		QUEUE_INFO* lpInfo = this->GetQueueHead();

		if(lpInfo == 0)
		{
			break;
		}

		HeapFree(GetProcessHeap(),0,lpInfo->buff);
		HeapFree(GetProcessHeap(),0,lpInfo);
	}

	this->m_critical.unlock();
}
