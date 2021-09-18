#include "TcpConnecter.h"
#include "TcpAccepter.h"
#include <GameEngineDebug.h>

// constructer destructer
TcpConnecter::TcpConnecter()  : GameEngineSocket(SOCKETTYPE::TCP)
{

}

TcpConnecter::~TcpConnecter() 
{

}
// member Func

void TcpConnecter::AcceptCreate(SOCKET _ConnectSocket, const GameEngineSocketAddress& _Value) 
{
	SetSocket(_ConnectSocket);
	SetAddress(_Value);
}

int TcpConnecter::Connect()
{
	// SyncCreate(_Ip, _Port, _IPType);
	// 부모쪽 함수 호출하려면 이렇게 해야합니다.
	return GameEngineSocket::Connect();
}

BOOL TcpConnecter::AcceptExConnecter()
{
	if (nullptr == m_ListenSocket)
	{
		GameEngineDebug::AssertMsg("if (nullptr == m_ListenSocket)");
	}

	GetAcceptOverRef().Clear();

	DWORD dwByte = 0;
	BOOL Check = AcceptEx(m_ListenSocket->GetSocket(), GetSocket(), static_cast<void*>(&GetAddressRef()), 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwByte, &GetAcceptOverRef());

	if (Check == TRUE)
	{
		return TRUE;
	}
	int Error = WSAGetLastError();
	if (ERROR_IO_PENDING != Error)
	{
		return FALSE;
	}

	return TRUE;
}

