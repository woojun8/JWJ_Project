// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPacketFunc.h"
#include "UnWorldMsgFunc.h"
#include "UnServerConnect.h"
#include "UnActorManager.h"
#include "MainActor.h"
#include <ServerToClientPacketUpdater.h>
#include <ServerToClient.h>
#include <ClientToServer.h>
#include "RankWindow.h"
#include "PlayUI.h"

ClientPacketFunc::ClientPacketFunc()
{
}

ClientPacketFunc::~ClientPacketFunc()
{
}


void ClientPacketFunc::Init()
{
    STOCPACKETCALLBACK(AccountResultPacket);
    STOCPACKETCALLBACK(LoginResultPacket);
    STOCPACKETCALLBACK(CharacterPacket);
    STOCPACKETCALLBACK(GameStartPacket);
    STOCPACKETCALLBACK(PlayerUpdateDataPacket);
    STOCPACKETCALLBACK(PlayerUpdatePacket);
    STOCPACKETCALLBACK(MonsterUpdatePacket);
    STOCPACKETCALLBACK(MonsterUpdateDataPacket);
    STOCPACKETCALLBACK(ItemUpdatePacket);
    STOCPACKETCALLBACK(PotalUpdatePacket);
    STOCPACKETCALLBACK(WorldMoveOKPacket);
    STOCPACKETCALLBACK(ServerChatPacket);
    STOCPACKETCALLBACK(ServerPartyPacket);
    STOCPACKETCALLBACK(RankPacket);
}

void ClientPacketFunc::CharacterPacketProcess(CharacterPacket _Packet)
{
    // [0][][][][]
    // [][][][][]
    // [][][][][]
    // [][][][0][]
    // [][][][][]

    UnServerConnect::GetInst().m_CharacterData = _Packet;
    UnServerConnect::GetInst().m_CharacterData.ItemDatas.clear();
    UnServerConnect::GetInst().m_CharacterData.ItemDatas.resize(25);

    for (size_t i = 0; i < UnServerConnect::GetInst().m_CharacterData.FriendDatas.size(); i++)
    {
        UE_LOG(LogTemp, Error, L"Friend! %lld", UnServerConnect::GetInst().m_CharacterData.FriendDatas[i]);
    }

    for (size_t i = 0; i < _Packet.ItemDatas.size(); i++)
    {
        UnServerConnect::GetInst().m_CharacterData.ItemDatas[_Packet.ItemDatas[i].InvenOrder] = _Packet.ItemDatas[i];
    }

    UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::PlayerCreate, _Packet);
}

void ClientPacketFunc::RankPacketProcess(RankPacket _Packet) 
{
    for (size_t i = 0; i < _Packet.m_RankDataList.size(); i++)
    {
        RankData Data = _Packet.m_RankDataList[i];

        UE_LOG(LogTemp, Error, L"Rank %d : %s : %d", Data.Rank, Data.Name.ConstStringPtr(), Data.Score);
    }

    
    UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::RankSetting, _Packet);
}

void ClientPacketFunc::AccountResultPacketProcess(AccountResultPacket _Packet)
{
    // 그냥 여기서 언리얼 클라이언트 코드를 치듯이 치면 동작이 될겁니다.

    if (0 != _Packet.m_Code)
    {
        UnServerConnect::GetInst().m_Login = 0;
        UE_LOG(LogTemp, Error, L"Login Error ");
    }
    else
    {
        UnServerConnect::GetInst().m_Login = 1;
        UE_LOG(LogTemp, Error, L"Login OK ");
    }
}

void ClientPacketFunc::LoginResultPacketProcess(LoginResultPacket _Packet)
{
    // 직접 쳐야할때가 있죠?
    // 컨텐츠 코드를 언리얼식으로 다시치게 된다.
    // 이걸 짜는건 서버일까요?
    // 크리티컬 섹션 걸면 되지 않느냐?
    // 프리락방식이라 컨텍스트 스위칭이 발생시키지 않아.
    // 락을 걸지 않았느냐?
    if (0 != _Packet.m_Code)
    {
        UnServerConnect::GetInst().m_Login = 0;
        UE_LOG(LogTemp, Error, L"Login Error ");
    }
    else
    {
        UnServerConnect::GetInst().m_Login = 1;
        UE_LOG(LogTemp, Error, L"Login OK ");



        // UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::PlayerCreate);
        // Recv쓰레드에서 

    }
}

void ClientPacketFunc::GameStartPacketProcess(GameStartPacket _Packet)
{
    UnServerConnect::GetInst().m_GameStart.Exchange(1);
    // UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::WaitPlayerCreate, Data);
    // 
}

void ClientPacketFunc::PlayerUpdatePacketProcess(PlayerUpdatePacket _Packet)
{
    if (0 == _Packet.m_PlayerData.size())
    {
        // 이건 맞고
        return;
    }

    for (size_t i = 0; i < _Packet.m_PlayerData.size(); i++)
    {
        PlayerUpdateDataPacketProcess(_Packet.m_PlayerData[i]);


    }
}

