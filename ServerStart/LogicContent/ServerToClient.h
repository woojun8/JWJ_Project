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
    // ���� �̷��� �ɹ������� �����ص�

public:
    int m_Code;

    // ��Ʈ��ũ ��ü�� ������ �ִ�.
    // ���̻� ȸ������ ���ϴ� ���̾�.
    // ���̵� ���ƾ�.

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
    // ���� �̷��� �ɹ������� �����ص�

public:
    int m_Code;

    // ��Ʈ��ũ ��ü�� ������ �ִ�.
    // ���̻� ȸ������ ���ϴ� ���̾�.
    // ���̵� ���ƾ�.

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
        // ������ �ְ�
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
    // ��Ż�� �ʿ��ϴٸ� �̰����� ������.

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
    // ���� �̷��� �ɹ������� �����ص�

public:
    int m_Code;
    __int64 ID;

    // ��Ʈ��ũ ��ü�� ������ �ִ�.
    // ���̻� ȸ������ ���ϴ� ���̾�.
    // ���̵� ���ƾ�.

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


// �̵� ���� ��� ȸ�� ���δ� �ϳ��� ��Ƽ� �����ϴ�.
class PlayerUpdateDataPacket : public ServerToClient
{
public:
    __int64 UpdateID; // ��� �÷��̾�� ���� ������ ��.
    ActorState m_State; // �ڵ带 �����Ҽ� �ִ� ��
    int Order; // ��� �÷��̾�� ���� ������ ��.
    ActorUpdateData m_Data;


public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << UpdateID; // ��� �÷��̾�� ���� ������ ��.
        Ser << m_State; // �ڵ带 �����Ҽ� �ִ� ��
        Ser << Order; // ��� �÷��̾�� ���� ������ ��.
        Ser << m_Data;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser)
    {
        ServerToClient::Serialize(_Ser);
        _Ser << UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser << m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser << Order; // ��� �÷��̾�� ���� ������ ��.
        _Ser << m_Data;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser >> m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser >> Order; // ��� �÷��̾�� ���� ������ ��.
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
    // ���� �̷��� �ɹ������� �����ص�

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
    __int64 UpdateID; // ��� �÷��̾�� ���� ������ ��.
    ActorState m_State; // �ڵ带 �����Ҽ� �ִ� ��
    int Order; // ��� �÷��̾�� ���� ������ ��.
    ActorUpdateData m_Data;
    

public:
    GameEngineSerializer Serialize()
    {
        GameEngineSerializer Ser;
        ServerToClient::Serialize(Ser);
        Ser << UpdateID; // ��� �÷��̾�� ���� ������ ��.
        Ser << m_State; // �ڵ带 �����Ҽ� �ִ� ��
        Ser << Order; // ��� �÷��̾�� ���� ������ ��.
        Ser << m_Data; // �̵��� ������ ��ġ
        Ser.ChangeToOffset(8);

        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser)
    {
        ServerToClient::Serialize(_Ser);
        _Ser << UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser << m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser << Order; // ��� �÷��̾�� ���� ������ ��.
        _Ser << m_Data; // �̵��� ������ ��ġ
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        ServerToClient::DeSerialize(_Ser);
        _Ser >> UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser >> m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser >> Order; // ��� �÷��̾�� ���� ������ ��.
        _Ser >> m_Data; // �̵��� ������ ��ġ
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
    __int64 UpdateID; // �ڱ��ڽ��� id
    ActorState m_State; // �ڵ带 �����Ҽ� �ִ� ��
    GEVector CurPos; // �̵��� ������ ��ġ
    __int64 EventPlayer; // �̵��� ������ ��ġ
    ItemData m_Data;

public:
    void Serialize(GameEngineSerializer& _Ser)
    {
        _Ser << UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser << m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser << CurPos; // �̵��� ������ ��ġ
        _Ser << EventPlayer; // �̵��� ������ ��ġ
        m_Data.Serialize(_Ser); // �̵��� ������ ��ġ
        // ���ο� �ٽ� ����ȭ�� �� ������ �ִ� ��ü�� ���� �ø�������� ����� �Ѵ�.
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        _Ser >> UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser >> m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser >> CurPos; // �̵��� ������ ��ġ
        _Ser >> EventPlayer; // �̵��� ������ ��ġ
        m_Data.DeSerialize(_Ser);
        // _Ser >> m_Data; // �̵��� ������ ��ġ
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
    __int64 UpdateID; // ��� �÷��̾�� ���� ������ ��.
    ActorState m_State; // �ڵ带 �����Ҽ� �ִ� ��
    GEVector CurPos; // �̵��� ������ ��ġ

public:
    void Serialize(GameEngineSerializer& _Ser)
    {
        _Ser << UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser << m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser << CurPos; // �̵��� ������ ��ġ
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        _Ser >> UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser >> m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser >> CurPos; // �̵��� ������ ��ġ
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