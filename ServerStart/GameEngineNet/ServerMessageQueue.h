#pragma once
#include <vector>
#include <functional>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerMessageQueue
{
private: // Static Var
public: // Static Func
private: // member Var
    int Offset;

    // std::vector<std::function<>>


public: // constructer destructer
    ServerMessageQueue();
    ~ServerMessageQueue();

public: // delete constructer 
    ServerMessageQueue(const ServerMessageQueue& _Other) = delete;
    ServerMessageQueue(const ServerMessageQueue&& _Other) = delete;

public: // delete operator
    ServerMessageQueue& operator=(const ServerMessageQueue& _Other) = delete;
    ServerMessageQueue& operator=(const ServerMessageQueue&& _Other) = delete;

public: // member Func
};

