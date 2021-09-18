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

    // ���ν������ ���������忡��
    // �׼�Ʈ ������ �����ϰ�
    // �⵿�Ҷ�����
    // ��ٷ��ָ� �˴ϴ�.

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

        std::cout << "���� ���� �Ϸ�." << std::endl;
    }

	std::cout << "���� ������ ��������." << std::endl;

    // ���� �ȵǴ� ��Ȳ

    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    int CpuCount = systemInfo.dwNumberOfProcessors;


    // ������Ʈ�� 60������ �����Դϴ�.
    WorldManager.SetUpdateFrameRate(60);

	while (true)
	{
        if (2 >= CpuCount)
        {
            Sleep(1);
        }
        // 

        // Server�� Logicthread�� Sleep�ɾ�� 
        // ���� �߽��ϰ� ���ư��� �մϴ�.
        // �ð� �������.
        GameEngineTime::GetInst().Update();
        // 9���� ������ � ���忡
        // ���ο� ���Ͱ� �ϳ� ����ٴ� ����?
        LogManager::Inst().PrintLog();
        WorldManager.Progress(GameEngineTime::GetInst().FTime());
	}
}