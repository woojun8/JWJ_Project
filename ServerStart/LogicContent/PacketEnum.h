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
    LoginPacket, // 로그인
    AccountPacket, // 회원가입
    ClientReadyPacket,
    ClientPlayerPacket, // 나 자신을 업데이트 해달라는 패킷
    GetRankPacket, // 랭킹좀 보내달라는 패킷
    ClientChatPacket, 
    ClientPartyPacket,
    MAX,
};


enum class SERVERTOCLIENTTYPE : int
{
    AccountResultPacket,
    LoginResultPacket,
    CharacterPacket,
    PlayerUpdateDataPacket, // 다른 유저들에게 보낼 패킷
    PlayerUpdatePacket, // 다른 유저들에게 보낼 패킷
    GameStartPacket,
    MonsterUpdateDataPacket, // 몬스터를 보내서 업데이트하게 만든다.
    MonsterUpdatePacket, // 몬스터를 보내서 업데이트하게 만든다.
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
    Att, // 업데이트와 동시에 처리된다.
    Death,
    WorldMove,
};