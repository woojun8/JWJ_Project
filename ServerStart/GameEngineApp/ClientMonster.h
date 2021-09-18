#pragma once
#include <Monster.h>
#include "ClientActor.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ClientMonster : public Monster, public ClientActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    ClientMonster();
    ~ClientMonster();

public: // delete constructer 
    ClientMonster(const ClientMonster& _Other) = delete;
    ClientMonster(const ClientMonster&& _Other) = delete;

public: // delete operator
    ClientMonster& operator=(const ClientMonster& _Other) = delete;
    ClientMonster& operator=(const ClientMonster&& _Other) = delete;

public: // member Func
    virtual void CollisionPrev() override;
};

