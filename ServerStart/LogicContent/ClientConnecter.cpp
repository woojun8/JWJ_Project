#include "ClientConnecter.h"
#include <GameEngineSerializer.h>

#include <GameEngineThread.h>
#include <GameEngineDebug.h>
#include "PacketType.h"
#include "ServerToClientPacketUpdater.h"

// Static Var

// Static Func

ClientConnecter ClientConnecter::Inst;

ClientConnecter& ClientConnecter::GetInst()
{
	return Inst;
}

// constructer destructer
ClientConnecter::ClientConnecter()  : IsConnect((int)CONNECTSTATE::CONNECTWAIT), m_ConnectThread(nullptr)
{
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		GameEngineDebug::AssertMsg("if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))");
	}
}

ClientConnecter::~ClientConnecter() 
{
	WSACleanup();
}

void ClientConnecter::RecvThread() 
{
	// 이쪽에서는 그 패킷을 받겠죠?
	ClientConnecter* Connecter = &ClientConnecter::GetInst();

	while (true)
	{
		// 알아서 내부에서 버퍼까지 다 만들어서 받는 행동을 한다.
		// 다시 동기 리시브로 가게 됩니다.
		int Len = Connecter->SyncRecv();

		// 패킷을 서버가 역으로 쏴줬다는 소리입니다.

		if (-1 == Len)
		{
			return;
		}

		if (0 == Len)
		{
			return;
		}

		// 이쪽은 어차피 동기 리시브
		// 지역변수 버퍼를 만든다음 처리해버리는 방법 
		ServerToClientPacketUpdater Converter(Connecter->GetRecvBuffer().RealBuffer, Len);
		Converter.Update();
	}
}

void ClientConnecter::ConnectThread()
{
	TcpConnecter* Connecter = &ClientConnecter::GetInst();

	int Result = Connecter->Connect();

	if (SOCKET_ERROR == Result)
	{
		ClientConnecter::GetInst().IsConnect = (int)CONNECTSTATE::CONNECTERROR;
		return;
	}

	ClientConnecter::GetInst().IsConnect = (int)CONNECTSTATE::CONNECTOK;

	// 여기까지 왔으면
	// Recv  쓰레드를 여기서 만들겁니다.

	Inst.m_RecvServer = std::make_shared<GameEngineThread>();
	Inst.m_RecvServer->SetThreadFunc(RecvThread);
	Inst.m_RecvServer->Start();
}

void ClientConnecter::ClientStart(int _Port, const char* _Ip, IPTYPE _IPType)
{
	CreateSyncConnection();
	AddressSetting(_Ip, _Port);


	m_ConnectThread = std::make_shared<GameEngineThread>();
	m_ConnectThread->SetThreadFunc(ConnectThread);
	m_ConnectThread->Start();
}

void ClientConnecter::Send(ClientToServer& _Data)
{
	GameEngineSerializer Ser = _Data.Serialize();
	SyncSend(Ser.GetBuffer(), Ser.GetOffsetInt());
}

void ClientConnecter::Destroy() 
{
	m_ConnectThread->Stop();
	m_RecvServer->Stop();
}