#pragma once
#include "EngineOver.h"
#include "ServerValue.h"
#include <memory>
#include <map>



// �����͸��� ���� Ŭ������ ���ο� ���� �ɹ������鸸 ����ִ� Ŭ����
// 

// �������� �̿��� Ŭ������ �����ؼ� �����ؾ� �մϴ�.
// ������
// => ���� ���� Ȥ�� ���̳ʸ��� ��ä�� �̿��� ������ �ؼ��� �ȵȴ�.
//    ������ Save()�� serialize(����ȭ �Լ��� �������� �մϴ�.)


// �����Լ��� �̷��� ����� ����� �ȵȴ�.
class GameEngineSocketAddress 
{
public:

    union 
    {
        SOCKADDR_IN UserAddIP4; // ipv4
        SOCKADDR_IN6 UserAddIP6; // ipv4
    };

public:
    GameEngineSocketAddress() : UserAddIP6{0}
    {

    }
};

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class GameEngineSocket : std::enable_shared_from_this<GameEngineSocket>
{
private: // Static Var
public: // Static Func
    // �̳༮�� �� ���������� �Ǿ������
    // CharacterData

private:
    static void SocketErrorInit();

private: // member Var
    SOCKET m_Socket;
    SOCKETTYPE m_SocketType;
    SOCKETSYNCTYPE m_SyncType;
    GameEngineSocketAddress m_Address;


    EngineOVERLAPPED  AcceptOver;
    EngineOVERLAPPED  RecvOver;
    EngineOVERLAPPED  SendOver;
    EngineOVERLAPPED  DisconnectOver;
    EngineOVERLAPPED  RealDisconnectOver;

    ConnectionBuffer RecvBuffer;

public:
    ConnectionBuffer& GetRecvBuffer() {
        return RecvBuffer;
    }

    const char* GetRecvRealBuffer() {
        return &RecvBuffer.RealBuffer[0];
    }


    EngineOVERLAPPED& GetAcceptOverRef() {
        return AcceptOver;
    }
    EngineOVERLAPPED& GetRecvOverRef() {
        return RecvOver;
    }
    EngineOVERLAPPED& GetSendOverRef() {
        return SendOver;
    }
    EngineOVERLAPPED& GetDisconnectOverRef() {
        return DisconnectOver;
    }
    
private:
    void OverInit();


public:
    GameEngineSocketAddress& GetAddressRef() {
        return m_Address;
    }

public:
    SOCKET GetSocket() const
    {
        return m_Socket;
    }

public: // constructer destructer
    GameEngineSocket(SOCKETTYPE _Type);
    // �Ҹ��� virtual�� ���� ������ ����� �ϴ� �Ŵϱ�.
    virtual ~GameEngineSocket();

public: // delete constructer 
    GameEngineSocket(const GameEngineSocket& _Other) = delete;
    GameEngineSocket(const GameEngineSocket&& _Other) = delete;

public: // delete operator
    GameEngineSocket& operator=(const GameEngineSocket& _Other) = delete;
    GameEngineSocket& operator=(const GameEngineSocket&& _Other) = delete;

public: // member Func
    void Reset();

    // �񵿱� ���Ʈ ������ ����� ���
    void CreateASyncAccpet();
    // ���� ���Ʈ ������ ����� ���
    void CreateSyncAccpet();
    // �񵿱� Ŀ�ؼ� ������ ����� ���
    void CreateASyncConnection();
    // ���� Ŀ�ؼ� ������ ����� ���
    void CreateSyncConnection();
    // void ASyncCreate(const char* _Ip, int _Port, IPTYPE _IPType = IPTYPE::IP4);
    void AddressSetting(const char* _Ip, int _Port, IPTYPE _IPType = IPTYPE::IP4);

public:
    SOCKETSYNCTYPE GetSyncType()
    {
        return m_SyncType;
    }

protected:

    void SetSocket(const SOCKET& _Socket) 
    {
        m_Socket = _Socket;
    }
    void SetAddress(const GameEngineSocketAddress& _Socket)
    {
        m_Address = _Socket;
    }

    int Connect();

public:
    void SocketError();

protected:
    void Bind();

public:
    void AsyncRecv();


    int SyncRecv();

    template<typename DataType>
    int SyncSend(DataType& _Data)
    {
        return SyncSend(reinterpret_cast<char*>(&_Data), sizeof(DataType));
    }

    int SyncSend(const char* DataPtr, int Len);

    int ConstSyncSend(const char* DataPtr, int Len) const;

    void Close();

    // �ݴ¹������ 2������ �ִٰ� �����ϼ���
    // ������ ������ �ʰ� ���Ḹ �����ϰ�
    // ����ϰ� �ٽ� ����ϴ� ���
    void RealDisconnect();

    void ReCreateASyncConnection();

public:
    // �����Լ���.
    virtual void DisConnectTask() {}

    // �ٷ� �ݰ� 
    // �� ������ ���� �ٽ� ������� �ʴ´ٰ� �ϰ�


};

