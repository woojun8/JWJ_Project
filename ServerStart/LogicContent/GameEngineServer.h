#pragma once
#ifndef UNREALDEFINE
// #include <MiniBaseHeader.h>
// window�� ��������� 

// winsock�� window�� ���� �ϳ��� ����Ҽ� �ֽ��ϴ�.
#include <WinSock2.h>// ���� ������ �Լ��������ϴ� �༮.
#include <MSWSock.h> // ����ũ�μ���Ʈ���� ���� �������ִ� ���� �Լ� ���
#include <WS2tcpip.h> // tcp/ip �����Լ�
#include <memory>
#include <GameEngineIocp.h>
#include <LockThreadSafeObjectPool.h>


// ��üȭ ���Ѽ� ���� => �̱���
// static StartUp(
// GameEngineServer::StartUp();

// �з�1 : Server
// �з�2 : 
// �뵵 : 
// ���� : 

class ServerTask : public std::enable_shared_from_this<ServerTask>
{
public:
    int Type;
    // ������ �˰� ������ � �����͸� �޾ƿͼ� ó���ؾ������� �𸣰� �Ǵ°Ŵ�.
    std::function<void()> TeskFunc;
};


class TcpAccepter;
class TcpConnecter;
class ServerConnecter;
class GameEngineServer
{
private: // Static Var
    static GameEngineServer Inst;

public: // Static Func
    static GameEngineServer& GetInst();
    static LONG ConnectUserCount;
    static LONG WorldUserCount;
    LockThreadSafeObjectPool<ServerTask> m_TaskPool;

private: // member Var
    GameEngineIocp m_Icop;
    std::shared_ptr<TcpAccepter> PtrTcpAccepter;

public:
    void PushServerTask(int _Type, std::function<void()> _Func)
    {
        std::shared_ptr<ServerTask> NewTask = m_TaskPool.Pop();
        NewTask->Type = _Type;
        NewTask->TeskFunc = _Func;
        m_Icop.IocpPost(reinterpret_cast<ULONG_PTR>(NewTask.get()), 0, nullptr);
    }

public: // constructer destructer
    GameEngineServer();
    ~GameEngineServer();

public: // delete constructer 
    GameEngineServer(const GameEngineServer& _Other) = delete;
    GameEngineServer(const GameEngineServer&& _Other) = delete;

private:
    static void GameServerIcopFunc();

public: // delete operator
    GameEngineServer& operator=(const GameEngineServer& _Other) = delete;
    GameEngineServer& operator=(const GameEngineServer&& _Other) = delete;

private:
    std::function<void(ServerConnecter*)> DisFunc;


public: // member Func
    void ServerStart(int _Port, std::function<void(ServerConnecter*)> _DisconnectFunc, int _Count = -1);

    
};

#endif
