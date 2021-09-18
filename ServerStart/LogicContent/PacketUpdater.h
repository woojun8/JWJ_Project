#pragma once
#include "PacketType.h"
#include "ClientToServer.h"
#include "ServerToClient.h"
#include <functional>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : �� ��Ŷ�� �������� �� ��Ŷ����
//       Ŭ���̾�Ʈ������ ��Ŷ���� �м��ϰ�
//       �׿� �´� ��Ŷ�� �������ִ� 
//       �츮�� �ް� �Ǵ°� char*�� size�ۿ� ����.


// ������ Ŭ�� �����°� 
class PacketUpdater
{
private: // Static Var
public: // Static Func
public: // member Var
    /*GameEngineSocket* m_Socket;*/
    PACKETTYPE PTYPE;
    SERVERTOCLIENTTYPE m_STOCType;
    CLIENTTOSERVERTYPE m_CTOSType;
    unsigned int m_UpdateSize;
    unsigned int m_MaxRecvByteSize;
    // char* Buffer;
    GameEngineSerializer Ser;

public:
    bool IsEnd() {
        return m_MaxRecvByteSize == m_UpdateSize;
    }

public: // constructer destructer
    // ���� �� �����ڿ��� ó���� ��Ŷ �ѹ���
    // �ٷ� ��Ŷ 1����� �̾߱Ⱑ �˴ϴ�.
    PacketUpdater(/*GameEngineSocket* _Socket,*/ char* _Ptr, size_t _Size) : /*m_Socket(_Socket), */Ser(_Ptr, _Size), m_UpdateSize(0), m_MaxRecvByteSize(static_cast<int>(_Size))
    {
    }
    ~PacketUpdater();

public:
    void PacketInit() 
    {
        size_t Offset = m_UpdateSize;
        memcpy_s(&PTYPE, sizeof(PACKETTYPE), &Ser[Offset], sizeof(PACKETTYPE));
        Offset += sizeof(PACKETTYPE);

        switch (PTYPE)
        {
        case PACKETTYPE::ServerToClient:
            memcpy_s(&m_STOCType, sizeof(PACKETTYPE), &Ser[Offset], sizeof(PACKETTYPE));
            Offset += sizeof(PACKETTYPE);
            break;
        case PACKETTYPE::ClientToServer:
            memcpy_s(&m_CTOSType, sizeof(PACKETTYPE), &Ser[Offset], sizeof(PACKETTYPE));
            Offset += sizeof(PACKETTYPE);
            break;
        case PACKETTYPE::ClientAndServer:
        default:
            GameEngineDebug::AssertMsg("default:");
            break;
        }

        int Size = 0;
        memcpy_s(&Size, sizeof(unsigned int), &Ser[Offset], sizeof(unsigned int));
    }

public: // delete constructer 
    PacketUpdater(const PacketUpdater& _Other) = delete;
    PacketUpdater(const PacketUpdater&& _Other) = delete;

public: // delete operator
    PacketUpdater& operator=(const PacketUpdater& _Other) = delete;
    PacketUpdater& operator=(const PacketUpdater&& _Other) = delete;

public: // member Func
};


#define STOCPACKETSTATIC(NAME) static std::function<void(##NAME##&)> ##NAME##Update; \
static const char* ##NAME##Text; 
#define STOCPACKETSTATICVAR(NAME) std::function<void(##NAME##&)> ServerToClientPacketUpdater::##NAME##Update = nullptr; \
const char* ServerToClientPacketUpdater::##NAME##Text = #NAME; 
#define STOCPACKETCALLBACK(NAME) ServerToClientPacketUpdater::##NAME##Update = &ClientPacketFunc::##NAME##Process; 
#define STOCCASE(NAME)   \
        case SERVERTOCLIENTTYPE::##NAME##: \
        { \
            NAME Packet; \
            Packet.DeSerialize(Ser); \
            ##NAME##Update(Packet); \
            m_UpdateSize += Packet.GetSize(); \
            return  NAME##Text; \
        } 



#define CTOSPACKETSTATIC(NAME) static std::function<void(ServerConnecter*, ##NAME##&)> ##NAME##Update; \
static const char* ##NAME##Text;
#define CTOSPACKETSTATICVAR(NAME) std::function<void(ServerConnecter*, ##NAME##&)> ClientToServerPacketUpdater::##NAME##Update = nullptr; \
const char* ClientToServerPacketUpdater::##NAME##Text = #NAME; 
#define CTOSPACKETCALLBACK(NAME) ClientToServerPacketUpdater::##NAME##Update = &ServerPacketFunc::##NAME##Process;

#define CTOSCASE(NAME) \
        case CLIENTTOSERVERTYPE::##NAME##: \
        { \
            NAME Packet; \
            Packet.DeSerialize(Ser); \
            ##NAME##Update(m_ServerConnecter, Packet); \
            m_UpdateSize += Packet.GetSize(); \
            return  NAME##Text; \
        } 
