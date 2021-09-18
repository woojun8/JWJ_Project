#include "ServerPacketFunc.h"
#include <AccountTable.h>
#include <LogicValue.h>
#include <ServerConnecter.h>
#include <PacketUpdater.h>
#include <CharacterTable.h>
#include "LogicThread.h"
#include "WorldMsgFunc.h"
#include <ClientToServerPacketUpdater.h>
#include <iostream>
#include "ServerWorldManager.h"
#include "ServerWorld.h"
#include <DBManager.h>
#include <AccountTable.h>
#include "DbTaskFunc.h"
#include <RedisConnecter.h>
#include "RedisResultFunc.h"

//AccountTable ATable;
//CharacterTable CTable;
//CharacterData NewUserData = {L"",L"0,0", 5, 5, 10, 100, 100};

void ServerPacketFunc::Init()
{
    // 가입을 하면 캐릭터도 자동으로 만들어주는 시스템이니 넣어줘야 한다.
    // 테스트용 운영자 캐릭터.
    //ATable.Insert(AccountData(L"f", L"f"));
    //CTable.Insert({ L"f",L"0,0", 5, 5, 10, 100, 100 });

    CTOSPACKETCALLBACK(AccountPacket);
    CTOSPACKETCALLBACK(LoginPacket);
    CTOSPACKETCALLBACK(ClientReadyPacket);
    CTOSPACKETCALLBACK(ClientPlayerPacket);
    CTOSPACKETCALLBACK(GetRankPacket);
    CTOSPACKETCALLBACK(ClientChatPacket);
    CTOSPACKETCALLBACK(ClientPartyPacket);
}


void ServerPacketFunc::AccountPacketProcess(ServerConnecter* Socket, AccountPacket _Packet)
{
    
    // 이걸 여기에서 람다로 처리할수도 있는데.
    DBManager::Inst().PushTaskBind(AccountTable::SelectQueryCreate(_Packet.ID),
        // std::bind(Func, std::placeholders::_1)
        [_Packet, Socket](DBConnecter* _Value)
        {
            std::vector<std::shared_ptr<AccountTableData>> Data;
            _Value->DynamicQueryTemplate(AccountTable::SelectQueryCreate(_Packet.ID).c_str(), Data);

            // 사이즈가 존재한다면
            if (0 != Data.size())
            {
                AccountResultPacket Packet;
                Packet.m_Code = (int)AccountResultType::IDOverlap;
                Socket->Send(Packet);
                return;
            }

            

            // 캐릭터도 생겨줘야 한다.

            // INSERT INTO `server11`.`accounttable` (`Name`, `Password`) VALUES('j', 'j');
            _Value->DynamicQueryTemplate(AccountTable::InsertQueryCreate(_Packet.ID, _Packet.PASS).c_str(), Data);

            __int64 PID = _Value->GetLastInsertId();

            CharacterTableData NewData;
            //// 1	1	f	0, 0	5	5	100	100	100
            NewData.no = 0;
            NewData.PID = PID;
            NewData.ATT = 10;
            NewData.HP = 100;
            NewData.MAXHP = 100;
            NewData.LastX = 5;
            NewData.LastY = 5;

            std::string Name = _Packet.ID.GetConvertMultiByteString();

            // 기본적으로 db는 utf-8 형식으로 처리해해줘야 하는데.
            // 멀티바이트 처리기 때문에 영문은 문제없이 들어갈수 있는데.
            // 한글은 문제가 생길수가 있다.
            memcpy_s(NewData.Name, sizeof(NewData.Name), Name.c_str(), strlen(Name.c_str()));
            memcpy_s(NewData.EndIndex, sizeof(NewData.EndIndex), "0,0", strlen("0,0"));


            // std::string TestQuery = CharacterTable::InsertQueryCreate(NewData);
            _Value->DynamicQueryTemplate(CharacterTable::InsertQueryCreate(NewData).c_str(), Data);

            // 이게 아니라면

            // 캐릭터도 만들어줘야 합니다.
           

        }
    );
    return;
}


