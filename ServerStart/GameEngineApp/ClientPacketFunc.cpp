#include "ClientPacketFunc.h"
#include "Main.h"
#include "ClientValue.h"
#include <ServerToClientPacketUpdater.h>
#include "ClientWorld.h"
#include "ClientWorldMsgFunc.h"
#include "ClientWorldManager.h"
#include "ConosleHelper.h"


void ClientPacketFunc::Init()
{
    // ServerToClientPacketUpdater;
    STOCPACKETCALLBACK(AccountResultPacket);
    STOCPACKETCALLBACK(LoginResultPacket);
    STOCPACKETCALLBACK(CharacterPacket);
    STOCPACKETCALLBACK(GameStartPacket);
    STOCPACKETCALLBACK(PlayerUpdatePacket);
    STOCPACKETCALLBACK(MonsterUpdatePacket);
    STOCPACKETCALLBACK(ItemUpdatePacket);
    STOCPACKETCALLBACK(PotalUpdatePacket);
    STOCPACKETCALLBACK(WorldMoveOKPacket);
}

void ClientPacketFunc::WorldMoveOKPacketProcess(WorldMoveOKPacket& _Packet) 
{

}

void ClientPacketFunc::ItemUpdatePacketProcess(ItemUpdatePacket& _Packet)
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
        ClientConnecter* Connecter = &ClientConnecter::GetInst();
        ActorState State = _Packet.m_ItemUpdateDataList[i].m_State;
        ItemUpdateData Data = _Packet.m_ItemUpdateDataList[i];
        switch (State)
        {
        case ActorState::Update:
            ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::UpdateItem, Connecter, Data);
            break;
        case ActorState::Death:
            ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::DeathItem, Connecter, Data);
            break;
        default:
            break;
        }
    }

}

void ClientPacketFunc::PotalUpdatePacketProcess(PotalUpdatePacket& _Packet)
{
    ClientConnecter* Connecter = &ClientConnecter::GetInst();
    for (size_t i = 0; i < _Packet.m_UpdateDataList.size(); i++)
    {
        ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::UpdatePotal, Connecter, _Packet.m_UpdateDataList[i]);
    }
}

void ClientPacketFunc::CharacterPacketProcess(CharacterPacket& _Packet) 
{
    std::shared_ptr<CharacterData> NewData = std::make_shared<CharacterData>();

    NewData->Att = _Packet.Att;
    NewData->Hp = _Packet.Hp;
    NewData->LastX = _Packet.LastX;
    NewData->LastY = _Packet.LastY;
    NewData->MaxHp = _Packet.MaxHp;
    NewData->NICKNAME = _Packet.NICKNAME;
    NewData->EndIndex = _Packet.EndIndex;

    // 여기서 클라이언트 월드는 미리 세팅해 놔야 겠네요.
    // 처리하는게 먼저 처리되지는 않네요.

    //std::shared_ptr<CharacterData> Data = ClientConnecter::GetInst().GetCharacterData();
    std::string InsertIndex = _Packet.EndIndex.GetConvertMultiByteString();

    std::shared_ptr<ClientWorld> StartWorld = ClientWorldManager::Inst()->FindClientWorld(InsertIndex);
    ClientConnecter::GetInst().SetClientWorld(StartWorld);

    ConosleHelper::SetSize(StartWorld->GetSize());
    PosToKeyConvert Convert = InsertIndex;
    ClientWorldManager::Inst()->UpdateCheck({ Convert.X, Convert.Y });

    std::shared_ptr<ClientPlayer> NewPlayer = StartWorld->CreateActor<ClientPlayer>(2);
    NewPlayer->SetPos({ NewData->LastX, NewData->LastY });
    NewPlayer->MainPlayerOn();

    ClientConnecter* Connecter = &ClientConnecter::GetInst();

    Connecter->SetCharacterData(NewData);

}

