#include "GameEngineSocket.h"
#include <GameEngineDebug.h>

#pragma comment (lib, "ws2_32")
#pragma comment(lib,"mswsock.lib")


// Static Var
// Static Func

// 메모리 단편화도 막고
// delete 느려.

void GameEngineSocket::OverInit() 
{
	AcceptOver.Type = EngineSocketEvent::ACCPET;
	AcceptOver.m_ParentSocket = this;
	RecvOver.Type = EngineSocketEvent::RECV;
	RecvOver.m_ParentSocket = this;
	SendOver.Type = EngineSocketEvent::SEND;
	SendOver.m_ParentSocket = this;
	DisconnectOver.Type = EngineSocketEvent::DISCONNECT;
	DisconnectOver.m_ParentSocket = this;
	RealDisconnectOver.Type = EngineSocketEvent::REALDISCONNECT;
	RealDisconnectOver.m_ParentSocket = this;

}

// constructer destructer
GameEngineSocket::GameEngineSocket(SOCKETTYPE _Type) : m_Socket(0), m_SocketType(_Type), m_SyncType(SOCKETSYNCTYPE::NONE)
{
	OverInit();
	// 소켓타입이 들어오자마자 소켓을 만든다.
	// Create();
}

GameEngineSocket::~GameEngineSocket() 
{
	Reset();
}
// member Func

void GameEngineSocket::Bind() 
{


	int Result = bind(m_Socket, (const sockaddr*)&m_Address.UserAddIP4, sizeof(m_Address.UserAddIP4));
	if (SOCKET_ERROR == Result)
	{
		DWORD error = GetLastError();
		SocketError();
		return;
	}

}

// 비동기 억셉트 소켓을 만드는 경우
void GameEngineSocket::CreateASyncAccpet() {
	Reset();
	
	m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == m_Socket)
	{
		GameEngineDebug::AssertMsg("if (INVALID_SOCKET == m_Socket)");
	}

	{
		unsigned long Mode = 1;
		int Result = ioctlsocket(m_Socket, FIONBIO, &Mode);

		if (SOCKET_ERROR == Result)
		{
			DWORD Code = GetLastError();
			GameEngineDebug::AssertMsg("if (SOCKET_ERROR == Result)");
			return;
		}

	}

}
// 동기 억셉트 소켓을 만드는 경우
void GameEngineSocket::CreateSyncAccpet() 
{
	Reset();
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == m_Socket)
	{
		GameEngineDebug::AssertMsg("if (INVALID_SOCKET == ServerListenSocket)");
	}
}
// 비동기 커넥션 소켓을 만드는 경우
void GameEngineSocket::CreateASyncConnection() 
{
	Reset();

	m_Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_Socket)
	{
		GameEngineDebug::AssertMsg("if (INVALID_SOCKET == m_Socket)");
	}
	{
		BOOL bNodelay = TRUE;
		// OSI 7계층중 TCP의 영역을 건드리겠다고 한거고
		int errorCode = setsockopt(m_Socket, IPPROTO::IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&bNodelay), sizeof(bNodelay));
		if (SOCKET_ERROR == errorCode)
		{
			closesocket(m_Socket);
			GameEngineDebug::AssertMsg("if (SOCKET_ERROR == errorCode)");
		}
	}
	{
		BOOL bReOpt = TRUE;
		int errorCode = setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&bReOpt), sizeof(bReOpt));
		if (SOCKET_ERROR == errorCode)
		{
			closesocket(m_Socket);
			GameEngineDebug::AssertMsg("if (INVALID_SOCKET == m_Socket)");
		}
	}
	{
		LINGER linOtp;
		linOtp.l_onoff = 1;
		linOtp.l_linger = 0;
		int errorCode = setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<const char*>(&linOtp), sizeof(LINGER));
		if (SOCKET_ERROR == errorCode)
		{
			closesocket(m_Socket);
			GameEngineDebug::AssertMsg("if (INVALID_SOCKET == m_Socket)");
		}
	}
	m_SyncType = SOCKETSYNCTYPE::ASYNC;
}
// 동기 커넥션 소켓을 만드는 경우
void GameEngineSocket::CreateSyncConnection()
{
	Reset();
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (SOCKET_ERROR == m_Socket)
	{
		GameEngineDebug::AssertMsg("if (SOCKET_ERROR == m_Socket)");
	}

	m_SyncType = SOCKETSYNCTYPE::SYNC;
}


//void GameEngineSocket::SyncCreate(const char* _Ip, int _Port, IPTYPE _IPType)
//{
//	if (INVALID_SOCKET == m_Socket)
//	{
//		GameEngineDebug::AssertMsg("if (INVALID_SOCKET == m_Socket)");
//	}
//	m_SyncType = SOCKETSYNCTYPE::SYNC;
//	AddressSetting(_Ip, _Port, _IPType);
//}


