// Fill out your copyright notice in the Description page of Project Settings.


#include "UnWorldMsgFunc.h"
#include "Player/PlayerCharacter.h"
#include "Block.h"
#include "MainActor.h"
#include "OtherPlayer.h"
#include "Item.h"
#include "UnActorManager.h"
#include <ServerToClient.h>
#include "PlayUI.h"
#include "InventoryWindow.h"
#include "RankWindow.h"
#include "PartyWindow.h"
#include "UnServerConnect.h"
#include "Components/ListView.h"
#include "ChatObject.h"
#include "PartyData.h"
#include <LogicValue.h>

UnWorldMsgFunc::UnWorldMsgFunc()
{
}

UnWorldMsgFunc::~UnWorldMsgFunc()
{
}


void UnWorldMsgFunc::PlayerCreate(UWorld* _World, CharacterPacket _Packet)
{
    //AMainActor::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY), 0 });
    //UnActorManager::GetInst().ActorManagerInit(&AMainActor::GetInst(), _World);

    APlayerCharacter::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY), 0 });
    UnActorManager::GetInst().ActorManagerInit(&APlayerCharacter::GetInst(), _World);
}

void UnWorldMsgFunc::WaitPlayerCreate(UWorld* _World, PlayerUpdateDataPacket Data)
{    
    /*AOtherPlayer* NewOtherPlayer = UnActorManager::GetInst().CreateServerManagerWaitObject<AOtherPlayer>(AMainActor::GetInst().m_OtherPlayerCreateType, { Data.m_Data.Pos.x,Data.m_Data.Pos.y,0}, (int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID);
    if (nullptr != NewOtherPlayer)
    {
        NewOtherPlayer->SetActorScale3D( { 100.0f, 100.0f, 100.0f });
    }*/

    AOtherPlayer* NewOtherPlayer = UnActorManager::GetInst().CreateServerManagerWaitObject<AOtherPlayer>(APlayerCharacter::GetInst().m_OtherPlayerCreateType, { Data.m_Data.Pos.x,Data.m_Data.Pos.y,0}, (int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID);
    if (nullptr != NewOtherPlayer)
    {
        NewOtherPlayer->SetActorScale3D({ 1.0f, 1.f, 1.0f});
        //NewOtherPlayer->SetActorScale3D({ Data.m_Data.Scale.x, Data.m_Data.Scale.y, Data.m_Data.Scale.z });
    }
}

void UnWorldMsgFunc::WaitPlayerInWorld(UWorld* _World, PlayerUpdateDataPacket Data)
{
    // 없으면 그냥 만들어버리면 되기는 하는데...
    AOtherPlayer* FindPtr = UnActorManager::GetInst().FindIDWaitActor<AOtherPlayer>((int)LogicValue::CollisionLayer::PLAYER,Data.UpdateID);

    if (nullptr == FindPtr)
    {
        UE_LOG(LogTemp, Log, TEXT("%f, %f"), Data.m_Data.Pos.x, Data.m_Data.Pos.y);
        //AOtherPlayer* NewPlayer = UnActorManager::GetInst().CreateServerManagerObjectToCol<AOtherPlayer>(AMainActor::GetInst().m_OtherPlayerCreateType, { Data.m_Data.Pos.x, Data.m_Data.Pos.y, Data.m_Data.Pos.z }, (int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
        AOtherPlayer* NewPlayer = UnActorManager::GetInst().CreateServerManagerObjectToCol<AOtherPlayer>(APlayerCharacter::GetInst().m_OtherPlayerCreateType, { Data.m_Data.Pos.x, Data.m_Data.Pos.y, Data.m_Data.Pos.z }, (int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
        if (nullptr != NewPlayer)
        {
            NewPlayer->SetActorScale3D({ 1.0f, 1.f, 1.0f});
            //NewPlayer->SetActorScale3D({ Data.m_Data.Scale.x, Data.m_Data.Scale.y, Data.m_Data.Scale.z });
        }
        UE_LOG(LogTemp, Error, TEXT("WaitPlayerInWorld if (nullptr == FindPtr) %lld"), Data.UpdateID);
        return;
    }

    AOtherPlayer* PlayerPtr = UnActorManager::GetInst().WaitActorInActorCol<AOtherPlayer>((int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID, {100.0f, 100.0f, 100.0f}, COLTYPE::CT_SPHERE);

    if (nullptr != PlayerPtr)
    {
        PlayerPtr->SetActorScale3D({ 1.0f, 1.f, 1.0f});
        //PlayerPtr->SetActorScale3D({ Data.m_Data.Scale.x, Data.m_Data.Scale.y, Data.m_Data.Scale.z });
        PlayerPtr->SetActorLocation({ Data.m_Data.Pos.x, Data.m_Data.Pos.y, Data.m_Data.Pos.z });
    }
    // 이녀석을 꺼놓고 동작하지 못하게 하는 기능이 필요하다.
    // UnActorManager::GetInst().PushIDActor(Data.UpdateID, FindPtr);
}

void UnWorldMsgFunc::UpdatePlayer(UWorld* _World, PlayerUpdateDataPacket Data)
{
    AOtherPlayer* FindPtr = UnActorManager::GetInst().FindIDActor<AOtherPlayer>((int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID);

    // 혹시나 죽었다고 하더라도 
    if (nullptr == FindPtr)
    {
        UE_LOG(LogTemp, Log, TEXT("%f, %f"), Data.m_Data.Pos.x, Data.m_Data.Pos.y);
        //AOtherPlayer* NewPlayer = UnActorManager::GetInst().CreateServerManagerObjectToCol<AOtherPlayer>(AMainActor::GetInst().m_OtherPlayerCreateType, { Data.m_Data.Pos.x, Data.m_Data.Pos.y, Data.m_Data.Pos.z }, (int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID, {100.0f, 100.0f, 100.0f}, COLTYPE::CT_SPHERE);
        AOtherPlayer* NewPlayer = UnActorManager::GetInst().CreateServerManagerObjectToCol<AOtherPlayer>(APlayerCharacter::GetInst().m_OtherPlayerCreateType, { Data.m_Data.Pos.x, Data.m_Data.Pos.y, Data.m_Data.Pos.z }, (int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
        if (nullptr != NewPlayer)
        {
            NewPlayer->SetActorScale3D({ 1.0f, 1.f, 1.0f});
            //NewPlayer->SetActorScale3D({ Data.m_Data.Scale.x, Data.m_Data.Scale.y, Data.m_Data.Scale.z });
        }
        return;
    }

    FindPtr->PushUpdateData(Data.m_Data);

    // 이렇게 바꿔주고 있단 말이야.
    // FindPtr->SetActorLocation(FVector(Data.m_Data.Pos.x, Data.m_Data.Pos.y, 0.0f));

    // FindPtr->AddActorLocalOffset(FVector(Data.MoveDir.x, Data.MoveDir.y, 0.0f));
    // NewActor->SetClientPos(Data.CurPos);

}
void UnWorldMsgFunc::DeathPlayer(UWorld* _World, PlayerUpdateDataPacket Data)
{
    AActor* FindActor = UnActorManager::GetInst().FindIDActor<AActor>((int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID);
    if (nullptr == FindActor)
    {
        // 로그 찍어서 이런게 발생한다는걸 기록으로 남기는게 좋아요.
        return;
    }

    FindActor->Destroy();
    // UnActorManager::GetInst().EraseIDActor(Data.UpdateID);
    // FindActor->Destroy();
}

void UnWorldMsgFunc::WorldMovePlayer(UWorld* _World, PlayerUpdateDataPacket Data)
{
    AActor* FindActor = UnActorManager::GetInst().FindIDActor<AActor>((int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID);
    if (nullptr == FindActor)
    {
        UE_LOG(LogTemp, Error, TEXT("void UnWorldMsgFunc::WorldMovePlayer"));
        // 로그 찍어서 이런게 발생한다는걸 기록으로 남기는게 좋아요.
        return;
    }

    //UnActorManager::GetInst().EraseIDActor(Data.UpdateID);
    FindActor->Destroy();
}

void UnWorldMsgFunc::UpdateMonster(UWorld* _World, MonsterUpdateDataPacket Data)
{
    AMonster* FindPtr = UnActorManager::GetInst().FindIDActor<AMonster>((int)LogicValue::CollisionLayer::MONSTER, Data.UpdateID);

    // 혹시나 죽었다고 하더라도 
    if (nullptr == FindPtr)
    {
        //AMonster* NewMonster = UnActorManager::GetInst().CreateServerManagerObjectToCol<AMonster>(AMainActor::GetInst().m_MonsterCreateType, 
        //    { Data.m_Data.Pos.x, Data.m_Data.Pos.y, Data.m_Data.Pos.z }, 
        //    (int)LogicValue::CollisionLayer::MONSTER, Data.UpdateID, 
        //    { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
        AMonster* NewMonster = UnActorManager::GetInst().CreateServerManagerObjectToCol<AMonster>(APlayerCharacter::GetInst().m_MonsterCreateType,
            { Data.m_Data.Pos.x, Data.m_Data.Pos.y, Data.m_Data.Pos.z }, 
            (int)LogicValue::CollisionLayer::MONSTER, Data.UpdateID, 
            { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
        if (nullptr != NewMonster)
        {
            NewMonster->ActorStart();
        }
        return;
    }

    FindPtr->PushUpdateData(Data.m_Data);
}

void UnWorldMsgFunc::DeathMonster(UWorld* _World, MonsterUpdateDataPacket Data)
{
    AActor* FindPtr = UnActorManager::GetInst().FindIDActor<AActor>((int)LogicValue::CollisionLayer::MONSTER, Data.UpdateID);
    if (nullptr == FindPtr)
    {
        // 로그 찍어서 이런게 발생한다는걸 기록으로 남기는게 좋아요.
        return;
    }

    UE_LOG(LogTemp, Error, TEXT("UnWorldMsgFunc::DeathMonster"));
    FindPtr->Destroy();

}

void UnWorldMsgFunc::UpdateItem(UWorld* _World, ItemUpdateData Data)
{
    AActor* FindPtr = UnActorManager::GetInst().FindIDActor<AActor>((int)LogicValue::CollisionLayer::ITEM, Data.UpdateID);

    // 혹시나 죽었다고 하더라도 
    if (nullptr == FindPtr)
    {
        // 그때는 다시 만들어줘야 합니다.
        //AItem* NewItem = UnActorManager::GetInst().CreateServerManagerObjectToCol<AItem>(AMainActor::GetInst().m_ItemCreateType, { Data.CurPos.x, Data.CurPos.y, Data.CurPos.z }, (int)LogicValue::CollisionLayer::ITEM, Data.UpdateID, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
        AItem* NewItem = UnActorManager::GetInst().CreateServerManagerObjectToCol<AItem>(APlayerCharacter::GetInst().m_ItemCreateType, { Data.CurPos.x, Data.CurPos.y, Data.CurPos.z }, (int)LogicValue::CollisionLayer::ITEM, Data.UpdateID, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
        if (nullptr != NewItem)
        {
            NewItem->SetActorScale3D({100.0f, 100.0f, 100.0f});
        }
        return;
    }
    // 여기는 좀 바뀌어야 할겁니다.
    FindPtr->SetActorLocation(FVector(Data.CurPos.x, Data.CurPos.y, 0.0f));
}

void UnWorldMsgFunc::DeathItem(UWorld* _World, ItemUpdateData Data)
{
    UE_LOG(LogTemp, Error, TEXT("UnWorldMsgFunc::DeathItem"));

    AActor* FindPtr = UnActorManager::GetInst().FindIDActor<AActor>((int)LogicValue::CollisionLayer::ITEM, Data.UpdateID);
    if (nullptr == FindPtr)
    {
        // 로그 찍어서 이런게 발생한다는걸 기록으로 남기는게 좋아요.
        return;
    }

    // UE_LOG(LogTemp, Error, TEXT("My Item Eat %lld"), UnServerConnect::GetInst().m_CharacterData.UpdateID);

    if (UnServerConnect::GetInst().m_CharacterData.UpdateID == Data.EventPlayer)
    {
        // 이게 먹은게 나라는 뜻이죠?
        // 비교하고 넣어줘야 합니다.
        UE_LOG(LogTemp, Error, TEXT("My Item Eat %s"), Data.m_Data.Name.ConstStringPtr());
        // 사실 실질적으로 클라이언트 입장에서는 한쌍이라고 볼수 있네요.
        // 접속하면 25개를 하는건 하니까.
        UnServerConnect::GetInst().m_CharacterData.ItemDatas[Data.m_Data.InvenOrder] = Data.m_Data;
        UPlayUI::PlayUIInst->GetInvenWindow()->SetItemData(Data.m_Data);
    }

    FindPtr->Destroy();
}

void UnWorldMsgFunc::UpdatePotal(UWorld* _World, PotalUpdateData Data)
{
    // 만들고 끝.
    //APotal* NewPotal = UnActorManager::GetInst().CreateServerManagerObjectToCol<APotal>(AMainActor::GetInst().m_PotalCreateType, { Data.CurPos.x, Data.CurPos.y, Data.CurPos.z }, (int)LogicValue::CollisionLayer::POTAL, Data.UpdateID, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
    APotal* NewPotal = UnActorManager::GetInst().CreateServerManagerObjectToCol<APotal>(APlayerCharacter::GetInst().m_PotalCreateType, { Data.CurPos.x, Data.CurPos.y, Data.CurPos.z }, (int)LogicValue::CollisionLayer::POTAL, Data.UpdateID, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
    if (nullptr != NewPotal)
    {
        NewPotal->SetActorScale3D({ 1.0f, 0.3f, 1.0f });
    }
}

void UnWorldMsgFunc::WorldCreate(UWorld* _World, int _X, int _Y)
{
    UPlayUI::PlayUIInst->SetVisibility(ESlateVisibility::Visible);
    UnActorManager::GetInst().SetSize(float4(_X, _Y));
}

void UnWorldMsgFunc::WorldDestroy(UWorld* _World, WorldMoveOKPacket _Pacekt)
{
    UnActorManager::GetInst().ActorRelease();
}

void UnWorldMsgFunc::RankSetting(UWorld* _World, RankPacket _Packet)
{
    for (size_t i = 0; i < _Packet.m_RankDataList.size(); i++)
    {
        UPlayUI::PlayUIInst->GetRankWindow()->SetRank(i, _Packet.m_RankDataList[i]);
    }
}

void UnWorldMsgFunc::ChatMessage(UWorld* _World, ServerChatPacket _Pacekt)
{
    UChatObject* ChatInfo = NewObject<UChatObject>();

    ChatInfo->PID = _Pacekt.PID;
    ChatInfo->Name = _Pacekt.Name.ConstStringPtr();
    ChatInfo->Text = _Pacekt.Chat.ConstStringPtr();
    ChatInfo->Filter = false;

    // m_ChatTextList->SetScrollOffset(m_ChatTextList->GetNumItems() * 50.0f);

    UPlayUI::PlayUIInst->m_ChatTextList->AddItem(ChatInfo);
    UPlayUI::PlayUIInst->ChatScrollSet();
}

void UnWorldMsgFunc::PartyMessage(UWorld* _World, ServerPartyPacket _Packet)
{
    ////UPartyData* PartyData = NewObject<UPartyData>();
    //UChatObject* PartyData = NewObject<UChatObject>();
    //
    ////FString Value = FString(TEXT("Invite Party"));
    //PartyData->PID = _Packet.PID;
    //PartyData->Name = _Packet.Name.ConstStringPtr();
    //PartyData->Text = FString(TEXT("Invite Party"));
    //PartyData->Filter = false;

    ////UPlayUI::PlayUIInst->GetPartyWindow()->m_ListView->AddItem(PartyData);
    //UPlayUI::PlayUIInst->m_ChatTextList->AddItem(PartyData);
    //UPlayUI::PlayUIInst->ChatScrollSet();

    PARTYPACKETTYPE Type = _Packet.Type;

    if (PARTYPACKETTYPE::Init == Type)
    {
        size_t size = _Packet.PID.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (0 != _Packet.PID[i])
            {
                UPlayUI::PlayUIInst->AddPID(_Packet.PID[i]);
                UPlayUI::PlayUIInst->AddName(_Packet.Name[i]);
                UPlayUI::PlayUIInst->AddConnect(_Packet.Connect[i]);
            }
        }

        UPlayUI::PlayUIInst->GetPartyWindow()->Setting();
    }    
    else if (PARTYPACKETTYPE::Invite == Type)
    {
        size_t size = _Packet.PID.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (0 != _Packet.PID[i])
            {
                UPlayUI::PlayUIInst->AddPID(_Packet.PID[i]);
                UPlayUI::PlayUIInst->AddName(_Packet.Name[i]);
                UPlayUI::PlayUIInst->AddConnect(_Packet.Connect[i]);
            }            
        }

        UPlayUI::PlayUIInst->PartyInviteWindow();
    }
    else if (PARTYPACKETTYPE::Accept == Type)
    {
        UPlayUI::PlayUIInst->PartyDataClear();

        size_t size = _Packet.PID.size();
        for (size_t i = 0; i < size; ++i)
        {
            UPlayUI::PlayUIInst->AddPID(_Packet.PID[i]);
            UPlayUI::PlayUIInst->AddName(_Packet.Name[i]);
            UPlayUI::PlayUIInst->AddConnect(_Packet.Connect[i]);
        }

        // 파티창 세팅
        UPlayUI::PlayUIInst->PartyWindowSetting();
    }


    
}
