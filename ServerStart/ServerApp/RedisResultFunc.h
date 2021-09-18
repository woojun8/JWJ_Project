#pragma once
#include <RedisConnecter.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ServerConnecter;
class RedisResultFunc
{
private: // Static Var
public: // Static Func
public: // member Var
    static void RankResultProcess(RedisResult _Result, ServerConnecter* _Socket, int _Start, int _End);
    static void UserRankResultProcess(RedisResult _Result, ServerConnecter* _Socket);

private: // constructer destructer
    RedisResultFunc() {}
    ~RedisResultFunc() {}
};

