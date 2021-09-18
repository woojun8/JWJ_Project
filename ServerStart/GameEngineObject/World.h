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
// �з�1 : object
// �з�2 : 
// �뵵 : 
// ���� : �Ϲ������� ���� ���α׷� ���ο� �����ϴ� 
//        ȭ������� ������ �� Ŭ�����μ� ǥ���� �̴ϴ�.
//        �߿� : �������̽��� �����ؾ� �Ѵ�.
//               �ּܼ�������? �̳༮�� �ܼ��� �˸� �ȵ˴ϴ�. 

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


    // ��� �̰� ó���ҹ���� �����
    // ���鼭 �� �غ�ƴ�? �غ�ƴ�?
    // �׷��ٰ� list�� ���۰� �ƴϾ�.
    // std::list<std::shared_ptr<Actor>> m_WaitActor;

    // �̷��� �����ϸ�
    // Ž������ �ѹ��� �̰����� ã�Ƽ� ���������� �ִ�.
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

    // 2���� ���� 
    // ����ȭ�� 2������ �̷������ �˴ϴ�.
    // �ޱ�� �ϴ� m_MsgList�� insert�ɶ�
    // �ΰ��� m_MsgList�� ������ �ٲ�.
    
    // �̰� ��ü�Ǵ� ��������
    // ����ȭ�� �ɾ���� �մϴ�.

private: // msg
    CRITICAL_SECTION_OBJ LockObj;
    DWORD MaxMsgListCount;
    DWORD RecvMsgListIndex;
    DWORD ProcessMsgIndex; // ó���� �޼��� �ε���
    DWORD RecvMsgIndex; // ���ú�� �޼��� �ε���
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

        // ���Ͷ����� ó���ǰ� �ִ� �Լ��� 
        // ���ٽÿ��� ���Ͷ��� �ɾ���� �ϴµ�.
        //  InterlockedExchangeNoFence
        

        // ���ú긦 �� ���� ����Ʈ�� ó���Ǿ�� �ϴ� ����Ʈ����?

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
        // ȿ���� ��Ÿ�������� ���� �ش�.
        //  1                                  1
        //  1                                  0<= �����忡 ��ȣ�Ǹ鼭 ���� ���� ���� �ִ� �޸𸮾ȿ����� ������ ���ϴ� ��찡 �ֽ��ϴ�.
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

    // �����δ�.
    virtual void UpdatePrev(float _DeltaTime);
    virtual void Update(float _DeltaTime);
    virtual void UpdateNext(float _DeltaTime);

    // ��ȣ�ۿ��Ѵ�.
    virtual void CollisionPrev();
    virtual void Collision();
    virtual void CollisionNext();

    // ����� �����Ұ� ������ �����Ѵ�.
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

