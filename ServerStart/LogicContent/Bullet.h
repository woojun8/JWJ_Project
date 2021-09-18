#pragma once
#include "GameActor.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class Bullet : public GameActor
{
private: // Static Var
public: // Static Func
protected: // member Var
    float Speed;
    float4 Dir;
    float DeathTime;
    GameActor* m_Actor;

public:
    GameActor* Master() 
    {
        return m_Actor;
    }

    void BulletSetting
    (
        float _Speed,
        float4 _Dir,
        float _DeathTime,
        GameActor* _Actor
    ) 
    {
        Speed = _Speed;
        Dir = _Dir;
        DeathTime = _DeathTime;
        m_Actor = _Actor;
    }

public: // constructer destructer
    Bullet();
    ~Bullet();

public: // delete constructer 
    Bullet(const Bullet& _Other) = delete;
    Bullet(const Bullet&& _Other) = delete;

public: // delete operator
    Bullet& operator=(const Bullet& _Other) = delete;
    Bullet& operator=(const Bullet&& _Other) = delete;

public: // member Func
    void Start() override;
};

