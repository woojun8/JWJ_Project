#pragma once
#include "EngineOver.h"
#include <process.h>
#include <GameEngineThread.h>
#include <vector>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 

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

    // �̳༮�� ����Ѵٴ� ���� �⺻������ �����ϰ� �մ� ��� ���ؼ� ���� �������Ƿ� �������� ������ �Ҽ��ۿ� ����.
    void MonitorHandle(HANDLE _Handle, ULONG_PTR _Data = 0);

    // �Ϲ������� ������� ó�� iocp�� ���ϰ� �Ǹ�
    // ���ø� ���� �ȴ�.
    // ������ ���ô� �⺻������ 
    // �� �����ϴ� ��� �������� �������� �������� ��ó�ϴ� �����̰�
    // ���� ���Ҷ� iocp�� ������ ���� ��ų�� �ִ� ����̴�.
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