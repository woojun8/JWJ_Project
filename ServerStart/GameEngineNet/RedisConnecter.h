#pragma once
#ifndef UNREALDEFINE

#include "GameEngineSocket.h"
#include "RedisCommand.h"
#include <GameEngineThread.h>
#include <queue>

// 레디스에 어떤 패킷을 날렸고


// 1. 그 결과가 단순한 문자열이라면 + 가 맨앞에 온다.
// 2. 그 결과가 에러라면 - 가 맨앞에 온다.
// 3. 그 결과가 정수라면 ":"
// 4. 그 결과가 Bulk Strings(개수가 많은 문자열)라면 "$"
// 5. 그 결과가 Arrays()라면 "*"

// "*6\r\n$1\r\n2\r\n$-1\r\n$1\r\n4\r\n$-1\r\n$1\r\n7\r\n$-1\r\n command\r\n"

// "*6
//  $1 2 $-1\r\n$1\r\n4\r\n$-1\r\n$1\r\n7\r\n$-1\r\n command\r\n"
//  $문자열일 것이다.
//  2
//  $-1

// * 배열이다.
// 6 


class RedisTask 
{
public:
    // 동적할당을 해야겠죠
    std::shared_ptr<RedisCommand::CommandBase> m_Commend;
    std::function<void(RedisResult)> m_Request;

public:
    void SetCommand(std::shared_ptr<RedisCommand::CommandBase> _Command, std::function<void(RedisResult)> _Request)
    {
        m_Commend = _Command;
        m_Request = _Request;
    }
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class RedisConnecter : public GameEngineSocket
{


private: // Static Var
public: // Static Func



public: // constructer destructer
    RedisConnecter();
    ~RedisConnecter();

public: // delete constructer 
    RedisConnecter(const RedisConnecter& _Other) = delete;
    RedisConnecter(const RedisConnecter&& _Other) = delete;

public: // delete operator
    RedisConnecter& operator=(const RedisConnecter& _Other) = delete;
    RedisConnecter& operator=(const RedisConnecter&& _Other) = delete;

public: // member Func
    void Connect(const char* _Ip, int _Port);

    // 이걸 날리면 단순히 커맨드를 날리는것이 아닌.
    // Queue에다가 넣어놓고
    // 그 Queue가 차있으면 처리하는 방식으로 
    template<typename CommandType, typename ... REST>
    void CommandArg(REST& ... _Arg) 
    {
        CommandType Type = CommandType(_Arg...);
        Command(Type);
    }

    template<typename CommandType, typename ... REST>
    RedisResult CommandArgResult(REST& ... _Arg)
    {
        // 이녀석 하나가 처리가 될때.
        // 그에 대한 결과를 넣어주는 방식으로 처리.

        CommandArg<CommandType>(_Arg...);
        return WaitResult();
    }

    template<typename CommandType, typename ... REST>
    RedisResult CommandArgResult(REST&& ... _Arg)
    {
        CommandArg<CommandType>(_Arg...);
        return WaitResult();
    }

    std::string WaitResult();



    void Command(const RedisCommand::CommandBase& Command) const;
};

class RedisManager
{
private: // member Var
    CRITICAL_SECTION_OBJ LockObj;
    // 풀방식으로 하는것이 가장 좋은데.
    // 버퍼 스왑이랑 비슷한 방식으로 처리
    // 별로 효율적인 방식은 아니라고 할수 있지만 다양한 방법을 본다는 의미에서 보도록 하죠.
    std::queue<std::shared_ptr<RedisTask>> m_FrontTaskQueue;
    std::queue<std::shared_ptr<RedisTask>> m_ProcessTaskQueue;

    std::shared_ptr<GameEngineThread> m_RedisThread;
    RedisConnecter m_Connecter;

public:
    void ProcessCheck()
    {
        while (false == m_FrontTaskQueue.empty())
        {
            m_ProcessTaskQueue.push(m_FrontTaskQueue.front());
            m_FrontTaskQueue.pop();
        }
    }

public:
    static RedisManager& GetInst()
    {
        static RedisManager Inst;
        return Inst;
    }

    static RedisConnecter& GetConnecter()
    {
        return GetInst().m_Connecter;
    }

public:
    bool IsProcess;

    void End()
    {
        IsProcess = false;
    }


    static void RedisThread(RedisConnecter* _Con);

    void Init(const char* _Ip, int _Port)
    {
        m_Connecter.Connect(_Ip, _Port);

        IsProcess = true;
        m_RedisThread = std::make_shared<GameEngineThread>();
        m_RedisThread->SetThreadFunc(std::bind(RedisThread, &m_Connecter));
        m_RedisThread->Start();
    }

public:
    // 이걸 쓰려면 레디스만 처리하는 쓰레드를 하나 만들것이기 때문에.
    template<typename CommandType, typename ... REST>
    void RedisCommandPush(std::function<void(RedisResult)> _Request, REST&& ... _Arg)
    {
        LockObj.Lock();

        std::shared_ptr<RedisTask> m_Task = std::make_shared<RedisTask>();
        std::shared_ptr<CommandType> m_Command = std::make_shared<CommandType>();
        m_Command->ArgValue(_Arg...);

        m_Task->SetCommand(m_Command, _Request);

        // 커맨드 및 인자 처리
        // m_Task->m_Commend = std::dynamic_pointer_cast<RedisCommand::CommandBase>(m_Command);
        // m_Task->m_Commend = m_Command;


        // m_Task->m_Request = _Request;
        m_FrontTaskQueue.push(m_Task);
    }
};



#endif