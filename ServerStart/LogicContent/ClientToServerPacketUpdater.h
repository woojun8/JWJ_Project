#ifndef UNREALDEFINE
#pragma once
#include "PacketUpdater.h"

class ClientToServerPacketUpdater : public PacketUpdater
{
public:
    class ServerConnecter* m_ServerConnecter;

public:
    CTOSPACKETSTATIC(AccountPacket)
    CTOSPACKETSTATIC(LoginPacket)
    CTOSPACKETSTATIC(ClientReadyPacket)
    CTOSPACKETSTATIC(ClientPlayerPacket)
    CTOSPACKETSTATIC(GetRankPacket)
    CTOSPACKETSTATIC(ClientChatPacket)
    CTOSPACKETSTATIC(ClientPartyPacket)

public:
    const char* Update()
    {
        PacketInit();

        switch (m_CTOSType)
        {
        //case CLIENTTOSERVERTYPE::LoginPacket:
        //{ 
        //    LoginPacket Packet;
        //    Packet.DeSerialize(Ser);
        //    LoginPacketUpdate(m_ServerConnecter, Packet);
        //    m_UpdateSize += Packet.GetSize();
        //    return  LoginPacketText;
        //} 
            CTOSCASE(LoginPacket)
            CTOSCASE(AccountPacket)
            CTOSCASE(ClientReadyPacket)
            CTOSCASE(ClientPlayerPacket)
            CTOSCASE(GetRankPacket)
            CTOSCASE(ClientChatPacket)
            CTOSCASE(ClientPartyPacket)
        case CLIENTTOSERVERTYPE::MAX:
        default:
            GameEngineDebug::AssertMsg("case CLIENTTOSERVERTYPE::MAX:");
            break;
        }

        return "ERROR";
    }

public:
    ClientToServerPacketUpdater(ServerConnecter* _Socket, char* _Ptr, size_t _Size) : PacketUpdater(_Ptr, _Size), m_ServerConnecter(_Socket)
    {
    }
};

#endif