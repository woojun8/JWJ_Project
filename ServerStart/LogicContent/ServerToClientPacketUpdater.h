#pragma once
#include "PacketUpdater.h"


class ServerToClientPacketUpdater : public PacketUpdater
{
public:
    STOCPACKETSTATIC(AccountResultPacket)
    STOCPACKETSTATIC(LoginResultPacket)
    STOCPACKETSTATIC(CharacterPacket)
    STOCPACKETSTATIC(GameStartPacket)
    STOCPACKETSTATIC(PlayerUpdatePacket)
    STOCPACKETSTATIC(PlayerUpdateDataPacket)
    STOCPACKETSTATIC(MonsterUpdatePacket)
    STOCPACKETSTATIC(MonsterUpdateDataPacket)
    STOCPACKETSTATIC(ItemUpdatePacket)
    STOCPACKETSTATIC(PotalUpdatePacket)
    STOCPACKETSTATIC(WorldMoveOKPacket)
    STOCPACKETSTATIC(ServerChatPacket)
    STOCPACKETSTATIC(ServerPartyPacket)
    STOCPACKETSTATIC(RankPacket)

public:
    const char* Update()
    {
        // 어떤 패킷인지 구분이 되고.
        PacketInit();

        switch (m_STOCType)
        {
            STOCCASE(AccountResultPacket)
            STOCCASE(LoginResultPacket)
            STOCCASE(CharacterPacket)
            STOCCASE(GameStartPacket)
            STOCCASE(PlayerUpdateDataPacket)
            STOCCASE(PlayerUpdatePacket)
            STOCCASE(MonsterUpdatePacket)
            STOCCASE(MonsterUpdateDataPacket)
            STOCCASE(ItemUpdatePacket)
            STOCCASE(PotalUpdatePacket)
            STOCCASE(WorldMoveOKPacket)
            STOCCASE(ServerChatPacket)
            STOCCASE(ServerPartyPacket)
            STOCCASE(RankPacket)
        case SERVERTOCLIENTTYPE::MAX:
        default:
            break;
        }
        return "ERROR";
    }

public:
    ServerToClientPacketUpdater(char* _Ptr, size_t _Size) : PacketUpdater(_Ptr, _Size)
    {
    }

    virtual ~ServerToClientPacketUpdater() 
    {
    }

};

