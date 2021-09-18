#include "GameEngineThread.h"
#include <WinSock2.h>

// Static Var
std::map<GameEngineString, std::shared_ptr<GameEngineThread>> GameEngineThread::m_AllThread;
// 
// 
// Static Func

// constructer destructer
GameEngineThread::GameEngineThread() : m_pThread(nullptr), m_pThreadFunc(nullptr), m_StartWaitTime(0)
{

}

GameEngineThread::GameEngineThread(std::function<void()>_Func) : m_pThread(nullptr), m_pThreadFunc(_Func), m_StartWaitTime(0)
{
}

GameEngineThread::~GameEngineThread() 
{
	Stop();
}

void ThreadMemberFunc(GameEngineThread* _ThreadPtr) 
{
	if (0 != _ThreadPtr->m_StartWaitTime)
	{
		Sleep(_ThreadPtr->m_StartWaitTime);
	}

	// 그냥 무조건 실행해줘도 됩니다.
	_ThreadPtr->ThreadUpdate();
}

void ThreadFunc(GameEngineThread* _ThreadPtr)
{
	if ( 0 != _ThreadPtr->m_StartWaitTime)
	{
		Sleep(_ThreadPtr->m_StartWaitTime);
	}

	if (nullptr != _ThreadPtr->m_pThreadFunc)
	{
		_ThreadPtr->m_pThreadFunc();
	}
	// _ThreadPtr->fun
}

// member Func
void GameEngineThread::Start(DWORD _StartWaitTime)
{
	if (nullptr != m_pThread)
	{
		Stop();
	}

	m_StartWaitTime = _StartWaitTime;

	m_pThread = new std::thread(ThreadFunc, this);
}

void GameEngineThread::Start(std::function<void()> _Func, DWORD _StartWaitTime)
{
	SetThreadFunc(_Func);
	Start(_StartWaitTime);
}

void GameEngineThread::StartMember(unsigned long _StartWaitTime)
{
	if (nullptr != m_pThread)
	{
		Stop();
	}

	m_StartWaitTime = _StartWaitTime;

	m_pThread = new std::thread(ThreadMemberFunc, this);
}

void GameEngineThread::Stop() 
{
	if (nullptr != m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
		m_pThread = nullptr;
	}
}

