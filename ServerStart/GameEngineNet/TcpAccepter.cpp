#include "TcpAccepter.h"
#include <GameEngineDebug.h>
#include "TcpConnecter.h"

// Static Var
// Static Func

// constructer destructer
TcpAccepter::TcpAccepter() : GameEngineSocket(SOCKETTYPE::TCP), m_ListenCount(-1), m_IsAcceptLoop(true)
{

}

TcpAccepter::~TcpAccepter() 
{

}
// member Func

bool TcpAccepter::listenSetting(int _Port, SOCKETSYNCTYPE _Type, const char* _Ip, int _ListenCount , IPTYPE _IPType )
{
	// ����ڵ带 ���ƴ��� ���ذ� �ǳ���?
	if (0 != GetSocket())
	{
		return true;
	}

	m_ListenCount = _ListenCount;

	switch (_Type)
	{
	case SOCKETSYNCTYPE::SYNC:
		CreateSyncAccpet();
		AddressSetting(_Ip, _Port, _IPType);
		break;
	case SOCKETSYNCTYPE::ASYNC:
		CreateASyncAccpet();
		AddressSetting(_Ip, _Port, _IPType);
		break;
	case SOCKETSYNCTYPE::NONE:
	default:
		GameEngineDebug::AssertMsg("SOCKETSYNCTYPE::NONE:");
		break;
	}
	
	Bind();

	if (SOCKET_ERROR == listen(GetSocket(), _ListenCount))
	{
		GameEngineDebug::AssertMsg("if (SOCKET_ERROR == listen(GetSocket(), _ListenCount))");
	}

	return true;
}

bool TcpAccepter::SyncAccept()
{
	if (0 == GetSocket())
	{
		GameEngineDebug::AssertMsg("if (0 == GetSocket())");
	}

	GameEngineSocketAddress Addr;
	int AddrSize = sizeof(Addr.UserAddIP4);

	SOCKET ConnectSocket = accept(GetSocket(), (sockaddr*)&Addr.UserAddIP4, &AddrSize);

	std::shared_ptr<TcpConnecter> NewConnecter(new TcpConnecter());

	NewConnecter->AcceptCreate(ConnectSocket, Addr);

	// ������ �׼��Ͱ� ��� �ְ� ����?
	// �̳༮�� ����ϸ� 1���� �����͸� �⺻�����ڷ� �׳� ������̴�.
	m_ConnectSocket.push_back(NewConnecter);

	// ���⼭ ���ú� �ɾ���� 
	// � ��Ŷ�� ������ �𸣴ϱ�.

	if (nullptr != m_pAcceptEvent)
	{
		m_pAcceptEvent(std::shared_ptr<TcpAccepter>(this), NewConnecter);
	}
	return true;
}

void TcpAccepter::AcceptLoop(AcceptEvent _Event /*= nullptr*/)
{
	m_pAcceptEvent = _Event;

	while (m_IsAcceptLoop)
	{
		if (SOCKET_ERROR == GetSocket())
		{
			m_IsAcceptLoop = false;
			break;
		}
		Accept();
	}
}

void TcpAccepter::Accept()
{
	switch (GetSyncType())
	{
	case SOCKETSYNCTYPE::SYNC:
		SyncAccept();
		break;
	case SOCKETSYNCTYPE::ASYNC:
		// ASyncAccept();
		break;
	default:
		break;
	}
}