void ServerPacketFunc::LoginPacketProcess(ServerConnecter* Socket, LoginPacket _Packet) 
{
    DBManager::Inst().PushTask(AccountTable::SelectQueryCreate(_Packet.ID), &DbTaskFunc::LoginSelectProcess, _Packet, Socket);
    return;
}

void ServerPacketFunc::ClientReadyPacketProcess(ServerConnecter* Socket, ClientReadyPacket _Packet) 
{
    if (nullptr == Socket->GetCharacterData())
    {
        GameEngineDebug::AssertMsg("if (nullptr == Socket->GetCharacterData())");
    }

    // 여기서 wait상태의 액터를 world로 진입시킨다.
    LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex,
            &WorldMsgFunc::WaitPlayerInWorld, Socket);

    // 이 패킷은 이미 최소한 기다리고 있는 액터들부터 가능한 패킷
    // 어떤 월드에 어떤 플레이어에게 온 패킷인지가 구분이 되어야 합니다.

    //
}

void ServerPacketFunc::ClientPlayerPacketProcess(ServerConnecter* Socket, ClientPlayerPacket _Packet)
{
    Socket->GetActor()->GetWorld()->MsgInsert(&WorldMsgFunc::PlayerUpdate, Socket, _Packet);

    //LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex.GetConvertMultiByteString(),
    //    &WorldMsgFunc::PlayerUpdate, Socket, _Packet);
    // std::cout << _Packet.UpdateID << "플레이어 업데이트" << std::endl;
}

void ServerPacketFunc::GetRankPacketProcess(ServerConnecter* _Socket, GetRankPacket _Packet)
{
    
    // 서버테스크로 옮겨서 서버쪽에서 처리해주는게 맞다.

    if (0 == _Packet.Type)
    {

        RedisManager::GetInst().RedisCommandPush<RedisCommand::ZADD>(
            std::bind(&RedisResultFunc::RankResultProcess, std::placeholders::_1, _Socket, 0, 5),
            "RANK", _Socket->GetCharacterData()->Score, _Socket->GetCharacterData()->Name);
    } 
    else if (1 == _Packet.Type)
    {
        RedisManager::GetInst().RedisCommandPush<RedisCommand::ZADD>(
            std::bind(&RedisResultFunc::UserRankResultProcess, std::placeholders::_1, _Socket),
            "RANK", _Socket->GetCharacterData()->Score, _Socket->GetCharacterData()->Name);


        //RedisManager::GetInst().RedisCommandPush<RedisCommand::ZCOUNT>(
        //    std::bind(&RedisResultFunc::UserRankResultProcess, std::placeholders::_1, _Socket),
        //    "RANK", 0, 300000);

        //// 1은 좀 복잡하고
        // 내가 점수를 등록시켜서 갱신하고
        // 그다음에 내 주션 사람들을 가져와야죠?
        //RedisManager::GetInst().RedisCommandPush<RedisCommand::ZADD>(
        //    std::bind(&RedisResultFunc::UserRankResultProcess, std::placeholders::_1, _Socket),
        //    "TESTKEY2", "1");
    }
    else {
        GameEngineDebug::AssertMsg("void ServerPacketFunc::GetRankPacketProcess(ServerConnecter* Socket, GetRankPacket& _Packet)");
    }
    int a = 0;
}

void ServerPacketFunc::ClientChatPacketProcess(ServerConnecter* Socket, ClientChatPacket _Packet)
{
    // static void ChatUpdate(World * _World, ServerConnecter * _Connecter, ClientChatPacket _Packet);
    LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex,
        &WorldMsgFunc::ClientChatPacketUpdate, Socket, _Packet);
}

void ServerPacketFunc::ClientPartyPacketProcess(ServerConnecter* Socket, ClientPartyPacket _Packet)
{
    LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex,
        &WorldMsgFunc::ClientPartyPacketUpdate, Socket, _Packet);
}
