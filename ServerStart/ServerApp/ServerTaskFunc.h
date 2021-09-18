#pragma once
// #include <ClientToServer.h>
#include <memory>
#include <vector>



// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class DBConnecter;
class DBTask;
class LoginPacket;
class ServerConnecter;
class CharacterTableData;
class ItemTableData;
class FriendTableData;
class PartyTableData;
class ClientChatPacket;
class ClientPartyPacket;
class ServerTaskFunc
{
public:
    // DB요청의 결과를 어떻게 처리할지를 결정하는 함수들을 모아놓을 겁니다.
    static void LoginOKProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<ItemTableData>> _Items, 
        std::vector<std::shared_ptr<FriendTableData>> _Friends, std::vector<std::shared_ptr<PartyTableData>> _Partys, ServerConnecter* Con);

    static void PartyInviteProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<PartyTableData>> _PartyData,
        ServerConnecter* Con, ClientChatPacket _Packet);

    static void PartyAcceptProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<PartyTableData>> _PartyData,
        ServerConnecter* Con, ClientPartyPacket _Packet);
};

