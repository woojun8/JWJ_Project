#pragma once
#include <RedisConnecter.h>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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

