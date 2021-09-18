#pragma once
#include <GameWorldManager.h>
#include <WorldDataParser.h>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class ClientWorld;
class ClientWorldManager : public GameWorldManager
{
private: // Static Var
    static ClientWorldManager* m_Inst;

public: // Static Func
    static ClientWorldManager* Inst() {
        return m_Inst;
    }

public: // constructer destructer
    ClientWorldManager();
    ~ClientWorldManager();

public: // delete constructer 
    ClientWorldManager(const ClientWorldManager& _Other) = delete;
    ClientWorldManager(const ClientWorldManager&& _Other) = delete;

public: // delete operator
    ClientWorldManager& operator=(const ClientWorldManager& _Other) = delete;
    ClientWorldManager& operator=(const ClientWorldManager&& _Other) = delete;

public: // member Func
    std::shared_ptr<ClientWorld> CreateClientWorld(const WorldData& _Data);

    std::shared_ptr<ClientWorld> FindClientWorld(std::string _Name)
    {
        std::shared_ptr<World> fWorld = FindWorld(_Name);

        // �̰� ���� ������ ���������ϴ�.
        return std::dynamic_pointer_cast<ClientWorld, World>(fWorld);
    }
};

