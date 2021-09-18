#pragma once


#include <WinSock2.h>// 새로 개선된 함수가존재하는 녀석.
#include <MSWSock.h> // 마이크로소프트에서 따로 지원해주는 소켓 함수 헤더
#include <WS2tcpip.h> // tcp/ip 지원함수

// int 뭐든지 될수 있다고 생각하고.
// void Func(int _Value) 값만 필요함.

// void Func(const int& _Value) 값만 필요한데 최적화는 된 함수


// 아래와 같은 함수를 사용하면 착각하게 되는 
// void Func(int*,& _Value) 값이 바뀔수 있는 함수
// int Value = 3000;
// 어차피 바뀌어서 나올건데.
// Func(Value);

enum class BUFFERSIZE
{
    Size_1K = 1024,
    Size_2K = 1024 * 2,
    Size_4K = 1024 * 4,
    Size_8K = 1024 * 8,
};

enum class EngineSocketEvent
{
    ACCPET,
    RECV,
    SEND,
    DISCONNECT,
    REALDISCONNECT,

    NONE
};

class GameEngineSocket;
class EngineOVERLAPPED : public OVERLAPPED
{
public:
    EngineSocketEvent Type;
    GameEngineSocket* m_ParentSocket;
    void* m_Data;

public:
    void Clear() 
    {
        // 나 자신의 pointer this는
        // 나의 메모리 시작점을 가리키죠?
        memset(this, 0, sizeof(OVERLAPPED));
    }

public:
    EngineOVERLAPPED() : OVERLAPPED({ 0 }), Type(EngineSocketEvent::NONE), m_ParentSocket(nullptr), m_Data(nullptr) {}
    ~EngineOVERLAPPED() {}
};

class ConnectionBuffer 
{
public:
    WSABUF WsaBuffer;
    char RealBuffer[(int)BUFFERSIZE::Size_1K];
    DWORD Byte;
    DWORD Flag;

public:
    void Clear() 
    {
        memset(RealBuffer, 0, (int)BUFFERSIZE::Size_1K);
        Byte = 0;
        WsaBuffer.buf = RealBuffer;
        WsaBuffer.len = sizeof(RealBuffer);
    }

//public:
//    operator WSABUF* () {
//        return &WsaBuffer;
//    }

public:
    ConnectionBuffer() : WsaBuffer{0,}, RealBuffer{ 0, }, Byte(0), Flag(0)
    {
        WsaBuffer.buf = RealBuffer;
        WsaBuffer.len = sizeof(RealBuffer);
    }
    ~ConnectionBuffer() 
    {
    }
};
