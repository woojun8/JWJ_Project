#pragma once

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class GameEngineDebug
{
private: // Static Var
public: // Static Func
    static void AssertMsg(const char* _Msg);
    static void LeckCheck();

private: // member Var

public: // constructer destructer
    GameEngineDebug();
    ~GameEngineDebug();

public: // delete constructer 
    GameEngineDebug(const GameEngineDebug& _Other) = delete;
    GameEngineDebug(const GameEngineDebug&& _Other) = delete;

public: // delete operator
    GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
    GameEngineDebug& operator=(const GameEngineDebug&& _Other) = delete;

public: // member Func
};

