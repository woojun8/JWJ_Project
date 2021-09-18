#pragma once
#include <functional>
#include <GameEngineMemory.h>
#include <ServerValue.h>
#include "LogicConnecter.h"
#include <unordered_map>
#include <GameEngineDebug.h>

enum class CONNECTSTATE
{
    CONNECTWAIT, // 커넥트를 시도하기 전
    CONNECTERROR, // 커넥트를 시도했지만 실패했다.
    CONNECTOK,
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ClientMonster;
class ClientPlayer;
class GameEngineThread;
class ClientToServer;
class ClientWorld;
class ClientItem;
class ClientConnecter : public LogicConnecter
{
private:
    static ClientConnecter Inst;
    static void ConnectThread();
    static void RecvThread();

public: // Static Func
    static ClientConnecter& GetInst();

public:
    std::shared_ptr<GameEngineThread> m_ConnectThread;
    std::shared_ptr<GameEngineThread> m_RecvServer;
    int IsConnect;
    __int64 ID;

    /// 3000 번 유저가 들어오면
    //       id       거기에 연관된 플레이어
    // 여기에는 나도 들어갑니다.

private:
    std::shared_ptr<ClientWorld> m_World;

    // 메모리를 더 사용하고 해쉬를 이용하기 때문에 탐색은 좀더 빠르다.
    // 그렇게 판단해서 탐색에 가장 유리한 방식을 취하기 취하기 위해서
    // 왜 해쉬가 좀더 빠르죠?
    std::unordered_map<__int64, std::shared_ptr<ClientPlayer>> m_AllPlayer;
    std::unordered_map<__int64, std::shared_ptr<ClientMonster>> m_AllMonster;
    std::unordered_map<__int64, std::shared_ptr<ClientItem>> m_AllItem;

public:
    void RemoveIDItem(__int64 _Id)
    {
        std::unordered_map<__int64, std::shared_ptr<ClientItem>>::iterator IDPlayer = m_AllItem.find(_Id);

        if (m_AllItem.end() == IDPlayer)
        {
            GameEngineDebug::AssertMsg("if (m_AllPlayer.end() == m_AllPlayer.find(_Id))");
            // 이것도 문제가 있기 때문에 
            return;
        }

        m_AllItem.erase(IDPlayer);
    }

    std::shared_ptr<ClientItem> FindIDItem(__int64 _Id)
    {
        // find하면 
        // insert find가 합쳐진거라고 했죠?

        if (m_AllItem.end() == m_AllItem.find(_Id))
        {
            return nullptr;
        }

        // 그냥 이걸 리턴하게 되면
        // insert를 하고 return 을 하기 때문에 
        // m_AllPlayer[_Id] 키가 생겨버린 상태가 됩니다.
        return m_AllItem[_Id];
    }

    void IDItemInsert(__int64 _Id, std::shared_ptr<ClientItem> _Ptr)
    {
        if (m_AllItem.end() != m_AllItem.find(_Id))
        {
            GameEngineDebug::AssertMsg("if (m_AllPlayer.end() != m_AllPlayer.find(_Id))");
        }
        m_AllItem[_Id] = _Ptr;
    }


public:
    void RemoveIDPlayer(__int64 _Id) 
    {
        std::unordered_map<__int64, std::shared_ptr<ClientPlayer>>::iterator IDPlayer = m_AllPlayer.find(_Id);

        if (m_AllPlayer.end() == IDPlayer)
        {
            GameEngineDebug::AssertMsg("if (m_AllPlayer.end() == m_AllPlayer.find(_Id))");
            // 이것도 문제가 있기 때문에 
            return;
        }

        m_AllPlayer.erase(IDPlayer);
    }

    std::shared_ptr<ClientPlayer> FindIDPlayer(__int64 _Id)
    {
        // find하면 
        // insert find가 합쳐진거라고 했죠?

        if (m_AllPlayer.end() ==  m_AllPlayer.find(_Id))
        {
            return nullptr;
        }

        // 그냥 이걸 리턴하게 되면
        // insert를 하고 return 을 하기 때문에 
        // m_AllPlayer[_Id] 키가 생겨버린 상태가 됩니다.
        return m_AllPlayer[_Id];
    }

    void IDPlayerInsert(__int64 _Id, std::shared_ptr<ClientPlayer> _Ptr)
    {
        if (m_AllPlayer.end() != m_AllPlayer.find(_Id))
        {
            GameEngineDebug::AssertMsg("if (m_AllPlayer.end() != m_AllPlayer.find(_Id))");
        }
        m_AllPlayer[_Id] = _Ptr;
    }

public:
    void RemoveIDMonster(__int64 _Id)
    {
        std::unordered_map<__int64, std::shared_ptr<ClientMonster>>::iterator IDMonster = m_AllMonster.find(_Id);

        if (m_AllMonster.end() == IDMonster)
        {
            GameEngineDebug::AssertMsg("if (m_AllMonster.end() == m_AllMonster.find(_Id))");
            // 이것도 문제가 있기 때문에 
            return;
        }

        m_AllMonster.erase(IDMonster);
    }

    std::shared_ptr<ClientMonster> FindIDMonster(__int64 _Id)
    {
        // find하면 
        // insert find가 합쳐진거라고 했죠?

        if (m_AllMonster.end() == m_AllMonster.find(_Id))
        {
            return nullptr;
        }

        // 그냥 이걸 리턴하게 되면
        // insert를 하고 return 을 하기 때문에 
        // m_AllMonster[_Id] 키가 생겨버린 상태가 됩니다.
        return m_AllMonster[_Id];
    }

    void IDMonsterInsert(__int64 _Id, std::shared_ptr<ClientMonster> _Ptr)
    {
        if (m_AllMonster.end() != m_AllMonster.find(_Id))
        {
            GameEngineDebug::AssertMsg("if (m_AllMonster.end() != m_AllMonster.find(_Id))");
        }
        m_AllMonster[_Id] = _Ptr;
    }

public:
    void SetClientWorld(std::shared_ptr<ClientWorld> _World)
    {
        m_World = _World;
    }

    std::shared_ptr<ClientWorld> GetClientWorld()
    {
        return m_World;
    }


public: // constructer destructer
    ClientConnecter();
    ~ClientConnecter();

public: // delete constructer 
    ClientConnecter(const ClientConnecter& _Other) = delete;
    ClientConnecter(const ClientConnecter&& _Other) = delete;

public: // delete operator
    ClientConnecter& operator=(const ClientConnecter& _Other) = delete;
    ClientConnecter& operator=(const ClientConnecter&& _Other) = delete;

public:
    CONNECTSTATE IsConnectState() 
    {
        return (CONNECTSTATE)IsConnect;
    }

public:
    // 무조건 이걸로만 날릴수 있게 한다.
    void Send(ClientToServer& _Data);

    void Destroy();
    

public: // member Func
    // void Connect();
    void ClientStart(int _Port, const char* _Ip = "127.0.0.1", IPTYPE _IPType = IPTYPE::IP4);

};

