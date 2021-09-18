#pragma once
#include "PacketType.h"
#include <GameEngineString.h>
#include <GameEngineSerializer.h>
#include <GEMath.h>

class RankData : public GameEngineSerializerObject
{
public:
    int Rank;
    GameEngineString Name;
    int Score;
    
public:
    RankData() : Rank(-1), Score(-1)    {    }

public:
    GameEngineSerializer Serialize()
    {
        GameEngineSerializer Ser;
        Ser << Rank;
        Ser << Name;
        Ser << Score;
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser)
    {
        _Ser << Rank;
        _Ser << Name;
        _Ser << Score;

    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        _Ser >> Rank;
        _Ser >> Name;
        _Ser >> Score;
    }
};

class ItemData : public GameEngineSerializerObject
{
public:
    GameEngineString Name;
    int     Type;
    int     InvenOrder;
    int     Count;
    int     IconResData;

public:
    ItemData() : Count(-1), Type(-1), InvenOrder(-1), Name(L""), IconResData(-1)
    {

    }


public:
    GameEngineSerializer Serialize()
    {
        GameEngineSerializer Ser;
        Ser << Name;
        Ser << Type;
        Ser << InvenOrder;
        Ser << Count;
        Ser << IconResData;
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser)
    {
        _Ser << Name;
        _Ser << Type;
        _Ser << InvenOrder;
        _Ser << Count;
        _Ser << IconResData;

    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        _Ser >> Name;
        _Ser >> Type;
        _Ser >> InvenOrder;
        _Ser >> Count;
        _Ser >> IconResData;
    }
};

//
class AccountResultPacket : public ServerToClient
{
    // 내가 이렇게 맴버변수만 선언해도

public:
    int m_Code;

    // 네트워크 자체가 문제가 있다.
    // 더이상 회원가입 못하는 곳이야.
    // 아이디가 겹쳤어.

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << m_Code;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << m_Code;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> m_Code;
    }

public:
    AccountResultPacket() : ServerToClient(SERVERTOCLIENTTYPE::AccountResultPacket), m_Code(-1)
    {
    }

    ~AccountResultPacket()
    {
    }
};

class LoginResultPacket : public ServerToClient
{
    // 내가 이렇게 맴버변수만 선언해도

public:
    int m_Code;

    // 네트워크 자체가 문제가 있다.
    // 더이상 회원가입 못하는 곳이야.
    // 아이디가 겹쳤어.

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << m_Code;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << m_Code;
        // 다집어 넣고
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> m_Code;
    }

public:
    LoginResultPacket() : ServerToClient(SERVERTOCLIENTTYPE::LoginResultPacket), m_Code(-1)
    {
    }

    ~LoginResultPacket()
    {
    }
};



class CharacterPacket : public ServerToClient
{
public:
    __int64 PID;
    __int64 UpdateID;
    GameEngineString NICKNAME;
    GameEngineString EndIndex;
    int LastX;
    int LastY;
    int Att;
    int Hp;
    int MaxHp;
    //GameEngineString CheatServerIp;
    //int Port;

    std::vector<__int64> FriendDatas;
    std::vector<ItemData> ItemDatas;
    // 포탈도 필요하다면 이곳에서 보낸다.

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << PID;
        Ser << UpdateID;
        Ser << NICKNAME;
        Ser << EndIndex;
        Ser << LastX;
        Ser << LastY;
        Ser << Att;
        Ser << Hp;
        Ser << MaxHp;
        Ser << FriendDatas;
        Ser << ItemDatas;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << PID;
        _Ser << UpdateID;
        _Ser << NICKNAME;
        _Ser << EndIndex;
        _Ser << LastX;
        _Ser << LastY;
        _Ser << Att;
        _Ser << Hp;
        _Ser << MaxHp;
        _Ser << FriendDatas;
        _Ser << ItemDatas;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> PID;
        _Ser >> UpdateID;
        _Ser >> NICKNAME;
        _Ser >> EndIndex;
        _Ser >> LastX;
        _Ser >> LastY;
        _Ser >> Att;
        _Ser >> Hp;
        _Ser >> MaxHp;
        _Ser >> FriendDatas;
        _Ser >> ItemDatas;
    }

public:
    CharacterPacket()
        : ServerToClient(SERVERTOCLIENTTYPE::CharacterPacket),
        PID(-1),
        NICKNAME(),
        EndIndex(),
        LastX(0),
        LastY(0),
        Att(0),
        Hp(0),
        MaxHp(0)
    {
    }

    virtual ~CharacterPacket()
    {
    }
};

