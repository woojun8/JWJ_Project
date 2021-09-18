

// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyWindow.h"
#include "Components/ListView.h"
#include "InvenItemData.h"
#include "PartyItem.h"
#include "PartyData.h"
#include "PlayUI.h"
#include <ClientToServer.h>
#include "UnServerConnect.h"

void UPartyWindow::PartyInit()
{
    if (nullptr == m_ListView)
    {
        m_ListView = Cast<UListView>(GetWidgetFromName(TEXT("PartyList")));

        if (nullptr != m_ListView)
        {
            for (int i = 0; i < 3; i++)
            {
                UPartyData* NewItem = NewObject<UPartyData>();
                m_ListView->AddItem(NewItem);
            }
            UE_LOG(LogTemp, Error, L"Party InitOk");
        }
    }

    IsPartyList = false;
    IsSet = false;
}


void UPartyWindow::ListAddEvent(UObject* _Item, UUserWidget* _Icon)
{
    UPartyItem* Item = Cast<UPartyItem>(_Icon);
    UE_LOG(LogTemp, Error, L"Add Party Item");
    PartyList.Add(Item);

    IsPartyList = true;
}

void UPartyWindow::Update()
{
    int a = 0;

    if (IsPartyList && IsSet)
    {
        size_t size = PartyList.Num();
        for (size_t i = 0; i < size; ++i)
        {
            if (i < UPlayUI::PlayUIInst->GetSize())
            {
                
                GameEngineString strName = UPlayUI::PlayUIInst->GetName(i);
                PartyList[i]->SetName(FString(strName.m_String.c_str()));

                __int64 Connect = UPlayUI::PlayUIInst->GetConnect(i);
                if (1 == Connect)
                {
                    PartyList[i]->SetConnect(FString(TEXT("Connect")));
                }
                else
                {
                    PartyList[i]->SetConnect(FString(TEXT("Not Connect")));
                }
            }
        }

        IsSet = false;
    }
 
}


void UPartyWindow::Button()
{


    // 테스트용
    //ClientPartyPacket Packet;
    //Packet.Type = PARTYPACKETTYPE::Accept;


    //Packet.PID.push_back(1);
    //Packet.Name.push_back(L"c");
    //Packet.PID.push_back(UnServerConnect::GetInst().m_CharacterData.PID);
    //Packet.Name.push_back(UnServerConnect::GetInst().m_CharacterData.NICKNAME);

    //UnServerConnect::GetInst().Send(Packet);
}

void UPartyWindow::Setting()
{
    IsSet = true;
    /*
    if (0 >= PartyList.Num())
    {
        return;
    }

    size_t size = PartyList.Num();
    for (size_t i = 0; i < size; ++i)
    {
        if (i < UPlayUI::PlayUIInst->GetSize())
        {
            GameEngineString strName = UPlayUI::PlayUIInst->GetName(i);
            PartyList[i]->SetName(FString(strName.m_String.c_str()));
        }        
    }   */  	
}
