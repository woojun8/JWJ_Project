#pragma once
#include "GameActor.h"


// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 게임에서 월드의 외벽 역할을 한다.
class Wall : public GameActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Wall();
    ~Wall();

public: // delete constructer 
    Wall(const Wall& _Other) = delete;
    Wall(const Wall&& _Other) = delete;

public: // delete operator
    Wall& operator=(const Wall& _Other) = delete;
    Wall& operator=(const Wall&& _Other) = delete;

public: // member Func
    virtual void Start() override;
};

