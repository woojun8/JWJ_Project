#pragma once
#ifndef UNREALDEFINE
// #include <MiniBaseHeader.h>
// window가 들어있으면 

// winsock과 window는 둘중 하나만 사용할수 있습니다.
#include <WinSock2.h>// 새로 개선된 함수가존재하는 녀석.
#include <MSWSock.h> // 마이크로소프트에서 따로 지원해주는 소켓 함수 헤더
#include <WS2tcpip.h> // tcp/ip 지원함수
#include <memory>
#include <GameEngineIocp.h>
#include <LockThreadSafeObjectPool.h>


// 객체화 시켜서 쓴다 => 싱글톤
// static StartUp(
// GameEngineServer::StartUp();

// 분류1 : Server
// 분류2 : 
// 용도 : 
// 설명 : 

class ServerTask : public std::enable_shared_from_this<ServerTask>
{
public:
    int Type;
    // 쿼리만 알고 있을뿐 어떤 데이터를 받아와서 처리해야할지는 모르게 되는거니.
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
