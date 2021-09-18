// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyInviteWindow.h"
#include "UnServerConnect.h"
#include "ClientToServer.h"
#include "PlayUI.h"

void UPartyInviteWindow::AcceptButton()
{   
    ClientPartyPacket Packet;
    Packet.Type = PARTYPACKETTYPE::Accept;

    size_t size = UPlayUI::PlayUIInst->GetSize();
    for (size_t i = 0; i < size; ++i)
    {
        Packet.PID.push_back(UPlayUI::PlayUIInst->GetPID(i));
        Packet.Name.push_back(UPlayUI::PlayUIInst->GetName(i));
        Packet.Connect.push_back(UPlayUI::PlayUIInst->GetConnect(i));
    }    
    Packet.PID.push_back(UnServerConnect::GetInst().m_CharacterData.PID);
    Packet.Name.push_back(UnServerConnect::GetInst().m_CharacterData.NICKNAME);
    Packet.Connect.push_back(1);

    UnServerConnect::GetInst().Send(Packet);

    SetVisibility(ESlateVisibility::Hidden);
}

void UPartyInviteWindow::RefuseButton()
{
    UPlayUI::PlayUIInst->PartyDataClear();

    SetVisibility(ESlateVisibility::Hidden);
}
