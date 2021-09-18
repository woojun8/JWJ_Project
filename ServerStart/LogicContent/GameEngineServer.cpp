#ifndef UNREALDEFINE
#include "GameEngineServer.h"
#include <GameEngineDebug.h>
#include <TcpAccepter.h>
#include <TcpConnecter.h>
#include "ServerConnecter.h"
#include <GameEngineIocp.h>
#include <iostream>
#include "ClientToServer.h"
#include "ServerToClient.h"
#include "ClientToServerPacketUpdater.h"
#include "Player.h"
#include <LogManager.h>
#include <DBConnecter.h>
// Static Var
// Static Func

// �׸� �ϳ��� ���鶧����
// ũ��Ƽ�� ������ �Ѱ��� �����������?
// �׷��� ���� ������ �ϳ��� �ϳ� ���鶧���� 
// �̰� �������ִ°� �� ¥������.
LONG GameEngineServer::ConnectUserCount = 0;
LONG GameEngineServer::WorldUserCount = 0;

GameEngineServer GameEngineServer::Inst;

thread_local std::function<void(ServerConnecter*)> ThreadDisFunc;

GameEngineServer& GameEngineServer::GetInst()
{
	return Inst;
}

// constructer destructer
GameEngineServer::GameEngineServer() 
{
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		GameEngineDebug::AssertMsg("if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))");
	}
}

GameEngineServer::~GameEngineServer() 
{
	WSACleanup();
}


void GameEngineServer::GameServerIcopFunc()
{
	// 32�� ��������ϴ�.
	GameEngineIocp::IocpWorker Worker = GetInst().m_Icop.CreateWorker();
	// HANDLE IcopHandle = GetInst().m_Icop.MonitorHandle
	// 32���� �������� �ϳ��ε�.
	// std::cout << "���� �̺�Ʈ �����尡 ����������ϴ�\n";
	ThreadDisFunc = GetInst().DisFunc;

	// ���������� �ƴϸ�
	// ���δ� �����ؿ�
	
	// ������ġ�� �ɾ�� �մϴ�.
	// �� => ������ ����
	// �����Ϳ��� => ������ ����

	ULONG_PTR ComKey;
	DWORD Len;
	EngineOVERLAPPED* OverData;
	EngineSocketEvent Type;
	GameEngineSocket* Socket;
	ServerConnecter* ServerCon;

	while (true)
	{
		Worker.GetQueueWait();

		ComKey =  Worker.GetComKey();
		Len = Worker.GetLen();
		OverData = Worker.OverData();

		// �����ͺ�Ű�� NULLPTR�� �ƴϰ�
		// OverData NULLPTR �ɵ������� �����忡 ó���ش޶��
		// ������ �˴ϴ�.
		// ���ϵ�� �߻��� �̺�Ʈ�Դϴ�.
		if (0 != ComKey && nullptr == OverData)
		{
			ServerTask* Task = reinterpret_cast<ServerTask*>(ComKey);
			if (nullptr != Task)
			{
				Task->TeskFunc();

				Task->TeskFunc = nullptr;

				GameEngineServer::Inst.m_TaskPool.Push(Task->shared_from_this());

				continue;
			}
			else 
			{
				GameEngineDebug::AssertMsg("if (nullptr != Task)");
			}

			continue;
		}


		Type = OverData->Type;
		Socket = OverData->m_ParentSocket;
		ServerCon = dynamic_cast<ServerConnecter*>(Socket);

		if (-1 == Len)
		{
			// ������ ������ ���� �߰ߵȴٸ�
			// ������ ������ ���Ӱ� �ٽ� �������� �Ѵ�.
			// ��Ȱ���� �ȵ˴ϴ�.
			int a = 0;
		}

		switch (Type)
		{
		case EngineSocketEvent::ACCPET:
			// ���ú�� �ٲ��ֱ⸸ �ϸ� �ȴ�.
			
			// ���ø��� ��Ʈ ���ص� �Ǵ� ����.
			// CreateIoCompletionPort(_Handle, m_IOCPMainHandle, (DWORD)_Data, 0)
			// ���� ������ �ʴ� ������ �̹� ���õǰ� �ִ� �����̴�.
			// Inst.m_Icop.MonitorHandle((HANDLE)Socket->GetSocket());

			std::cout << Socket->GetSocket() << " �� ���ӵǾ����ϴ�." << std::endl;

			// ���� ������ �񵿱� ���ú긦 ���ѳ����ϴ�.
			// ��
			Socket->AsyncRecv();
			// m_Icop.MonitorHandle((HANDLE)NewCon->GetSocket());

			InterlockedIncrement(&ConnectUserCount);
			break;
		case EngineSocketEvent::RECV:
		{
			// 2���� ������
			// ��ٷ� ������ �񵿱� ���ú� �ɾ������
			if (0 == Len)
			{
				// �ٸ� �����尡 ������̰�
				// �� �����尡 �� ������ ��Ŀ��Ʈ�� ó���Ұ̴ϴ�.
				// GameEngineDebug::AssertMsg("���� ó���� ���߽��ϴ�.");
				Worker.IocpPost(reinterpret_cast<ULONG_PTR>(Socket), sizeof(8), &Socket->GetDisconnectOverRef());
				continue;
			}

			// std::cout << Len << std::endl;


			// �������� ���۸� ������� ó���ع����� ��� 

			ClientToServerPacketUpdater Converter(ServerCon, Socket->GetRecvBuffer().RealBuffer, Len);

			while (false == Converter.IsEnd())
			{
				const char* Text = Converter.Update();
				if (0 != strcmp(Text, "ClientPlayerPacket"))
				{
					LogManager::Inst().PushLog(Text);
				}
			}

			Socket->AsyncRecv();
			break;
		}
		case EngineSocketEvent::SEND:
			break;
		case EngineSocketEvent::DISCONNECT:
			// ��Ŀ��Ʈ�� �Ǹ�
			// �ٽ� �׼�Ʈ�� �ɾ���� �Ѵ�.
			// �׳༮�� �ٽ� �����ڸ� ������ �ִ� ������ �ȴ�.
		{
			// ��Ŀ��Ʈ �ɶ��ε�.

			ServerCon->RealDisconnect();
			break;
		}
		case EngineSocketEvent::REALDISCONNECT:
		{
			// ���⼭�� �Լ������ͷ� ó���ؾ� �Ʒ��ʿ� �ִ� serverapp�� ������ ���� ������ �ֽ��ϴ�.

			// �Լ������ͷ� ó������� �մϴ�.

			if (nullptr != ServerCon->GetPlayer())
			{
				ThreadDisFunc(ServerCon);
				ServerCon->DisConnectTask();
				ServerCon->GetPlayer()->Death();
			}

			std::cout << ServerCon->GetSocket() << " ������ ����Ǿ����ϴ�." << std::endl;
			std::cout << ServerCon->GetSocket() << " �� ��Ȱ�� �˴ϴ�." << std::endl;

			BOOL Check = ServerCon->AcceptExConnecter();

			if (FALSE == Check)
			{
				int a = 0;
			}

			break;
		}
		case EngineSocketEvent::NONE:
		default:
			// ���� �ھ�κп�
			GameEngineDebug::AssertMsg("�ھ ġ������ ������ �߻��߽��ϴ�.");
			break;
		}

	}


}

