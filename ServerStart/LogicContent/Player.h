#pragma once
#include "GameActor.h"
#include <queue>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 게임에서 플레이어 역할을 한다.
class ActorUpdateData;
class Player : public GameActor
{
private: // Static Var
public: // Static Func
private: // member Var
    // 플레이어가 자신이 존재하는 월드키를 알고 있어야 한다.
    int Hp;
    bool m_MoveCheck;
    bool m_AttCheck;
    // 쌓아놓기 위한 Queue입니다.
public:
    bool IsMoveCheck() 
    {
        return m_MoveCheck;
    }

    void MoveCheckOn() 
    {
        m_MoveCheck = true;
    }

    void MoveCheckOff() {
        m_MoveCheck = false;
    }

    bool IsAttCheck()
    {
        return m_AttCheck;
    }

    void AttCheckOn()
    {
        m_AttCheck = true;
    }

    void AttCheckOff() {
        m_AttCheck = false;
    }


public: // constructer destructer
    Player();
    ~Player();

public: // delete constructer 
    Player(const Player& _Other) = delete;
    Player(const Player&& _Other) = delete;

public: // delete operator
    Player& operator=(const Player& _Other) = delete;
    Player& operator=(const Player&& _Other) = delete;

public: // member Func
    virtual void Start() override;
};

