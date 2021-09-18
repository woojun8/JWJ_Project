// Fill out your copyright notice in the Description page of Project Settings.


#include "RankWindow.h"
#include "Components/ListView.h"
#include "InvenItemData.h"
#include "RankItem.h"
#include <ClientToServer.h>
#include "RankItemData.h"
#include "UnServerConnect.h"


void URankWindow::RankInit()
{
    if (nullptr == m_ListView)
    {
        m_ListView = Cast<UListView>(GetWidgetFromName(TEXT("RankList")));

        if (nullptr != m_ListView)
        {
            for (int i = 0; i < 5; i++)
            {
                URankItemData* NewItem = NewObject<URankItemData>();
                m_ListView->AddItem(NewItem);
            }
            UE_LOG(LogTemp, Error, L"Rank InitOk");
        }

        // m_TileView->ClearListItems();
    }

    // this->SetVisibility(ESlateVisibility::Hidden);
}


void URankWindow::ListAddEvent(UObject* _Item, UUserWidget* _Icon) 
{
    URankItem* Item = Cast<URankItem>(_Icon);
    UE_LOG(LogTemp, Error, L"Add Rank Item");
    RankList.Add(Item);
}

void URankWindow::SettingTopRank() 
{
    UE_LOG(LogTemp, Error, L"URankWindow::SettingTopRank()");

    GetRankPacket Packet;
    Packet.Type = 0;

    UnServerConnect::GetInst().Send(Packet);
    // 여기서 바로 send를 한다.

}

void URankWindow::SettingUserRank() 
{
    GetRankPacket Packet;
    Packet.Type = 1;

    UnServerConnect::GetInst().Send(Packet);
    UE_LOG(LogTemp, Error, L"URankWindow::SettingUserRank() ");
}

void URankWindow::SetRank(int _Index, RankData& _Data) 
{
    if (0 > _Index)
    {
        return;
    }

    if (_Index >= RankList.Num())
    {
        return;
    }

    RankList[_Index]->SetRank(_Data.Rank);
    RankList[_Index]->SetName(_Data.Name.ConstStringPtr());
    RankList[_Index]->SetScore(_Data.Score);
}