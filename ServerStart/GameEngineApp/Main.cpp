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
    
    // �����ӿ�ũ�� �̴ϼȶ������� �۾��� �ϰ� �˴ϴ�.
    GameEngineDebug::LeckCheck();
    ConosleHelper::Init();


    // ������ ���۵� ���� �ʾҴ�.




    ClientWorldManager WorldManager;
    {
        // ���带 ���δ� ������ ������
        // �׳� ��������.
        // Ŭ���̾�Ʈ�� ����ϴµ�
        // �ε��ý���
        // ���� ���� �����ϴ� ������ ����� �Ǵ°�.
        // wow�� 60�Ⱑ �ε� ��ü���带 �� ����� 60�Ⱑ�� �ø� ram�� �������?
        // ���� ���� �������忡 �ִ��� ���հ��� �ִ� �Ҹ��� ������ �ε��� �ʿ䰡 ������?
        // [x][x][x]
        // [x][L][X]
        // [L][0][L]

        // �ε��� ���ؼ� �̾߱����ڸ�
        // Ŭ���̾�Ʈ

        GameEngineFile NewFile;
        GameEngineDirectory NewDir;
        NewDir.MoveParent(L"ServerStart");
        GameEngineFile File = NewDir.GetFile(L"ConsoleGameData.txt");
        File.FileOpen(L"rt");
        GameEngineString Text = File.ToString();
        std::list<GameEngineString> StrList = Text.CenterCut(L'<', L'>');

        // ȸ�翡���� ������ �������.
        // ���ټ��� �ְ� �����ټ��� �ִµ�.
        // ���ʿ� ȸ�翡 ����
        // �ϰ� ������ �˾Ƴ�.
        // ������Ʈ �ľ����ϰ� ���������̼��� �϶�� �ؿ�.
        for (GameEngineString MapDataText : StrList)
        {
            WorldData GetWorldData = WorldDataParser::GetStringToWorldData(MapDataText);
            // Ŭ���̾�Ʈ�� Ŭ���̾�Ʈ�� ���带 �����
            // ���� �ð��� �۾��� ��������� �������带 �������.
            WorldManager.CreateClientWorld(GetWorldData);
            int a = 0;
        }
    }

    ClientValue::mClientMode = ClientMode::ConnectClient;
    if (ClientMode::ConnectClient == ClientValue::mClientMode)
    {
        if (false == ConnectProgress())
        {
            std::cout << "Ŭ���̾�Ʈ�� �����մϴ�" << std::endl;
            _getch();
            ClientConnecter::GetInst().Destroy();
            exit(0);
            return 0;
        }
    }


    // Ŭ���̾�Ʈ ���α׷��ӵ�� ���� ���α׷��ӵ��� 
    // �� ���̰� �ִ� �κ��� �ִµ�.
    // ������ Ŭ������ ������ �����ϱ�.
    // �����ش�.

    // Ŭ��� ������ �������� �����ϸ� �ǰڱ���.
    
    // 1��.
    // Ŭ������ ���ҽ� ���� ���� �� �������� ��ٷ��� �մϴ�.
    // ��Ŷ�� �������� �Ҽ� �ִ� �ϵ��� ���� ������ �����ϰ�
    // �� ó���ϰ� ���� ĳ���� ������ ��ٸ���.
    
    // 2��. 
    // �� ���ҽ� ó���� �ٳ����� ������ �غ� �ƴ�. ĳ���� ������.

    std::cout << "ĳ���� ���� ��ٸ�����" << std::endl;

    // ĳ���� ������ ���õɶ����� ���⼭ ��ٸ���.
    while (nullptr == ClientConnecter::GetInst().GetCharacterData()) 
    {
        Sleep(1);
    }



    // ���带 �������ش�.

    // ���� �̷��� �غ��ϴ� ����
    // ���� ����� �ε��ϴ� ����
    // �ٸ� ������ ���� ���ɼ��� �ֳ��� ������?
    // �ε��̶�°� ����?
    // �ٸ� �����鵵 ����� ������ ����� �־����?

    // Ŭ���̾�Ʈ�� ���⿡ ������?

    // �ε��� ������.
    // �ε������� ��Ŷ�� �����ָ�

    // ���Ⱑ �ε��ϴ� ���̾��� ������?
    ClientReadyPacket NewPacket;
    NewPacket.m_Code = 1;
    ClientConnecter::GetInst().Send(NewPacket);


    // ���⿡�� �ٷ� ���� �ȵǰ�
    while (ClientValue::m_GameStartCheck)
    {
        Sleep(1);
        std::cout << "���� ���ӽ�ŸƮ ��Ŷ ��ٸ��� ��" << std::endl;
    }
    system("cls");

    GameEngineTime FrameTimer = GameEngineTime();
    float Frame = 1.0f / 60.0f;
    float AccFrame = 0.0f;
    //float SendFrame = 1.0f / 30.0f;
    //float AccSendFrame = 0.0f;
    int SendCount = 0;

    // ���尡 �����ϱ����� ���� ��������
    // �˰ڳ���?

    while (true)
    {
        // �ʼ� �̰����� ������ ���ؽ�Ʈ ����Ī�� �Ͼ�� �ʾƼ�
        // �� ���α׷��� CPU�� ������ �����ع�����.
        Sleep(1);

        // �÷��� �ϴ� ���߿� ���͵�
        // �� ��� ������ ����?

        // ������ ���� �ðԴ� ���εΰ�
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
            // 30�����ӿ� 1�� ��������?
            // ���⼭ Send�� �մϴ�.
        }

        GameEngineTime::GetInst().Update();
        GameEngineInput::GetInst().KeyCheck();
        WorldManager.Progress();
    }
}