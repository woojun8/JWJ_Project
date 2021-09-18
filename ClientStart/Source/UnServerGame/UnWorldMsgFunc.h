// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
// 여기서 전방선으로처리하는 이유는
// 헤더가 추가되서 언리얼과 충돌하는 상황을 최대한 막기 위해서 입니다.
class MonsterUpdateData;
class PlayerUpdateData;
class CharacterPacket;
class ItemUpdateData;
class PotalUpdateData;
class RankPacket;
class WorldMoveOKPacket;
class PlayerUpdateDataPacket;
class MonsterUpdateDataPacket;
class ServerChatPacket;
class ServerPartyPacket;
class UNSERVERGAME_API UnWorldMsgFunc
{
public:
	static void PlayerCreate(UWorld* _World, CharacterPacket _Packet);

	static void WaitPlayerCreate(UWorld* _World, PlayerUpdateDataPacket Data);
    static void WaitPlayerInWorld(UWorld* _World, PlayerUpdateDataPacket Data);

    static void UpdatePlayer(UWorld* _World, PlayerUpdateDataPacket Data);
    static void DeathPlayer(UWorld* _World, PlayerUpdateDataPacket Data);
    static void WorldMovePlayer(UWorld* _World, PlayerUpdateDataPacket Data);

    static void UpdateMonster(UWorld* _World, MonsterUpdateDataPacket Data);
    static void DeathMonster(UWorld* _World, MonsterUpdateDataPacket Data);

    static void UpdateItem(UWorld* _World, ItemUpdateData Data);
    static void DeathItem(UWorld* _World, ItemUpdateData Data);

    static void UpdatePotal(UWorld* _World, PotalUpdateData Data);
    static void WorldCreate(UWorld* _World, int _X, int _Y);
    static void WorldDestroy(UWorld* _World, WorldMoveOKPacket _Pacekt);

    static void RankSetting(UWorld* _World, RankPacket _Packet);

    static void ChatMessage(UWorld* _World, ServerChatPacket _Packet);

    static void PartyMessage(UWorld* _World, ServerPartyPacket _Packet);
private:
	UnWorldMsgFunc();
	virtual ~UnWorldMsgFunc() = 0;
};
