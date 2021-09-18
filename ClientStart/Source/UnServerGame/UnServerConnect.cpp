// Fill out your copyright notice in the Description page of Project Settings.


#include "UnServerConnect.h"
#include <ClientToServer.h>
#include <GameEngineSerializer.h>
#include <ServerToClient.h>
#include <ServerToClientPacketUpdater.h>
#include "ClientPacketFunc.h"
#include "LoginScreenWidget.h"
// #include "ClientPacketFunc.h"

// int ConnectTesk::Check = 0;

void ConnectTask::DoWork() 
{
    // ++Check;

    // �𸮾� �α״� �����忡 �����մϴ�.

    // �̳༮�� task�� ó���ϰ� ������ ���� task�� ó���ϴ� ������� �����ϴ� �������ε�.
    // while�� �ɾ������
    // �𸮾� �ɰ��� ������ ����ų���� �ֽ��ϴ�.
    // �� ��������� �ٸ� �α׳� �̷��༮���� ó���ϱ� ���ؼ� ������� �༮�̱� ������
    // ���� �ű⿡ ���� ������ �̴ϴ�.
    // �ѹ��� �ϳ��� �Լ��� ó���ϴ� �뵵�� �����忡��
    // ���� �װ� ������ �����ع����� �𸮾� �ɰ��� ������ ����ų���� �ֽ��ϴ�.
    //if (0 == (Check % 100000))
    //{
    UnServerConnect::GetInst().Connect();

    // �𸮾� �� ������Ǯ�� ���� ����ϱ� ������
    // ��������� ���⼭ while�� ����ϸ� �ȵ˴ϴ�.

}

void ConnectTask::DoWorkMain()
{
    DoWork();
}
/////////////////////////////////////////////////////// 

UnrealRecvThread::UnrealRecvThread() 
{
    UnServerConnect::GetInst().m_ThreadProcess.Exchange(1);
}

uint32 UnrealRecvThread::Run()
{
    UnServerConnect::GetInst().m_ThreadProcess.Exchange(1);

    // ��� �÷������� 
    // ���� �� �������� �ѹ� ���մٴ°� �����̹Ƿ� �������� ���� ������ ��� ���Ͽ��� �������� �ʰ� ���� Client
    FSocket* ConnectSocket = UnServerConnect::GetInst().ConnectSocket;

    // ConnectSocket->soxck

    int RecvByte = 0;
    
    uint8 ArrBuffer[1024 * 8];


    while (1 == UnServerConnect::GetInst().m_ThreadProcess)
    {
        // UE_LOG(LogTemp, Error, L"??");
        // Ŀ��Ʈ�� �߸��Ȱ��̴�.
        if (false == ConnectSocket->Recv(ArrBuffer, sizeof(ArrBuffer), RecvByte))
        {
            UE_LOG(LogTemp, Error, L"Recv Error false");
            break;
        }
        
        // if���� switch������ ��ĥ�� �˴ϴ�.
        ServerToClientPacketUpdater Converter(reinterpret_cast<char*>(ArrBuffer), RecvByte);
        // ��Ŷ�� ��� ó���Ҷ����� ��� ����.
        while (false == Converter.IsEnd())
        {
            const char* Text = Converter.Update();
            FString Fs = FString(ANSI_TO_TCHAR(Text));
            if (Fs != TEXT("PlayerUpdatePacket") &&
                Fs != TEXT("MonsterUpdateDataPacket"))
            {
                UE_LOG(LogTemp, Error, TEXT("%s %d"), *Fs, RecvByte);
            }
        }
    }

    UE_LOG(LogTemp, Error, L"Thread End");
    return 0;
}
void UnrealRecvThread::Stop()
{
    UnServerConnect::GetInst().m_ThreadProcess.Exchange(0);
}
void UnrealRecvThread::Exit()
{

}


////////////////////////////////////////////////////////////////////

UnServerConnect::UnServerConnect() : ConnectSocket(nullptr), m_IsConnect(false), RecvThread(NULL), IsServer(true)
{
    // SSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
}

UnServerConnect::~UnServerConnect()
{
    
    // Close();
}


UnServerConnect& UnServerConnect::GetInst() 
{
    static UnServerConnect Inst;
    return Inst;
}

bool UnServerConnect::IsConnect() 
{
    // ���⿡ ���̴� ������ ������ �������� ����?
    // �����忡�� ó���ɶ� ���⿡�� �˷��ִ� ������ ������ �ɼ��� �ִ�.

    return m_IsConnect;
}

