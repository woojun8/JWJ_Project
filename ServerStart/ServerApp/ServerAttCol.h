#pragma once
#include <GameActor.h>
#include "ServerActor.h"


// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerAttCol : public GameActor, public ServerActor
{
public: // constructer destructer
    ServerAttCol();
    ~ServerAttCol();

public: // delete constructer 
    ServerAttCol(const ServerAttCol& _Other) = delete;
    ServerAttCol(const ServerAttCol&& _Other) = delete;

public: // delete operator
    ServerAttCol& operator=(const ServerAttCol& _Other) = delete;
    ServerAttCol& operator=(const ServerAttCol&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update(float _DeltaTime) override;
    void ColStay(GameActor* _Left, GameActor* _Right);
};