void ClientPacketFunc::PlayerUpdateDataPacketProcess(PlayerUpdateDataPacket        _Packet)
{
    ActorState State = _Packet.m_State;
    // PlayerUpdateDataPacket Data = _Packet;
    switch (State)
    {
    case ActorState::Wait:
    {
        UE_LOG(LogTemp, Error, L"PlayerPacket Wait");
        UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::WaitPlayerCreate, _Packet);
        break;
    }
    case ActorState::in:
        UE_LOG(LogTemp, Error, L"PlayerPacket in");
        UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::WaitPlayerInWorld, _Packet);
        break;
    case ActorState::Update:
    case ActorState::Att:
        //if (State == ActorState::Att)
        //{
        //    UE_LOG(LogTemp, Error, L"ATTT");
        //}
        // UE_LOG(LogTemp, Error, L"PlayerPacket Update");
        UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::UpdatePlayer, _Packet);
        break;
    case ActorState::Death:
        UE_LOG(LogTemp, Error, L"PlayerPacket Death");
        UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::DeathPlayer, _Packet);
        break;
    case ActorState::WorldMove:
        UE_LOG(LogTemp, Error, L"PlayerPacket WorldMove");
        UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::WorldMovePlayer, _Packet);
        break;
    default:
        break;
    }

}

void ClientPacketFunc::MonsterUpdateDataPacketProcess(MonsterUpdateDataPacket       _Packet)
{
    ActorState State = _Packet.m_State;
    switch (State)
    {
    case ActorState::Update:
        UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::UpdateMonster, _Packet);
        break;
    case ActorState::Death:
        UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::DeathMonster, _Packet);
        break;
    default:
        break;
    }
}

void ClientPacketFunc::MonsterUpdatePacketProcess(MonsterUpdatePacket _Packet)
{
    if (0 == _Packet.m_MonsterData.size())
    {
        return;
    }

    // 클라이언트 월드라고 다른 처리를 하지는 않는다.
    // 메세지로 처리합니다.
    //LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex.GetConvertMultiByteString(),
    //    &WorldMsgFunc::WaitActorInWorld, Socket);

    // 여기 들어왔을때.
    for (size_t i = 0; i < _Packet.m_MonsterData.size(); i++)
    {

        MonsterUpdateDataPacketProcess(_Packet.m_MonsterData[i]);

    }
}


void ClientPacketFunc::ItemUpdatePacketProcess(ItemUpdatePacket _Packet)
{
    if (0 == _Packet.m_ItemUpdateDataList.size())
    {
        return;
    }

    // 클라이언트 월드라고 다른 처리를 하지는 않는다.
    // 메세지로 처리합니다.
    //LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex.GetConvertMultiByteString(),
    //    &WorldMsgFunc::WaitActorInWorld, Socket);

    // 여기 들어왔을때.
    for (size_t i = 0; i < _Packet.m_ItemUpdateDataList.size(); i++)
    {
        ActorState State = _Packet.m_ItemUpdateDataList[i].m_State;
        ItemUpdateData Data = _Packet.m_ItemUpdateDataList[i];
        switch (State)
        {
        case ActorState::Update:
            UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::UpdateItem, Data);
            // ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::UpdateMonster, Connecter, Data);
            break;
        case ActorState::Death:
            UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::DeathItem, Data);
            // ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::DeathMonster, Connecter, Data);
            break;
        default:
            break;
        }
    }
}

void ClientPacketFunc::PotalUpdatePacketProcess(PotalUpdatePacket _Packet)
{
    UE_LOG(LogTemp, Error, L"World Size !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! %d %d", _Packet.WorldSizeX, _Packet.WorldSizeY);
    UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::WorldCreate, _Packet.WorldSizeX, _Packet.WorldSizeY);

    for (size_t i = 0; i < _Packet.m_UpdateDataList.size(); i++)
    {
        UE_LOG(LogTemp, Error, L"Potal!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::UpdatePotal, _Packet.m_UpdateDataList[i]);
    }
}

void ClientPacketFunc::WorldMoveOKPacketProcess(WorldMoveOKPacket _Packet) 
{
    UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::WorldDestroy, _Packet);
    // UnActorManager::GetInst().ActorRelease();
}

void ClientPacketFunc::ServerChatPacketProcess(ServerChatPacket _Packet)
{
    // UE_LOG(LogTemp, Error, L"ServerChatPacket");
    UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::ChatMessage, _Packet);
}

void ClientPacketFunc::ServerPartyPacketProcess(ServerPartyPacket _Packet)
{
    UnServerConnect::GetInst().MsgInsert(&UnWorldMsgFunc::PartyMessage, _Packet);
}
