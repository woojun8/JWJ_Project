#pragma once


#include <WinSock2.h>// ���� ������ �Լ��������ϴ� �༮.
#include <MSWSock.h> // ����ũ�μ���Ʈ���� ���� �������ִ� ���� �Լ� ���
#include <WS2tcpip.h> // tcp/ip �����Լ�

// int ������ �ɼ� �ִٰ� �����ϰ�.
// void Func(int _Value) ���� �ʿ���.

// void Func(const int& _Value) ���� �ʿ��ѵ� ����ȭ�� �� �Լ�


// �Ʒ��� ���� �Լ��� ����ϸ� �����ϰ� �Ǵ� 
// void Func(int*,& _Value) ���� �ٲ�� �ִ� �Լ�
// int Value = 3000;
// ������ �ٲ� ���ðǵ�.
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
        // �� �ڽ��� pointer this��
        // ���� �޸� �������� ����Ű��?
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
