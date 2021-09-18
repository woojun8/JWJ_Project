#pragma once
#include <GameWorldManager.h>
#include <WorldDataParser.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
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

        // 이걸 쓰면 없으면 만들어버립니다.
        return std::dynamic_pointer_cast<ClientWorld, World>(fWorld);
    }
};

