#pragma once
#include <GEMath.h>
#include "PacketType.h"
#include <queue>
#include <Actor.h>
#include <GameEngineDebug.h>
#include <GameEngineCollision.h>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : ���ӿ��� �⺻ �������̽��� ��ġ�� ����Ѵ�.
class GameWorld;
class GameActor : public Actor
{
private: // Static Var
public: // Static Func
private: // member Var
private:
    bool ColOnOff;

    GameWorld* m_ParentWorld;
    bool m_IsMove;



    

    // ���������� 
    // Ŭ���̾�Ʈ���
    // ������ ���ð� ���尡 ���� �ʿ䰡 �����ϴ�.
    Posfloat4  m_Pos;   // ��ġ
    Sizefloat4 m_Scale; // ũ��
    Sizefloat4 m_Rot;   // ȸ��

    // ȸ��ó���� �̳༮�� �̿��Ұ��̰�
    // obb�� ȸ���� �浹ü�� ���� ó���� �� ������� �̿��ؼ� ó���� �̴ϴ�.
    // obb ���� �������ӿ��� ������� �ʴ´�.
    Sizefloat4 m_Quaternion; // �����

public:

    bool GetIsCol() {
        return ColOnOff;
    }

    void SetColOn() {
        ColOnOff = true;
    }


    void SetColOff() {
        ColOnOff = false;
    }

    void SetScale(float4 _Scale)
    {
        m_Scale = _Scale;
        Data.SetScale(m_Scale);
    }


    void SetAddRotX(float _Rot)
    {
        m_Rot.x += _Rot;
    }

    void SetPos(Posfloat4  _Pos)
    {
        m_Pos = _Pos;
    }

    void SetMovePos(Posfloat4  _Pos)
    {
        m_Pos += _Pos;
    }

    // �ֶܼ��� �ʿ��޴��Ű�
    bool IsMove()
    {
        return m_IsMove;
    }

    inline bool MoveCheckReset()
    {
        bool Check = m_IsMove;
        m_IsMove = false;
        return Check;
    }

    inline GEVector GetRot()
    {
        return m_Rot;
    }

    inline GEVector GetPos()
    {
        return m_Pos;
    }


protected:
    std::queue<ActorUpdateData> m_UpdateData;

public:
    void PushUpdateData(const ActorUpdateData& _Data) {
        m_UpdateData.push(_Data);
    }


public: // constructer destructer
    GameActor();
    ~GameActor();

public: // delete constructer 
    GameActor(const GameActor& _Other) = delete;
    GameActor(const GameActor&& _Other) = delete;

public: // delete operator
    GameActor& operator=(const GameActor& _Other) = delete;
    GameActor& operator=(const GameActor&& _Other) = delete;

private: // CollisionData
    int m_ColOrder;
    COLTYPE m_Type;
    GameEngineColData Data;

public:
    GameEngineColData& GetCollisionDataRef() 
    {
        return Data;
    }

public:
    void Setting();
    void SetColOrder(int _ColOrder, float4 _Scale, COLTYPE _ColType);

    int GetColOrder()
    {
        return m_ColOrder;
    }

    COLTYPE GetColType()
    {
        return m_Type;
    }


public: // member Func
    // �浹������ �ڽĵ��� �籸���ϸ� ȣ��Ǵ� �Լ�
    virtual void ColStay(GameActor* _this, GameActor* _Other) {}
};