class GameStartPacket : public ServerToClient
{
    // 내가 이렇게 맴버변수만 선언해도

public:
    int m_Code;
    __int64 ID;

    // 네트워크 자체가 문제가 있다.
    // 더이상 회원가입 못하는 곳이야.
    // 아이디가 겹쳤어.

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << m_Code;
        Ser << ID;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << m_Code;
        _Ser << ID;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> m_Code;
        _Ser >> ID;
    }

public:
    GameStartPacket() : ServerToClient(SERVERTOCLIENTTYPE::GameStartPacket), m_Code(-1), ID(-1)
    {
    }

    virtual ~GameStartPacket()
    {
    }
};


// 이동 공격 방어 회피 전부다 하나로 모아서 보냅니다.
class PlayerUpdateDataPacket : public ServerToClient
{
public:
    __int64 UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
    ActorState m_State; // 코드를 구분할수 있는 값
    int Order; // 어떠한 플레이어에게 붙은 고유의 값.
    ActorUpdateData m_Data;


public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        Ser << m_State; // 코드를 구분할수 있는 값
        Ser << Order; // 어떠한 플레이어에게 붙은 고유의 값.
        Ser << m_Data;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser)
    {
        ServerToClient::Serialize(_Ser);
        _Ser << UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser << m_State; // 코드를 구분할수 있는 값
        _Ser << Order; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser << m_Data;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser >> m_State; // 코드를 구분할수 있는 값
        _Ser >> Order; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser >> m_Data;
    }

public:
    PlayerUpdateDataPacket() : ServerToClient(SERVERTOCLIENTTYPE::PlayerUpdateDataPacket)
    {
    }

    virtual ~PlayerUpdateDataPacket()
    {
    }


};

class PlayerUpdatePacket : public ServerToClient
{
    // 내가 이렇게 맴버변수만 선언해도

public:
    std::vector<PlayerUpdateDataPacket> m_PlayerData;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << m_PlayerData;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << m_PlayerData;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> m_PlayerData;
    }

public:
    PlayerUpdatePacket() : ServerToClient(SERVERTOCLIENTTYPE::PlayerUpdatePacket)
    {
    }

    virtual ~PlayerUpdatePacket()
    {
    }
};

class MonsterUpdateDataPacket : public ServerToClient
{
public:
    __int64 UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
    ActorState m_State; // 코드를 구분할수 있는 값
    int Order; // 어떠한 플레이어에게 붙은 고유의 값.
    ActorUpdateData m_Data;
    

public:
    GameEngineSerializer Serialize()
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        Ser << m_State; // 코드를 구분할수 있는 값
        Ser << Order; // 어떠한 플레이어에게 붙은 고유의 값.
        Ser << m_Data; // 이동을 시작한 위치
        Ser.ChangeToOffset(8);

        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser)
    {
        ServerToClient::Serialize(_Ser);
        _Ser << UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser << m_State; // 코드를 구분할수 있는 값
        _Ser << Order; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser << m_Data; // 이동을 시작한 위치
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser >> m_State; // 코드를 구분할수 있는 값
        _Ser >> Order; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser >> m_Data; // 이동을 시작한 위치
    }

public:
    MonsterUpdateDataPacket() : ServerToClient(SERVERTOCLIENTTYPE::MonsterUpdateDataPacket)
    {
    }

    virtual ~MonsterUpdateDataPacket()
    {
    }

};



class MonsterUpdatePacket : public ServerToClient
{
public:
    std::vector<MonsterUpdateDataPacket> m_MonsterData;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << m_MonsterData;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << m_MonsterData;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> m_MonsterData;
    }

public:
    MonsterUpdatePacket() : ServerToClient(SERVERTOCLIENTTYPE::MonsterUpdatePacket)
    {
    }

    virtual ~MonsterUpdatePacket()
    {
    }
};

