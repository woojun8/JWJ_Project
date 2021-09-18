#pragma once
#include <Wall.h>
#include "ServerActor.h"

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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

