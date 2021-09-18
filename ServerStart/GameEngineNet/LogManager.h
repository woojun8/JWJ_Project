#pragma once
#include "GameEngineIocp.h"
#include <atomic>

//분류 1 :
//분류 2 :
//용도 :
//설명 :

class LogManager
{
public:
	static LogManager& Inst() 
	{
		static LogManager NewInst;
		return NewInst;
	}

private: // static var
	GameEngineIocp LogIocp;
	int MaxListCount;
	int MaxLogCount;
	std::atomic_uint32_t CurMessageCount;
	std::atomic_uint32_t LogStartCheck;
	std::vector<std::vector<const char*>> m_LogList;
	// std::vector<std::vector<std::string>> m_LogStringList;

public:
	bool IsLog() 
	{
		return MaxListCount == LogStartCheck;
	}

public:
	void PushLog(const char* _Log);
	void PrintLog();

public:
	void Init(int _LogCount, int LogMaxCount);

private:
	static void LogThreadFunc();

public: // constructor destructor
	LogManager();
	~LogManager();

public: // delete constructor

	LogManager(const LogManager& _other) = delete;
	LogManager(const LogManager&& _other) = delete;

public: // delete operator
	LogManager& operator=(const LogManager& _other) = delete;
	LogManager& operator=(const LogManager&& _other) = delete;

};

