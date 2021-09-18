#include "DbTaskFunc.h"
#include <DBManager.h>
#include <AccountTable.h>
#include <ClientToServer.h>
#include "ServerConnecter.h"
#include "GameEngineServer.h"
#include <LogicValue.h>
#include "ServerTaskFunc.h"
#include <ItemTable.h>
#include <FriendTable.h>
#include <PartyTable.h>
#include <CharacterTable.h>
// Static Var
// Static Func



void DbTaskFunc::AddFriendProcess(DBConnecter* Connecter, DBTask* _Ptr, __int64 PID, std::string& PName, GameEngineString Name)
{
    std::vector<std::shared_ptr<AccountTableData>> Data;
    Connecter->DynamicQueryTemplate(AccountTable::SelectQueryCreate(Name).c_str(), Data);

    // Name�̶�� �ϴ� �༮�� �ֳ�?
    if (1 != Data.size())
    {
        return;
    }

    std::vector<std::shared_ptr<FriendTableData>> FriendDatas;
    Connecter->DynamicQueryTemplate(FriendTable::SelectQueryCreate(PID, Data[0]->PID).c_str(), FriendDatas);
    if (0 != FriendDatas.size())
    {
        return;
    }
        
    std::string FName = Data[0]->Name;
    Connecter->DynamicQuery(FriendTable::InsertQueryCreate(PID, PName, Data[0]->PID, FName).c_str());
}

void DbTaskFunc::PartyAcceptProcess(DBConnecter* Connecter, DBTask* _Ptr, ServerConnecter* _Connecter, ClientPartyPacket _Packet)
{
    // C�� F�� �ʴ��߾ �� ��Ŷ�� ������ ����� F�ϱ�
    // Ŀ���ʹ� �翬�� F��
    // 0���� �ʴ븦 �ѻ��(��Ƽ�� �������� ��������)
    long long PID = _Packet.PID[0];

    std::vector<std::shared_ptr<PartyTableData>> PartyData;
    Connecter->DynamicQueryTemplate(PartyTable::SelectQueryCreate(PID).c_str(), PartyData);

    std::vector<std::shared_ptr<CharacterTableData>> ChDatas;
    // ��Ƽ�����Ͱ� ���ٸ�
    if (0 == PartyData.size())
    {
        // ������ �Ѵ�
        if (3 > _Packet.PID.size())
        {
            int Empty = 0;
            GameEngineString EmptyStr = L"Epmty";
            Connecter->DynamicQuery(PartyTable::InsertQueryCreate(_Packet.PID[0], _Packet.Name[0], _Packet.Connect[0], _Packet.PID[1], _Packet.Name[1], _Packet.Connect[1]).c_str());
        }
		/*else
		{
			Connecter->DynamicQuery(PartyTable::InsertQueryCreate(_Packet.PID[0], _Packet.Name[0], _Packet.PID[1], _Packet.Name[1], _Packet.PID[2], _Packet.Name[2]).c_str());
		}*/
    }
    else
    {
        // ��Ƽ��� ������Ʈ
        //Connecter->DynamicQueryTemplate(PartyTable::SelectQueryCreate((PartyData[0]->ID1)).c_str(), PartyData);
        PartyData[0]->ID3 = _Packet.PID[2];
        strcpy_s(PartyData[0]->Name3, _Packet.Name[2].GetConvertMultiByteString().c_str());
        PartyData[0]->Connect3 = _Packet.Connect[2];

        std::string UpdateQuery = PartyTable::UpdateQueryCreate(*PartyData[0]);
        Connecter->DynamicQuery(UpdateQuery.c_str());
    }

    Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(PID)).c_str(), ChDatas);

    GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT,
        std::bind(&ServerTaskFunc::PartyAcceptProcess, ChDatas[0], PartyData, _Connecter, _Packet));   
}

void DbTaskFunc::PartyInviteProcess(DBConnecter* Connecter, DBTask* _Ptr, ServerConnecter* _Connecter, ClientChatPacket _Packet)
{
    long long PID = _Connecter->GetCharacterData()->PID;
    std::string strPID = _Connecter->GetCharacterData()->Name;

    std::vector<std::shared_ptr<CharacterTableData>> ChDatas;    

    std::vector<std::shared_ptr<PartyTableData>> PartyData;
    Connecter->DynamicQueryTemplate(PartyTable::SelectQueryCreate(PID).c_str(), PartyData);
    if (0 == PartyData.size())
    {
        // ������� ��Ƽ�����Ͱ� ���ٸ�        
        // AccountTable���� ĳ���� ������ ������
        std::vector<std::shared_ptr<AccountTableData>> Data;
        Connecter->DynamicQueryTemplate(AccountTable::SelectQueryCreateStr(strPID).c_str(), Data);                
        Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(Data[0]->PID)).c_str(), ChDatas);
    }
    else
    {
        // ������ �ٷ� ������
        Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(PartyData[0]->ID1)).c_str(), ChDatas);
    }

    GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT,
        std::bind(&ServerTaskFunc::PartyInviteProcess, ChDatas[0], PartyData, _Connecter, _Packet));
}

