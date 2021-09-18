#pragma once
#ifndef UNREALDEFINE
#include "LogicConnecter.h"
#include "ServerToClient.h"
#include "CharacterTable.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class Player;
class ServerConnecter : public LogicConnecter
{
private: // Static Var
public: // Static Func
private: // member Var
    Player* m_Player;

public:
    Player* GetPlayer() 
    {
        return m_Player;
    }

    void SetPlayer(Player* _Player)
    {
        m_Player = _Player;
    }

public:
    void ItemDataReset();

public: // constructer destructer
    ServerConnecter();
    ~ServerConnecter();

public: // delete constructer 
    ServerConnecter(const ServerConnecter& _Other) = delete;
    ServerConnecter(const ServerConnecter&& _Other) = delete;

public: // delete operator
    ServerConnecter& operator=(const ServerConnecter& _Other) = delete;
    ServerConnecter& operator=(const ServerConnecter&& _Other) = delete;

public: // member Func
    int Send(ServerToClient& _Send);
};

#endif