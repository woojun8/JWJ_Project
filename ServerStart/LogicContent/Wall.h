#pragma once
#include "GameActor.h"


// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : ���ӿ��� ������ �ܺ� ������ �Ѵ�.
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

