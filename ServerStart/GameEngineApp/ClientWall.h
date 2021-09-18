#pragma once
#include <Wall.h>
#include "ClientActor.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ClientWall : public Wall, public ClientActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    ClientWall();
    ~ClientWall();

public: // delete constructer 
    ClientWall(const ClientWall& _Other) = delete;
    ClientWall(const ClientWall&& _Other) = delete;

public: // delete operator
    ClientWall& operator=(const ClientWall& _Other) = delete;
    ClientWall& operator=(const ClientWall&& _Other) = delete;

public: // member Func
    virtual void CollisionPrev() override;
};

