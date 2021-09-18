// ServerApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#include "GameEngineServer.h"
#include <GameEngineString.h>
#include <GameEngineDirectory.h>
#include <GameEngineFile.h>
#include <WorldDataParser.h>
#include "ServerWorldManager.h"
#include <GameEngineTime.h>
#include "AccpetThread.h"
#include "LogicThread.h"
#include <GameEngineSerializer.h>
#include <PacketType.h>
#include <GameEngineSerializer.h>
#include <LogManager.h>

#pragma comment(lib, "GameEngineBase")
#pragma comment(lib, "GameEngineNet")
#pragma comment(lib, "GameEngineObject")
#pragma comment(lib, "LogicContent")

#include <iostream>
#include <GameEngineThread.h>
#include <GameWorldManager.h>
#include <ClientToServer.h>
#include <PacketUpdater.h>
#include <LogicValue.h>
#include "ServerPacketFunc.h"
#include <DBConnecter.h>
#include <AccountTable.h>
#include <DBManager.h>
#include <RedisConnecter.h>
#include "ServerAppEvent.h"
#include <GameEngineCollision.h>
#include <KDTREE.h>
#include <GameEngineRandom.h>

//void TestFunc(RedisResult _Result) 
//{
//    int a = 0;
//}

int main()
{
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //std::vector<GameObject*> m_ObjectVector;
    //std::vector<float4> m_PosVector;

    //for (size_t i = 0; i < 100; i++)
    //{
    //    m_PosVector.push_back({ GameEngineRandom::GetRandomFloat(-1000, 1000), GameEngineRandom::GetRandomFloat(-1000, 1000) });
    //    // m_PosVector.push_back({150.0f + i, 100.0f });
    //}
    //KDTree Tree = &m_PosVector;
    //std::vector<int> Result = Tree.RadiusSearch({100, 100}, 200);
    //return 0;

    // redis-server --service-install redisStart.conf --service-name redisStart

    // redis-server --service-install redis.windows.conf --service-name redisStart
    // redis-server --service-uninstall --service-name redisStart
    // 레디스 설치 port를 잘 기억해 놔야 합니다.
    // redis.windows.conf파일을 종류별로 여러개 만들어 놓는 경우가 많습니다.

    // 일반적인 DB는 멀티쓰레드로 커넥션을 N개를 만드는 것이 이득일수 있다.
    // 그냥 단순히 커넥터를 많이 만드는건 별로 의미가 없다고 했지만
    // 용도에 의한 의미가 있기는 있어요.
    //RedisConnecter Con;
    //Con.Connect("127.0.0.1", 6379);

    //for (size_t i = 0; i < 20; i++)
    //{
    //    int Value = i * 100;
    //    std::string Name = "User" + std::to_string(i);

    //    RedisResult Res = Con.CommandArgResult<RedisCommand::ZADD>("RANK", std::to_string(Value), Name);
    //}

    // 싱글쓰레드에서 DBCONNETER의 커넥트는 다 걸어놓고
    // 만들어진 연결들을 쓰레드에게 분담시켜주고
    // 처리하는 겁니다.


    // 레디스는 싱글 쓰레드이기 때문에 내가 커넥션을 많이 만들고
    // 그걸 어떻게 보내더라도 
    // 처리에 대한 효율은 변하지 않습니다.
    // 레디스는 커넥션을 만들때 성능에 의해서 만드는것이 아니고
    // 용도에 의해서 만들게 됩니다.
    // 레디스를 어떠한 용도로 사용하느냐에 따라서 달라집니다.

    //RedisManager::GetInst().Init("127.0.0.1", 6379);
    // RedisManager::GetInst().RedisCommandPush<RedisCommand::SET>(TestFunc, "TESTKEY", "1");

    // Sleep(INFINITE);


    DBManager::Inst().Init("root", "4321", "server11", 8);

    GameEngineCollision::Init();

    LogManager::Inst().Init(3, 1000);
    LogManager::Inst().PushLog("LogThread Create");
    ServerPacketFunc::Init();
    GameEngineServer::GetInst().ServerStart(30000, ServerAppEvent::DisConnectEvent);
    GameEngineThread::CreateThread<LogicThread>(L"LogicThread");

    Sleep(INFINITE);
}
