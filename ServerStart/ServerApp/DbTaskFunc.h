#pragma once
// #include <ClientToServer.h>
#include <GameEngineMemory.h>
#include <vector>
#include <LogicConnecter.h>
#include <GameEngineString.h>


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
class ClientPartyPacket;
class ServerPartyPacket;
class ClientChatPacket;
class DbTaskFunc
{
public:
    static void LoginSelectProcess(DBConnecter* Connecter, DBTask* _Ptr, LoginPacket _Data, ServerConnecter* _Socket);
    static void DisConnectDataUpdateProcess(DBConnecter* Connecter, DBTask* _Ptr, std::shared_ptr<CharacterTableData> _CharacterData, std::vector<std::shared_ptr<ItemTableData>> _ItemsData, std::vector<ITEMDBCHECKTYPE> _ItemCheck);
    static void AddFriendProcess(DBConnecter* Connecter, DBTask* _Ptr, __int64 PID, std::string& PName, GameEngineString Name);
    static void AddPartyProcess(DBConnecter* Connecter, DBTask* _Ptr, __int64 PID, std::string& PName, ClientPartyPacket Name);
    
    static void PartyAcceptProcess(DBConnecter* Connecter, DBTask* _Ptr, ServerConnecter* _Connecter, ClientPartyPacket _Packet);
    static void PartyInviteProcess(DBConnecter* Connecter, DBTask* _Ptr, ServerConnecter* _Connecter, ClientChatPacket _Packet);
    // DB��û�� ����� ��� ó�������� �����ϴ� �Լ����� ��Ƴ��� �̴ϴ�.
};