void DbTaskFunc::AddPartyProcess(DBConnecter* Connecter, DBTask* _Ptr, __int64 PID, std::string& PName, ClientPartyPacket Name)
{
//    std::vector<std::shared_ptr<AccountTableData>> Data;
//    Connecter->DynamicQueryTemplate(AccountTable::SelectQueryCreate(Name).c_str(), Data);
//
//    if (1 != Data.size())
//    {
//        return;
//    }
//
//    std::vector<std::shared_ptr<PartyTableData>> PartyDatas;
//    Connecter->DynamicQueryTemplate(PartyTable::SelectQueryCreate(PID, Data[0]->PID).c_str(), PartyDatas);
//    if (0 != PartyDatas.size())
//    {
//        return;
//    }
//
//    std::string FName = Data[0]->Name;
//    Connecter->DynamicQuery(PartyTable::InsertQueryCreate(PID, PName, Data[0]->PID, FName).c_str());

    ClientPartyPacket Packet;
}

void DbTaskFunc::LoginSelectProcess(DBConnecter* Connecter, DBTask* _Ptr,
    LoginPacket _Data, ServerConnecter* _Socket)
{
    std::vector<std::shared_ptr<AccountTableData>> Data;
    Connecter->DynamicQueryTemplate(_Ptr->Query.c_str(), Data);

    // DB���� �����͸� ������ �˴ϴ�.

    // �ƿ� �� ĳ���Ͱ� �������� �ʴ´�.
    if (0 >= Data.size())
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT,
            [_Ptr, _Socket]()
        {
            // DB������
            LoginResultPacket Pacekt;
            Pacekt.m_Code = (int)LoginResultType::IDERROR;
            _Socket->Send(Pacekt);

            //[Data]() 
            //{
            //    // ��Ŷ������
            //};

            DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
        });

        return;
    }

    if (1 < Data.size())
    {
        // �� ������ �ɰ��� ���� 2���� ���ü� ����.

        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, [_Ptr, _Socket]()
        {
            LoginResultPacket Pacekt;
            Pacekt.m_Code = (int)LoginResultType::ServerError;
            _Socket->Send(Pacekt);
            DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
        });

        return;
    }

    std::shared_ptr<AccountTableData> AccountData = Data[0];

    if (nullptr == AccountData)
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, [_Ptr, _Socket]()
        {
            LoginResultPacket Pacekt;
            Pacekt.m_Code = (int)LoginResultType::ServerError;
            _Socket->Send(Pacekt);
            DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
        });

        return;
    }

    std::vector<std::shared_ptr<CharacterTableData>> ChDatas;
    Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ChDatas);

    if (0 == ChDatas.size()
        || 2 < ChDatas.size())
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, [_Ptr, _Socket]()
        {
            LoginResultPacket Pacekt;
            Pacekt.m_Code = (int)LoginResultType::ServerError;
            _Socket->Send(Pacekt);
            DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
        });
    }

    std::vector<std::shared_ptr<FriendTableData>> FriendDatas;
    Connecter->DynamicQueryTemplate(FriendTable::SelectQueryCreate(AccountData->PID).c_str(), FriendDatas);

    std::vector<std::shared_ptr<ItemTableData>> ItemDatas;
    Connecter->DynamicQueryTemplate(ItemTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ItemDatas);

    std::vector<std::shared_ptr<PartyTableData>> PartyData;
    Connecter->DynamicQueryTemplate(PartyTable::SelectQuery(AccountData->PID).c_str(), PartyData);

    GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT,
        std::bind(&ServerTaskFunc::LoginOKProcess, ChDatas[0], ItemDatas, FriendDatas, PartyData, _Socket));
}

void DbTaskFunc::DisConnectDataUpdateProcess(DBConnecter* Connecter, DBTask* _Ptr, std::shared_ptr<CharacterTableData> _CharacterData, std::vector<std::shared_ptr<ItemTableData>> _Item, std::vector<ITEMDBCHECKTYPE> _ItemCheck)
{
    {
        std::string UpdateQuery = CharacterTable::UpdateQueryCreate(*_CharacterData);
        Connecter->DynamicQuery(UpdateQuery.c_str());
    }

    {
        for (size_t i = 0; i < _ItemCheck.size(); i++)
        {
            if (ITEMDBCHECKTYPE::UPDATE == _ItemCheck[i])
            {
                std::string ItemUpdateQuery = ItemTable::UpdateQueryCreate(*_Item[i]);
                Connecter->DynamicQuery(ItemUpdateQuery.c_str());
            }
            else if (ITEMDBCHECKTYPE::NEW == _ItemCheck[i])
            {
                std::string ItemInsertQuery = ItemTable::InsertQueryCreate(*_Item[i]);
                Connecter->DynamicQuery(ItemInsertQuery.c_str());
            }
        }
    }
}