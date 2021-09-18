#pragma once
#include <ClientToServer.h>
#include <ServerToClient.h>


class ServerConnecter;
class ServerPacketFunc
{
public:
    static void Init();
    static void AccountPacketProcess(ServerConnecter* Socket, AccountPacket _Packet);
    static void LoginPacketProcess(ServerConnecter* Socket, LoginPacket _Packet);
    static void ClientReadyPacketProcess(ServerConnecter* Socket, ClientReadyPacket _Packet);
    static void ClientPlayerPacketProcess(ServerConnecter* Socket, ClientPlayerPacket _Packet);
    static void GetRankPacketProcess(ServerConnecter* Socket, GetRankPacket _Packet);
    static void ClientChatPacketProcess(ServerConnecter* Socket, ClientChatPacket _Packet);
    static void ClientPartyPacketProcess(ServerConnecter* Socket, ClientPartyPacket _Packet);

private: // constructer destructer
    ServerPacketFunc() {}
    ~ServerPacketFunc() {}

public: // delete constructer 
    ServerPacketFunc(const ServerPacketFunc& _Other) = delete;
    ServerPacketFunc(const ServerPacketFunc&& _Other) = delete;

public: // delete operator
    ServerPacketFunc& operator=(const ServerPacketFunc& _Other) = delete;
    ServerPacketFunc& operator=(const ServerPacketFunc&& _Other) = delete;

public: // member Func
};

