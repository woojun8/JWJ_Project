#pragma once
#include <list>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <WinSock2.h>
#include <set>
#include "Actor.h"
#include <GameEngineThread.h>
// #include <unordered_set>

// 
// 분류1 : object
// 분류2 : 
// 용도 : 
// 설명 : 일반적으로 게임 프로그램 내부에 존재하는 
//        화면단위의 구조를 이 클래스로서 표현할 겁니다.
//        중요 : 인터페이스만 제공해야 한다.
//               콘솔세상이죠? 이녀석이 콘솔을 알면 안됩니다. 

class WorldManager;
class World : public std::enable_shared_from_this<World>
{
    friend WorldManager;

private: // Static Var
public: // Static Func
private: // member Var
    WorldManager* m_pManager; 
    std::map<int, std::list<std::shared_ptr<Actor>>>  m_ActorList;

    std::list<std::shared_ptr<Actor>>  m_MoveActorList;


    // 어떻게 이걸 처리할방법이 없어요
    // 돌면서 너 준비됐니? 준비됐니?
    // 그렇다고 list가 나쁜건 아니야.
    // std::list<std::shared_ptr<Actor>> m_WaitActor;

    // 이렇게 관리하면
    // 탐색으로 한번에 이곳에서 찾아서 빼버릴수가 있다.
    std::map<int, std::set<std::shared_ptr<Actor>>> m_WaitActor;


public:
    std::list<std::shared_ptr<Actor>>& GetActorList(int _Layer) 
    {
        if (m_ActorList.end() == m_ActorList.find(_Layer))
        {
            m_ActorList[_Layer];
        }

        return m_ActorList[_Layer];
    }

    // 2개인 이유 
    // 동기화는 2곳에서 이루어지게 됩니다.
    // 받기는 하는 m_MsgList에 insert될때
    // 두개의 m_MsgList의 순서가 바뀔때.
    
    // 이게 교체되는 순간만은
    // 동기화를 걸어줘야 합니다.

private: // msg
    CRITICAL_SECTION_OBJ LockObj;
    DWORD MaxMsgListCount;
    DWORD RecvMsgListIndex;
    DWORD ProcessMsgIndex; // 처리용 메세지 인덱스
    DWORD RecvMsgIndex; // 리시브용 메세지 인덱스
    std::vector< std::vector<std::function<void()>> > m_MsgList;

private:
    //void MsgListChange()
    //{
    //    InterlockedIncrement(&RecvMsgListIndex);
    //    if (MaxMsgListCount <= RecvMsgListIndex)
    //    {
    //        InterlockedExchange(&ProcessMsgIndex, RecvMsgIndex);
    //        InterlockedExchange(&RecvMsgListIndex, 0);
    //    }
    //}

    std::vector<std::function<void()>>& GetRecvList()
    {
        return m_MsgList[RecvMsgListIndex];
    }

    std::vector<std::function<void()>>& GetProcessMsgList() 
    {
        LockObj.Lock();
        // MsgListChange();

        // 인터락으로 처리되고 있는 함수는 
        // 접근시에도 인터락을 걸어줘야 하는데.
        //  InterlockedExchangeNoFence
        

        // 리시브를 다 받은 리스트가 처리되어야 하는 리스트겠죠?

        if (0 == m_MsgList[RecvMsgListIndex].size())
        {
            return m_MsgList[RecvMsgListIndex];
        }

        int CurIndex = RecvMsgListIndex;
        InterlockedIncrement(&RecvMsgListIndex);

        if (MaxMsgListCount >= RecvMsgListIndex)
        {
            InterlockedExchange(&RecvMsgListIndex, 0);
        }

        // InterlockedExchange(&RecvMsgIndex, 0);
        return m_MsgList[CurIndex];
    }

public:
    void MsgUpdate();
    void MsgListInit(int _Count, int _Size);

    template<typename FuncType,  typename ... Rest>
    void MsgInsert(FuncType _Func, Rest&& ... _Arg)
    {
        LockObj.Lock();
        // 효과가 나타났을때의 값을 준다.
        //  1                                  1
        //  1                                  0<= 쓰레드에 보호되면서 지금 내가 보고 있는 메모리안에서는 증가를 못하는 경우가 있습니다.
        std::vector<std::function<void()>>& RecvList = GetRecvList();
        RecvList.push_back(std::bind(_Func, this, _Arg...));
    }


private:
    void SetManager(WorldManager* _World)
    {
        m_pManager = _World;
    }

public:
    WorldManager* GetGameWorld()
    {
        return m_pManager;
    }

public:
    void PushActor(std::shared_ptr<Actor> _Actor, int _LayerIndex);
    void PushWaitActor(std::shared_ptr<Actor> _Actor, int _LayerIndex);

public:
    virtual void WorldStart() {}
    virtual void WorldUpdate() {}

    virtual void WorldMoveCheck();

    // 움직인다.
    virtual void UpdatePrev(float _DeltaTime);
    virtual void Update(float _DeltaTime);
    virtual void UpdateNext(float _DeltaTime);

    // 상호작용한다.
    virtual void CollisionPrev();
    virtual void Collision();
    virtual void CollisionNext();

    // 결과를 정리할게 있으면 정리한다.
    virtual void Release();

public: // constructer destructer
    World();
    virtual ~World();

public: // delete constructer 
    World(const World& _Other) = delete;
    World(const World&& _Other) = delete;

public: // delete operator
    World& operator=(const World& _Other) = delete;
    World& operator=(const World&& _Other) = delete;

public: // member Func
    bool WaitActorInWorld(std::shared_ptr<Actor> _Ptr);


    template<typename T>
    std::shared_ptr<T> CreateWaitActor(int _Layer)
    {
        std::shared_ptr<T> Ptr = std::make_shared<T>();
        PushWaitActor(Ptr, _Layer);
        return Ptr;
    }

    template<typename T>
    std::shared_ptr<T> CreateActor(int _Layer)
    {
        std::shared_ptr<T> Ptr = std::make_shared<T>();
        PushActor(Ptr, _Layer);
        ActorStart(Ptr.get());
        return Ptr;
    }

    virtual void ActorStart(Actor* _Actor) 
    {
        _Actor->Start();
    }

};