class ItemUpdateData : public GameEngineSerializerObject
{
public:
    __int64 UpdateID; // 자기자신의 id
    ActorState m_State; // 코드를 구분할수 있는 값
    GEVector CurPos; // 이동을 시작한 위치
    __int64 EventPlayer; // 이동을 시작한 위치
    ItemData m_Data;

public:
    void Serialize(GameEngineSerializer& _Ser)
    {
        _Ser << UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser << m_State; // 코드를 구분할수 있는 값
        _Ser << CurPos; // 이동을 시작한 위치
        _Ser << EventPlayer; // 이동을 시작한 위치
        m_Data.Serialize(_Ser); // 이동을 시작한 위치
        // 내부에 다시 직렬화를 을 가지고 있는 객체라 직접 시리얼라이즈 해줘야 한다.
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        _Ser >> UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser >> m_State; // 코드를 구분할수 있는 값
        _Ser >> CurPos; // 이동을 시작한 위치
        _Ser >> EventPlayer; // 이동을 시작한 위치
        m_Data.DeSerialize(_Ser);
        // _Ser >> m_Data; // 이동을 시작한 위치
    }

};


class ItemUpdatePacket : public ServerToClient
{
public:
    std::vector<ItemUpdateData> m_ItemUpdateDataList;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << m_ItemUpdateDataList;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << m_ItemUpdateDataList;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> m_ItemUpdateDataList;
    }

public:
    ItemUpdatePacket() : ServerToClient(SERVERTOCLIENTTYPE::ItemUpdatePacket)
    {
    }

    virtual ~ItemUpdatePacket()
    {
    }
};


class RankPacket : public ServerToClient
{
public:
    std::vector<RankData> m_RankDataList;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << m_RankDataList;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << m_RankDataList;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> m_RankDataList;
    }

public:
    RankPacket() : ServerToClient(SERVERTOCLIENTTYPE::RankPacket)
    {
    }

    virtual ~RankPacket()
    {
    }
};


class PotalUpdateData : public GameEngineSerializerObject
{
public:
    __int64 UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
    ActorState m_State; // 코드를 구분할수 있는 값
    GEVector CurPos; // 이동을 시작한 위치

public:
    void Serialize(GameEngineSerializer& _Ser)
    {
        _Ser << UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser << m_State; // 코드를 구분할수 있는 값
        _Ser << CurPos; // 이동을 시작한 위치
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        _Ser >> UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser >> m_State; // 코드를 구분할수 있는 값
        _Ser >> CurPos; // 이동을 시작한 위치
    }

};


class PotalUpdatePacket : public ServerToClient
{
public:
    int WorldSizeX;
    int WorldSizeY;
    std::vector<PotalUpdateData> m_UpdateDataList;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << WorldSizeX;
        Ser << WorldSizeY;
        Ser << m_UpdateDataList;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << WorldSizeX;
        _Ser << WorldSizeY;
        _Ser << m_UpdateDataList;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> WorldSizeX;
        _Ser >> WorldSizeY;
        _Ser >> m_UpdateDataList;
    }

public:
    PotalUpdatePacket() : ServerToClient(SERVERTOCLIENTTYPE::PotalUpdatePacket)
    {
    }

    virtual ~PotalUpdatePacket()
    {
    }
};

class WorldMoveOKPacket : public ServerToClient
{
public:
    int Test;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << Test;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << Test;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> Test;
    }

public:
    WorldMoveOKPacket() : ServerToClient(SERVERTOCLIENTTYPE::WorldMoveOKPacket)
    {
    }

    virtual ~WorldMoveOKPacket()
    {
    }
};

class ServerChatPacket : public ServerToClient
{
public:
    __int64 PID;
    int Type;
    GameEngineString Name;
    GameEngineString Chat;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << PID;
        Ser << Type;
        Ser << Name;
        Ser << Chat;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << PID;
        _Ser << Type;
        _Ser << Name;
        _Ser << Chat;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> PID;
        _Ser >> Type;
        _Ser >> Name;
        _Ser >> Chat;
    }

public:
    ServerChatPacket() : ServerToClient(SERVERTOCLIENTTYPE::ServerChatPacket)
    {
    }
};

class ServerPartyPacket : public ServerToClient
{
public:
    PARTYPACKETTYPE Type;
    std::vector<__int64> PID;
    std::vector<GameEngineString> Name;
    std::vector<__int64> Connect;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << Type;
        Ser << PID;
        Ser << Name;
        Ser << Connect;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::Serialize(_Ser);
        _Ser << Type;
        _Ser << PID;
        _Ser << Name;
        _Ser << Connect;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> Type;
        _Ser >> PID;
        _Ser >> Name;
        _Ser >> Connect;
    }

public:
    ServerPartyPacket() : ServerToClient(SERVERTOCLIENTTYPE::ServerPartyPacket)
    {
    }
};