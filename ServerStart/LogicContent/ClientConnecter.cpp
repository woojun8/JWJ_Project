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
	// ���ʿ����� �� ��Ŷ�� �ް���?
	ClientConnecter* Connecter = &ClientConnecter::GetInst();

	while (true)
	{
		// �˾Ƽ� ���ο��� ���۱��� �� ���� �޴� �ൿ�� �Ѵ�.
		// �ٽ� ���� ���ú�� ���� �˴ϴ�.
		int Len = Connecter->SyncRecv();

		// ��Ŷ�� ������ ������ ����ٴ� �Ҹ��Դϴ�.

		if (-1 == Len)
		{
			return;
		}

		if (0 == Len)
		{
			return;
		}

		// ������ ������ ���� ���ú�
		// �������� ���۸� ������� ó���ع����� ��� 
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

	// ������� ������
	// Recv  �����带 ���⼭ ����̴ϴ�.

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