// ProcessQuery.h: interface for the CProcessQuery class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

typedef LONG KPRIORITY;

typedef NTSTATUS(WINAPI*NTQUERYSYSTEMINFORMATION)(SYSTEM_INFORMATION_CLASS,PVOID,ULONG,PULONG);

#define STATUS_SUCCESS ((NTSTATUS)0x00000000)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004)
#define STATUS_DATA_ERROR ((NTSTATUS)0xC000003E)
#define SystemExtendedProcessInformation ((SYSTEM_INFORMATION_CLASS)57)
#define SystemHandleInformation ((SYSTEM_INFORMATION_CLASS)16)
#define SystemExtendedHandleInformation ((SYSTEM_INFORMATION_CLASS)64)
#define SystemKernelDebuggerInformation ((SYSTEM_INFORMATION_CLASS)35)

enum THREAD_STATE
{
	Running = 2,
	Waiting = 5,
};

enum KWAIT_REASON
{
	Executive = 0,
	FreePage = 1,
	PageIn = 2,
	PoolAllocation = 3,
	DelayExecution = 4,
	Suspended = 5,
	UserRequest = 6,
	WrExecutive = 7,
	WrFreePage = 8,
	WrPageIn = 9,
	WrPoolAllocation = 10,
	WrDelayExecution = 11,
	WrSuspended = 12,
	WrUserRequest = 13,
	WrEventPair = 14,
	WrQueue = 15,
	WrLpcReceive = 16,
	WrLpcReply = 17,
	WrVirtualMemory = 18,
	WrPageOut = 19,
	WrRendezvous = 20,
	Spare2 = 21,
	Spare3 = 22,
	Spare4 = 23,
	Spare5 = 24,
	WrCalloutStack = 25,
	WrKernel = 26,
	WrResource = 27,
	WrPushLock = 28,
	WrMutex = 29,
	WrQuantumEnd = 30,
	WrDispatchInt = 31,
	WrPreempted = 32,
	WrYieldExecution = 33,
	WrFastMutex = 34,
	WrGuardedMutex = 35,
	WrRundown = 36,
	MaximumWaitReason = 37,
};

struct CLIENT_ID
{
	PVOID UniqueProcess;
	PVOID UniqueThread;
};

struct SYSTEM_THREAD_INFO
{
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	KPRIORITY Priority;
	LONG BasePriority;
	ULONG ContextSwitches;
	ULONG ThreadState;
	KWAIT_REASON WaitReason;
};

struct SYSTEM_EXTENDED_THREAD_INFO
{
	SYSTEM_THREAD_INFO ThreadInfo;
	PVOID StackBase;
	PVOID StackLimit;
	PVOID Win32StartAddress;
	PVOID TebAddress; // since VISTA
	ULONG Reserved1;
	ULONG Reserved2;
	ULONG Reserved3;
};

struct SYSTEM_PROCESS_INFO
{
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
	ULONG HardFaultCount; // since WIN7
	ULONG NumberOfThreadsHighWatermark; // since WIN7
	ULONGLONG CycleTime; // since WIN7
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	KPRIORITY BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
	SYSTEM_THREAD_INFO Threads[1];
};

struct SYSTEM_EXTENDED_PROCESS_INFO
{
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
	ULONG HardFaultCount; // since WIN7
	ULONG NumberOfThreadsHighWatermark; // since WIN7
	ULONGLONG CycleTime; // since WIN7
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	KPRIORITY BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
	SYSTEM_EXTENDED_THREAD_INFO Threads[1];
};

struct SYSTEM_HANDLE_ENTRY_INFO
{
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PVOID Object;
	ULONG GrantedAccess;
};

struct SYSTEM_HANDLE_INFO
{
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_ENTRY_INFO Handles[1];
};

struct SYSTEM_HANDLE_ENTRY_INFO_EX
{
	PVOID Object;
	ULONG UniqueProcessId;
	ULONG HandleValue;
	ULONG GrantedAccess;
	USHORT CreatorBackTraceIndex;
	USHORT ObjectTypeIndex;
	ULONG HandleAttributes;
	ULONG Reserved;
};

struct SYSTEM_HANDLE_INFO_EX
{
	ULONG NumberOfHandles;
	ULONG Reserved;
	SYSTEM_HANDLE_ENTRY_INFO_EX Handles[1];
};

struct SYSTEM_KERNEL_DEBUGGER_INFO
{
	BOOLEAN DebuggerEnabled;
	BOOLEAN DebuggerNotPresent;
};

class CProcessQuery
{
public:
	CProcessQuery();
	virtual ~CProcessQuery();
	void Start();
	void Close();
	bool Fetch(SYSTEM_INFORMATION_CLASS SysInfoClass,DWORD QuerySize);
	SYSTEM_HANDLE_INFO* GetHandleInfo();
	SYSTEM_HANDLE_INFO_EX* GetExtendedHandleInfo();
	SYSTEM_KERNEL_DEBUGGER_INFO* GetKernelDebuggerInfo();
	SYSTEM_PROCESS_INFO* GetProcessInfoByID(HANDLE ProcessId);
	SYSTEM_EXTENDED_PROCESS_INFO* GetExtendedProcessInfoByID(HANDLE ProcessId);
	SYSTEM_THREAD_INFO* GetThreadInfoByID(SYSTEM_PROCESS_INFO* lpSystemProcessInfo,HANDLE ThreadId);
	SYSTEM_EXTENDED_THREAD_INFO* GetExtendedThreadInfoByID(SYSTEM_EXTENDED_PROCESS_INFO* lpSystemProcessInfo,HANDLE ThreadId);
public:
	static NTQUERYSYSTEMINFORMATION m_NtQuerySystemInformation;
private:
	BYTE* m_QueryData;
	DWORD m_QuerySize;
	NTSTATUS m_QueryStatus;
};
