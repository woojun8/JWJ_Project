#pragma once
#include <GameWorldManager.h>
#include <WorldDataParser.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
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

