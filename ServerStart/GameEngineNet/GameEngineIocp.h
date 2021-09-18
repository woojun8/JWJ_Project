#pragma once
#include "EngineOver.h"
#include <process.h>
#include <GameEngineThread.h>
#include <vector>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 

class GameEngineIocp : std::enable_shared_from_this<GameEngineThread>
{
public:
    class IocpWorker
    {
    private:
        GameEngineIocp& Parent;
        HANDLE hIOCPMainHandle;
        DWORD DwTime;
        DWORD DwLen;
        EngineOVERLAPPED* PtrOverData;
        ULONG_PTR m_ComKey;

    public:
        void GetQueueWait();
        EngineOVERLAPPED* OverData() {
            return PtrOverData;
        }

        ULONG_PTR GetComKey() 
        {
            return m_ComKey;
        }

        DWORD GetLen() {
            return DwLen;
        }

    public:
        void IocpPost(ULONG_PTR _ComKey, const DWORD _dwLen, LPOVERLAPPED _Over);

    public:
        IocpWorker(GameEngineIocp& _Parent) : hIOCPMainHandle(_Parent.m_IOCPMainHandle), Parent(_Parent), DwLen(0), DwTime(INFINITE), PtrOverData(nullptr)
        {

        }
    };

private: // Static Var
public: // Static Func

private: // member Var
    HANDLE m_IOCPMainHandle;
    std::vector<std::shared_ptr<GameEngineThread>> ThreadPool;

public:
    IocpWorker CreateWorker();

public:
    void Start(std::function<void()> _Func, int Count = -1);
    void ThreadCreate(std::function<void()> _Func);

    // 이녀석을 사용한다는 것은 기본적으로 감시하고 잇는 대상에 대해서 일이 벌어지므로 수동적인 역할을 할수밖에 없다.
    void MonitorHandle(HANDLE _Handle, ULONG_PTR _Data = 0);

    // 일반적으로 사람들이 처음 iocp를 접하게 되면
    // 감시를 배우게 된다.
    // 하지만 감시는 기본적으로 
    // 그 감시하는 대상에 무슨일이 있을때만 수동으로 대처하는 수단이고
    // 내가 원할때 iocp를 깨워서 일을 시킬수 있는 방법이다.
    void IocpPost(ULONG_PTR _ComKey, const DWORD _dwLen, LPOVERLAPPED _Over);

public: // constructer destructer
    GameEngineIocp(DWORD _CurrentThread = 0);
    ~GameEngineIocp();

public: // delete constructer 
    GameEngineIocp(const GameEngineIocp& _Other) = delete;
    GameEngineIocp(const GameEngineIocp&& _Other) = delete;

public: // delete operator
    GameEngineIocp& operator=(const GameEngineIocp& _Other) = delete;
    GameEngineIocp& operator=(const GameEngineIocp&& _Other) = delete;

public: // member Func
};