void GameEngineSocket::Reset() {
	if (0 != m_Socket)
	{
		closesocket(m_Socket);
		m_Socket = 0;
	}
}

void GameEngineSocket::AddressSetting(const char* _Ip, int _Port, IPTYPE _IPType)
{
	switch (_IPType)
	{
	case IPTYPE::IP4:
	{
		ZeroMemory(&m_Address, sizeof(m_Address));

		m_Address.UserAddIP4.sin_family = AF_INET;
		m_Address.UserAddIP4.sin_port = htons((u_short)_Port);
		// 127.0.0.1주소는 루프백이라고
		// 내 컴퓨터에 로컬 주소를 의미한다.
		// 서버는 보통 그냥 ip 로컬 컴퓨터에 오는 이 주소를 사용하면
		// 119.65.226.249
		if (1 != inet_pton(AF_INET, _Ip, &m_Address.UserAddIP4.sin_addr))
		{
			GameEngineDebug::AssertMsg("if (1 != inet_pton(AF_INET, _Ip, &m_Address.UserAddIP4.sin_addr))");
		}
		break;
	}
	case IPTYPE::IP6:
	{
		break;
	}
	default:
		break;
	}
}

int GameEngineSocket::Connect()
{
	return connect(m_Socket, (const sockaddr*)&m_Address, sizeof(SOCKADDR_IN));

}

int GameEngineSocket::SyncRecv() 
{
	return recv(GetSocket(), RecvBuffer.RealBuffer, sizeof(RecvBuffer.RealBuffer), 0);
}

int GameEngineSocket::SyncSend(const char* DataPtr, int Len)
{
	return send(GetSocket(), DataPtr, Len, 0);
}

void GameEngineSocket::AsyncRecv() 
{
	// RecvOver
	// RecvOver내부에 무슨값이 채워져있었던지 의미가 없다고 생각해버린다.

	// 초기화를 안해주면 리시브가 제대로 동작하지 못한다.
	RecvOver.Clear();
	RecvBuffer.Clear();

	if (SOCKET_ERROR == WSARecv(
		GetSocket(),
		&RecvBuffer.WsaBuffer, // wsa 버퍼의 배열을 넣어줄수 있는데. 1 Arr[1]
		1, // 넣어준 버퍼의 개수를 입력
		&RecvBuffer.Byte, // 리시브된 데이터의 양을 여기에 담아서 준다는 의미. 
		&RecvBuffer.Flag,  // 리시브도중 특이사항이 있을때 그에 대한 데이터를 넣준다.
		&RecvOver,
		nullptr)
		)
	{
		int Error = WSAGetLastError();
		if (WSA_IO_PENDING != Error)
		{
			GameEngineDebug::AssertMsg("if (WSA_IO_PENDING != Error)");
		}
	}
}

void GameEngineSocket::Close()
{
	// 문제가 tcp경우에는 3 - way handshake 때문에 
	// Send나 Recv를 할때 순서가 보장됩니다.
	// 종료할때는 포핸드쉐이킹
	
	// TCP 는 Connection-Oriented (연결 지향) 프로토콜 입니다. 
	//따라서, 논리적인 접속 상태를 "해제"하기 위해서도 필요한 과정이 있는데
	//이것이 4 - way handshake 입니다.
	//해당 과정을 통하여 sever, client는 tcp 연결이 해제되며 연결을 위해
	//사용하였던 리소스의 정리가 일어나게 됩니다.

	// 일단 여기서 이걸 했다고 단순히 끝나는 것은 아니니까 조심하자.

	if (INVALID_SOCKET != m_Socket)
	{
		// 모든 기능을 종료
		shutdown(m_Socket, SD_BOTH);
		closesocket(m_Socket);	
		m_Socket = INVALID_SOCKET;
	}

}

void GameEngineSocket::RealDisconnect() 
{
	// 소켓을 재사용하려고 하는겁니다.
	if (INVALID_SOCKET == m_Socket)
	{
		return;
	}

	// 끊는 용도로 쓰는거라
	BOOL Result = TransmitFile(m_Socket, NULL, 0, 0, &RealDisconnectOver, NULL, TF_DISCONNECT | TF_REUSE_SOCKET);

	if (FALSE == Result)
	{
		DWORD Error = GetLastError();

		// io가 제대로 끝나기를 기다리는 작업이면 이거.
		if (ERROR_IO_PENDING != Error)
		{
			GameEngineDebug::AssertMsg("BOOL Result = TransmitFile(m_Socket, NULL, 0, 0, &RealDisconnectOver, NULL, TF_DISCONNECT | TF_REUSE_SOCKET)");
		}
	}
}

void GameEngineSocket::ReCreateASyncConnection()
{
	Close();
	CreateASyncConnection();
}

int GameEngineSocket::ConstSyncSend(const char* DataPtr, int Len) const
{
	return send(GetSocket(), DataPtr, Len, 0);
}