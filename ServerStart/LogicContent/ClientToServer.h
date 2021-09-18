#pragma once
#include "PacketType.h"
#include <GEMath.h>


// ���⼭ ����� �༮���� ���δ� 
class LoginPacket : public ClientToServer
{
public:
    GameEngineString ID;
    GameEngineString PASS;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << ID;
        Ser << PASS;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override 
    {
        ClientToServer::Serialize(_Ser);
        _Ser << ID;
        _Ser << PASS;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> ID;
        _Ser >> PASS;
    }

public:
    LoginPacket() : ClientToServer(CLIENTTOSERVERTYPE::LoginPacket)
    {
    }

    virtual ~LoginPacket() 
    {
    }
};


class AccountPacket : public ClientToServer
{
    // ���� �̷��� �ɹ������� �����ص�

public:
    GameEngineString ID;
    GameEngineString PASS;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << ID;
        Ser << PASS;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << ID;
        _Ser << PASS;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> ID;
        _Ser >> PASS;
    }

public:
    AccountPacket() : ClientToServer(CLIENTTOSERVERTYPE::AccountPacket)
    {
    }

    ~AccountPacket()
    {
    }
};


class ClientReadyPacket : public ClientToServer
{
    // ���� �̷��� �ɹ������� �����ص�

public:
    int m_Code;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << m_Code;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << m_Code;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> m_Code;
    }

public:
    ClientReadyPacket() : ClientToServer(CLIENTTOSERVERTYPE::ClientReadyPacket)
    {
    }

    ~ClientReadyPacket()
    {
    }
};

class ClientPlayerPacket : public ClientToServer
{
public:
    __int64 UpdateID; // ��� �÷��̾�� ���� ������ ��.
    ActorState m_State; // �ڵ带 �����Ҽ� �ִ� ��
    int Order; // ��� �÷��̾�� ���� ������ ��.
    ActorUpdateData ActorData;
  
public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << UpdateID; // ��� �÷��̾�� ���� ������ ��.
        Ser << m_State; // �ڵ带 �����Ҽ� �ִ� ��
        Ser << Order; // ��� �÷��̾�� ���� ������ ��.
        ActorData.Serialize(Ser);
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser << m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser << Order; // ��� �÷��̾�� ���� ������ ��.
        ActorData.Serialize(_Ser);
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> UpdateID; // ��� �÷��̾�� ���� ������ ��.
        _Ser >> m_State; // �ڵ带 �����Ҽ� �ִ� ��
        _Ser >> Order; // ��� �÷��̾�� ���� ������ ��.
        ActorData.DeSerialize(_Ser);
    }

public:
    ClientPlayerPacket() : ClientToServer(CLIENTTOSERVERTYPE::ClientPlayerPacket)
    {
    }

    virtual ~ClientPlayerPacket()
    {
    }
};


class GetRankPacket : public ClientToServer
{
public:
    // 0 TopRank;
    // 1 UserRank;
    int Type;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << Type;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << Type;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> Type;
    }

public:
    GetRankPacket() : ClientToServer(CLIENTTOSERVERTYPE::GetRankPacket)
    {
    }

};

class ClientChatPacket : public ClientToServer
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
        ClientToServer::Serialize(Ser);
        Ser << PID;
        Ser << Type;
        Ser << Name;
        Ser << Chat;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << PID;
        _Ser << Type;
        _Ser << Name;
        _Ser << Chat;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> PID;
        _Ser >> Type;
        _Ser >> Name;
        _Ser >> Chat;
    }

public:
    ClientChatPacket() : ClientToServer(CLIENTTOSERVERTYPE::ClientChatPacket)
    {
    }
};

class ClientPartyPacket : public ClientToServer
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
        ClientToServer::Serialize(Ser);
        Ser << Type;
        Ser << PID;
        Ser << Name;
        Ser << Connect;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << Type;
        _Ser << PID;
        _Ser << Name;
        _Ser << Connect;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> Type;
        _Ser >> PID;
        _Ser >> Name;
        _Ser >> Connect;
    }

public:
    ClientPartyPacket() : ClientToServer(CLIENTTOSERVERTYPE::ClientPartyPacket)
    {
    }
};
