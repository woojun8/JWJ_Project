#include "WorldMsgFunc.h"
#include <World.h>
#include <LogicValue.h>
#include "ServerActor.h"
#include "ServerPlayer.h"
#include "ServerMonster.h"
#include "ServerItem.h"
#include "ServerPotal.h"
#include "ServerBullet.h"
#include <GameWorld.h>
#include <ServerToClient.h>
#include <ClientToServer.h>
#include <ItemTable.h>
#include <iostream>
#include <FriendTable.h>
#include <PartyTable.h>
#include <DBManager.h>
#include "DbTaskFunc.h"

void WorldMsgFunc::WaitPlayerCreate(World* _World, ServerConnecter* _Connecter)
{

    // 커넥터 세팅해주고
    // 월드에 대기하고 있는 엑터를 하나 만들어준다.
    // 실제 위쪽에 영향을 주지 않겠죠.
    std::shared_ptr<ServerPlayer> NewPlayer = _World->CreateWaitActor<ServerPlayer>((int)LogicValue::CollisionLayer::PLAYER);
    NewPlayer->SetPos({ _Connecter->GetCharacterData()->LastX , _Connecter->GetCharacterData()->LastY });
    NewPlayer->SetConnecter(_Connecter);
    _Connecter->SetActor(NewPlayer);
    _Connecter->SetPlayer(NewPlayer.get());

    std::shared_ptr<CharacterTableData> _Data = _Connecter->GetCharacterData();

    CharacterPacket NewCharacterPacket;
    NewCharacterPacket.PID = _Data->PID;
    NewCharacterPacket.UpdateID = reinterpret_cast<__int64>(NewPlayer.get());
    NewCharacterPacket.NICKNAME = GameEngineString::GlobalSetConvertMultiByteString(_Data->Name);
    NewCharacterPacket.EndIndex = GameEngineString::GlobalSetConvertMultiByteString(_Data->EndIndex);
    NewCharacterPacket.LastX = _Data->LastX;
    NewCharacterPacket.LastY = _Data->LastY;
    NewCharacterPacket.MaxHp = _Data->MAXHP;
    NewCharacterPacket.Hp = _Data->HP;
    NewCharacterPacket.Att = _Data->ATT;

    std::vector<std::shared_ptr<FriendTableData>>& _FriendData = _Connecter->GetFriendDataRef();

    for (size_t i = 0; i < _FriendData.size(); i++)
    {
        NewCharacterPacket.FriendDatas.push_back(_FriendData[i]->FID);
    }

    //std::cout << NewCharacterPacket.UpdateID << std::endl;

    std::vector<std::shared_ptr<ItemTableData>>& _ItemData = _Connecter->GetItemsDataRef();

    for (size_t i = 0; i < _ItemData.size(); i++)
    {
        if (nullptr == _ItemData[i])
        {
            continue;
        }

        ItemData Data;
        // Data.Name = L"FASDFSADF";
        Data.Name = GameEngineString::GlobalSetConvertMultiByteString(_ItemData[i]->Name, CP_UTF8);
        Data.InvenOrder = _ItemData[i]->InvenOrder;
        Data.Type = _ItemData[i]->Type;
        Data.Count = _ItemData[i]->Count;
        Data.IconResData = _ItemData[i]->IconResData;

        NewCharacterPacket.ItemDatas.push_back(Data);
    }

    //auto ddd = NewCharacterPacket.Serialize();
    //CharacterPacket tmp;
    //tmp.DeSerialize(ddd);

    if (SOCKET_ERROR == _Connecter->Send(NewCharacterPacket))
    {
        int a = 0;
    }

    std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
    {
        PlayerUpdateDataPacket Data;
        Data.UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
        Data.m_State = ActorState::Wait;
        Data.m_Data.Pos = _Connecter->GetPlayer()->GetPos();

        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            if (0 == Ptr->GetConnecter()->Send(Data))
            {
                int a = 0;
            }
        }
    }

    {
        PlayerUpdatePacket AllActorPacket; // 나를 알려주는 패킷

        // 내가 이미 접속해서 이제 들어가 있죠?
        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerPlayer> OtherPlayer = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            PlayerUpdateDataPacket Data;
            Data.UpdateID = reinterpret_cast<__int64>(OtherPlayer.get());
            Data.m_State = ActorState::Update;
            Data.m_Data.SetData(OtherPlayer->GetPos(), OtherPlayer->GetRot());
            AllActorPacket.m_PlayerData.push_back(Data);
        }

        NewPlayer->GetConnecter()->Send(AllActorPacket);
    }

    std::vector<std::shared_ptr<PartyTableData>>& Partys = _Connecter->GetPartyDataRef();

    if (0 != Partys.size())
    {
        ServerPartyPacket PartyPacket;
        PartyPacket.Type = PARTYPACKETTYPE::Init;
        //PartyPacket.PID

        PartyPacket.PID.push_back(Partys[0]->ID1);
        PartyPacket.Name.push_back(GameEngineString::GlobalSetConvertMultiByteString(Partys[0]->Name1));
        PartyPacket.Connect.push_back(Partys[0]->Connect1);

        PartyPacket.PID.push_back(Partys[0]->ID2);
        PartyPacket.Name.push_back(GameEngineString::GlobalSetConvertMultiByteString(Partys[0]->Name2));
        PartyPacket.Connect.push_back(Partys[0]->Connect2);

        if (-3617008641903833651 != Partys[0]->ID3)
        {
            PartyPacket.PID.push_back(Partys[0]->ID3);
            PartyPacket.Name.push_back(GameEngineString::GlobalSetConvertMultiByteString(Partys[0]->Name3));
            PartyPacket.Connect.push_back(Partys[0]->Connect3);
        }

        if (SOCKET_ERROR == _Connecter->Send(PartyPacket))
        {
            int a = 0;
        }
    }

    // 이녀석은 대기 유저인데.

    // 상대 액터를 알고 있다면 그녀석한만 귓속말을 보낸다거나 이런것도 가능해집니다.
}

