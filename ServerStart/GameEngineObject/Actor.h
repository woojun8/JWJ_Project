#pragma once
#include <memory>
#include <GEMath.h>
#include <string>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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

    // ���带 �� �̵��ϱ� ���� �������̽�
    virtual void WorldPrevMoveTask() {}

    // ���带 �� �̵��ϰ� ������ �������̽�
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

    // ���ʹ� ���״�� �������̽��� �������ִ� ������ �ϰ�
    // ������ �� �ൿ�� �ϴ� ���� �ڽĵ��� �˴ϴ�.

    // void (*UpdatePrevCallBack)();

    // �־��� �Լ��� �ݹ����� �����ִ� ���
    // Ŭ���̾�Ʈ�� Ŭ���̾�Ʈ �Լ� �־��ְ�
    // ������ �����Լ� �־��ָ�
    // ������ �޶����� �ƴϿ���

    // �����δ�.
    virtual void UpdatePrev(float _DeltaTime)
    {
        // Ŭ���̾�Ʈ������ Ŭ���̾�Ʈ �Լ� �־��ְ�
        // ���������� �����Լ��� �־��ָ� 
        //if (nullptr != UpdatePrevCallBack)
        //{
        //    UpdatePrevCallBack();
        //}
    
    }
    virtual void Update(float _DeltaTime) {}
    virtual void UpdateNext(float _DeltaTime) {}

    // ��ȣ�ۿ��Ѵ�.
    virtual void CollisionPrev() {}
    virtual void Collision() {}
    virtual void CollisionNext() {}

    // ����� �����Ѵ�.
    virtual void Release() {}

    virtual void Start() {}


    // ���� ���� �ʴ�.
/// <summary>
    // �Ʒ��ִ� 
    // GEVector m_Pos; ���а�������?
    // �����ϰ� ������Ʈ�μ��� ���Ҹ� ó���ϰ� �ϰڽ��ϴ�.
};