void GameEngineServer::ServerStart(
    int _Port,
	std::function<void(ServerConnecter*)> _DisconnectFunc,
    int _Count /*= -1*/
)
{
	DisFunc = _DisconnectFunc;

	// Iocp�� ���������

	m_Icop.Start(GameServerIcopFunc, _Count);
	m_TaskPool.Init(1000);

	std::cout << "���� �̺�Ʈ �����尡 ����������ϴ�\n";

	// Iocp���� ����͸� �ش޶�� ��û�ؾ� �ϴ� �༮���� �ִµ�.

	PtrTcpAccepter = std::make_shared<TcpAccepter>();
	
	// 
	// 456789 ....... 512����� ��� ���� ������ �־�� 
	// 	   ���� �츮���� Ŀ��Ʈ�� �� Ŭ���̾�Ʈ ���̱⵵ �ϴ�.
	// 
	// [][][][][][][]....... 10000�� AcceptEx

	// Accept �̺�Ʈ�� �߻��ϴ°� ������ ������ �ƴϰ� �����ѳ��� AcceptEx���Ͽ��� �߻��Ѵ�.
	// [1][2][3] === �̰� 10000��

	// �� �ο��� ���ÿ� ������ ó�������ϳİ� 512
	if (false == PtrTcpAccepter->listenSetting(_Port, SOCKETSYNCTYPE::ASYNC, "0.0.0.0", 512))
	{
		GameEngineDebug::AssertMsg("if (false == NewTcpAccepter->listenSetting(_Port, _Type, _Ip, _ListenCount, _IPType))");
	}

	// ����Ʈ�� �޴� ������ 1����
	m_Icop.MonitorHandle((HANDLE)PtrTcpAccepter->GetSocket());

	// 10�������� �ɸ� �˴ϴ�.

	// ���� �׼�Ʈ�� ����ϸ�
	// �׼�Ʈ �Լ��� �������� ���� �˴ϴ�.
	// ó��ó��ó��ó��ó��ó��
	// 
	// �׼�Ʈ EX�� ��ŭ ���Դٸ� �� �������� �� ��� ó���Ѵ�.
	// ���� ������ 512�� �߾ ������ 10�� ��Ͻ��� ������
	// 10�� ó���Ǵ� ���� ������ �ο����� �ϴ� ��α׶�� ó���� ���ؼ�
	// ��� ���� ����
	// ���� AcceptEx�� �Ŵ¼��� �� ��α׿��� ���ͼ� ó���� �˴ϴ�.
	// 512���� ������ �������� ������ �Ǹ� �� ������ ������ ��� �����ϴ���?

	// IOCP�� Ŀ�ؼ� ���ϵ��� ��������?
	// �� �ο��� ���ÿ� ������ ó�������ϳİ� 512

	// Ǯ�� ����� �����Ͱ� �ٸ��� ����.
	// ������ ����Ʈ EX�� �̷��� ���� ���ʿ�� ����.
	// 
	for (size_t i = 0; i < 10000; i++)
	{
		// ����� ��򰡿� ������ �س��� �ʰ�
		// ������ IOCP�� 
		std::shared_ptr<ServerConnecter> NewCon = PtrTcpAccepter->CreateAcceptExConnection<ServerConnecter>();
		// EngineOVERLAPPED& Test = NewCon->GetAcceptOverRef();
		m_Icop.MonitorHandle((HANDLE)NewCon->GetSocket());
	}


	//// �������� STATIC  �����߳���?"
	//static int NumberValue = 100;
	//static EngineOVERLAPPED  TestOver;
	//TestOver.Type = EngineSocketEvent::DISCONNECT;
	//m_Icop.IocpPost(reinterpret_cast<ULONG_PTR>(&NumberValue), sizeof(8), &TestOver);

}
#endif