void WorldMsgFunc::WaitPlayerInWorld(World* _World, ServerConnecter* _Connecter) 
{
    // 내가 이미 들어갔어요.
    if (false == _World->WaitActorInWorld(_Connecter->GetActor()))
    {
        GameEngineDebug::AssertMsg("if (false == _World->WaitActorInWorld(_Connecter->GetActor()))");
    }

    GameStartPacket Packet;
    Packet.ID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
    _Connecter->Send(Packet);

    // 유저 리스트를 받아온다.
    // 현재 존재하는 모든 유저들에게 나의 존재를 알렸다.
    {
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);

        _Connecter->GetActor();

        PlayerUpdateDataPacket Data;
        Data.UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
        Data.m_State = ActorState::in;
        Data.m_Data.SetData(_Connecter->GetPlayer()->GetPos(), _Connecter->GetPlayer()->GetRot());
        // 위치 여기로 등장시켜라.
        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(Data);
        }
    }

    {
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList((int)LogicValue::CollisionLayer::PLAYER);

        PlayerUpdatePacket AllActorPacket; // 나에게 모든 다룬 유저들을 알려주는 패킷

        for (auto& _Actor : GetActor)
        {
            // 나의 정보는 나에게 보내는 정보로 들어가면 안된다.
            // 내가 받기는 하겠지만 거기에 내가 또 들어가있을 필요는 없다.
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerPlayer> OtherPlayer = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            PlayerUpdateDataPacket Data;
            Data.UpdateID = reinterpret_cast<__int64>(OtherPlayer.get());
            Data.m_State = ActorState::Update;
            // 여기서 회전값도 같이 보내요.
            Data.m_Data.SetData(OtherPlayer->GetPos(), OtherPlayer->GetRot());
            AllActorPacket.m_PlayerData.push_back(Data);
        }

        _Connecter->Send(AllActorPacket);
    }


    {
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList((int)LogicValue::CollisionLayer::MONSTER);

        MonsterUpdatePacket AllMonsterPacket; 

        for (auto& _Actor : GetActor)
        {
            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerMonster> OtherMonster = std::dynamic_pointer_cast<ServerMonster, Actor>(_Actor);
            OtherMonster->Setting();
            OtherMonster->MonsterData.m_State = ActorState::Update;
            AllMonsterPacket.m_MonsterData.push_back(OtherMonster->MonsterData);
        }

        _Connecter->Send(AllMonsterPacket);
    }

    {
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList((int)LogicValue::CollisionLayer::ITEM);

        ItemUpdatePacket AllItemPacket; // 나에게 모든 다룬 유저들을 알려주는 패킷

        for (auto& _Actor : GetActor)
        {
            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerItem> OtherItem = std::dynamic_pointer_cast<ServerItem, Actor>(_Actor);
            AllItemPacket.m_ItemUpdateDataList.push_back(OtherItem->GetItemData());
        }

        _Connecter->Send(AllItemPacket);
    }

    {
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList((int)LogicValue::CollisionLayer::POTAL);
        PotalUpdatePacket AllPoatalPacket; // 나에게 모든 다룬 유저들을 알려주는 패킷

        
        GameWorld* GamePtr = dynamic_cast<GameWorld*>(_World);
        AllPoatalPacket.WorldSizeX = GamePtr->GetSize().ix();
        AllPoatalPacket.WorldSizeY = GamePtr->GetSize().iy();
        for (auto& _Actor : GetActor)
        {
            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerPotal> OtherItem = std::dynamic_pointer_cast<ServerPotal, Actor>(_Actor);
            AllPoatalPacket.m_UpdateDataList.push_back(OtherItem->GetPotalData());
        }

        _Connecter->Send(AllPoatalPacket);
    }




    // 여기 리스트 안에 있는 Actor들 중에서
    // 나와 같지 않은 유저들은
    // 나한테 다른 패킷이라고 쏴줘야 합니다.

    int a = 0;


    // 좀 어려운점이.
    // _Connecter과 연결된 WaitActor를 어떻게 찾을거냐?
    // 찾는건 좀 짜증나므로
    // 보통 메모리와 연산을 사용하면 탐색이 필요없고
    // 쉽게 처
}

