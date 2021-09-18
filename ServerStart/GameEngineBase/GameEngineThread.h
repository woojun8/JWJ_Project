#pragma once
#include <thread>
#include <functional>
#include <map>
#include "GameEngineMemory.h"
#include "GameEngineString.h"
#include <WinSock2.h>

class GameEngineThread;
void ThreadFunc(GameEngineThread* _ThreadPtr);

class GameEngineThread;
void ThreadMemberFunc(GameEngineThread* _ThreadPtr);

// 분류1 : 
// 분류2 : 
// 용도 : Thread
// 설명 : GameEngineThread가 매니저 역할도 함께하는 방법도 보여드리겠습니다.

class GameEngineThread : std::enable_shared_from_this<GameEngineThread>
{
private: // Static Var
    // 순서를 조절할수가 없어요
    static std::map<GameEngineString, std::shared_ptr<GameEngineThread>> m_AllThread;


public: 
    template<typename ThreadType>
    static std::shared_ptr<ThreadType> CreateThread(GameEngineString _Name)
    {
        if (m_AllThread.end() != m_AllThread.find(_Name))
        {
            return std::dynamic_pointer_cast<ThreadType, GameEngineThread>(m_AllThread[_Name]);
        }

        m_AllThread[_Name] = std::make_shared<ThreadType>();
        m_AllThread[_Name]->StartMember();
        return nullptr;
    }

    // Static Func
    //GameEngineThread& Inst() 
    //{
    //    // 
    //    static GameEngineThread NewInst;
    //    return NewInst;
    //}

private: // member Var
    unsigned long m_StartWaitTime;
    std::thread* m_pThread;
    std::function<void()> m_pThreadFunc;

private:
    // friend 클래스에만 걸어줄수 있는게 아니고
    // 어떤 특정 함수를 특정지어서 friend를 걸어줄수도 있습니다.
    friend void ThreadFunc(GameEngineThread* _ThreadPtr);
    friend void ThreadMemberFunc(GameEngineThread* _ThreadPtr);

public:
    void SetThreadFunc(std::function<void()> _Func)
    {
        m_pThreadFunc = _Func;
    }

public: // constructer destructer
    GameEngineThread();
    GameEngineThread(std::function<void()> _Func);
    virtual ~GameEngineThread();

public: // delete constructer 
    GameEngineThread(const GameEngineThread& _Other) = delete;
    GameEngineThread(const GameEngineThread&& _Other) = delete;

public: // delete operator
    GameEngineThread& operator=(const GameEngineThread& _Other) = delete;
    GameEngineThread& operator=(const GameEngineThread&& _Other) = delete;

public: // member Func

    void Start(std::function<void()> _Func, unsigned long _StartWaitTime = 0);
    void Start(unsigned long _StartWaitTime = 0);

    void StartMember(unsigned long _StartWaitTime = 0);

    void Stop(); // 쓰레드가 정지하나?
    // 기존쓰레드는 그대로 돌아가게 놔둔상태로
    // 현재 실행하는 쓰레드를 교체하는 방식으로 만들겁니다.


public:
    virtual void ThreadUpdate() {};
};

class CRITICAL_SECTION_OBJ 
{
private:
    CRITICAL_SECTION m_CS;

public:
    class Lock_Obj
    {
        friend CRITICAL_SECTION_OBJ;
    private:
        CRITICAL_SECTION& m_CS;

    private:
        Lock_Obj(CRITICAL_SECTION_OBJ& CS_Obj) : m_CS(CS_Obj.m_CS)
        {
            EnterCriticalSection(&m_CS);
        }

    public:
        ~Lock_Obj() 
        {
            LeaveCriticalSection(&m_CS);
        }
    };

public:
    Lock_Obj Lock()
    {
        return Lock_Obj(*this);
    }

public:
    CRITICAL_SECTION_OBJ() : m_CS({0,})
    {
        InitializeCriticalSection(&m_CS);
    }

    ~CRITICAL_SECTION_OBJ() 
    {
        DeleteCriticalSection(&m_CS);
    }
};

