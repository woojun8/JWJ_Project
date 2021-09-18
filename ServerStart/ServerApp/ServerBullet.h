#pragma once
#include <Bullet.h>
#include "ServerActor.h"
#include <ServerToClient.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerBullet : public Bullet, public ServerActor
{
private: // Static Var
public: // Static Func
private: // member Var


public: // constructer destructer
    ServerBullet();
    ~ServerBullet();

public: // delete constructer 
    ServerBullet(const ServerBullet& _Other) = delete;
    ServerBullet(const ServerBullet&& _Other) = delete;

public: // delete operator
    ServerBullet& operator=(const ServerBullet& _Other) = delete;
    ServerBullet& operator=(const ServerBullet&& _Other) = delete;

public: // member Func
    
    void Update(float _DeltaTime) override;
    void ColStay(GameActor* _Left, GameActor* _Right);
};

