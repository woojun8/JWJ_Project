#pragma once
#include <Player.h>
#include "ClientActor.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ClientPlayer : public Player, public ClientActor
{
private: // Static Var
public: // Static Func
private: // member Var
    float m_MoveDelay;
    float m_AttDelay;
    bool m_MainPlayer;

public:
    void MainPlayerOn() 
    {
        m_MainPlayer = true;
    }

public: // constructer destructer
    ClientPlayer();
    ~ClientPlayer();

public: // delete constructer 
    ClientPlayer(const ClientPlayer& _Other) = delete;
    ClientPlayer(const ClientPlayer&& _Other) = delete;

public: // delete operator
    ClientPlayer& operator=(const ClientPlayer& _Other) = delete;
    ClientPlayer& operator=(const ClientPlayer&& _Other) = delete;

public: // member Func
    virtual void UpdatePrev() override;
    virtual void Update() override;
    virtual void CollisionPrev() override;

public:
    void MoveCheck();

public:
    virtual void ColStay(GameActor* _this, GameActor* _Other);
};

