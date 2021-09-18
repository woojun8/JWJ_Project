// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginScreenWidget.h"

#include "Player/PlayerCharacter.h"

#include "Sockets.h"
#include "UnServerConnect.h"
#include <string>
#include <GameEngineString.h>
#include <GameEngineDirectory.h>
#include <GameEngineFile.h>
#include "UnActorManager.h"
#include <ClientToServer.h>
#include "MainActor.h"
#include "UnServerConnect.h"
#include <LogicValue.h>

// �𸮾���
// ��Ƽ������ �����
// �Ⱦ���


//#include <WinSock2.h>
//#include <string>
//#include <map>


FString ULoginScreenWidget::IPText;

void ULoginScreenWidget::ConnectProgress() 
{
    IPText = m_IP.ToString();
    IPSave();
    UnServerConnect::GetInst().ConnectTaskStart();
}

void ULoginScreenWidget::LoginProgress() 
{
    // ��Ŷ�� ���������
    // Ŀ��Ʈ�� �ɰų� ���� �ʾƿ�?
    
    // �̰����� Ŀ��Ʈ�� �ɰų� ���ų��Դϴ�.
    //std::string Text;
    //std::map<int, int> m_Map;

    // m_Map.insert()

    // UE_LOG(LogTemp, Error, L"ID %s | PW %s", *m_ID.ToString(), *m_Password.ToString());
    // UnServerConnect::GetInst().Connect();

    // GameEngineString Test;


    GameEngineString Text = L"";

    LoginPacket NewPacket;

    NewPacket.ID = *m_ID.ToString();
    NewPacket.PASS = *m_Password.ToString();

    // LoginPacket Packet;

    if (false == UnServerConnect::GetInst().IsConnect())
    {
        UE_LOG(LogTemp, Error, L"Is Not Connect ID %s | PW %s", *m_ID.ToString(), *m_Password.ToString());
    }
    else 
    {
        // AMainActor::GetInst().IsMouseCenter = true;
        UnServerConnect::GetInst().Send(NewPacket);
        UE_LOG(LogTemp, Error, L"Is Login Packet Send ID %s | PW %s", *m_ID.ToString(), *m_Password.ToString());
        // ��Ŷ �α��� ��Ŷ�� ������.
    }

    // UnServerConnect::GetInst().is
    
}

void ULoginScreenWidget::AccountProgress() 
{
    // �� ID�� �� PW�� ȸ�������Ϸ��� ��츦 ������ ���Ƴ��°� ���ڳ׿�.
    //if (m_ID == "")
    //{
    //}

    if (m_ID.ToString() == TEXT("") || m_Password.ToString() == TEXT(""))
    {
        return;
    }

    AccountPacket NewPacket;
    NewPacket.ID = *m_ID.ToString();
    NewPacket.PASS = *m_Password.ToString();
    UnServerConnect::GetInst().Send(NewPacket);
    UE_LOG(LogTemp, Error, L"ULoginScreenWidget::AccountProgress() ID %s | PW %s", *m_ID.ToString(), *m_Password.ToString());
}

void ULoginScreenWidget::NativeTick(const FGeometry& _MyGeometry, float _Delta) 
{
    Super::NativeTick(_MyGeometry, _Delta);

    if (1 == UnServerConnect::GetInst().m_Login)
    {
        // ui�� �Ѱ� ���� �ְ� �������� �Լ���
        UE_LOG(LogTemp, Error, L"Is Login OK");
        SetVisibility(ESlateVisibility::Hidden);
    }
}

ULoginScreenWidget::~ULoginScreenWidget() 
{

}

void ULoginScreenWidget::IPSave() 
{
    // UE_LOG(LogTemp, Error, L"void ULoginScreenWidget::BeginPlay() ");
    GameEngineDirectory NewDir;

    // ���� ���� �ڵ带 �𸮾󿡼� ����ϴ� �Ŵϱ� �����Ҽ��� ������
    GameEngineFile NewFile = NewDir.GetFile(L"IPSAVE.Data");

    FString FStringText = m_IP.ToString();

    GameEngineString Text = (*FStringText);

    NewFile.FileOpen(L"wb");
    NewFile << Text;
}

void ULoginScreenWidget::IPLoad() 
{
    TArray<int> ARR;
    for (size_t i = 0; i < 10; i++)
    {
        ARR.Add(i);
    }

    for (size_t i = 0; i < 10; i++)
    {
        UE_LOG(LogTemp, Error, L"%d", ARR[i]);
    }
    

    // UE_LOG(LogTemp, Error, L"void ULoginScreenWidget::BeginPlay() ");
    GameEngineDirectory NewDir;

    // ���� ���� �ڵ带 �𸮾󿡼� ����ϴ� �Ŵϱ� �����Ҽ��� ������
    GameEngineFile NewFile = NewDir.GetFile(L"IPSAVE.Data");

    GameEngineString Text;
    if (true == NewFile.IsExist())
    {
        NewFile.FileOpen(L"rb");
        NewFile >> Text;

        m_IP = FText::FromString(Text.ConstStringPtr());

        return;
    }

    return;
}

void ULoginScreenWidget::SingleProgress() 
{
    // �𸮾�
    // x 0 0 1 0
    // y 1 0 0 0
    // z 0 1 0 0
    // z 0 0 0 1

    // ������ ��쿡�� �浹���� �츮�� ����� ������� ���Ѵٴ�
    UnServerConnect::GetInst().m_Login = 1;
    UnServerConnect::GetInst().m_GameStart = 1;
    UnServerConnect::GetInst().IsServer = false;
    //UnActorManager::GetInst().SetMainActor(&AMainActor::GetInst(), {100.0f, 100.0f, 100.0f}, 1);
    UnActorManager::GetInst().SetMainActor(&APlayerCharacter::GetInst(), { 100.0f, 100.0f, 100.0f }, 1);
    UnActorManager::GetInst().SetSize(float4(5000.0f, 5000.0f));

    // 

    UnActorManager::GetInst().TestMonsterCreate(2);
    //AMainActor::GetInst().IsMouseCenter = true;

}