#pragma once
#include <GameEngineDebug.h>
#include <GameEngineSerializer.h>
#include "PacketEnum.h"
#include <GEMath.h>

class PacketBase : public GameEngineSerializerObject
{
protected:
    PACKETTYPE PType;
    unsigned int m_Size;

public:
    unsigned int GetSize() 
    {
        return m_Size;
    }

    bool PacketTypeCheck()
    {
        if (PACKETTYPE::ServerToClient > PType
            || PACKETTYPE::MAX <= PType)
        {
            return false;
        }
        return true;
    }

    PACKETTYPE GetPType() 
    {
        return PType;
    }

    virtual bool ContentsTypeCheck() = 0;

    virtual GameEngineSerializer Serialize() = 0
    {
        GameEngineSerializer Ser;
        Ser << PType;
        return Ser;
    }

    virtual void Serialize(GameEngineSerializer& _Ser)  = 0
    {
        _Ser << PType;
    }

    virtual void DeSerialize(GameEngineSerializer& _Ser)  = 0
    {
        _Ser >> PType;
    }


protected:
    PacketBase(PACKETTYPE _PType) : PType(_PType)
    {
    }

    virtual ~PacketBase() 
    {
    }
};



// 서버쪽에서는 Recv만 받을수 있고
// 클라쪽에서는 Send만 받을수 있게 만들어 놓을겁니다.
class ClientToServer : public PacketBase
{
protected:
    CLIENTTOSERVERTYPE CType;

public:
    int GetCType() {
        return (int)CType;
    }

public:
    bool ContentsTypeCheck() override
    {
        if (0 > (int)CType
            || CLIENTTOSERVERTYPE::MAX <= CType)
        {
            return false;
        }
        return true;
    }

    virtual GameEngineSerializer Serialize()
    {
        GameEngineSerializer Ser;
        Ser << PType;
        Ser << CType;
        Ser << m_Size;
        return Ser;
    }

    virtual void Serialize(GameEngineSerializer& _Ser) = 0
    {
        _Ser << PType;
        _Ser << CType;
        _Ser << m_Size;
    }

    virtual void DeSerialize(GameEngineSerializer& _Ser) = 0
    {
        _Ser >> PType;
        _Ser >> CType;
        _Ser >> m_Size;
    }

protected:
    ClientToServer(CLIENTTOSERVERTYPE _CType) : PacketBase(PACKETTYPE::ClientToServer), CType(_CType)
    {
    }

    virtual ~ClientToServer() 
    {
    }
};


class ServerToClient : public PacketBase
{
protected:
    SERVERTOCLIENTTYPE CType;

public:
    int GetCType() {
        return (int)CType;
    }

public:
    bool ContentsTypeCheck() override
    {
        if (0 > (int)CType
            || SERVERTOCLIENTTYPE::MAX <= CType)
        {
            return false;
        }
        return true;
    }

    virtual GameEngineSerializer Serialize()
    {
        GameEngineSerializer Ser;
        Ser << PType;
        Ser << CType;
        Ser << m_Size;
        return Ser;
    }

    virtual void Serialize(GameEngineSerializer& _Ser) = 0
    {
        _Ser << PType;
        _Ser << CType;
        _Ser << m_Size;
    }

    virtual void DeSerialize(GameEngineSerializer& _Ser) = 0
    {
        _Ser >> PType;
        _Ser >> CType;
        _Ser >> m_Size;
    }

protected:
    ServerToClient(SERVERTOCLIENTTYPE _CType) : PacketBase(PACKETTYPE::ServerToClient), CType(_CType)
    {
    }

    virtual ~ServerToClient() 
    {
    }
};

class ActorAnimData : public GameEngineSerializerObject
{
public:
    int m_AnimType;
    int m_AttackType;
    float m_MoveDirAngle;
    bool m_IsMove;
    bool m_AttackEnable;
    bool m_AttackLink;

public:
    ActorAnimData() : m_AnimType(0), m_AttackType(0), m_MoveDirAngle(0.0f),
        m_IsMove(false), m_AttackEnable(false), m_AttackLink(false)
    {
    }

public:
    GameEngineSerializer Serialize()
    {
        GameEngineSerializer Ser;
        Ser << m_AnimType;
        Ser << m_AttackType;
        Ser << m_MoveDirAngle;
        Ser << m_IsMove;
        Ser << m_AttackEnable;
        Ser << m_AttackLink;
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser)
    {
        _Ser << m_AnimType;
        _Ser << m_AttackType;
        _Ser << m_MoveDirAngle;
        _Ser << m_IsMove;
        _Ser << m_AttackEnable;
        _Ser << m_AttackLink;
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        _Ser >> m_AnimType;
        _Ser >> m_AttackType;
        _Ser >> m_MoveDirAngle;
        _Ser >> m_IsMove;
        _Ser >> m_AttackEnable;
        _Ser >> m_AttackLink;
    }
};

class ActorUpdateData : public GameEngineSerializerObject
{
public:
    std::vector<__int64> CreateUpdateID; // 이 명령을 통해서 만들어진 무언가가 있다면 거기에 부여될 id
    int    Count;
    int    SubType;
    float  DeltaTime;
    float  MoveSpeed;
    float  RotSpeed;
    float4 Pos;             // 현재위치
    float4 Scale;           // 현재크기
    float4 Rot;             // 이동하려는 위치
    float4 Dir;             // 이동하려는 위치면서 바라보는 방향
    float4 Right;           // 이동하려는 위치면서 바라보는 방향
    float4 Move;            // 이동하려는 위치면서 바라보는 방향
    float4 AttPos;          // 공격 위치
    bool IsSet;             
    ActorAnimData AnimData;                            

public:
    ActorUpdateData() : Count(0), DeltaTime(0.0f), MoveSpeed(0.0f), RotSpeed(0.0f), IsSet(false)
    {
    }

public:
    void SetOn() 
    {
        IsSet = true;
    }

    void SetData(float4 _Pos, float4 _Rot)
    {
        SetOn();
        Pos = _Pos;
        Rot = _Rot;
    }


public:
    GameEngineSerializer Serialize()
    {
        GameEngineSerializer Ser;
        Ser << CreateUpdateID;
        Ser << Count;
        Ser << SubType;
        Ser << DeltaTime;
        Ser << MoveSpeed;
        Ser << RotSpeed;
        Ser << Pos;
        Ser << Scale;
        Ser << Rot;
        Ser << Dir;
        Ser << Right;
        Ser << Move;
        Ser << AttPos;
        Ser << IsSet;
        AnimData.Serialize();
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser)
    {
        _Ser << CreateUpdateID;
        _Ser << Count;
        _Ser << SubType;
        _Ser << DeltaTime;
        _Ser << MoveSpeed;
        _Ser << RotSpeed;
        _Ser << Pos;
        _Ser << Scale;
        _Ser << Rot;
        _Ser << Dir;
        _Ser << Right;
        _Ser << Move;
        _Ser << AttPos;
        _Ser << IsSet;
        AnimData.Serialize(_Ser);
    }

    void DeSerialize(GameEngineSerializer& _Ser)
    {
        _Ser >> CreateUpdateID;
        _Ser >> Count;
        _Ser >> SubType;
        _Ser >> DeltaTime;
        _Ser >> MoveSpeed;
        _Ser >> RotSpeed;
        _Ser >> Pos;
        _Ser >> Scale;
        _Ser >> Rot;
        _Ser >> Dir;
        _Ser >> Right;
        _Ser >> Move;
        _Ser >> AttPos;
        _Ser >> IsSet;
        AnimData.DeSerialize(_Ser);
    }
};

