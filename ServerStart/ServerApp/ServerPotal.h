#pragma once
#include <WorldDataParser.h>
#include <Potal.h>
#include "ServerActor.h"
#include <ServerToClient.h>
// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerPotal : public Potal, public ServerActor
{
private: // Static Var
public: // Static Func
private: // member Var
    PotalData m_Data;

public:
    PotalData GetWorldMoveData() 
    {
        return m_Data;
    }

public:
    void SetPotalData(const PotalData& _Data);

public:
    PotalUpdateData GetPotalData(ActorState _State = ActorState::Update);

public: // constructer destructer
    ServerPotal();
    ~ServerPotal();

public: // delete constructer 
    ServerPotal(const ServerPotal& _Other) = delete;
    ServerPotal(const ServerPotal&& _Other) = delete;

public: // delete operator
    ServerPotal& operator=(const ServerPotal& _Other) = delete;
    ServerPotal& operator=(const ServerPotal&& _Other) = delete;

public: // member Func
    void CollisionPrev() override;
};

