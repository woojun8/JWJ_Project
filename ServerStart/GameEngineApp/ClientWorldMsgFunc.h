#pragma once
#include "ClientPlayer.h"
#include "ClientMonster.h"
#include <ClientConnecter.h>
#include <ClientToServer.h>
#include <ServerToClient.h>
// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class ClientWorldMsgFunc
{
public:
    static void WaitPlayerCreate(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data);
    static void WaitPlayerInWorld(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data);

    // �̰� ��ٷ� ���͸� ����� �����ϴ�.
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

