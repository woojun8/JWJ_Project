#pragma once
#include <memory>
#include <GEMath.h>
#include <string>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class World;
class Actor : public std::enable_shared_from_this<Actor>
{
private: // Static Var
public: // Static Func
private:
    World* m_WorldPtr;
    int m_Layer;
    bool m_WorldMove;
    bool m_Death;
    std::string NextWorldName;

public:
    std::string GetNextWorldName()
    {
        return NextWorldName;
    }

    void WorldMoveOn(std::string _NextWorld)
    {
        NextWorldName = _NextWorld;
        m_WorldMove = true;
    }

    void WorldMoveOff()
    {
        m_WorldMove = false;
    }

    bool IsWorldMove()
    {
        return m_WorldMove;
    }

    // 월드를 다 이동하기 전의 인터페이스
    virtual void WorldPrevMoveTask() {}

    // 월드를 다 이동하고 난후의 인터페이스
    virtual void WorldNextMoveTask() {}

    bool IsDeath() 
    {
        return m_Death;
    }

    void Death() 
    {
        m_Death = true;
    }

    virtual void DeathTask() 
    {
    }


public:
    void SetWorld(World* _WorldPtr)
    {
        m_WorldPtr = _WorldPtr;
    }

    World*  GetWorld()
    {
        return m_WorldPtr;
    }

    void SetLayer(int _Layer) 
    {
        m_Layer = _Layer;
    }

    int GetLayer() 
    {
        return m_Layer;
    }


public: // constructer destructer
    Actor();
    virtual ~Actor() = 0;

public: // delete constructer 
    Actor(const Actor& _Other) = delete;
    Actor(const Actor&& _Other) = delete;

public: // delete operator
    Actor& operator=(const Actor& _Other) = delete;
    Actor& operator=(const Actor&& _Other) = delete;

public: // member Func

    // 액터는 말그대로 인터페이스만 제공해주는 역할을 하고
    // 실제로 그 행동을 하는 것은 자식들이 됩니다.

    // void (*UpdatePrevCallBack)();

    // 넣어준 함수를 콜백으로 돌려주는 방법
    // 클라이언트는 클라이언트 함수 넣어주고
    // 서버는 서버함수 넣어주면
    // 동작이 달라질거 아니에요

    // 움직인다.
    virtual void UpdatePrev(float _DeltaTime)
    {
        // 클라이언트에서는 클라이언트 함수 넣어주고
        // 서버에서는 서버함수를 넣어주면 
        //if (nullptr != UpdatePrevCallBack)
        //{
        //    UpdatePrevCallBack();
        //}
    
    }
    virtual void Update(float _DeltaTime) {}
    virtual void UpdateNext(float _DeltaTime) {}

    // 상호작용한다.
    virtual void CollisionPrev() {}
    virtual void Collision() {}
    virtual void CollisionNext() {}

    // 결과를 정리한다.
    virtual void Release() {}

    virtual void Start() {}


    // 별로 좋지 않다.
/// <summary>
    // 아래있는 
    // GEVector m_Pos; 수학개념이죠?
    // 순수하게 오브젝트로서의 역할만 처리하게 하겠습니다.
};

