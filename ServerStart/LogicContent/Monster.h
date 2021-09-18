#pragma once
#include "GameActor.h"

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : ���ӿ��� ���� ������ �Ѵ�.
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

