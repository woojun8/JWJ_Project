#pragma once
#include <GameEngineThread.h>
#include "ServerWorldManager.h"

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class LogicThread : public GameEngineThread
{
private: // Static Var
public: // Static Func
private: // member Var
    static ServerWorldManager WorldManager;

public:
    static ServerWorldManager& GetWorldManager() 
    {
        return WorldManager;
    }


public:
    template<typename FuncPtrType, typename ... Rest>
    static void InsertMessage(std::string _WorldKey, FuncPtrType _Func, Rest&& ... _Arg)
    {
        std::shared_ptr<World> FindWorld = WorldManager.FindWorld(_WorldKey);

        if (nullptr == FindWorld)
        {
            GameEngineDebug::AssertMsg("if (nullptr == FindWorld)");
        }

        FindWorld->MsgInsert(_Func, _Arg...);
    }

    template<typename FuncPtrType, typename ... Rest>
    static void InsertMessage(std::shared_ptr<World> _World, FuncPtrType _Func, Rest&& ... _Arg)
    {
        if (nullptr == _World)
        {
            GameEngineDebug::AssertMsg("if (nullptr == FindWorld)");
        }

        _World->MsgInsert(_Func, _Arg...);
    }

public: // constructer destructer
    LogicThread();
    ~LogicThread();

public: // delete constructer 
    LogicThread(const LogicThread& _Other) = delete;
    LogicThread(const LogicThread&& _Other) = delete;

public: // delete operator
    LogicThread& operator=(const LogicThread& _Other) = delete;
    LogicThread& operator=(const LogicThread&& _Other) = delete;

public: // member Func
    void ThreadUpdate() override;
};

