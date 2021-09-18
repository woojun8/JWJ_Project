#pragma once
#include <Wall.h>
#include "ServerActor.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerWall : public Wall, public ServerActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    ServerWall();
    ~ServerWall();

public: // delete constructer 
    ServerWall(const ServerWall& _Other) = delete;
    ServerWall(const ServerWall&& _Other) = delete;

public: // delete operator
    ServerWall& operator=(const ServerWall& _Other) = delete;
    ServerWall& operator=(const ServerWall&& _Other) = delete;

public: // member Func
    virtual void CollisionPrev() override;
};

