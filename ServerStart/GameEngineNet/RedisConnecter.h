#pragma once
#ifndef UNREALDEFINE

#include "GameEngineSocket.h"
#include "RedisCommand.h"
#include <GameEngineThread.h>
#include <queue>

// ���𽺿� � ��Ŷ�� ���Ȱ�


// 1. �� ����� �ܼ��� ���ڿ��̶�� + �� �Ǿտ� �´�.
// 2. �� ����� ������� - �� �Ǿտ� �´�.
// 3. �� ����� ������� ":"
// 4. �� ����� Bulk Strings(������ ���� ���ڿ�)��� "$"
// 5. �� ����� Arrays()��� "*"

// "*6\r\n$1\r\n2\r\n$-1\r\n$1\r\n4\r\n$-1\r\n$1\r\n7\r\n$-1\r\n command\r\n"

// "*6
//  $1 2 $-1\r\n$1\r\n4\r\n$-1\r\n$1\r\n7\r\n$-1\r\n command\r\n"
//  $���ڿ��� ���̴�.
//  2
//  $-1

// * �迭�̴�.
// 6 


class RedisTask 
{
public:
    // �����Ҵ��� �ؾ߰���
    std::shared_ptr<RedisCommand::CommandBase> m_Commend;
    std::function<void(RedisResult)> m_Request;

public:
    void SetCommand(std::shared_ptr<RedisCommand::CommandBase> _Command, std::function<void(RedisResult)> _Request)
    {
        m_Commend = _Command;
        m_Request = _Request;
    }
};

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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

    // �̰� ������ �ܼ��� Ŀ�ǵ带 �����°��� �ƴ�.
    // Queue���ٰ� �־����
    // �� Queue�� �������� ó���ϴ� ������� 
    template<typename CommandType, typename ... REST>
    void CommandArg(REST& ... _Arg) 
    {
        CommandType Type = CommandType(_Arg...);
        Command(Type);
    }

    template<typename CommandType, typename ... REST>
    RedisResult CommandArgResult(REST& ... _Arg)
    {
        // �̳༮ �ϳ��� ó���� �ɶ�.
        // �׿� ���� ����� �־��ִ� ������� ó��.

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
    // Ǯ������� �ϴ°��� ���� ������.
    // ���� �����̶� ����� ������� ó��
    // ���� ȿ������ ����� �ƴ϶�� �Ҽ� ������ �پ��� ����� ���ٴ� �ǹ̿��� ������ ����.
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
    // �̰� ������ ���𽺸� ó���ϴ� �����带 �ϳ� ������̱� ������.
    template<typename CommandType, typename ... REST>
    void RedisCommandPush(std::function<void(RedisResult)> _Request, REST&& ... _Arg)
    {
        LockObj.Lock();

        std::shared_ptr<RedisTask> m_Task = std::make_shared<RedisTask>();
        std::shared_ptr<CommandType> m_Command = std::make_shared<CommandType>();
        m_Command->ArgValue(_Arg...);

        m_Task->SetCommand(m_Command, _Request);

        // Ŀ�ǵ� �� ���� ó��
        // m_Task->m_Commend = std::dynamic_pointer_cast<RedisCommand::CommandBase>(m_Command);
        // m_Task->m_Commend = m_Command;


        // m_Task->m_Request = _Request;
        m_FrontTaskQueue.push(m_Task);
    }
};



#endif