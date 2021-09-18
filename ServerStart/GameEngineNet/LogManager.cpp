#include "LogManager.h"
#include <iostream>

LogManager::LogManager()
{
}

LogManager::~LogManager()
{
}



void LogManager::Init(int _LogCount, int LogMaxCount)
{
	setlocale(LC_ALL, "KOR");
	MaxListCount = _LogCount;
	MaxLogCount = LogMaxCount;
	CurMessageCount = 0;
	LogStartCheck = _LogCount;

    LogIocp.Start(&LogManager::LogThreadFunc, 1);
	m_LogList.resize(_LogCount);
	for (size_t i = 0; i < _LogCount; i++)
	{
		m_LogList[i].reserve(LogMaxCount);
	}

	Sleep(500);

	int a = 0;
}

void LogManager::PushLog(const char* _Log)
{
	LogIocp.IocpPost(reinterpret_cast<ULONG_PTR>(_Log), 0, nullptr);
}
void LogManager::PrintLog()
{
	LogIocp.IocpPost(-1, 0, nullptr);
}

void LogManager::LogThreadFunc() 
{
	GameEngineIocp::IocpWorker Worker = Inst().LogIocp.CreateWorker();
	// HANDLE IcopHandle = GetInst().m_Icop.MonitorHandle
	// 32개의 쓰레드중 하나인데.
	// std::cout << "서버 이벤트 쓰레드가 만들어졌습니다\n";


	// 지역변수가 아니면
	// 전부다 위험해요

	// 안전장치를 걸어야 합니다.
	// 힙 => 무조건 위험
	// 데이터영역 => 무조건 위험

	ULONG_PTR ComKey;

	std::atomic_uint32_t& RefCurMessageCount = Inst().CurMessageCount;
	int MaxListCount = Inst().MaxListCount;
	int MaxLogCount = Inst().MaxLogCount;
	std::vector<std::vector<const char*>>& LogList = Inst().m_LogList;

	Inst().LogStartCheck.fetch_add(1);

	while (true)
	{
		// IOCP를 사용하는 이유
		Worker.GetQueueWait();
		ComKey = Worker.GetComKey();

		if (-1 != ComKey)
		{
			// unsigned int Recv = RefCurLogCount.fetch_add(1);
			LogList[RefCurMessageCount].push_back(reinterpret_cast<const char*>(ComKey));
		}
		else if(-1 == ComKey)
		{
			int CurList = RefCurMessageCount;
			RefCurMessageCount.fetch_add(1);

			if ((int)RefCurMessageCount + 1 <= MaxLogCount)
			{
				RefCurMessageCount.exchange(0);
			}

			if (0 == LogList[CurList].size())
			{
				continue;
			}

			for (size_t i = 0; i < LogList[CurList].size(); i++)
			{
				std::cout << LogList[CurList][i] << std::endl;
			}

			LogList[CurList].clear();
		}
	}
}