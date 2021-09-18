#include "Main.h"
#include <iostream>
#include <GameEngineDebug.h>
#include <GameEngineTime.h>
#include <GameEngineFile.h>
#include <GameEngineDirectory.h>
#include "ConosleHelper.h"
#include <World.h>
#include <WorldManager.h>
#include <GameEngineThread.h>
#include <GameWorldManager.h>
#include <GameWorld.h>
#include "ClientWorld.h"
#include "ClientWorldManager.h"
#include "ClientPlayer.h"
#include "ClientValue.h"
#include "ConosleHelper.h"
#include <WorldDataParser.h>
#include <MiniBaseHeader.h>
#include <GameEngineSocket.h>
#include <TcpConnecter.h>
#include <ClientConnecter.h>
#include <conio.h>
#include <LogicValue.h>
#include <ClientToServer.h>

#pragma comment(lib, "GameEngineObject")
#pragma comment(lib, "GameEngineBase")
#pragma comment(lib, "GameEngineNet")
#pragma comment(lib, "LogicContent")

#include "ClientPacketFunc.h"

int main() 
{
    ClientPacketFunc::Init();
    
    // 프레임워크는 이니셜라이즈라는 작업을 하게 됩니다.
    GameEngineDebug::LeckCheck();
    ConosleHelper::Init();


    // 게임은 시작도 하지 않았다.




    ClientWorldManager WorldManager;
    {
        // 월드를 전부다 만들지 않지만
        // 그냥 만들었어요.
        // 클라이언트가 담당하는데
        // 로딩시스템
        // 내가 현재 존재하는 지역만 만들면 되는것.
        // wow가 60기가 인데 전체월드를 다 만들면 60기가를 올릴 ram이 있을까요?
        // 내가 지금 스톰윈드에 있는저 저먼곳에 있는 불모의 땅까지 로딩할 필요가 있을까?
        // [x][x][x]
        // [x][L][X]
        // [L][0][L]

        // 로딩에 대해서 이야기하자면
        // 클라이언트

        GameEngineFile NewFile;
        GameEngineDirectory NewDir;
        NewDir.MoveParent(L"ServerStart");
        GameEngineFile File = NewDir.GetFile(L"ConsoleGameData.txt");
        File.FileOpen(L"rt");
        GameEngineString Text = File.ToString();
        std::list<GameEngineString> StrList = Text.CenterCut(L'<', L'>');

        // 회사에서는 설명을 안해줘요.
        // 해줄수도 있고 안해줄수도 있는데.
        // 최초에 회사에 들어가면
        // 니가 스스로 알아내.
        // 프로젝트 파악을하고 프레젠테이션을 하라고 해요.
        for (GameEngineString MapDataText : StrList)
        {
            WorldData GetWorldData = WorldDataParser::GetStringToWorldData(MapDataText);
            // 클라이언트는 클라이언트의 월드를 만들고
            // 이후 시간에 작업할 서버월드는 서버월드를 만들겠죠.
            WorldManager.CreateClientWorld(GetWorldData);
            int a = 0;
        }
    }

    ClientValue::mClientMode = ClientMode::ConnectClient;
    if (ClientMode::ConnectClient == ClientValue::mClientMode)
    {
        if (false == ConnectProgress())
        {
            std::cout << "클라이언트를 종료합니다" << std::endl;
            _getch();
            ClientConnecter::GetInst().Destroy();
            exit(0);
            return 0;
        }
    }


    // 클라이언트 프로그래머들과 서버 프로그래머들이 
    // 좀 차이가 있는 부분이 있는데.
    // 서버는 클라한테 관심이 없으니까.
    // 보내준다.

    // 클라는 받으면 이제부터 시작하면 되겠구나.
    
    // 1안.
    // 클라쪽은 리소스 관련 일을 다 끝내놓고 기다려야 합니다.
    // 패킷이 오기전에 할수 있는 일들이 뭐가 있을지 생각하고
    // 다 처리하고 나서 캐릭터 정보를 기다린다.
    
    // 2안. 
    // 그 리소스 처리를 다끝내면 서버로 준비가 됐다. 캐릭터 보내라.

    std::cout << "캐릭터 정보 기다리는중" << std::endl;

    // 캐릭터 정보가 세팅될때까지 여기서 기다린다.
    while (nullptr == ClientConnecter::GetInst().GetCharacterData()) 
    {
        Sleep(1);
    }



    // 월드를 세팅해준다.

    // 내가 이렇게 준비하는 동안
    // 월드 만들고 로딩하는 동안
    // 다른 유저가 들어올 가능성이 있나요 없나요?
    // 로딩이라는게 뭐죠?
    // 다른 유저들도 만들수 있으면 만들수 있어야죠?

    // 클라이언트는 여기에 들어왔죠?

    // 로딩이 끝났다.
    // 로딩끝났다 패킷을 보내주면

    // 여기가 로딩하는 곳이었죠 여러분?
    ClientReadyPacket NewPacket;
    NewPacket.m_Code = 1;
    ClientConnecter::GetInst().Send(NewPacket);


    // 여기에서 바로 들어가면 안되고
    while (ClientValue::m_GameStartCheck)
    {
        Sleep(1);
        std::cout << "서버 게임스타트 패킷 기다리는 중" << std::endl;
    }
    system("cls");

    GameEngineTime FrameTimer = GameEngineTime();
    float Frame = 1.0f / 60.0f;
    float AccFrame = 0.0f;
    //float SendFrame = 1.0f / 30.0f;
    //float AccSendFrame = 0.0f;
    int SendCount = 0;

    // 월드가 시작하기전에 들어온 유저들은
    // 알겠나요?

    while (true)
    {
        // 필수 이걸하지 않으면 컨텍스트 스위칭이 일어나지 않아서
        // 이 프로그램이 CPU를 완전히 점유해버린다.
        Sleep(1);

        // 플레이 하는 도중에 들어와도
        // 그 즉시 보여야 하죠?

        // 프레임 전용 시게는 따로두고
        FrameTimer.Update();
        AccFrame += FrameTimer.FTime();
        if (Frame > AccFrame)
        {
            continue;
        }
        AccFrame = 0.0f;
        ++SendCount;

        if (SendCount % 2)
        {
            // 30프레임에 1번 들어오겠죠?
            // 여기서 Send를 합니다.
        }

        GameEngineTime::GetInst().Update();
        GameEngineInput::GetInst().KeyCheck();
        WorldManager.Progress();
    }
}