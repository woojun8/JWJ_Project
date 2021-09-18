// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayUI.h"
#include "InventoryWindow.h"
#include "RankWindow.h"
#include "PartyWindow.h"
#include "PartyInviteWindow.h"
#include "Components/ListView.h"
#include "Components/EditableTextBox.h"
#include "UnServerConnect.h"
#include "ClientToServer.h"
#include "ChatObject.h"
#include "ChatItem.h"
#include <set>

UPlayUI* UPlayUI::PlayUIInst = nullptr;

void UPlayUI::PlayUIInit()
{
    m_InvenWindow = Cast<UInventoryWindow>(GetWidgetFromName(TEXT("InvenWindow")));
    //m_RankWindow = Cast<URankWindow>(GetWidgetFromName(TEXT("RankWindowBP")));
    m_PartyWindow = Cast<UPartyWindow>(GetWidgetFromName(TEXT("PartyWindowBP")));
    m_PartyInviteWindow = Cast<UPartyInviteWindow>(GetWidgetFromName(TEXT("PartyInviteWindowBP")));
    m_ChatTextList = Cast<UListView>(GetWidgetFromName(TEXT("ChatList")));
    m_ChatTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ChatText")));
    m_IsFriend = false;
    
    if (nullptr == m_InvenWindow)
    {
        UE_LOG(LogTemp, Error, L"Inven Init Error");
        return;
    }

    //if (nullptr == m_RankWindow)
    //{
    //    UE_LOG(LogTemp, Error, L"Rank Init Error");
    //    return;
    //}

    if (nullptr == m_PartyWindow)
    {
        UE_LOG(LogTemp, Error, L"Party Init Error");
        return;
    }

    if (nullptr == m_PartyInviteWindow)
    {
        UE_LOG(LogTemp, Error, L"PartyInvite Init Error");
        return;
    }

    m_eInvenOpenState = ESlateVisibility::Hidden;
    m_eRankOpenState = ESlateVisibility::Hidden;
    m_ePartyOpenState = ESlateVisibility::Hidden;

    PlayUIInst = this;

    // SetVisibility(ESlateVisibility::Hidden);
    //m_PartyWindow->SetVisibility(m_ePartyOpenState);
}

void UPlayUI::InvenOpenCheck() 
{
    if (ESlateVisibility::Hidden == m_eInvenOpenState)
    {
        m_InvenWindow->SetVisibility(ESlateVisibility::Visible);
        m_eInvenOpenState = ESlateVisibility::Visible;

        for (size_t i = 0; i < UnServerConnect::GetInst().m_CharacterData.ItemDatas.size(); i++)
        {
            if (false == UnServerConnect::GetInst().IsConnect())
            {
                continue;
            }

            UPlayUI::PlayUIInst->GetInvenWindow()->SetItemData(UnServerConnect::GetInst().m_CharacterData.ItemDatas[i]);
        }
    }
    else
    {
        m_InvenWindow->SetVisibility(ESlateVisibility::Hidden);
        m_eInvenOpenState = ESlateVisibility::Hidden;
    }
}

void UPlayUI::RankOpenCheck() 
{
    if (ESlateVisibility::Hidden == m_eRankOpenState)
    {
        m_RankWindow->SetVisibility(ESlateVisibility::Visible);
        m_eRankOpenState = ESlateVisibility::Visible;
    }
    else 
    {
        m_RankWindow->SetVisibility(ESlateVisibility::Hidden);
        m_eRankOpenState = ESlateVisibility::Hidden;
    }
}

void UPlayUI::PartyOpenCheck()
{
    if (ESlateVisibility::Hidden == m_ePartyOpenState)
    {
        m_PartyWindow->SetVisibility(ESlateVisibility::Visible);
        m_ePartyOpenState = ESlateVisibility::Visible;
        
        // SetVisiblility가 활성화되고 실행이 될거라
        // 무조건적으로 믿지말자
        // 언제 활성화될지 나는 모른다
        //m_PartyWindow->Button();
    }
    else 
    {
        m_PartyWindow->SetVisibility(ESlateVisibility::Hidden);
        m_ePartyOpenState = ESlateVisibility::Hidden;
    }
}

void UPlayUI::ChatScrollSet()
{
    if (nullptr == m_ChatTextList)
    {
        UE_LOG(LogTemp, Error, L"if (nullptr == m_ChatTextList)");
        return;
    }

    m_ChatTextList->SetScrollOffset(m_ChatTextList->GetNumItems() * 50.0f);
}

