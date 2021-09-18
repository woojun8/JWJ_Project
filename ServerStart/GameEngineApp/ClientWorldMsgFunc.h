#pragma once
#include "ClientPlayer.h"
#include "ClientMonster.h"
#include <ClientConnecter.h>
#include <ClientToServer.h>
#include <ServerToClient.h>
// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ClientWorldMsgFunc
{
public:
    static void WaitPlayerCreate(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data);
    static void WaitPlayerInWorld(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data);

    // 이건 곧바로 액터를 만들어 버립니다.
    static void UpdatePlayer(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data);
    static void DeathPlayer(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data);


    static void UpdateMonster(World* _World, ClientConnecter* _Connecter, MonsterUpdateData Data);
    static void DeathMonster(World* _World, ClientConnecter* _Connecter, MonsterUpdateData Data);

    static void UpdateItem(World* _World, ClientConnecter* _Connecter, ItemUpdateData Data);
    static void DeathItem(World* _World, ClientConnecter* _Connecter, ItemUpdateData Data);

    static void UpdatePotal(World* _World, ClientConnecter* _Connecter, PotalUpdateData Data);

private: // constructer destructer
    ClientWorldMsgFunc();
    ~ClientWorldMsgFunc();
};

