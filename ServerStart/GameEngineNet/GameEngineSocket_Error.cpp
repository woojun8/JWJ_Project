#include "GameEngineSocket.h"
#include <GameEngineDebug.h>
#include <map>

std::map<int, const char* > SocketErrorMap;

void GameEngineSocket::SocketError()
{
	GameEngineDebug::AssertMsg(SocketErrorMap[WSAGetLastError()]);
}

void GameEngineSocket::SocketErrorInit()
{
	//SocketErrorMap[WSA_INVALID_HANDLE] = "������ �̺�Ʈ ��ü �ڵ��� �߸��Ǿ����ϴ�.		���� ���α׷��� �̺�Ʈ ��ü�� ����Ϸ��������� ������ �ڵ��� ��ȿ���� �ʽ��ϴ�.";
	//SocketErrorMap[WSA_NOT_ENOUGH_MEMORY] = "��� ������ �޸𸮰� �����մϴ�. ���� ���α׷��� SocketErrorMap[WindoSocketErrorMap[Ws ��ɿ� ���� ���εǴ� SocketErrorMap[WindoSocketErrorMap[Ws ���� ����� ����߽��ϴ�.SocketErrorMap[WindoSocketErrorMap[Ws ����� �ʿ��� �޸� ���ҽ��� �������� ��Ÿ���ϴ�.";
	//SocketErrorMap[WSA_INVALID_PARAMETER] = "�ϳ� �̻��� �Ű� ������ �߸��Ǿ����ϴ�. ���� ���α׷��� SocketErrorMap[WindoSocketErrorMap[Ws ��ɿ� ���� ���εǴ� SocketErrorMap[WindoSocketErrorMap[Ws ���� ����� ����߽��ϴ�.SocketErrorMap[WindoSocketErrorMap[Ws ����� �ϳ� �̻��� �Ű� ������ ������ ������ ��Ÿ���ϴ�.";
	//SocketErrorMap[WSA_OPERATION_ABORTED] = "��ģ �۾��� �ߴܵǾ����ϴ�.		���� ��� �Ǵ� SocketErrorMap[WSAIoctl ���� SIO_FLUSH ��� �������� ���� ��ø �� �۾��� ��ҵǾ����ϴ� .
	//	SocketErrorMap[WSA_IO_INCOMPLETE
	//	
	//	��ø �� I / O �̺�Ʈ ��ü�� ��ȣ ���°� �ƴմϴ�.
	//	���ø����̼��� ���� �Ϸ���� ���� �ߺ� �۾��� ���¸� Ȯ���Ϸ����߽��ϴ�.���� ��忡�� SocketErrorMap[WSAGetOverlappedResult(fSocketErrorMap[Wait �÷��װ� FALSE�� ���� ��)�� ����Ͽ� ��ø �� �۾��� ���� �Ϸ�Ǿ����� Ȯ���ϴ� ���� ���α׷��� �۾��� �Ϸ� �� �������� ���� �ڵ带�޽��ϴ�.
	//	SocketErrorMap[WSA_IO_PENDING
	//	
	//	�ߺ� �� �۾��� ���߿� �Ϸ�˴ϴ�.
	//	���� ���α׷��� ��� �Ϸ� �� ������ �ߺ� �۾��� �����߽��ϴ�.�۾��� �Ϸ�Ǹ� ���߿� �Ϸ� ǥ�ð� �����˴ϴ�.
	//	SocketErrorMap[WSAEINTR
	//	
	//	�Լ� ȣ���� �ߴܵǾ����ϴ�.
	//	SocketErrorMap[WSACancelBlockingCall ȣ��� ���� ���� �۾��� �ߴ� �Ǿ����ϴ� .
	//	SocketErrorMap[WSAEBADF
	//	
	//	���� �ڵ��� ��ȿ���� �ʽ��ϴ�.
	//	������ ���� �ڵ��� ��ȿ���� �ʽ��ϴ�.
	//	SocketErrorMap[WSAEACCES
	//	
	//	������ �źεǾ����ϴ�.
	//	�׼��� ���ѿ� ���� ���� �� ������� ���Ͽ� �׼����Ϸ����߽��ϴ�.���� ��� setsockopt(SO_BROADCAST)�� ����Ͽ� ��ε� ĳ��Ʈ ������ �������� �ʰ� sendto�� ��ε� ĳ��Ʈ �ּҸ� ����ϴ� �� �Դϴ�.SocketErrorMap[WSAEACCES ������ �� �ٸ� ������ ������ ���ε� ����� ȣ�� �� ��(SP �̻��� ��ġ�� SocketErrorMap[WindoSocketErrorMap[Ws NT .����) �ٸ� ���� ���α׷�, ���� �Ǵ� Ŀ�� ��� ����̹��� �ܵ� �׼��� �������� ������ �ּҿ� ���ε��Ǳ� �����Դϴ�.�̷��� �ܵ� �׼����� SP �̻��� ��ġ�� SocketErrorMap[WindoSocketErrorMap[Ws NT .�� ���ο� ����̸� SO_EXCLUSIVEADDRUSE �ɼ� �� ����Ͽ� �����˴ϴ� .

	//	SocketErrorMap[WSAEFAULT
	//	
	//	�߸��� �ּ��Դϴ�.
	//	�ý����� ȣ���� ������ �μ��� ����Ϸ��� �� �� �߸��� ������ �ּҸ� �����߽��ϴ�.�� ������ ���� ���α׷��� �߸��� ������ ���� �����ϰų� ���� ���̰� �ʹ� ���� ��� �߻��մϴ�.���� ���, sockaddr ���� �� �μ��� ���̰� sizeof(sockaddr)���� �� ����.
	//	SocketErrorMap[WSAEINVAL
	//	
	//	�߸��� �μ��Դϴ�.
	//	�Ϻ� �߸��� �μ��� �����Ǿ����ϴ�(�� : setsockopt �Լ��� �߸��� ���� ����).� ��쿡�� ������ ���� ����(�� : ���� ������� �ʴ� ���Ͽ��� accept ȣ��) �� �����ϱ⵵ �մϴ�.
	//	SocketErrorMap[WSAEMFILE
	//	
	//	���� ������ �ʹ� �����ϴ�.
	//	���� ������ �ʹ� �����ϴ�.�� �������� ����, ���μ��� �Ǵ� ������ �� ��� ������ �ִ� ���� �ڵ� �������� �� �ֽ��ϴ�.
	//	SocketErrorMap[WSAESocketErrorMap[WOULDBLOCK
	//	
	//	���ҽ��� �Ͻ������� ����� �� �����ϴ�.
	//	�� ������ ��� �Ϸ� �� ������ �� ���ŷ ���Ͽ� ���� �۾�(�� : ���Ͽ��� ���� �����Ͱ� ��⿭�� �߰����� ���� ��� recv) ���� ��ȯ�˴ϴ�.ġ�������� ���� �����̸� ���߿� �۾��� �ٽ� �õ��ؾ��մϴ�.SocketErrorMap[WSAESocketErrorMap[WOULDBLOCK �� �� ���ŷ SOCK_STREAM ���Ͽ��� connect �� ȣ�� �� ����κ���Ǵ� ���� �����Դϴ�.������ ���� �Ƿ��� �ణ�� �ð��� ����ؾ��ϱ� �����Դϴ�.
	//	SocketErrorMap[WSAEINPROGRESS
	//	
	//	���� �۾��� ���� ���Դϴ�.
	//	���� �۾��� ���� ���� ���Դϴ�.SocketErrorMap[WindoSocketErrorMap[Ws ������ �۾� �� �Ǵ� ������ �� ���� ���� �۾� �� ó�� �� �� �ֵ��� ����ϸ� �ٸ� �Լ� ȣ���� ����Ǹ�(�� �Ǵ� �ٸ� ������ �����ϴ��� ���ο� �������) SocketErrorMap[WSAEINPROGRESS ������ �Բ� �Լ��� �����մϴ�.
	//	SocketErrorMap[WSAEALREADY
	//	
	//	�۾��� �̹� ���� ���Դϴ�.
	//	�۾��� �̹� �������� �� ���ŷ ���Ͽ��� �õ��Ǿ����ϴ�.��, �̹� �������� �� ���ŷ ���Ͽ��� �� ��°�� connect�� ȣ�� �ϰų� �̹� ��� �Ǵ� �Ϸ�� �񵿱� ��û(SocketErrorMap[WSAAsyncGetXbyY)�� ����߽��ϴ�.
	//	SocketErrorMap[WSAENOTSOCK
	//	
	//	�� ���Ͽ����� ���� �۾�.
	//	������ �ƴ� �׸񿡼� �۾��� �õ��߽��ϴ�.���� �ڵ� �Ű� ������ ��ȿ�� ������ �������� �ʾҰų� select �� ��� fd_set �� ����� ��ȿ���� �ʽ��ϴ�.
	//	SocketErrorMap[WSAEDESTADDRREQ
	//	
	//	������ �ּҰ� �ʿ��մϴ�.
	//	������ �۾����� �ʼ� �ּҰ� �����Ǿ����ϴ�.���� ���, ADDR_ANY�� ���� �ּҷ� sendto �� ȣ�� �Ǹ��� ������ ���ϵ˴ϴ� .
	//	SocketErrorMap[WSAEMSGSIZE
	//	
	//	�޽����� �ʹ� ��ϴ�.
	//	������ �׷� ���Ͽ��� ���� �޽����� ���� �޽��� ���� �Ǵ� �ٸ� ��Ʈ��ũ ���Ѻ��� ũ�ų� ������ �׷��� �����ϴ� �� ��� �� ���۰� ������ �׷� ��ü���� �۽��ϴ�.
	//	SocketErrorMap[WSAEPROTOTYPE
	//	
	//	���Ͽ� ���� �������� �߸��� �����Դϴ�.
	//	��û �� ���� ������ �ǹ̸� �������� �ʴ� ���� �Լ� ȣ�� �� ���������� �����Ǿ����ϴ�.���� ���, ARPA ���ͳ� UDP ���������� ���� ���� SOCK_STREAM���� ������ �� �����ϴ�.
	//	SocketErrorMap[WSAENOPROTOOPT
	//	
	//	�߸��� �������� �ɼ��Դϴ�.
	//	�� �� ���ų� ��ȿ���� �ʰų� �������� �ʴ� �ɼ� �Ǵ� ������ getsockopt �Ǵ� setsockopt ȣ�� �� �����Ǿ����ϴ� .
	//	SocketErrorMap[WSAEPROTONOS ����
	//	
	//	���������� �������� �ʽ��ϴ�.
	//	��û �� ���������� �ý��ۿ� �������� �ʾҰų� �̿� ���� ������ �����ϴ�.���� ���, ���� ȣ���� SOCK_DGRAM ������ ��û������ ��Ʈ�� ���������� �����մϴ�.
	//	SocketErrorMap[WSAESOCKTNOSUPPORT
	//	
	//	���� ������ �������� �ʽ��ϴ�.
	//	������ ���� ������ ���� �������� �ּ� �迭�� �����ϴ�.���� ���, ���� ȣ�� ���� ������ ���� SOCK_RASocketErrorMap[W�� ������ �� ������ ������ SOCK_RASocketErrorMap[W ������ ���� �������� �ʽ��ϴ�.
	//	SocketErrorMap[WSAEOPNOTSUPP
	//	
	//	�������� �ʴ� �۾��Դϴ�.
	//	�õ��� �۾��� ���� �� ��ü ������ ���� �������� �ʽ��ϴ�.�Ϲ��������� �۾��� ������ ������ ���Ͽ� ���� ���� �����ڰ� ������ �׷� ���Ͽ��� ������ �����Ϸ��� �� �� �߻��մϴ�.
	//	SocketErrorMap[WSAEPFNOSUPPORT
	//	
	//	�������� ��ǰ���� �������� �ʽ��ϴ�.
	//	�������� ��ǰ���� �ý��ۿ� �������� �ʾҰų� �̿� ���� ������ �����ϴ�.�� �޽����� SocketErrorMap[WSAEAFNOSUPPORT�� �ణ �ٸ� �ǹ̸� �����ϴ�.�׷��� ��κ��� ��� ��ȣ ��ȯ�� �����ϸ� �̷��� �޽��� �� �ϳ��� ��ȯ�ϴ� ��� SocketErrorMap[WindoSocketErrorMap[Ws ���� �Լ��� SocketErrorMap[WSAEAFNOSUPPORT�� �����մϴ�.
	//	SocketErrorMap[WSAEAFNOSUPPORT
	//	
	//	�������� ��ǰ������ �������� �ʴ� �ּ� ��ǰ���Դϴ�.
	//	��û�� �������ݰ� ȣȯ���� �ʴ� �ּҰ� ���Ǿ����ϴ�.��� ������ ������ �ּ� �迭(��, ���ͳ� ���������� ��� AF_INET) �� �Ϲ� �������� ����(��, SOCK_STREAM)���� �����˴ϴ�.���� ȣ�� ���� �߸��� ���������� ��� ������ ��û �ǰų� ���� �� �߸��� �йи��� �ּҰ� ��� �� ���(�� : sendto) �� ������ ��ȯ�˴ϴ� .
	//	SocketErrorMap[WSAEADDRINUSE
	//	
	//	�̹� ������� �ּ��Դϴ�.
	//	�Ϲ������� �� ���� �ּ�(�������� / IP �ּ� / ��Ʈ)�� �� ���� ����� �� �ֽ��ϴ�.�� ������ ���� ���α׷� �� ���� ���Ͽ� �̹� ��� �� IP �ּ� / ��Ʈ �Ǵ� ����� ������ ���� ���� �Ǵ� ���� �ݴ� �������ִ� ���Ͽ� ���� �� ���ε� �Ϸ��� �õ��ϴ� ��� �߻��մϴ�.���� ������ ������ ��Ʈ ��ȣ �� ���ε� �ؾ��ϴ� ���� ���ø����̼��� ��� setsockopt(SO_REUSEADDR) ����� ����Ͻʽÿ�.Ŭ���̾�Ʈ ���� ���α׷��� �Ϲ������� bind �� ȣ�� �� �ʿ䰡 �����ϴ�.connect �� ������� �ʴ� ��Ʈ�� �ڵ����� �����մϴ�.���ε� �� �����ϵ� ī�� �ּ�(ADDR_ANY ����)�� ȣ��Ǹ� Ư�� �ּҰ� Ŀ�� �� ������ SocketErrorMap[WSAEADDRINUSE ������ ���� �� �� �ֽ��ϴ�.�̴� connect, listen, SocketErrorMap[WSAConnect �Ǵ� SocketErrorMap[WSAJoinLeaf�� �����Ͽ� ���߿� �ٸ� �Լ��� ȣ�� �� �� �߻��� �� �ֽ��ϴ� .
	//	SocketErrorMap[WSAEADDRNOTAVAIL
	//	
	//	��û�� �ּҸ� �Ҵ� �� �� �����ϴ�.
	//	��û�� �ּҴ� �ش� ���ؽ�Ʈ���� ��ȿ���� �ʽ��ϴ�.�̴� �Ϲ������� ���� ��ǻ�Ϳ� ��ȿ���� ���� �ּ� �� ���ε� �Ϸ��� �õ��� ���� �߻� �մϴ�.���� �ּ� �Ǵ� ��Ʈ�� ���� ��ǻ��(�� : �ּ� �Ǵ� ��Ʈ )�� ��ȿ���� ���� ��� connect, sendto, SocketErrorMap[WSAConnect, SocketErrorMap[WSAJoinLeaf �Ǵ� SocketErrorMap[WSASendTo ���� �߻��� ���� �ֽ��ϴ� .
	//	SocketErrorMap[WSAENETDOSocketErrorMap[WN
	//	
	//	��Ʈ��ũ�� �ٿ�Ǿ����ϴ�.
	//	���� �۾����� ���� ��Ʈ��ũ�� �߻��߽��ϴ�.�̴� ��Ʈ��ũ �ý���(��, SocketErrorMap[WindoSocketErrorMap[Ws ���� DLL�� ����Ǵ� �������� ����), ��Ʈ��ũ �������̽� �Ǵ� ���� ��Ʈ��ũ ��ü�� �ɰ��� ������ ��Ÿ�� �� �ֽ��ϴ�.
	//	SocketErrorMap[WSAENETUNREACH
	//	
	//	��Ʈ��ũ�� ������ �� �����ϴ�.
	//	������ ������ ��Ʈ��ũ�� ���� �۾��� �õ��߽��ϴ�.�̰��� �Ϲ������� ���� ����Ʈ��� ���� ȣ��Ʈ�� ���� �� ��θ� ���� ������ �ǹ��մϴ�.
	//	SocketErrorMap[WSAENETRESET
	//	
	//	�缳���� ��Ʈ��ũ ������ ���������ϴ�.
	//	�۾��� ����Ǵ� ���� ���и� �����ϴ� ���� ���� Ȱ������ ���� ������ ���������ϴ�.�̹� ������ ���ῡ�� SO_KEEPALIVE �� �����Ϸ��� �õ��ϴ� ��� setsockopt�� ���� ��ȯ �� ���� �ֽ��ϴ� .
	//	SocketErrorMap[WSAECONNABORTED
	//	
	//	����Ʈ����� ���� ������ �ߴܵǾ����ϴ�.
	//	������ ���� �ð� �ʰ� �Ǵ� �������� ������ ���� ȣ��Ʈ ��ǻ���� ����Ʈ��� ���� ������ ������ �ߴܵǾ����ϴ�.
	//	SocketErrorMap[WSAECONNRESET
	//	
	//	�Ǿ ������ �缳���߽��ϴ�.
	//	���� ������ ���� ȣ��Ʈ�� ���� ������ �������ϴ�.�̴� �Ϲ������� ���� ȣ��Ʈ�� �Ǿ� ���� ���α׷��� ���ڱ� �����ǰų�, ȣ��Ʈ�� ����õǰų�, ȣ��Ʈ �Ǵ� ���� ��Ʈ��ũ �������̽��� ��Ȱ��ȭ�ǰų�, ���� ȣ��Ʈ�� �ϵ� �ݱ⸦ ����ϴ� ��� �߻��մϴ�(���� ȣ��Ʈ �� SO_LINGER �ɼǿ� ���� �ڼ��� ���� �� setsockopt ����).����).�� ������ �ϳ� �̻��� �۾��� �������� ���� ���и� �����ϴ� ���� ���� Ȱ������ ���� ������ ������ ��쿡�� �߻��� �� �ֽ��ϴ�.���� ���̴� �۾��� SocketErrorMap[WSAENETRESET���� �����մϴ�.SocketErrorMap[WSAECONNRESET���� �ļ� �۾��� �����մϴ�.
	//	SocketErrorMap[WSAENOBUFS
	//	
	//	��� ������ ���� ������ �����ϴ�.
	//	�ý��ۿ� ����� ���� ������ �����ϰų� ť�� ���� ���� ���Ͽ��� �۾��� ���� �� �� �����ϴ�.
	//	SocketErrorMap[WSAEISCONN
	//	
	//	������ �̹� ����Ǿ����ϴ�.
	//	�̹� ����� ���Ͽ��� ���� ��û�� �̷�������ϴ�.�Ϻ� ���� ������ ����� SOCK_DGRAM ���Ͽ��� sendto �� ȣ�� �� ��� ������ ������ ��ȯ �մϴ�(SOCK_STREAM ������ ��� sendto �� to �Ű� ���� �� ���� ��).�ٸ� �����������̸� �չ��� �� �߻����� ����մϴ�.
	//	SocketErrorMap[WSAENOTCONN
	//	
	//	������ ������� �ʾҽ��ϴ�.
	//	������ ������� �ʾҰ�(sendto�� ����Ͽ� ������ �׷� ���Ͽ��� ���� ��) �ּҰ� ���� ���� �ʾұ� ������ ������ ���� �Ǵ� ���� ��û�� ������ �ʾҽ��ϴ�.�ٸ� ������ �۾����� ������ ��ȯ �� �� �ֽ��ϴ�.���� ���, ������ �缳�� �� ��� setsockopt ���� SO_KEEPALIVE �� �ֽ��ϴ�.
	//	SocketErrorMap[WSAESHUTDOSocketErrorMap[WN
	//	
	//	���� ���� �� ���� �� �����ϴ�.
	//	������ ���� ���� ȣ�� �� �ش� �������� �̹� ���� �Ǿ��� ������ ������ ���� �Ǵ� ���� ��û�� ������ �ʾҽ��ϴ�.shutdoSocketErrorMap[Wn �� ȣ�� �ϸ� ������ �κ� �ݱⰡ ��û�Ǹ�, �̴� �۽� �Ǵ� ���� �Ǵ� �� �� �ߴܵǾ��ٴ� ��ȣ�Դϴ�.
	//	SocketErrorMap[WSAETOOMANYREFS
	//	
	//	������ �ʹ� �����ϴ�.
	//	�Ϻ� Ŀ�� ��ü�� ���� ������ �ʹ� �����ϴ�.
	//	SocketErrorMap[WSAETIMEDOUT
	//	
	//	���� �ð��� �ʰ��Ǿ����ϴ�.
	//	���� �ð��� ������ �����ڰ� ����� �������� �ʾ� ���� �õ��� �����߰ų� ����� ȣ��Ʈ�� �������� �ʾ� ������ �������� �ʾҽ��ϴ�.
	//	SocketErrorMap[WSAECONNREFUSED
	//	
	//	������ �źεǾ����ϴ�.
	//	��� ��ǻ�Ͱ� ������ �ź��߱� ������ ������ �� �����ϴ�.�̴� �Ϲ������� �ܺ� ȣ��Ʈ���� ��Ȱ�� ���� �� ����, �� �������� ���� ���� ���α׷��̾��� ���񽺿� �����Ϸ��� �� �� �߻��մϴ�.
	//	SocketErrorMap[WSAELOOP
	//	
	//	�̸��� ���� �� �� �����ϴ�.
	//	�̸��� ���� �� �� �����ϴ�.
	//	SocketErrorMap[WSAENAMETOOLONG
	//	
	//	�̸��� �ʹ� ��ϴ�.
	//	�̸� ���� ��� �Ǵ� �̸��� �ʹ� ��ϴ�.
	//	SocketErrorMap[WSAEHOSTDOSocketErrorMap[WN
	//	
	//	ȣ��Ʈ�� �ٿ�Ǿ����ϴ�.
	//	��� ȣ��Ʈ�� �ٿ�Ǿ� ���� �۾��� �����߽��ϴ�.���� �۾����� ���� ȣ��Ʈ�� �߻��߽��ϴ�.���� ȣ��Ʈ���� ��Ʈ��ŷ Ȱ���� ���۵��� �ʾҽ��ϴ�.�̷��� ������ SocketErrorMap[WSAETIMEDOUT ������ ǥ�� �� ���ɼ��� �����ϴ�.
	//	SocketErrorMap[WSAEHOSTUNREACH
	//	
	//	ȣ��Ʈ ��ΰ� �����ϴ�.
	//	������ ������ ȣ��Ʈ�� ���� �۾��� �õ��߽��ϴ�.SocketErrorMap[WSAENETUNREACH�� �����Ͻʽÿ�.
	//	SocketErrorMap[WSAENOTEMPTY
	//	
	//	���丮�� ��� ���� �ʽ��ϴ�.
	//	��� ���� ���� ���丮�� ���� �� �� �����ϴ�.
	//	SocketErrorMap[WSAEPROCLIM
	//	
	//	���μ����� �ʹ� �����ϴ�.
	//	SocketErrorMap[WindoSocketErrorMap[Ws ���� �������� ���ÿ� ����� ���ִ� ���� ���α׷� ���� ���������� �� �ֽ��ϴ�.���ѿ� �����ϸ� SocketErrorMap[WSAStartup ���� ������ �Բ� ���� �� �� �ֽ��ϴ�.
	//	SocketErrorMap[WSAEUSERS
	//	
	//	����� �Ҵ緮�� �ʰ��Ǿ����ϴ�.
	//	����� �Ҵ緮�� �����߽��ϴ�.
	//	SocketErrorMap[WSAEDQUOT
	//	
	//	��ũ �Ҵ緮�� �ʰ�.
	//	��ũ �Ҵ緮�� �����߽��ϴ�.
	//	SocketErrorMap[WSAESTALE
	//	
	//	������ ���� �ڵ� ����.
	//	���� �ڵ� ������ �� �̻� ����� �� �����ϴ�.
	//	SocketErrorMap[WSAEREMOTE
	//	
	//	�׸��� �����Դϴ�.
	//	�׸��� ���ÿ��� ����� �� �����ϴ�.
	//	SocketErrorMap[WSASYSNOTREADY
	//	
	//	��Ʈ��ũ ���� �ý����� ����� �� �����ϴ�.
	//	�� ������ ��Ʈ��ũ ���񽺸� �����ϴ� �� ����ϴ� �⺻ �ý����� ���� ����� �� ���� ������ SocketErrorMap[WindoSocketErrorMap[Ws ���� ������ ���� �۵� �� ������ ��� SocketErrorMap[WSAStartup�� ���� ��ȯ�˴ϴ�.����ڴ� ���� ������ Ȯ���ؾ��մϴ�.
	//	������ SocketErrorMap[WindoSocketErrorMap[Ws ���� DLL ������ ���� ��ο� �ִ��� Ȯ���մϴ�.
	//	�� �̻��� SocketErrorMap[WindoSocketErrorMap[Ws ���� ������ ���ÿ� ����Ϸ������� �ʽ��ϴ�.�ý��ۿ� �� �̻��� SocketErrorMap[Winsock DLL���ִ� ��� ����� ù ��° DLL�� ����ε� �� ��Ʈ��ũ ���� �ý��ۿ� ������ �� Ȯ���Ͻʽÿ�.
	//	�ʿ��� ��� ���� ��Ұ� ���� �ùٸ��� ��ġ �� �����Ǿ����� Ȯ���ϱ����� SocketErrorMap[WindoSocketErrorMap[Ws ���� ���� ����
	//	SocketErrorMap[WSAVERNOTSUPPORTED
	//	
	//	SocketErrorMap[Winsock.dll ������ ������ ������ϴ�.
	//	���� SocketErrorMap[WindoSocketErrorMap[Ws ���� ������ ���� ���α׷����� ��û�� SocketErrorMap[WindoSocketErrorMap[Ws ���� ��� ������ �������� �ʽ��ϴ�.���� SocketErrorMap[WindoSocketErrorMap[Ws ���� DLL ���Ͽ� �׼����ϰ� ���� ������ Ȯ���Ͻʽÿ�.
	//	SocketErrorMap[WSANOTINITIALISED
	//	
	//	�������� SocketErrorMap[WSAStartup�� ���� ������� �ʾҽ��ϴ�.
	//	��� ���� ���α׷��� ȣ����� SocketErrorMap[WSAStartup�� �Ǵ� SocketErrorMap[WSAStartup �Լ��� �����߽��ϴ�.���� ���α׷��� ���� Ȱ�� �۾��� �������� ���� ���Ͽ� �׼����ϰ� �ְų�(��, �۾����� ������ �����Ϸ��� ��) SocketErrorMap[WSACleanup �� �ʹ� ���� ȣ��Ǿ��� �� �ֽ��ϴ�.
	//	SocketErrorMap[WSAEDISCON
	//	
	//	���� ���ᰡ ���� ���Դϴ�.
	//	���� ����ڰ� ���� ���� �������� ���������� ��Ÿ ���� ���� SocketErrorMap[WSARecv �� SocketErrorMap[WSARecvFrom �� ���� ��ȯ�˴ϴ� .
	//	SocketErrorMap[WSAENOMORE
	//	
	//	�� �̻� ����� �����ϴ�.
	//	SocketErrorMap[WSALookupServiceNext �Լ� �� �� �̻� ����� ��ȯ �� �� �����ϴ� .
	//	SocketErrorMap[WSAECANCELLED
	//	
	//	��ȭ�� ��ҵǾ����ϴ�.
	//	�� ȣ���� ��� ó���Ǵ� ���� SocketErrorMap[WSALookupServiceEnd �Լ��� ȣ���߽��ϴ�.��ȭ�� ��ҵǾ����ϴ�.
	//	SocketErrorMap[WSAEINVALIDPROCTABLE
	//	
	//	���� ���� ȣ�� ���̺��� ��ȿ���� �ʽ��ϴ�.
	//	���� ������ ���� ���� ȣ�� ���̺��� �߸��Ǿ����ϴ�.���� �����ڰ� ��¥ ���� ���� ���̺��� SocketErrorMap[Ws_.dll�� ��ȯ�߽��ϴ�.�̴� �Ϲ������� �ϳ� �̻��� �Լ� �����Ͱ� NULL �� ��� �߻��մϴ� .
	//	SocketErrorMap[WSAEINVALIDPROVIDER
	//	
	//	���� ���� ��ü�� �߸��Ǿ����ϴ�.
	//	��û�� ���� ���� ��ü�� �߸��Ǿ����ϴ�.�� ������ ������ �������� �׸��� ã�� ������ ��� SocketErrorMap[WSCGetProviderInfo �� SocketErrorMap[WSCGetProviderInfo �Լ��� ���� ��ȯ�˴ϴ�.�� ������ ���� �����ڰ� .�� �ƴ� ���� ��ȣ�� ��ȯ �� ��쿡�� ��ȯ�˴ϴ�.
	//	SocketErrorMap[WSAEPROVIDERFAILEDINIT
	//	
	//	���� ���� ��ü�� �ʱ�ȭ���� ���߽��ϴ�.
	//	��û�� ���� ���� ��ü���ε��ϰų� �ʱ�ȭ �� �� �����ϴ�.�� ������ ���� �������� DLL���ε� �� �� ���ų�(LoadLibrary ����) �������� SocketErrorMap[WSPStartup �Ǵ� NSPStartup �Լ��� ������ ��쿡 ��ȯ �˴ϴ�.
	//	SocketErrorMap[WSASYSCALLFAILURE
	//	
	//	�ý��� ȣ�� ����.
	//	���� �����ؼ��� �ȵǴ� �ý��� ȣ���� �����߽��ϴ�.�پ��� ���ǿ��� ��ȯ�Ǵ� �Ϲ� ���� �ڵ��Դϴ�.
	//	���� �����ؼ��� �ȵǴ� �ý��� ȣ���� ���� �� �� ��ȯ�˴ϴ�.���� ��� SocketErrorMap[WaitForMultipleEvents�� ���� ȣ���� �����ϰų� ������Ʈ�� �Լ� �� �ϳ��� �������� / ���� �����̽� īŻ�α׸� �����ϴ� �� �����ϴ� ����Դϴ�.
	//	�����ڰ� SUCCESS�� ��ȯ���� �ʰ� Ȯ�� ���� �ڵ带 �������� ���� �� ��ȯ�˴ϴ�.���� ���� ��ü ���� ������ ��Ÿ�� �� �ֽ��ϴ�.
	//	SocketErrorMap[WSASERVICE_NOT_FOUND
	//	
	//	���񽺸� ã�� �� �����ϴ�.
	//	�׷��� ���񽺴� �˷��� ���� �ʽ��ϴ�.������ ���� �����̽����� ���񽺸� ã�� �� �����ϴ�.
	//	SocketErrorMap[WSATYPE_NOT_FOUND
	//	
	//	Ŭ���� ������ ã�� �� �����ϴ�.
	//	������ Ŭ������ ã�� �� �����ϴ�.
	//	SocketErrorMap[WSA_E_NO_MORE
	//	
	//	�� �̻� ����� �����ϴ�.
	//	SocketErrorMap[WSALookupServiceNext �Լ� �� �� �̻� ����� ��ȯ �� �� �����ϴ� .
	//	SocketErrorMap[WSA_E_CANCELLED
	//	
	//	��ȭ�� ��ҵǾ����ϴ�.
	//	�� ȣ���� ��� ó���Ǵ� ���� SocketErrorMap[WSALookupServiceEnd �Լ��� ȣ���߽��ϴ�.��ȭ�� ��ҵǾ����ϴ�.
	//	SocketErrorMap[WSAEREFUSED
	//	
	//	�����ͺ��̽� ������ �źεǾ����ϴ�.
	//	�����ͺ��̽� ������ ���������� �ź� �Ǿ��� ������ �����߽��ϴ�.
	//	SocketErrorMap[WSAHOST_NOT_FOUND
	//	
	//	ȣ��Ʈ�� ã�� �� �����ϴ�.
	//	�׷��� ȣ��Ʈ�� �˷��� ���� �ʽ��ϴ�.�̸��� ���� ȣ��Ʈ �̸� �Ǵ� ������ �ƴϰų� ��ȸ���� �����ͺ��̽����� ã�� �� �����ϴ�.�� ������ �������� �� ���� ������ ���ؼ��� ��ȯ �� �� ������ ������ �̸��� ���� �����ͺ��̽����� ã�� �� ������ �ǹ��մϴ�.
	//	SocketErrorMap[WSATRY_AGAIN
	//	
	//	�ŷ��� ������ ȣ��Ʈ�� ã�� �� �����ϴ�.
	//	�̴� �Ϲ������� ȣ��Ʈ �̸� Ȯ�� �� �Ͻ����� �����̸� ���� ������ �����ִ� �����κ��� ���������� �������� �ǹ��մϴ�.���߿� �ٽ� �õ��ϸ� ������ �� �ֽ��ϴ�.
	//	SocketErrorMap[WSANO_RECOVERY
	//	
	//	�̰��� ���� �� ������ �����Դϴ�.
	//	�̰��� �����ͺ��̽� ��ȸ �߿� ������ ���� �Ұ����� ������ �߻������� ��Ÿ���ϴ�.�̴� �����ͺ��̽� ����(�� : BSD ȣȯ HOSTS, SERVICES �Ǵ� PROTOCOLS ����)�� ã�� �� ���ų� �������� �ɰ��� ������ �Բ� DNS ��û�� ��ȯ�߱� ������ �� �ֽ��ϴ�.
	//	SocketErrorMap[WSANO_DATA
	//	
	//	��ȿ�� �̸�, ��û �� ������ ������ ���ڵ尡 �����ϴ�.
	//	��û �� �̸��� ��ȿ�ϰ� �����ͺ��̽����� �߰ߵǾ����� Ȯ������ �ùٸ� ���� �����Ͱ� �����ϴ�.�̿� ���� �Ϲ����� �� �� DNS(������ �̸� ����)�� ��� �ϴ� ȣ��Ʈ �̸� �� �ּ� ��ȯ �õ�(gethostbyname �Ǵ� SocketErrorMap[WSAAsyncGetHostByName ���)�Դϴ�.MX ���ڵ尡 ��ȯ������ A ���ڵ�� �����ϴ�.�̴� ȣ��Ʈ ��ü�� ���������� ���� ������ �� ������ ��Ÿ���ϴ�.
	//	SocketErrorMap[WSA_QOS_RECEIVERS
	//	
	//	QoS ���ű�.
	//	�ּ��� �ϳ��� QoS ������ �����߽��ϴ�.
	//	SocketErrorMap[WSA_QOS_SENDERS
	//	
	//	QoS �߽���.
	//	�ϳ� �̻��� QoS ���� ��ΰ� �����߽��ϴ�.
	//	SocketErrorMap[WSA_QOS_NO_SENDERS
	//	
	//	QoS �߽��ڰ� �����ϴ�.
	//	QoS �߽��ڰ� �����ϴ�.
	//	SocketErrorMap[WSA_QOS_NO_RECEIVERS
	//	
	//	QoS ���ű� ����.
	//	QoS ���űⰡ �����ϴ�.
	//	SocketErrorMap[WSA_QOS_REQUEST_CONFIRMED
	//	
	//	QoS ��û�� Ȯ�εǾ����ϴ�.
	//	QoS ���� ��û�� Ȯ�εǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_ADMISSION_FAILURE
	//	
	//	QoS ���� �����Դϴ�.
	//	���ҽ� �������� QoS ������ �߻��߽��ϴ�.
	//	SocketErrorMap[WSA_QOS_POLICY_FAILURE
	//	
	//	QoS ��å ����.
	//	��å �ý����� ���� ��å ������ ��û �� ���ҽ��� �Ҵ� �� �� ���� ������ QoS ��û�� �źεǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_BAD_STYLE
	//	
	//	QoS �߸��� ��Ÿ��.
	//	�� �� ���ų� �浹�ϴ� QoS ��Ÿ���� �߰ߵǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_BAD_OBJECT
	//	
	//	QoS �ҷ� ��ü.
	//	�Ϲ������� filterspec�� �Ϻ� �Ǵ� ������ �� ���ۿ� ������ �߻��߽��ϴ�.
	//	SocketErrorMap[WSA_QOS_TRAFFIC_CTRL_ERROR
	//	
	//	QoS Ʈ���� ���� �����Դϴ�.
	//	�Ϲ� QoS ��û�� TC API�� ���� ���� ������ ���� ��ȯ�Ǿ��� �� �⺻ Ʈ���� ����(TC) API�� ������ �߻��߽��ϴ�.�̴� �޸� ���� ���� �Ǵ� ���� QoS ������ ���� ������ �� �ֽ��ϴ�.
	//	SocketErrorMap[WSA_QOS_GENERIC_ERROR
	//	
	//	QoS �Ϲ� �����Դϴ�.
	//	�Ϲ����� QoS �����Դϴ�.
	//	SocketErrorMap[WSA_QOS_ESERVICETYPE
	//	
	//	QoS ���� ���� �����Դϴ�.
	//	QoS floSocketErrorMap[Wspec���� ��ȿ���� �ʰų� �νĵ��� �ʴ� ���� ������ �߰ߵǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EFLOSocketErrorMap[WSPEC
	//	
	//	QoS floSocketErrorMap[Wspec �����Դϴ�.
	//	QOS ���� ���� ��ȿ���� �ʰų� ��ġ���� �ʴ� floSocketErrorMap[Wspec�� �߰ߵǾ����ϴ� .
	//	SocketErrorMap[WSA_QOS_EPROVSPECBUF
	//	
	//	��ȿ���� ���� QoS ������ ����.
	//	��ȿ���� ���� QoS ������ �� �����Դϴ�.
	//	SocketErrorMap[WSA_QOS_EFILTERSTYLE
	//	
	//	QoS ���� ��Ÿ���� �߸��Ǿ����ϴ�.
	//	��ȿ���� ���� QoS ���� ��Ÿ���� ���Ǿ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EFILTERTYPE
	//	
	//	�߸��� QoS ���� �����Դϴ�.
	//	��ȿ���� ���� QoS ���� ������ ���Ǿ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EFILTERCOUNT
	//	
	//	QoS ���� ���� �߸��Ǿ����ϴ�.
	//	FLOSocketErrorMap[WDESCRIPTOR�� �ùٸ��� ���� ���� QoS FILTERSPEC�� �����Ǿ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EOBJLENGTH
	//	
	//	QoS ��ü ���̰� �߸��Ǿ����ϴ�.
	//	��ȿ���� ���� ObjectLength �ʵ尡�ִ� ��ü�� QoS ������ �� ���ۿ� �����Ǿ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EFLOSocketErrorMap[WCOUNT
	//	
	//	QoS �帧 ���� �߸��Ǿ����ϴ�.
	//	QoS ������ �߸��� ���� �帧 �����ڰ� �����Ǿ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EUNKOSocketErrorMap[WNPSOBJ
	//	
	//	�ν� �� ������ QoS ��ü�Դϴ�.
	//	QoS ������ �� ���ۿ��� �ν� �� ������ ��ü�� �߰ߵǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EPOLICYOBJ
	//	
	//	��ȿ���� ���� QoS ��å ��ü�Դϴ�.
	//	QoS ������ �� ���ۿ��� �߸��� ��å ��ü�� �߰ߵǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EFLOSocketErrorMap[WDESC
	//	
	//	�߸��� QoS �帧 �������Դϴ�.
	//	�帧 ������ ��Ͽ��� �߸��� QoS �帧 �����ڰ� �߰ߵǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EPSFLOSocketErrorMap[WSPEC
	//	
	//	QoS ������ �� floSocketErrorMap[Wspec�� �ùٸ��� �ʽ��ϴ�.
	//	QoS ������ �� ���ۿ��� ��ȿ���� �ʰų� ��ġ���� �ʴ� floSocketErrorMap[Wspec�� �߰ߵǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_EPSFILTERSPEC
	//	
	//	QoS ������ �� ���� ����� �߸��Ǿ����ϴ�.
	//	QoS ������ �� ���ۿ��� ��ȿ���� ���� FILTERSPEC�� �߰ߵǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_ESDMODEOBJ
	//	
	//	�߸��� QoS ��� ��� ��� ��ü�Դϴ�.
	//	QoS ������ �� ���ۿ��� �߸��� ��� ���� ��� ��ü�� ã�ҽ��ϴ�.
	//	SocketErrorMap[WSA_QOS_ESHAPERATEOBJ
	//	
	//	QoS ���� �ӵ� ��ü�� �߸��Ǿ����ϴ�.
	//	QoS ������ �� ���ۿ��� �߸��� ���� �ӵ� ��ü�� �߰ߵǾ����ϴ�.
	//	SocketErrorMap[WSA_QOS_RESERVED_PETYPE
	//	
	//	���� �� ��å QoS ��� �����Դϴ�.
	//	QoS ������ �� ���ۿ��� ���� �� ��å ��Ҹ� ã�ҽ��ϴ�.

}
