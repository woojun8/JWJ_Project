#pragma once
#include <GameWorld.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ClientWorld : public GameWorld
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    ClientWorld();
    ~ClientWorld();

public: // delete constructer 
    ClientWorld(const ClientWorld& _Other) = delete;
    ClientWorld(const ClientWorld&& _Other) = delete;

public: // delete operator
    ClientWorld& operator=(const ClientWorld& _Other) = delete;
    ClientWorld& operator=(const ClientWorld&& _Other) = delete;

public: // member Func
    virtual void CreateWallPos(const Sizefloat4& _Pos) override;
    virtual void CreatePotalPos(const PotalData& _PotalData) override;

};

