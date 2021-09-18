#pragma once
#include "GameActor.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class Potal : public GameActor
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    Potal();
    ~Potal();

public: // delete constructer 
    Potal(const Potal& _Other) = delete;
    Potal(const Potal&& _Other) = delete;

public: // delete operator
    Potal& operator=(const Potal& _Other) = delete;
    Potal& operator=(const Potal&& _Other) = delete;

public: // member Func
    virtual void Start() override;
};

