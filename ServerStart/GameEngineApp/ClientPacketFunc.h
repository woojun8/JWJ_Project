#pragma once
#include <ServerToClient.h>
#include <ClientConnecter.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ClientPacketFunc
{
private: // Static Var
public: // Static Func
    static void Init();
    static void AccountResultPacketProcess(AccountResultPacket& _Packet);
    static void LoginResultPacketProcess(LoginResultPacket& _Packet);
    static void CharacterPacketProcess(CharacterPacket& _Packet);
    static void GameStartPacketProcess(GameStartPacket& _Packet);
    static void PlayerUpdatePacketProcess(PlayerUpdatePacket& _Packet);
    static void MonsterUpdatePacketProcess(MonsterUpdatePacket& _Packet);
    static void ItemUpdatePacketProcess(ItemUpdatePacket& _Packet);
    static void PotalUpdatePacketProcess(PotalUpdatePacket& _Packet);
    static void WorldMoveOKPacketProcess(WorldMoveOKPacket& _Packet);

private: // member Var

public: // constructer destructer
    ClientPacketFunc() {}
    ~ClientPacketFunc() {}

public: // delete constructer 
    ClientPacketFunc(const ClientPacketFunc& _Other) = delete;
    ClientPacketFunc(const ClientPacketFunc&& _Other) = delete;

public: // delete operator
    ClientPacketFunc& operator=(const ClientPacketFunc& _Other) = delete;
    ClientPacketFunc& operator=(const ClientPacketFunc&& _Other) = delete;
public: // member Func
};

