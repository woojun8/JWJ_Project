#pragma once
#include <functional>
#include <GameEngineMemory.h>
#include <ServerValue.h>
#include "LogicConnecter.h"
#include <unordered_map>
#include <GameEngineDebug.h>

enum class CONNECTSTATE
{
    CONNECTWAIT, // Ŀ��Ʈ�� �õ��ϱ� ��
    CONNECTERROR, // Ŀ��Ʈ�� �õ������� �����ߴ�.
    CONNECTOK,
};

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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

    /// 3000 �� ������ ������
    //       id       �ű⿡ ������ �÷��̾�
    // ���⿡�� ���� ���ϴ�.

private:
    std::shared_ptr<ClientWorld> m_World;

    // �޸𸮸� �� ����ϰ� �ؽ��� �̿��ϱ� ������ Ž���� ���� ������.
    // �׷��� �Ǵ��ؼ� Ž���� ���� ������ ����� ���ϱ� ���ϱ� ���ؼ�
    // �� �ؽ��� ���� ������?
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
            // �̰͵� ������ �ֱ� ������ 
            return;
        }

        m_AllItem.erase(IDPlayer);
    }

    std::shared_ptr<ClientItem> FindIDItem(__int64 _Id)
    {
        // find�ϸ� 
        // insert find�� �������Ŷ�� ����?

        if (m_AllItem.end() == m_AllItem.find(_Id))
        {
            return nullptr;
        }

        // �׳� �̰� �����ϰ� �Ǹ�
        // insert�� �ϰ� return �� �ϱ� ������ 
        // m_AllPlayer[_Id] Ű�� ���ܹ��� ���°� �˴ϴ�.
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
            // �̰͵� ������ �ֱ� ������ 
            return;
        }

        m_AllPlayer.erase(IDPlayer);
    }

    std::shared_ptr<ClientPlayer> FindIDPlayer(__int64 _Id)
    {
        // find�ϸ� 
        // insert find�� �������Ŷ�� ����?

        if (m_AllPlayer.end() ==  m_AllPlayer.find(_Id))
        {
            return nullptr;
        }

        // �׳� �̰� �����ϰ� �Ǹ�
        // insert�� �ϰ� return �� �ϱ� ������ 
        // m_AllPlayer[_Id] Ű�� ���ܹ��� ���°� �˴ϴ�.
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
            // �̰͵� ������ �ֱ� ������ 
            return;
        }

        m_AllMonster.erase(IDMonster);
    }

    std::shared_ptr<ClientMonster> FindIDMonster(__int64 _Id)
    {
        // find�ϸ� 
        // insert find�� �������Ŷ�� ����?

        if (m_AllMonster.end() == m_AllMonster.find(_Id))
        {
            return nullptr;
        }

        // �׳� �̰� �����ϰ� �Ǹ�
        // insert�� �ϰ� return �� �ϱ� ������ 
        // m_AllMonster[_Id] Ű�� ���ܹ��� ���°� �˴ϴ�.
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
    // ������ �̰ɷθ� ������ �ְ� �Ѵ�.
    void Send(ClientToServer& _Data);

    void Destroy();
    

public: // member Func
    // void Connect();
    void ClientStart(int _Port, const char* _Ip = "127.0.0.1", IPTYPE _IPType = IPTYPE::IP4);

};

