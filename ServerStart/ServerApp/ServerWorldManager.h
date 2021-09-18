#pragma once
#include <GameWorldManager.h>
#include <WorldDataParser.h>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class ServerWorld;
class ServerWorldManager : public GameWorldManager
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    ServerWorldManager();
    ~ServerWorldManager();

public: // delete constructer 
    ServerWorldManager(const ServerWorldManager& _Other) = delete;
    ServerWorldManager(const ServerWorldManager&& _Other) = delete;

public: // delete operator
    ServerWorldManager& operator=(const ServerWorldManager& _Other) = delete;
    ServerWorldManager& operator=(const ServerWorldManager&& _Other) = delete;

public: // member Func
    std::shared_ptr<ServerWorld> CreateServerWorld(const WorldData& _Data);
};

