#pragma once
#include <GEMath.h>
#include "PacketType.h"
#include <queue>
#include <Actor.h>
#include <GameEngineDebug.h>
#include <GameEngineCollision.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 게임에서 기본 인터페이스인 위치를 담당한다.
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



    

    // 서버에서는 
    // 클라이언트라면
    // 서버는 로컬과 월드가 보통 필요가 없습니다.
    Posfloat4  m_Pos;   // 위치
    Sizefloat4 m_Scale; // 크기
    Sizefloat4 m_Rot;   // 회전

    // 회전처리는 이녀석을 이용할것이고
    // obb나 회전한 충돌체에 대한 처리는 이 사원수를 이용해서 처리할 겁니다.
    // obb 보통 서버게임에서 사용하지 않는다.
    Sizefloat4 m_Quaternion; // 사원수

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

    // 콘솔때나 필요햇던거고
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
    // 충돌했을시 자식들이 재구현하면 호출되는 함수
    virtual void ColStay(GameActor* _this, GameActor* _Other) {}
};

