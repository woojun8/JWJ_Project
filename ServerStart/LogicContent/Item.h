#pragma once
#include "GameActor.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class Item : public GameActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Item();
    ~Item();

public: // delete constructer 
    Item(const Item& _Other) = delete;
    Item(const Item&& _Other) = delete;

public: // delete operator
    Item& operator=(const Item& _Other) = delete;
    Item& operator=(const Item&& _Other) = delete;


public: // member Func
    void Start() override;
};

