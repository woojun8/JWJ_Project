#pragma once
#include <memory>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class GameEngineMemory
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    GameEngineMemory();
    ~GameEngineMemory();

public: // delete constructer 
    GameEngineMemory(const GameEngineMemory& _Other) = delete;
    GameEngineMemory(const GameEngineMemory&& _Other) = delete;

public: // delete operator
    GameEngineMemory& operator=(const GameEngineMemory& _Other) = delete;
    GameEngineMemory& operator=(const GameEngineMemory&& _Other) = delete;

public: // member Func
};

