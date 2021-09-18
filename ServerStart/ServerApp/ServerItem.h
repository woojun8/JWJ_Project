#pragma once
#include <Item.h>
#include "ServerActor.h"
#include <ServerToClient.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerItem : public Item, public ServerActor
{
private: // Static Var
public: // Static Func
private: // member Var
    // 자신이 죽을 획득한 유저가 있으면 먹은 유저의 UpdateId를 기억해놔야 가능하겠죠.

    // 자신을 먹은 유저의 id를 기록해놓고
    // 그 유저에게는 다른 정보를 보내준다.

public:
    __int64 EventPlayer;
    ItemData Data;


public:
    ItemUpdateData GetItemData(ActorState _State = ActorState::Update);

public: // constructer destructer
    ServerItem();
    ~ServerItem();

public: // delete constructer 
    ServerItem(const ServerItem& _Other) = delete;
    ServerItem(const ServerItem&& _Other) = delete;

public: // delete operator
    ServerItem& operator=(const ServerItem& _Other) = delete;
    ServerItem& operator=(const ServerItem&& _Other) = delete;

public:
    void DeathTask() override;
};