void ClientPacketFunc::AccountResultPacketProcess(AccountResultPacket& _Packet)
{
    AccountResultType ResultType = (AccountResultType)_Packet.m_Code;
    InterlockedExchange(&ClientValue::m_AccountCheck, static_cast<unsigned long long>(ResultType));
}

void ClientPacketFunc::LoginResultPacketProcess(LoginResultPacket& _Packet) 
{
    LoginResultType ResultType = (LoginResultType)_Packet.m_Code;
    InterlockedExchange(&ClientValue::m_LoginCheck, static_cast<unsigned long long>(ResultType));
}

void ClientPacketFunc::GameStartPacketProcess(GameStartPacket& _Packet) 
{
    if (-1 == _Packet.ID)
    {
        GameEngineDebug::AssertMsg("if (-1 == _Packet.ID)");
    }

    ClientConnecter* Connecter = &ClientConnecter::GetInst();

    Connecter->ID = _Packet.ID;

    InterlockedExchange(&ClientValue::m_GameStartCheck, 0);
}

void ClientPacketFunc::PlayerUpdatePacketProcess(PlayerUpdatePacket& _Packet) 
{
    // 아무유저도 없네

    if (0 == _Packet.m_PlayerData.size())
    {
        return;
    }
 
    // 클라이언트 월드라고 다른 처리를 하지는 않는다.
    // 메세지로 처리합니다.
    //LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex.GetConvertMultiByteString(),
    //    &WorldMsgFunc::WaitActorInWorld, Socket);

    // 여기 들어왔을때.
    for (size_t i = 0; i < _Packet.m_PlayerData.size(); i++)
    {
        ClientConnecter* Connecter =  &ClientConnecter::GetInst();

        // SetWorld를 안했네용.
        //std::shared_ptr<ClientWorld> Ptr = ClientConnecter::GetInst().GetWorld();

        //if (nullptr == Ptr)
        //{
        //    GameEngineDebug::AssertMsg("if (nullptr == Ptr)");
        //}
        
        ActorState State = _Packet.m_PlayerData[i].m_State;
        PlayerUpdateData Data = _Packet.m_PlayerData[i];
        switch (State)
        {
        case ActorState::Wait:
        {
            ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::WaitPlayerCreate, Connecter, Data);
            break;
        }
        case ActorState::in:
            ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::WaitPlayerInWorld, Connecter, Data);
            break;
        case ActorState::Update:
            ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::UpdatePlayer, Connecter, Data);
            break;
        case ActorState::Death:

            // 이녀석을 그냥 여기서 바로 실행해버릴수 있지만
            // 어떤일이 발생할지 선생님도 알수가 없습니다.
            // 문제가 안생길수도 있어요.
            // 그런데 선생님기준으로는 그냥 운이 좋았던거야.
            // 사용하는 인원수가 많아지면
            // 1000번 밖에 안되는거죠?
            // ClientWorldMsgFunc::DeathPlayer

            // 메세지로 넣어서 처리하고 있어요
            ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::DeathPlayer, Connecter, Data);
            break;
        default:
            break;
        }

        

    }
}

void ClientPacketFunc::MonsterUpdatePacketProcess(MonsterUpdatePacket& _Packet) 
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
        ClientConnecter* Connecter = &ClientConnecter::GetInst();

        // SetWorld를 안했네용.
        //std::shared_ptr<ClientWorld> Ptr = ClientConnecter::GetInst().GetWorld();

        //if (nullptr == Ptr)
        //{
        //    GameEngineDebug::AssertMsg("if (nullptr == Ptr)");
        //}

        ActorState State = _Packet.m_MonsterData[i].m_State;
        MonsterUpdateData Data = _Packet.m_MonsterData[i];
        switch (State)
        {
        case ActorState::Update:
            ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::UpdateMonster, Connecter, Data);
            break;
        case ActorState::Death:
            ClientConnecter::GetInst().GetClientWorld()->MsgInsert(&ClientWorldMsgFunc::DeathMonster, Connecter, Data);
            break;
        default:
            break;
        }
    }
}