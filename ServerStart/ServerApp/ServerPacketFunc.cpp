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
    // ������ �ϸ� ĳ���͵� �ڵ����� ������ִ� �ý����̴� �־���� �Ѵ�.
    // �׽�Ʈ�� ��� ĳ����.
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
    
    // �̰� ���⿡�� ���ٷ� ó���Ҽ��� �ִµ�.
    DBManager::Inst().PushTaskBind(AccountTable::SelectQueryCreate(_Packet.ID),
        // std::bind(Func, std::placeholders::_1)
        [_Packet, Socket](DBConnecter* _Value)
        {
            std::vector<std::shared_ptr<AccountTableData>> Data;
            _Value->DynamicQueryTemplate(AccountTable::SelectQueryCreate(_Packet.ID).c_str(), Data);

            // ����� �����Ѵٸ�
            if (0 != Data.size())
            {
                AccountResultPacket Packet;
                Packet.m_Code = (int)AccountResultType::IDOverlap;
                Socket->Send(Packet);
                return;
            }

            

            // ĳ���͵� ������� �Ѵ�.

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

            // �⺻������ db�� utf-8 �������� ó��������� �ϴµ�.
            // ��Ƽ����Ʈ ó���� ������ ������ �������� ���� �ִµ�.
            // �ѱ��� ������ ������� �ִ�.
            memcpy_s(NewData.Name, sizeof(NewData.Name), Name.c_str(), strlen(Name.c_str()));
            memcpy_s(NewData.EndIndex, sizeof(NewData.EndIndex), "0,0", strlen("0,0"));


            // std::string TestQuery = CharacterTable::InsertQueryCreate(NewData);
            _Value->DynamicQueryTemplate(CharacterTable::InsertQueryCreate(NewData).c_str(), Data);

            // �̰� �ƴ϶��

            // ĳ���͵� �������� �մϴ�.
           

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

    // ���⼭ wait������ ���͸� world�� ���Խ�Ų��.
    LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex,
            &WorldMsgFunc::WaitPlayerInWorld, Socket);

    // �� ��Ŷ�� �̹� �ּ��� ��ٸ��� �ִ� ���͵���� ������ ��Ŷ
    // � ���忡 � �÷��̾�� �� ��Ŷ������ ������ �Ǿ�� �մϴ�.

    //
}

void ServerPacketFunc::ClientPlayerPacketProcess(ServerConnecter* Socket, ClientPlayerPacket _Packet)
{
    Socket->GetActor()->GetWorld()->MsgInsert(&WorldMsgFunc::PlayerUpdate, Socket, _Packet);

    //LogicThread::InsertMessage(Socket->GetCharacterData()->EndIndex.GetConvertMultiByteString(),
    //    &WorldMsgFunc::PlayerUpdate, Socket, _Packet);
    // std::cout << _Packet.UpdateID << "�÷��̾� ������Ʈ" << std::endl;
}

void ServerPacketFunc::GetRankPacketProcess(ServerConnecter* _Socket, GetRankPacket _Packet)
{
    
    // �����׽�ũ�� �Űܼ� �����ʿ��� ó�����ִ°� �´�.

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

        //// 1�� �� �����ϰ�
        // ���� ������ ��Ͻ��Ѽ� �����ϰ�
        // �״����� �� �ּ� ������� �����;���?
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
