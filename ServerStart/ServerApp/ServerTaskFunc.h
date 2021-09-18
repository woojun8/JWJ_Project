#pragma once
// #include <ClientToServer.h>
#include <memory>
#include <vector>



// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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
    // DB��û�� ����� ��� ó�������� �����ϴ� �Լ����� ��Ƴ��� �̴ϴ�.
    static void LoginOKProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<ItemTableData>> _Items, 
        std::vector<std::shared_ptr<FriendTableData>> _Friends, std::vector<std::shared_ptr<PartyTableData>> _Partys, ServerConnecter* Con);

    static void PartyInviteProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<PartyTableData>> _PartyData,
        ServerConnecter* Con, ClientChatPacket _Packet);

    static void PartyAcceptProcess(std::shared_ptr<CharacterTableData> _Data, std::vector<std::shared_ptr<PartyTableData>> _PartyData,
        ServerConnecter* Con, ClientPartyPacket _Packet);
};

