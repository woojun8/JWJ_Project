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

// 언리얼의
// 멀티프랫폼 기능을
// 안쓰게


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
    // 패킷을 쏘는일이지
    // 커넥트를 걸거나 하지 않아요?
    
    // 이곳에서 커넥트를 걸거냐 말거냐입니다.
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
        // 패킷 로그인 패킷을 날린다.
    }

    // UnServerConnect::GetInst().is
    
}

void ULoginScreenWidget::AccountProgress() 
{
    // 빈 ID나 빈 PW로 회원가입하려는 경우를 다음에 막아놓는게 좋겠네요.
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
        // ui를 켜고 끌수 있게 만들어놓은 함수가
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

    // 내가 만든 코드를 언리얼에서 사용하는 거니까 위험할수도 있으니
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

    // 내가 만든 코드를 언리얼에서 사용하는 거니까 위험할수도 있으니
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
    // 언리얼
    // x 0 0 1 0
    // y 1 0 0 0
    // z 0 1 0 0
    // z 0 0 0 1

    // 서버일 경우에는 충돌등을 우리가 제대로 사용하지 못한다는
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