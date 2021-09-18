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

// 항목 하나를 만들때마다
// 크리티컬 섹션은 한개씩 만들어져야죠?
// 그런데 보통 정수형 하나를 하나 만들때마다 
// 이걸 세팅해주는건 좀 짜증나죠.
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
	// 32개 만들어집니다.
	GameEngineIocp::IocpWorker Worker = GetInst().m_Icop.CreateWorker();
	// HANDLE IcopHandle = GetInst().m_Icop.MonitorHandle
	// 32개의 쓰레드중 하나인데.
	// std::cout << "서버 이벤트 쓰레드가 만들어졌습니다\n";
	ThreadDisFunc = GetInst().DisFunc;

	// 지역변수가 아니면
	// 전부다 위험해요
	
	// 안전장치를 걸어야 합니다.
	// 힙 => 무조건 위험
	// 데이터영역 => 무조건 위험

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

		// 컴퍼터블키가 NULLPTR이 아니고
		// OverData NULLPTR 능동적으로 쓰레드에 처리해달라고
		// 보낸게 됩니다.
		// 소켓등에서 발생한 이벤트입니다.
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
			// 완전한 오류로 만약 발견된다면
			// 소켓을 완전히 새롭게 다시 만들어줘야 한다.
			// 재활용이 안됩니다.
			int a = 0;
		}

		switch (Type)
		{
		case EngineSocketEvent::ACCPET:
			// 리시브로 바꿔주기만 하면 된다.
			
			// 컴플리션 포트 안해도 되는 이유.
			// CreateIoCompletionPort(_Handle, m_IOCPMainHandle, (DWORD)_Data, 0)
			// 내가 빼주지 않는 어차피 이미 감시되고 있는 소켓이다.
			// Inst.m_Icop.MonitorHandle((HANDLE)Socket->GetSocket());

			std::cout << Socket->GetSocket() << " 가 접속되었습니다." << std::endl;

			// 들어온 접속자 비동기 리시브를 시켜놓습니다.
			// 굳
			Socket->AsyncRecv();
			// m_Icop.MonitorHandle((HANDLE)NewCon->GetSocket());

			InterlockedIncrement(&ConnectUserCount);
			break;
		case EngineSocketEvent::RECV:
		{
			// 2가지 선택지
			// 곧바로 소켓을 비동기 리시브 걸어버리고
			if (0 == Len)
			{
				// 다른 쓰레드가 깨어날것이고
				// 그 쓰레드가 이 소켓의 디스커넥트를 처리할겁니다.
				// GameEngineDebug::AssertMsg("아직 처리를 못했습니다.");
				Worker.IocpPost(reinterpret_cast<ULONG_PTR>(Socket), sizeof(8), &Socket->GetDisconnectOverRef());
				continue;
			}

			// std::cout << Len << std::endl;


			// 지역변수 버퍼를 만든다음 처리해버리는 방법 

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
			// 디스커넥트가 되면
			// 다시 액셉트를 걸어줘야 한다.
			// 그녀석은 다시 접속자를 받을수 있는 소켓이 된다.
		{
			// 디스커넥트 될때인데.

			ServerCon->RealDisconnect();
			break;
		}
		case EngineSocketEvent::REALDISCONNECT:
		{
			// 여기서도 함수포인터로 처리해야 아래쪽에 있는 serverapp에 영향을 받지 않을수 있습니다.

			// 함수포인터로 처리해줘야 합니다.

			if (nullptr != ServerCon->GetPlayer())
			{
				ThreadDisFunc(ServerCon);
				ServerCon->DisConnectTask();
				ServerCon->GetPlayer()->Death();
			}

			std::cout << ServerCon->GetSocket() << " 접속이 종료되었습니다." << std::endl;
			std::cout << ServerCon->GetSocket() << " 가 재활용 됩니다." << std::endl;

			BOOL Check = ServerCon->AcceptExConnecter();

			if (FALSE == Check)
			{
				int a = 0;
			}

			break;
		}
		case EngineSocketEvent::NONE:
		default:
			// 서버 코어부분에
			GameEngineDebug::AssertMsg("코어에 치명적인 오류가 발생했습니다.");
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

	// Iocp가 만들어지고

	m_Icop.Start(GameServerIcopFunc, _Count);
	m_TaskPool.Init(1000);

	std::cout << "서버 이벤트 쓰레드가 만들어졌습니다\n";

	// Iocp에게 모니터를 해달라고 요청해야 하는 녀석들이 있는데.

	PtrTcpAccepter = std::make_shared<TcpAccepter>();
	
	// 
	// 456789 ....... 512명까지 대기 시켜 놓을수 있어요 
	// 	   리슨 우리에게 커넥트를 건 클라이언트 들이기도 하다.
	// 
	// [][][][][][][]....... 10000개 AcceptEx

	// Accept 이벤트가 발생하는건 리스닝 소켓이 아니고 대기시켜놓은 AcceptEx소켓에서 발생한다.
	// [1][2][3] === 이게 10000명

	// 그 인원을 동시에 몇명까지 처리가능하냐가 512
	if (false == PtrTcpAccepter->listenSetting(_Port, SOCKETSYNCTYPE::ASYNC, "0.0.0.0", 512))
	{
		GameEngineDebug::AssertMsg("if (false == NewTcpAccepter->listenSetting(_Port, _Type, _Ip, _ListenCount, _IPType))");
	}

	// 엑셉트를 받는 소켓은 1개고
	m_Icop.MonitorHandle((HANDLE)PtrTcpAccepter->GetSocket());

	// 10명정도만 걸면 됩니다.

	// 동기 액셉트를 사용하면
	// 액셉트 함수가 쉴새없이 돌게 됩니다.
	// 처리처리처리처리처리처리
	// 
	// 액셉트 EX한 만큼 들어왔다면 그 유저들은 그 즉시 처리한다.
	// 내가 리슨을 512명 했어도 소켓을 10개 등록시켜 놓으면
	// 10명만 처리되는 동안 더들어온 인원들은 일단 백로그라는 처리를 통해서
	// 대기 시켜 놓고
	// 내가 AcceptEx를 거는순간 그 백로그에서 빼와서 처리가 됩니다.
	// 512넘은 수많은 유저들이 들어오게 되면 이 리스닝 소켓은 어떻게 동작하느냐?

	// IOCP가 커넥션 소켓들을 감시하죠?
	// 그 인원을 동시에 몇명까지 처리가능하냐가 512

	// 풀을 만들어 놓은것과 다름이 없고.
	// 실제로 엑셉트 EX를 이렇게 많이 할필요는 없다.
	// 
	for (size_t i = 0; i < 10000; i++)
	{
		// 만들고 어딘가에 보관도 해놓지 않고
		// 오로지 IOCP에 
		std::shared_ptr<ServerConnecter> NewCon = PtrTcpAccepter->CreateAcceptExConnection<ServerConnecter>();
		// EngineOVERLAPPED& Test = NewCon->GetAcceptOverRef();
		m_Icop.MonitorHandle((HANDLE)NewCon->GetSocket());
	}


	//// 지역변수 STATIC  설명했나요?"
	//static int NumberValue = 100;
	//static EngineOVERLAPPED  TestOver;
	//TestOver.Type = EngineSocketEvent::DISCONNECT;
	//m_Icop.IocpPost(reinterpret_cast<ULONG_PTR>(&NumberValue), sizeof(8), &TestOver);

}
#endif