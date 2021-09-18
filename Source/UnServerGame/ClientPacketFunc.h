// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class AccountResultPacket;
class LoginResultPacket;
class CharacterPacket;
class GameStartPacket;
class PlayerUpdatePacket;
class MonsterUpdatePacket;
class ItemUpdatePacket;
class PotalUpdatePacket;
class WorldMoveOKPacket;
class RankPacket;
class PlayerUpdateDataPacket;
class MonsterUpdateDataPacket;
class ServerChatPacket;
class ServerPartyPacket;
class UNSERVERGAME_API ClientPacketFunc
{
private: // Static Var
public: // Static Func
    static void Init();
    static void AccountResultPacketProcess      (AccountResultPacket       _Packet);
    static void LoginResultPacketProcess        (LoginResultPacket         _Packet);
    static void CharacterPacketProcess          (CharacterPacket           _Packet);
    static void GameStartPacketProcess          (GameStartPacket           _Packet);
    static void PlayerUpdatePacketProcess       (PlayerUpdatePacket        _Packet);
    static void PlayerUpdateDataPacketProcess   (PlayerUpdateDataPacket        _Packet);
    static void MonsterUpdatePacketProcess      (MonsterUpdatePacket       _Packet);
    static void MonsterUpdateDataPacketProcess  (MonsterUpdateDataPacket       _Packet);
    static void ItemUpdatePacketProcess         (ItemUpdatePacket           _Packet);
    static void PotalUpdatePacketProcess        (PotalUpdatePacket _Packet);
    static void WorldMoveOKPacketProcess        (WorldMoveOKPacket _Packet);
    static void ServerChatPacketProcess         (ServerChatPacket _Packet);
    static void ServerPartyPacketProcess        (ServerPartyPacket _Packet);
    static void RankPacketProcess               (RankPacket _Packet);

private: // member Var

public:
	ClientPacketFunc();
	~ClientPacketFunc();
};
