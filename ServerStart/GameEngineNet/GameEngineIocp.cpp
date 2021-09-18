#include "GameEngineIocp.h"
#include <GameEngineDebug.h>

void GameEngineIocp::IocpWorker::IocpPost(ULONG_PTR _ComKey, const DWORD _dwLen, LPOVERLAPPED _Over) 
{
	Parent.IocpPost(_ComKey, _dwLen, _Over);
}

void GameEngineIocp::IocpWorker::GetQueueWait() 
{
	//DWORD Len;
	//OVERLAPPED* OverData = nullptr;
	//void* EventUser = 0;


	//if (FALSE == GetQueuedCompletionStatus(hIOCPMainHandle, &Len, (PULONG_PTR)&EventUser, &OverData, INFINITE))
	//{
	//	DWORD LastError = GetLastError();
	//	GameEngineDebug::AssertMsg("if (FALSE == GetQueuedCompletionStatus(hIOCPMainHandle, &DwLen, ComKey, &PtrOverData, DwTime))");
	//}


	if (FALSE == GetQueuedCompletionStatus(hIOCPMainHandle, &DwLen, &m_ComKey, (LPOVERLAPPED*)&PtrOverData, DwTime))
	{
		// 아무것도 찾을수 없는 경우에만 심각한 에러를 내겠습니다.
		if (0 == DwLen
			&& nullptr == PtrOverData)
		{
			GameEngineDebug::AssertMsg("if (FALSE == GetQueuedCompletionStatus(hIOCPMainHandle, &DwLen, ComKey, &PtrOverData, DwTime))");
		}

		// DWORD LastError = GetLastError();
		// 
	}
}

// Static Var
// Static Func

// constructer destructer
GameEngineIocp::GameEngineIocp(DWORD _CurrentThread /*= 0*/) : m_IOCPMainHandle(0)
{
	m_IOCPMainHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);

	if (nullptr == m_IOCPMainHandle)
	{
		GameEngineDebug::AssertMsg("if (nullptr == hIOCPHandle)");
	}
}

GameEngineIocp::~GameEngineIocp() 
{
	if (nullptr != m_IOCPMainHandle)
	{
		CloseHandle(m_IOCPMainHandle);
	}
}
// member Func

void GameEngineIocp::Start(std::function<void()> _Func, int Count/* = -1*/)
{
	if (-1 == Count)
	{
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		// CPU 코어 개수를 알아냈고
		Count = systemInfo.dwNumberOfProcessors;
		Count *= 2;
	}

	for (size_t i = 0; i < Count; i++)
	{
		ThreadCreate(_Func);
	}

}

void GameEngineIocp::ThreadCreate(std::function<void()> _Func) 
{
	ThreadPool.push_back(std::make_shared<GameEngineThread>());
	ThreadPool[ThreadPool.size() - 1]->SetThreadFunc(_Func);
	ThreadPool[ThreadPool.size() - 1]->Start();
}

void GameEngineIocp::MonitorHandle(HANDLE _Handle, ULONG_PTR _Data)
{
	if (nullptr == m_IOCPMainHandle)
	{
		GameEngineDebug::AssertMsg("if (nullptr == m_IOCPMainHandle)");
	}

	if (NULL == CreateIoCompletionPort(_Handle, m_IOCPMainHandle, (DWORD)_Data, 0))
	{
		GameEngineDebug::AssertMsg("if (NULL == CreateIoCompletionPort(_Handle, m_IOCPMainHandle, (DWORD)_Data, 0))");
	}
}

GameEngineIocp::IocpWorker GameEngineIocp::CreateWorker()
{
	return IocpWorker(*this);
}




void GameEngineIocp::IocpPost(ULONG_PTR _ComKey, const DWORD _dwLen, LPOVERLAPPED _Over) 
{
	if (nullptr == m_IOCPMainHandle)
	{
		GameEngineDebug::AssertMsg("if (nullptr == m_IOCPMainHandle)");
	}

	// 실패
	if (0 == PostQueuedCompletionStatus(m_IOCPMainHandle, _dwLen, _ComKey, _Over))
	{
		GameEngineDebug::AssertMsg("0 == PostQueuedCompletionStatus(m_IOCPMainHandle, _dwLen, _ComKey, _Over)");
	}

}