void UPlayUI::ChatCommit(FText Text, ETextCommit::Type _eType)
{
    switch (_eType)
    {
    case ETextCommit::Default:
        UE_LOG(LogTemp, Error, L"ETextCommit::Default");
        break;
    case ETextCommit::OnEnter:
    {
        // 파티장 체크 
        GameEngineString Chat = *Text.ToString();
        if (false == PartyHostCheck() &&
            std::string::npos != Chat.FindOf(TEXT("/I")))
        {
            return;
        }

        UE_LOG(LogTemp, Error, L"ETextCommit::OnEnter");
        ClientChatPacket Pacekt;
        // Pacekt.Cheat = *Text.ToString();
        Pacekt.PID = UnServerConnect::GetInst().m_CharacterData.PID;
        Pacekt.Name = UnServerConnect::GetInst().m_CharacterData.NICKNAME;
        Pacekt.Chat = *Text.ToString();
        UnServerConnect::GetInst().Send(Pacekt);

        //UE_LOG(LogTemp, Error, L"%lld", Pacekt.Chat.FindOf(TEXT("/F")));
        if (std::string::npos != Pacekt.Chat.FindOf(TEXT("/F")) ||
            std::string::npos != Pacekt.Chat.FindOf(TEXT("/I")))
        {
            return;
        }

        if (nullptr == m_ChatTextList)
        {
            UE_LOG(LogTemp, Error, L"if (nullptr == m_ChatTextList)");
            return;
        }

        UChatObject* Item = NewObject<UChatObject>();
        Item->PID = UnServerConnect::GetInst().m_CharacterData.PID;
        Item->Name = UnServerConnect::GetInst().m_CharacterData.NICKNAME.ConstStringPtr();
        Item->Text = *Text.ToString();
        Item->Filter = false;

        m_ChatTextList->AddItem(Item);
        ChatScrollSet();

        break;
    }
    case ETextCommit::OnUserMovedFocus:
        UE_LOG(LogTemp, Error, L"ETextCommit::OnUserMovedFocus");
        break;
    case ETextCommit::OnCleared:
    {
        UE_LOG(LogTemp, Error, L"ETextCommit::OnCleared");

        m_ChatTextBox->SetFocus();
        break;
    }
    default:
        UE_LOG(LogTemp, Error, L"case default");
        break;
    }

    return;
}

UFUNCTION(BlueprintCallable, Category = Attachment)
void UPlayUI::ChatAddEvent(UObject* _Item, UUserWidget* _Icon)
{
    if (nullptr == _Item || nullptr == _Icon)
    {
        return;
    }

    UChatObject* ChatInfo = Cast<UChatObject>(_Item);
    UChatItem* Item = Cast<UChatItem>(_Icon);

    if (nullptr == ChatInfo || nullptr == Item)
    {
        return;
    }

    Item->m_PID = ChatInfo->PID;
    Item->m_Name = ChatInfo->Name;
    Item->m_Text = ChatInfo->Text;

    if (false == ChatInfo->Filter)
    {
        m_ChatList.push_back(ChatInfo);
    }
}


void UPlayUI::ChatModeChange()
{
    if (0 == m_ChatList.size())
    {
        return;
    }

    m_IsFriend = !m_IsFriend;

    if (true == m_IsFriend)
    {
        m_ModeText = L"Friend";
    }
    else
    {
        m_ModeText = L"World";
    }

    m_ChatTextList->ClearListItems();
    // m_ChatList.front()-;

    std::set<__int64> m_FriendSet;

    for (size_t i = 0; i < UnServerConnect::GetInst().m_CharacterData.FriendDatas.size(); i++)
    {
        m_FriendSet.insert(UnServerConnect::GetInst().m_CharacterData.FriendDatas[i]);
    }



    // m_FriendSet.insert(UnServerConnect::GetInst().m_CharacterData.PID);

    for (auto& _Data : m_ChatList)
    {
        _Data->Filter = true;
        if (true == m_IsFriend)
        {
            if (m_FriendSet.end() != m_FriendSet.find(_Data->PID))
            {
                m_ChatTextList->AddItem(_Data);
            }
        }
        else
        {
            m_ChatTextList->AddItem(_Data);
        }
    }

    m_ChatTextList->RegenerateAllEntries();
}

void UPlayUI::PartyInviteWindow()
{
    m_PartyInviteWindow->SetVisibility(ESlateVisibility::Visible);
}

void UPlayUI::PartyWindowSetting()
{
    PartyOpenCheck();

    m_PartyWindow->Setting();
}

bool UPlayUI::PartyHostCheck()
{
    // 여기서 판단할수 있는 상황은
    // 파티데이터가 있는데 내가 호스타가 아니야
    if (0 != ArrPID.Num() &&
        ArrPID[0] != UnServerConnect::GetInst().m_CharacterData.PID)
    {
        LOG(TEXT("Not Host"));
        return false;
    }

    // 이미 파티가 꽉찼어
    if (3 <= ArrPID.Num())
    {
        LOG(TEXT("Arr Over"));
        return false;
    }

    // 이미 파티가 있는 플레이어를 초대한다?
    // 여기선 판단이 안되지
    /*if (ArrPID[0] == UnServerConnect::GetInst().m_CharacterData.PID)
    {
        return true;
    }*/

    return true;
}