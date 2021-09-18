#pragma once
#include "GameActor.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 게임에서 몬스터 역할을 한다.
class Monster : public GameActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Monster();
    virtual ~Monster();

public: // delete constructer 
    Monster(const Monster& _Other) = delete;
    Monster(const Monster&& _Other) = delete;

public: // delete operator
    Monster& operator=(const Monster& _Other) = delete;
    Monster& operator=(const Monster&& _Other) = delete;

public: // member Func
    void Start() override;
};

