#pragma once
#include "GameActor.h"

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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

