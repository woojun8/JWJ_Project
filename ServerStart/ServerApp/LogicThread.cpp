#include "LogicThread.h"
#include <iostream>
#include <GameEngineFile.h>
#include <GameEngineDirectory.h>
#include <WorldDataParser.h>
#include "ServerWorld.h"
#include <GameEngineTime.h>
#include <LogManager.h>
#include <GameEngineRandom.h>

// Static Var
ServerWorldManager LogicThread::WorldManager;

// constructer destructer
LogicThread::LogicThread() 
{

}

LogicThread::~LogicThread() 
{

}
// member Func

void LogicThread::ThreadUpdate()
{
    //for (size_t i = 0; i < 100; i++)
    //{
    //	GameEngineThread::CreateThread<Test>(L"TestThread");
    //}

    // 메인스레드와 로직스레드에서
    // 액셉트 스레드 생성하고
    // 기동할때까지
    // 기다려주면 됩니다.

    GameEngineRandom::Init();

    {
        GameEngineFile NewFile;

        GameEngineDirectory NewDir;
        GameEngineFile File = NewDir.GetCurrentDirectoryPath() + L"ConsoleGameData.txt";
        if (false == File.IsExist())
        {
            NewDir.MoveParent(L"ServerStart");
            File = NewDir.GetFile(L"ConsoleGameData.txt");
        }
        else 
        {
            File = NewDir.GetFile(L"ConsoleGameData.txt");
        }

        File.FileOpen(L"rt");
        GameEngineString Text = File.ToString();

        std::list<GameEngineString> StrList = Text.CenterCut(L'<', L'>');

        for (GameEngineString MapDataText : StrList)
        {
            WorldData GetWorldData = WorldDataParser::GetStringToWorldData(MapDataText);
            std::shared_ptr<ServerWorld> SW = WorldManager.CreateServerWorld(GetWorldData);
            SW->MsgListInit(3, 1000);
            WorldManager.UpdateCheck(GetWorldData.Index);
            int a = 0;
        }

        std::cout << "월드 생성 완료." << std::endl;
    }

	std::cout << "월드 열심히 돌리는중." << std::endl;

    // 말이 안되는 상황

    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    int CpuCount = systemInfo.dwNumberOfProcessors;


    // 업데이트는 60프레임 제한입니다.
    WorldManager.SetUpdateFrameRate(60);

	while (true)
	{
        if (2 >= CpuCount)
        {
            Sleep(1);
        }
        // 

        // Server의 Logicthread는 Sleep걸어야 
        // 가장 쌩쌩하게 돌아가야 합니다.
        // 시간 재줘야죠.
        GameEngineTime::GetInst().Update();
        // 9개의 월드중 어떤 월드에
        // 새로운 액터가 하나 생긴다는 거죠?
        LogManager::Inst().PrintLog();
        WorldManager.Progress(GameEngineTime::GetInst().FTime());
	}
}