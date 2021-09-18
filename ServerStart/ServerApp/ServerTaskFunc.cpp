#include "ServerTaskFunc.h"
#include <DBManager.h>
#include <AccountTable.h>
#include <ClientToServer.h>
#include <ServerConnecter.h>
#include "GameEngineServer.h"
#include <LogicValue.h>
#include "LogicThread.h"
#include "WorldMsgFunc.h"
#include <ItemTable.h>
#include <FriendTable.h>
#include <PartyTable.h>
// Static Var
// Static Func


void ServerTaskFunc::LoginOKProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<ItemTableData>> _Items,
    std::vector<std::shared_ptr<FriendTableData>> _Friends, std::vector<std::shared_ptr<PartyTableData>> _Partys, ServerConnecter* Con)
{
    LoginResultPacket OKPacket;
    OKPacket.m_Code = (int)LoginResultType::OK;

    if (SOCKET_ERROR == Con->Send(OKPacket))
    {
        int a = 0;
    }
    Con->SetCharacterData(_Data);
    Con->SetItemsData(_Items);
    Con->SetFriendData(_Friends);
    Con->SetPartyData(_Partys);
    LogicThread::InsertMessage(
        _Data->EndIndex,
        &WorldMsgFunc::WaitPlayerCreate, Con);

}

void ServerTaskFunc::PartyInviteProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<PartyTableData>> _PartyData,
    ServerConnecter* Con, ClientChatPacket _Packet)
{
    Con->SetPartyData(_PartyData);
    LogicThread::InsertMessage(_Data->EndIndex, &WorldMsgFunc::PartyInviteProcess, Con, _Packet);
}

void ServerTaskFunc::PartyAcceptProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<PartyTableData>> _PartyData,
    ServerConnecter* Con, ClientPartyPacket _Packet)
{
    Con->SetPartyData(_PartyData);
    LogicThread::InsertMessage(_Data->EndIndex, &WorldMsgFunc::PartyAcceptProcess, Con, _Packet);
}
