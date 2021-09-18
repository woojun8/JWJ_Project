#pragma once
#include "GameEngineSocket.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class TcpAccepter;
class TcpConnecter : public GameEngineSocket
{
    friend TcpAccepter;

private: // Static Var
public: // Static Func
private: // member Var
    TcpAccepter* m_ListenSocket;

private:
    void SetListenSocket(TcpAccepter* _ListenSocket) 
    {
        m_ListenSocket = _ListenSocket;
    }

public: // constructer destructer
    TcpConnecter();
public:
    ~TcpConnecter();

public: // delete constructer 
    TcpConnecter(const TcpConnecter& _Other) = delete;
    TcpConnecter(const TcpConnecter&& _Other) = delete;

public: // delete operator
    TcpConnecter& operator=(const TcpConnecter& _Other) = delete;
    TcpConnecter& operator=(const TcpConnecter&& _Other) = delete;

public: // member Func
    int Connect();
    void DisConnect();

    BOOL AcceptExConnecter();

private:
    void AcceptCreate(SOCKET _ConnectSocket, const GameEngineSocketAddress& _Value);
};

