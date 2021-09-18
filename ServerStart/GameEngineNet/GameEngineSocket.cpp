#include "GameEngineSocket.h"
#include <GameEngineDebug.h>

#pragma comment (lib, "ws2_32")
#pragma comment(lib,"mswsock.lib")


// Static Var
// Static Func

// �޸� ����ȭ�� ����
// delete ����.

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
	// ����Ÿ���� �����ڸ��� ������ �����.
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

// �񵿱� ���Ʈ ������ ����� ���
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
// ���� ���Ʈ ������ ����� ���
void GameEngineSocket::CreateSyncAccpet() 
{
	Reset();
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == m_Socket)
	{
		GameEngineDebug::AssertMsg("if (INVALID_SOCKET == ServerListenSocket)");
	}
}
// �񵿱� Ŀ�ؼ� ������ ����� ���
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
		// OSI 7������ TCP�� ������ �ǵ帮�ڴٰ� �ѰŰ�
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
// ���� Ŀ�ؼ� ������ ����� ���
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
		// 127.0.0.1�ּҴ� �������̶��
		// �� ��ǻ�Ϳ� ���� �ּҸ� �ǹ��Ѵ�.
		// ������ ���� �׳� ip ���� ��ǻ�Ϳ� ���� �� �ּҸ� ����ϸ�
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
	// RecvOver���ο� �������� ä�����־����� �ǹ̰� ���ٰ� �����ع�����.

	// �ʱ�ȭ�� �����ָ� ���ú갡 ����� �������� ���Ѵ�.
	RecvOver.Clear();
	RecvBuffer.Clear();

	if (SOCKET_ERROR == WSARecv(
		GetSocket(),
		&RecvBuffer.WsaBuffer, // wsa ������ �迭�� �־��ټ� �ִµ�. 1 Arr[1]
		1, // �־��� ������ ������ �Է�
		&RecvBuffer.Byte, // ���ú�� �������� ���� ���⿡ ��Ƽ� �شٴ� �ǹ�. 
		&RecvBuffer.Flag,  // ���ú굵�� Ư�̻����� ������ �׿� ���� �����͸� ���ش�.
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
	// ������ tcp��쿡�� 3 - way handshake ������ 
	// Send�� Recv�� �Ҷ� ������ ����˴ϴ�.
	// �����Ҷ��� ���ڵ彦��ŷ
	
	// TCP �� Connection-Oriented (���� ����) �������� �Դϴ�. 
	//����, ������ ���� ���¸� "����"�ϱ� ���ؼ��� �ʿ��� ������ �ִµ�
	//�̰��� 4 - way handshake �Դϴ�.
	//�ش� ������ ���Ͽ� sever, client�� tcp ������ �����Ǹ� ������ ����
	//����Ͽ��� ���ҽ��� ������ �Ͼ�� �˴ϴ�.

	// �ϴ� ���⼭ �̰� �ߴٰ� �ܼ��� ������ ���� �ƴϴϱ� ��������.

	if (INVALID_SOCKET != m_Socket)
	{
		// ��� ����� ����
		shutdown(m_Socket, SD_BOTH);
		closesocket(m_Socket);	
		m_Socket = INVALID_SOCKET;
	}

}

void GameEngineSocket::RealDisconnect() 
{
	// ������ �����Ϸ��� �ϴ°̴ϴ�.
	if (INVALID_SOCKET == m_Socket)
	{
		return;
	}

	// ���� �뵵�� ���°Ŷ�
	BOOL Result = TransmitFile(m_Socket, NULL, 0, 0, &RealDisconnectOver, NULL, TF_DISCONNECT | TF_REUSE_SOCKET);

	if (FALSE == Result)
	{
		DWORD Error = GetLastError();

		// io�� ����� �����⸦ ��ٸ��� �۾��̸� �̰�.
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