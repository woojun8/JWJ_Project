#pragma once
#include <Player.h>
#include "ServerActor.h"
#include <ServerConnecter.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerPlayer : public Player, public ServerActor
{
private: // Static Var
public: // Static Func
private: // member Var
    float m_MoveDelay;
    ServerConnecter* Connecter;

public:
    void SetConnecter(ServerConnecter* _Connecter) 
    {
        Connecter = _Connecter;
    }

    ServerConnecter* GetConnecter()
    {
        return Connecter;
    }

public: // constructer destructer
    ServerPlayer();
    ~ServerPlayer();

public: // delete constructer 
    ServerPlayer(const ServerPlayer& _Other) = delete;
    ServerPlayer(const ServerPlayer&& _Other) = delete;

public: // delete operator
    ServerPlayer& operator=(const ServerPlayer& _Other) = delete;
    ServerPlayer& operator=(const ServerPlayer&& _Other) = delete;

public: // member Func
    virtual void UpdatePrev(float _DeltaTime) override;
    virtual void Update(float _DeltaTime) override;
    virtual void CollisionPrev() override;

public:
    void MoveCheck();

public:
    virtual void ColStay(GameActor* _this, GameActor* _Other);
    virtual void DeathTask();
    void WorldPrevMoveTask() override;
    void WorldNextMoveTask() override;
};

