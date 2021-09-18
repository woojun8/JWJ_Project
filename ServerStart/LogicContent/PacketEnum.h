#pragma once

enum class PACKETTYPE : int
{
    ServerToClient,
    ClientToServer,
    ClientAndServer,
    MAX
};


enum class CLIENTTOSERVERTYPE : int
{
    LoginPacket, // �α���
    AccountPacket, // ȸ������
    ClientReadyPacket,
    ClientPlayerPacket, // �� �ڽ��� ������Ʈ �ش޶�� ��Ŷ
    GetRankPacket, // ��ŷ�� �����޶�� ��Ŷ
    ClientChatPacket, 
    ClientPartyPacket,
    MAX,
};


enum class SERVERTOCLIENTTYPE : int
{
    AccountResultPacket,
    LoginResultPacket,
    CharacterPacket,
    PlayerUpdateDataPacket, // �ٸ� �����鿡�� ���� ��Ŷ
    PlayerUpdatePacket, // �ٸ� �����鿡�� ���� ��Ŷ
    GameStartPacket,
    MonsterUpdateDataPacket, // ���͸� ������ ������Ʈ�ϰ� �����.
    MonsterUpdatePacket, // ���͸� ������ ������Ʈ�ϰ� �����.
    ItemUpdatePacket, // 
    PotalUpdatePacket, // 
    WorldMoveOKPacket, // 
    RankPacket, // 
    ServerChatPacket,
    ServerPartyPacket,
    MAX,
};

enum class PARTYPACKETTYPE : int
{
    Init,
    Invite,
    Accept,
    Refuse,
    MAX
};

enum class ActorState : int
{
    Wait,
    in,
    Update,
    Att, // ������Ʈ�� ���ÿ� ó���ȴ�.
    Death,
    WorldMove,
};