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
	// 방어코드를 왜쳤는지 이해가 되나요?
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

	// 소켓을 액셉터가 들고 있게 되죠?
	// 이녀석을 사용하면 1개의 데이터를 기본생정자로 그냥 만든것이다.
	m_ConnectSocket.push_back(NewConnecter);

	// 여기서 리시브 걸어놓고 
	// 어떤 패킷을 보낼지 모르니까.

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

