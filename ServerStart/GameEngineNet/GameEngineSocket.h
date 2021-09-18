#pragma once
#include "EngineOver.h"
#include "ServerValue.h"
#include <memory>
#include <map>



// 데이터만을 위한 클래스와 내부에 값형 맴버변수들만 들어있는 클래스
// 

// 다형성을 이용할 클래스는 구분해서 생각해야 합니다.
// 포인터
// => 보통 저장 혹은 바이너리로 통채로 이용할 생각을 해서는 안된다.
//    무조건 Save()나 serialize(정규화 함수를 만들어줘야 합니다.)


// 가상함수나 이런거 만들면 절대로 안된다.
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

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class GameEngineSocket : std::enable_shared_from_this<GameEngineSocket>
{
private: // Static Var
public: // Static Func
    // 이녀석은 그 게임전용이 되어버려요
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
    // 소멸자 virtual은 거의 무조건 해줘야 하는 거니까.
    virtual ~GameEngineSocket();

public: // delete constructer 
    GameEngineSocket(const GameEngineSocket& _Other) = delete;
    GameEngineSocket(const GameEngineSocket&& _Other) = delete;

public: // delete operator
    GameEngineSocket& operator=(const GameEngineSocket& _Other) = delete;
    GameEngineSocket& operator=(const GameEngineSocket&& _Other) = delete;

public: // member Func
    void Reset();

    // 비동기 억셉트 소켓을 만드는 경우
    void CreateASyncAccpet();
    // 동기 억셉트 소켓을 만드는 경우
    void CreateSyncAccpet();
    // 비동기 커넥션 소켓을 만드는 경우
    void CreateASyncConnection();
    // 동기 커넥션 소켓을 만드는 경우
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

    // 닫는방법에는 2가지가 있다고 생각하세요
    // 소켓을 지우지 않고 연결만 해제하고
    // 깔끔하게 다시 사용하는 방법
    void RealDisconnect();

    void ReCreateASyncConnection();

public:
    // 가상함수들.
    virtual void DisConnectTask() {}

    // 바로 닫고 
    // 그 소켓을 이제 다시 사용하지 않는다고 하고


};