void WorldMsgFunc::PlayerUpdate(World* _World, ServerConnecter* _Connecter, ClientPlayerPacket _Packet)
{

    // 여기까지 왔으면
    // 플레이어는 무조건 세팅되어 있어야 하고
    if (nullptr == _Connecter->GetPlayer())
    {
        GameEngineDebug::AssertMsg("if (nullptr == _Connecter->GetPlayer())");
    }

    ActorState State = _Packet.m_State;

    switch (State)
    {
    case ActorState::Update:

        // std::cout << "Count " << _Packet.ActorData.Count << std::endl;
        _Connecter->GetPlayer()->PushUpdateData(_Packet.ActorData);
        {
            PlayerUpdatePacket AllActorPacket; // 나를 알려주는 패킷
            AllActorPacket.m_PlayerData.resize(1);
            AllActorPacket.m_PlayerData[0].m_State = ActorState::Update;
            AllActorPacket.m_PlayerData[0].m_Data = _Packet.ActorData;
            AllActorPacket.m_PlayerData[0].UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
            std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
            for (auto& _Actor : GetActor)
            {
                if (_Actor.get() == _Connecter->GetPlayer())
                {
                    continue;
                }

                // 내가 여기 들어있을 일은 없으니
                std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
                Ptr->GetConnecter()->Send(AllActorPacket);
            }
        }
        break;
    case ActorState::Att:
    {
        int a = 0;
        _Connecter->GetPlayer()->PushUpdateData(_Packet.ActorData);


        break;
    }
    case ActorState::WorldMove:
    {
        PlayerUpdatePacket AllActorPacket; // 나를 알려주는 패킷
        AllActorPacket.m_PlayerData.resize(1);
        AllActorPacket.m_PlayerData[0].m_State = ActorState::WorldMove;
        AllActorPacket.m_PlayerData[0].UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
        break;
    case ActorState::Death:
        break;
    default:
        break;
    }




}

void WorldMsgFunc::PlayerDeath(World* _World, __int64 _ID) 
{

    // 월드에 있는 모든 유저들에게 나의 죽음을 알려줘야 하니까.
    // 다른 모든 유저들에게 내가 움직였다는 사실을 알려준다. 
    {
        PlayerUpdatePacket AllActorPacket; // 나를 알려주는 패킷
        AllActorPacket.m_PlayerData.resize(1);
        AllActorPacket.m_PlayerData[0].m_State = ActorState::Death;
        AllActorPacket.m_PlayerData[0].UpdateID = _ID;
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == reinterpret_cast<Actor*>(_ID))
            {
                continue;
            }

            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
}

void WorldMsgFunc::ItemUpdate(World* _World, ItemUpdateData _Packet) 
{
    {
        std::shared_ptr<ServerItem> NewItem = _World->CreateActor<ServerItem>((int)LogicValue::CollisionLayer::ITEM);

        ItemUpdatePacket AllActorPacket; // 나를 알려주는 패킷
        _Packet.UpdateID = reinterpret_cast<__int64>(NewItem.get());
        AllActorPacket.m_ItemUpdateDataList.push_back(_Packet);

        // 아이템의 위치를 세팅해줘야
        NewItem->SetPos(_Packet.CurPos);

        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
}

void WorldMsgFunc::ItemDeath(World* _World, ItemUpdateData _Packet)
{
    if (_Packet.m_State != ActorState::Death)
    {
        int a = 0;
    }

    // 월드에 있는 모든 유저들에게 나의 죽음을 알려줘야 하니까.
      // 다른 모든 유저들에게 내가 움직였다는 사실을 알려준다. 
    {
        // 먹은 유저에게는 특별한 ItemUpdateData 날릴것이냐
        // 아니면 그냥 다 날리고 클라이언트에서 처리할거냐
        // 다 날리고 클라이언트에서 처리.

        ItemUpdatePacket AllActorPacket; // 나를 알려주는 패킷
        AllActorPacket.m_ItemUpdateDataList.push_back(_Packet);
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
}

void WorldMsgFunc::MonsterUpdate(World* _World, MonsterUpdateDataPacket _Data) 
{   
	_Data.m_State = ActorState::Update;
	std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
	for (auto& _Actor : GetActor)
	{
		// 몬스터랑 플레이어가 _Data.UpdateID가 겹칠리가 없는데
		// 선생님이 그냥 코드 복사하다가.
		// 붙어버린거네요.
		if (_Actor.get() == reinterpret_cast<Actor*>(_Data.UpdateID))
		{
			continue;
		}

		// 내가 여기 들어있을 일은 없으니
		std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
		Ptr->GetConnecter()->Send(_Data);
	}  
}

void WorldMsgFunc::MonsterDeath(World* _World, MonsterUpdateDataPacket _MonsterData)
{    
	ItemUpdateData NewData;
	NewData.CurPos = _MonsterData.m_Data.Pos;
	NewData.m_State = ActorState::Update;
	_World->MsgInsert(&WorldMsgFunc::ItemUpdate, NewData);

	std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
	for (auto& _Actor : GetActor)
	{
		if (_Actor.get() == reinterpret_cast<Actor*>(_MonsterData.UpdateID))
		{
			continue;
		}

		// 내가 여기 들어있을 일은 없으니
		std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
		Ptr->GetConnecter()->Send(_MonsterData);
	}    
}

void WorldMsgFunc::WorldMoveOk(World* _World, ServerConnecter* _Connect) 
{
    // 이걸 사용한 당사자에게 날리는 처리.
    WorldMoveOKPacket Pacekt;
    _Connect->Send(Pacekt);
}

void WorldMsgFunc::ClientChatPacketUpdate(World* _World, ServerConnecter* _Connecter, ClientChatPacket _Packet)
{
    // 친구추가
    if (std::string::npos != _Packet.Chat.FindOf(L"/F"))
    {
        _Packet.Chat.DeleteString(0, 3);

        GameEngineString FriendName;

        if (GameEngineString::GlobalSetConvertMultiByteString(_Connecter->GetCharacterData()->Name)
            == _Packet.Chat)
        {
            int b = 0;
            return;
        }

        std::string Name = _Connecter->GetCharacterData()->Name;
        DBManager::Inst().PushTask("", &DbTaskFunc::AddFriendProcess, _Connecter->GetCharacterData()->PID, Name, _Packet.Chat);
        return;
    }

    // 파티초대
    if (InviteParty(_World, _Connecter, _Packet))
    {
        return;
    }

    std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
    {
        ServerChatPacket Data;
        Data.PID = _Packet.PID;
        Data.Type = _Packet.Type;
        Data.Name = _Packet.Name;
        Data.Chat = _Packet.Chat;

        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            if (0 == Ptr->GetConnecter()->Send(Data))
            {
            }
        }
    }
}

bool WorldMsgFunc::InviteParty(World* _World, ServerConnecter* _Connecter, ClientChatPacket _Packet)
{
    if (std::string::npos != _Packet.Chat.FindOf(L"/I"))
    {
        _Packet.Chat.DeleteString(0, 3);

        // 나를 초대 한다면
        if (GameEngineString::GlobalSetConvertMultiByteString(_Connecter->GetCharacterData()->Name)
            == _Packet.Chat)
        {
            return false;
        }
               
        ServerPartyPacket PartyData;
        DBManager::Inst().PushTask("", &DbTaskFunc::PartyInviteProcess, _Connecter, _Packet);

       

        //// 접속중이 아닌 유저를 초대한다면
        // 이거 일단 나중에 생각
        //bool IsPlaying = false;
        //std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        //for (auto& _Actor : GetActor)
        //{
        //    std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
        //    if (_Packet.Chat == GameEngineString::GlobalSetConvertMultiByteString(Ptr->GetConnecter()->GetCharacterData()->Name))
        //    {
        //        IsPlaying = true;
        //        continue;
        //    }
        //}

        //if (IsPlaying)
        //{
        //    std::string Name = _Connecter->GetCharacterData()->Name;
        //    DBManager::Inst().PushTask("", &DbTaskFunc::AddFriendProcess, _Connecter->GetCharacterData()->PID, Name, _Packet.Chat);
        //}
        //else
        //{
        //    
        //}

        return true;
    }

    return false;
}

void WorldMsgFunc::ClientPartyPacketUpdate(World* _World, ServerConnecter* _Connecter, ClientPartyPacket _Packet)
{
    // 파티를 수락했을때
    if (PARTYPACKETTYPE::Accept == _Packet.Type)
    {
        // 디비
        DBManager::Inst().PushTask("", &DbTaskFunc::PartyAcceptProcess, _Connecter, _Packet);
    } 
}

void WorldMsgFunc::PartyInviteProcess(World* _World, ServerConnecter* _Connecter, ClientChatPacket _Packet)
{
    std::vector<std::shared_ptr<PartyTableData>>& PartyData = _Connecter->GetPartyDataRef();
    size_t PartyDataSize = PartyData.size();

    ServerPartyPacket ServerPartyData;
    // 파티데이터가 없다
    if (0 == PartyDataSize)
    {
        // 파티 만들기 시작
        ServerPartyData.Type = PARTYPACKETTYPE::Invite;
        ServerPartyData.PID.push_back(_Connecter->GetCharacterData()->PID);
        ServerPartyData.Name.push_back(GameEngineString::GlobalSetConvertMultiByteString(_Connecter->GetCharacterData()->Name));
        ServerPartyData.Connect.push_back(1);
    }
    else
    {
        ServerPartyData.Type = PARTYPACKETTYPE::Invite;
        ServerPartyData.PID.push_back(PartyData[0]->ID1);
        ServerPartyData.Name.push_back(GameEngineString::GlobalSetConvertMultiByteString(PartyData[0]->Name1));
        ServerPartyData.Connect.push_back(PartyData[0]->Connect1);
        ServerPartyData.PID.push_back(PartyData[0]->ID2);
        ServerPartyData.Name.push_back(GameEngineString::GlobalSetConvertMultiByteString(PartyData[0]->Name2));
        ServerPartyData.Connect.push_back(PartyData[0]->Connect2);
        //ServerPartyData.PID.push_back(PartyData[0]->ID3);
        //ServerPartyData.Name.push_back(GameEngineString::GlobalSetConvertMultiByteString(PartyData[0]->Name3));
        //ServerPartyData.Connect.push_back(1);
    }

    // 상대한테 알려줘
    std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
    for (auto& _Actor : GetActor)
    {
        std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
        if (_Packet.Chat == GameEngineString::GlobalSetConvertMultiByteString(Ptr->GetConnecter()->GetCharacterData()->Name))
        {
            Ptr->GetConnecter()->Send(ServerPartyData);
        }
    }
}

void WorldMsgFunc::PartyAcceptProcess(World* _World, ServerConnecter* _Connecter, ClientPartyPacket _Packet)
{
    // 상대한테 알려줘야지
    std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
    std::list<std::shared_ptr<Actor>>::iterator BeginIter = GetActor.begin();
    std::list<std::shared_ptr<Actor>>::iterator EndIter = GetActor.end();
    for (; BeginIter != EndIter; ++BeginIter)
    {
        std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(*BeginIter);
        size_t size = _Packet.Name.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (_Packet.Name[i] == GameEngineString::GlobalSetConvertMultiByteString(Ptr->GetConnecter()->GetCharacterData()->Name))
            {
                ServerPartyPacket ServerPartyData;
                ServerPartyData.Type = PARTYPACKETTYPE::Accept;
                ServerPartyData.PID = _Packet.PID;
                ServerPartyData.Name = _Packet.Name;
                ServerPartyData.Connect = _Packet.Connect;

                Ptr->GetConnecter()->Send(ServerPartyData);
            }
        }
    }
}
