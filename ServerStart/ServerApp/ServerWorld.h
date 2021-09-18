#pragma once
#include <GameWorld.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerWorld : public GameWorld
{
private: // Static Var
public: // Static Func
    int CurMonsterCount;
    float CurMonsterCreateTime;

private: // member Var
    void WorldUpdate() override;

public: // constructer destructer
    ServerWorld();
    ~ServerWorld();

public: // delete constructer 
    ServerWorld(const ServerWorld& _Other) = delete;
    ServerWorld(const ServerWorld&& _Other) = delete;

public: // delete operator
    ServerWorld& operator=(const ServerWorld& _Other) = delete;
    ServerWorld& operator=(const ServerWorld&& _Other) = delete;

public: // member Func
    virtual void CreateWallPos(const float4& _Pos, const float4& _Size) override;
    virtual void CreatePotalPos(const PotalData& _PotalData) override;

};