void UnServerConnect::ConnectSocketCreate() 
{
    // Ŀ��Ʈ�� �����忡�� ������ �Ǵµ�.
    Close();

    ISocketSubsystem* SSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

    if (nullptr == SSS)
    {
        UE_LOG(LogTemp, Error, L"if (nullptr == SSS)");
        return;
    }

    UE_LOG(LogTemp, Error, L"Socket Init");

    // FTcpSocketBuilder("SERVERGAMECONNECTER").AsReusable();


    // NAME_DGram UDP
    ConnectSocket = SSS->CreateSocket(NAME_Stream, "ServerGameConnecter", false);
    ConnectSocket->SetNoDelay(true);

    if (NULL != ConnectSocket)
    {
        UE_LOG(LogTemp, Error, L"Socket Create OK");
    }
    else {
        UE_LOG(LogTemp, Error, L"Socket Create ERROR");
    }

    FIPv4Address::Parse(ULoginScreenWidget::IPText, ip);
    EndPoint = FIPv4Endpoint(ip, 30000);
    UE_LOG(LogTemp, Error, TEXT("%s"), *ULoginScreenWidget::IPText);

    // ConnectSocket->Bind(EndPoint.ToInternetAddr().Get());
}

bool UnServerConnect::Connect() 
{
    ConnectSocketCreate();

    // ������ �����带 ����� �׳� �α׶�� ���ڽ��ϴ�.

    if (false == ConnectSocket->Connect(EndPoint.ToInternetAddr().Get()))
    {
        ISocketSubsystem* SSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        FString ErrorText = SSS->GetSocketError(SSS->GetLastErrorCode());
        UE_LOG(LogTemp, Error, L"Server Error %s", *ErrorText);
        ConnectSocket = NULL;
        m_IsConnect = false;
        return false;
    }

    m_IsConnect = true;

    UE_LOG(LogTemp, Log, L"Server Connect Success");

    // ��� ���ټ� �־�� ��Ŷó���� ����������.
    // ClientPacketFunc::Init();

    // ���ú� ������� �̶� ���������.
    if (true == FPlatformProcess::SupportsMultithreading())
    {
        RecvThread = new UnrealRecvThread();
        RecvFRunnable = FRunnableThread::Create(RecvThread, TEXT("RecvThread"));
    }


    return true;
}

// ���ุ ���ָ� �����忡 �Ѱܼ� Ŀ��Ʈ�� ó���ϰ� �׿� ���� ���¸� �˷��ִ� �Լ�
void UnServerConnect::ConnectTaskStart() 
{
    // �̶� �׳� �����带 �����ڽ��ϴ�.


    if (nullptr == ConnectTaskAsync)
    {
        ConnectTaskAsync = new FAutoDeleteAsyncTask<ConnectTask>();
    }

    ConnectTaskAsync->StartBackgroundTask();

    // ����ϴ� ���� �����忡 �ڽ��� �ѱ�� �ȴ�.
    // ConnectTaskAsync.StartBackgroundTask();
}

void UnServerConnect::ThreadStop() 
{
    if (NULL != RecvThread)
    {
        RecvThread->Stop();
        RecvThread = NULL;
    }
}

void UnServerConnect::Close() 
{
    UE_LOG(LogTemp, Error, L"UnServerConnect::Close() ");

    // SSS;
    m_Login.Exchange(0); // 0�̸� ���� �α����� ����� ���� �ʾҴ�.
    m_GameStart.Exchange(0); // �����

    //if (nullptr != SSS)
    //{
    //    SSS->ShutdownAllSystems();
    //}

    if (nullptr != ConnectTaskAsync)
    {
        ConnectTaskAsync = NULL;
    }

    if (nullptr != ConnectSocket)
    {
        ConnectSocket->Close();
        ConnectSocket = nullptr;
    }
}



// �־��ַ��� ����
void UnServerConnect::Send(const uint8* Data, int32 Count/*, int32& BytesSent*/)
{
    ConnectSocket->Send(Data, Count, m_SendByte);
}

void UnServerConnect::Send(ClientToServer& _Data) 
{
    GameEngineSerializer Ser = _Data.Serialize();
    // UE_LOG(LogTemp, Error, TEXT("Pacekt %d %d"), _Data.GetCType(), Ser.GetOffsetInt());
    ConnectSocket->Send(Ser.GetUnsignedBuffer(), Ser.GetOffsetInt(), m_SendByte);
}

void UnServerConnect::Init(UWorld* _World)
{
    UnServerConnect::GetInst().m_CharacterData.ItemDatas.clear();
    MainProcess.MsgListInit(3, 1000);
    MainWorld = _World;
    m_ThreadProcess.Exchange(1);
    m_Login.Exchange(0); // 0�̸� ���� �α����� ����� ���� �ʾҴ�.
    m_GameStart.Exchange(0); // �����
    m_IsConnect = false;

    ClientPacketFunc::Init();
}