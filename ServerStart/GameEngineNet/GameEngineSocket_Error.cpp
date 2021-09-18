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
	//SocketErrorMap[WSA_INVALID_HANDLE] = "지정된 이벤트 개체 핸들이 잘못되었습니다.		응용 프로그램이 이벤트 객체를 사용하려고하지만 지정된 핸들이 유효하지 않습니다.";
	//SocketErrorMap[WSA_NOT_ENOUGH_MEMORY] = "사용 가능한 메모리가 부족합니다. 응용 프로그램은 SocketErrorMap[WindoSocketErrorMap[Ws 기능에 직접 매핑되는 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 기능을 사용했습니다.SocketErrorMap[WindoSocketErrorMap[Ws 기능은 필요한 메모리 리소스가 부족함을 나타냅니다.";
	//SocketErrorMap[WSA_INVALID_PARAMETER] = "하나 이상의 매개 변수가 잘못되었습니다. 응용 프로그램은 SocketErrorMap[WindoSocketErrorMap[Ws 기능에 직접 매핑되는 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 기능을 사용했습니다.SocketErrorMap[WindoSocketErrorMap[Ws 기능은 하나 이상의 매개 변수에 문제가 있음을 나타냅니다.";
	//SocketErrorMap[WSA_OPERATION_ABORTED] = "겹친 작업이 중단되었습니다.		소켓 폐쇄 또는 SocketErrorMap[WSAIoctl 에서 SIO_FLUSH 명령 실행으로 인해 중첩 된 작업이 취소되었습니다 .
	//	SocketErrorMap[WSA_IO_INCOMPLETE
	//	
	//	중첩 된 I / O 이벤트 개체가 신호 상태가 아닙니다.
	//	애플리케이션이 아직 완료되지 않은 중복 작업의 상태를 확인하려고했습니다.폴링 모드에서 SocketErrorMap[WSAGetOverlappedResult(fSocketErrorMap[Wait 플래그가 FALSE로 설정 됨)를 사용하여 중첩 된 작업이 언제 완료되었는지 확인하는 응용 프로그램은 작업이 완료 될 때까지이 오류 코드를받습니다.
	//	SocketErrorMap[WSA_IO_PENDING
	//	
	//	중복 된 작업은 나중에 완료됩니다.
	//	응용 프로그램이 즉시 완료 할 수없는 중복 작업을 시작했습니다.작업이 완료되면 나중에 완료 표시가 제공됩니다.
	//	SocketErrorMap[WSAEINTR
	//	
	//	함수 호출이 중단되었습니다.
	//	SocketErrorMap[WSACancelBlockingCall 호출로 인해 차단 작업이 중단 되었습니다 .
	//	SocketErrorMap[WSAEBADF
	//	
	//	파일 핸들이 유효하지 않습니다.
	//	제공된 파일 핸들이 유효하지 않습니다.
	//	SocketErrorMap[WSAEACCES
	//	
	//	권한이 거부되었습니다.
	//	액세스 권한에 의해 금지 된 방식으로 소켓에 액세스하려고했습니다.예를 들어 setsockopt(SO_BROADCAST)를 사용하여 브로드 캐스트 권한을 설정하지 않고 sendto에 브로드 캐스트 주소를 사용하는 것 입니다.SocketErrorMap[WSAEACCES 오류의 또 다른 가능한 이유는 바인드 기능이 호출 될 때(SP 이상이 설치된 SocketErrorMap[WindoSocketErrorMap[Ws NT .에서) 다른 응용 프로그램, 서비스 또는 커널 모드 드라이버가 단독 액세스 권한으로 동일한 주소에 바인딩되기 때문입니다.이러한 단독 액세스는 SP 이상이 설치된 SocketErrorMap[WindoSocketErrorMap[Ws NT .의 새로운 기능이며 SO_EXCLUSIVEADDRUSE 옵션 을 사용하여 구현됩니다 .

	//	SocketErrorMap[WSAEFAULT
	//	
	//	잘못된 주소입니다.
	//	시스템이 호출의 포인터 인수를 사용하려고 할 때 잘못된 포인터 주소를 감지했습니다.이 오류는 응용 프로그램이 잘못된 포인터 값을 전달하거나 버퍼 길이가 너무 작은 경우 발생합니다.예를 들어, sockaddr 구조 인 인수의 길이가 sizeof(sockaddr)보다 작 으면.
	//	SocketErrorMap[WSAEINVAL
	//	
	//	잘못된 인수입니다.
	//	일부 잘못된 인수가 제공되었습니다(예 : setsockopt 함수에 잘못된 수준 지정).어떤 경우에는 소켓의 현재 상태(예 : 수신 대기하지 않는 소켓에서 accept 호출) 를 참조하기도 합니다.
	//	SocketErrorMap[WSAEMFILE
	//	
	//	열린 파일이 너무 많습니다.
	//	열린 소켓이 너무 많습니다.각 구현에는 전역, 프로세스 또는 스레드 당 사용 가능한 최대 소켓 핸들 수가있을 수 있습니다.
	//	SocketErrorMap[WSAESocketErrorMap[WOULDBLOCK
	//	
	//	리소스를 일시적으로 사용할 수 없습니다.
	//	이 오류는 즉시 완료 할 수없는 비 블로킹 소켓에 대한 작업(예 : 소켓에서 읽을 데이터가 대기열에 추가되지 않은 경우 recv) 에서 반환됩니다.치명적이지 않은 오류이며 나중에 작업을 다시 시도해야합니다.SocketErrorMap[WSAESocketErrorMap[WOULDBLOCK 이 비 블로킹 SOCK_STREAM 소켓에서 connect 를 호출 한 결과로보고되는 것은 정상입니다.연결이 설정 되려면 약간의 시간이 경과해야하기 때문입니다.
	//	SocketErrorMap[WSAEINPROGRESS
	//	
	//	현재 작업이 진행 중입니다.
	//	차단 작업이 현재 실행 중입니다.SocketErrorMap[WindoSocketErrorMap[Ws 소켓은 작업 당 또는 스레드 당 단일 차단 작업 만 처리 할 수 있도록 허용하며 다른 함수 호출이 수행되면(이 또는 다른 소켓을 참조하는지 여부에 관계없이) SocketErrorMap[WSAEINPROGRESS 오류와 함께 함수가 실패합니다.
	//	SocketErrorMap[WSAEALREADY
	//	
	//	작업이 이미 진행 중입니다.
	//	작업이 이미 진행중인 비 블로킹 소켓에서 시도되었습니다.즉, 이미 연결중인 비 블로킹 소켓에서 두 번째로 connect를 호출 하거나 이미 취소 또는 완료된 비동기 요청(SocketErrorMap[WSAAsyncGetXbyY)을 취소했습니다.
	//	SocketErrorMap[WSAENOTSOCK
	//	
	//	비 소켓에서의 소켓 작업.
	//	소켓이 아닌 항목에서 작업을 시도했습니다.소켓 핸들 매개 변수가 유효한 소켓을 참조하지 않았거나 select 의 경우 fd_set 의 멤버가 유효하지 않습니다.
	//	SocketErrorMap[WSAEDESTADDRREQ
	//	
	//	목적지 주소가 필요합니다.
	//	소켓의 작업에서 필수 주소가 생략되었습니다.예를 들어, ADDR_ANY의 원격 주소로 sendto 가 호출 되면이 오류가 리턴됩니다 .
	//	SocketErrorMap[WSAEMSGSIZE
	//	
	//	메시지가 너무 깁니다.
	//	데이터 그램 소켓에서 보낸 메시지가 내부 메시지 버퍼 또는 다른 네트워크 제한보다 크거나 데이터 그램을 수신하는 데 사용 된 버퍼가 데이터 그램 자체보다 작습니다.
	//	SocketErrorMap[WSAEPROTOTYPE
	//	
	//	소켓에 대한 프로토콜 잘못된 유형입니다.
	//	요청 된 소켓 유형의 의미를 지원하지 않는 소켓 함수 호출 에 프로토콜이 지정되었습니다.예를 들어, ARPA 인터넷 UDP 프로토콜은 소켓 유형 SOCK_STREAM으로 지정할 수 없습니다.
	//	SocketErrorMap[WSAENOPROTOOPT
	//	
	//	잘못된 프로토콜 옵션입니다.
	//	알 수 없거나 유효하지 않거나 지원되지 않는 옵션 또는 레벨이 getsockopt 또는 setsockopt 호출 에 지정되었습니다 .
	//	SocketErrorMap[WSAEPROTONOS 지원
	//	
	//	프로토콜이 지원되지 않습니다.
	//	요청 된 프로토콜이 시스템에 구성되지 않았거나 이에 대한 구현이 없습니다.예를 들어, 소켓 호출은 SOCK_DGRAM 소켓을 요청하지만 스트림 프로토콜을 지정합니다.
	//	SocketErrorMap[WSAESOCKTNOSUPPORT
	//	
	//	소켓 유형이 지원되지 않습니다.
	//	지정된 소켓 유형에 대한 지원이이 주소 계열에 없습니다.예를 들어, 소켓 호출 에서 선택적 유형 SOCK_RASocketErrorMap[W를 선택할 수 있으며 구현은 SOCK_RASocketErrorMap[W 소켓을 전혀 지원하지 않습니다.
	//	SocketErrorMap[WSAEOPNOTSUPP
	//	
	//	지원되지 않는 작업입니다.
	//	시도한 작업은 참조 된 개체 유형에 대해 지원되지 않습니다.일반적으로이 작업을 지원할 수없는 소켓에 대한 소켓 설명자가 데이터 그램 소켓에서 연결을 수락하려고 할 때 발생합니다.
	//	SocketErrorMap[WSAEPFNOSUPPORT
	//	
	//	프로토콜 제품군이 지원되지 않습니다.
	//	프로토콜 제품군이 시스템에 구성되지 않았거나 이에 대한 구현이 없습니다.이 메시지는 SocketErrorMap[WSAEAFNOSUPPORT와 약간 다른 의미를 갖습니다.그러나 대부분의 경우 상호 교환이 가능하며 이러한 메시지 중 하나를 반환하는 모든 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 함수도 SocketErrorMap[WSAEAFNOSUPPORT를 지정합니다.
	//	SocketErrorMap[WSAEAFNOSUPPORT
	//	
	//	프로토콜 제품군에서 지원하지 않는 주소 제품군입니다.
	//	요청한 프로토콜과 호환되지 않는 주소가 사용되었습니다.모든 소켓은 연관된 주소 계열(즉, 인터넷 프로토콜의 경우 AF_INET) 및 일반 프로토콜 유형(즉, SOCK_STREAM)으로 생성됩니다.소켓 호출 에서 잘못된 프로토콜이 명시 적으로 요청 되거나 소켓 에 잘못된 패밀리의 주소가 사용 된 경우(예 : sendto) 이 오류가 반환됩니다 .
	//	SocketErrorMap[WSAEADDRINUSE
	//	
	//	이미 사용중인 주소입니다.
	//	일반적으로 각 소켓 주소(프로토콜 / IP 주소 / 포트)를 한 번만 사용할 수 있습니다.이 오류는 응용 프로그램 이 기존 소켓에 이미 사용 된 IP 주소 / 포트 또는 제대로 닫히지 않은 소켓 또는 아직 닫는 과정에있는 소켓에 소켓 을 바인딩 하려고 시도하는 경우 발생합니다.여러 소켓을 동일한 포트 번호 에 바인딩 해야하는 서버 애플리케이션의 경우 setsockopt(SO_REUSEADDR) 사용을 고려하십시오.클라이언트 응용 프로그램은 일반적으로 bind 를 호출 할 필요가 없습니다.connect 는 사용하지 않는 포트를 자동으로 선택합니다.바인딩 할 때와일드 카드 주소(ADDR_ANY 포함)로 호출되면 특정 주소가 커밋 될 때까지 SocketErrorMap[WSAEADDRINUSE 오류가 지연 될 수 있습니다.이는 connect, listen, SocketErrorMap[WSAConnect 또는 SocketErrorMap[WSAJoinLeaf를 포함하여 나중에 다른 함수를 호출 할 때 발생할 수 있습니다 .
	//	SocketErrorMap[WSAEADDRNOTAVAIL
	//	
	//	요청한 주소를 할당 할 수 없습니다.
	//	요청한 주소는 해당 컨텍스트에서 유효하지 않습니다.이는 일반적으로 로컬 컴퓨터에 유효하지 않은 주소 에 바인딩 하려는 시도로 인해 발생 합니다.원격 주소 또는 포트가 원격 컴퓨터(예 : 주소 또는 포트 )에 유효하지 않은 경우 connect, sendto, SocketErrorMap[WSAConnect, SocketErrorMap[WSAJoinLeaf 또는 SocketErrorMap[WSASendTo 에서 발생할 수도 있습니다 .
	//	SocketErrorMap[WSAENETDOSocketErrorMap[WN
	//	
	//	네트워크가 다운되었습니다.
	//	소켓 작업에서 데드 네트워크가 발생했습니다.이는 네트워크 시스템(즉, SocketErrorMap[WindoSocketErrorMap[Ws 소켓 DLL이 실행되는 프로토콜 스택), 네트워크 인터페이스 또는 로컬 네트워크 자체의 심각한 오류를 나타낼 수 있습니다.
	//	SocketErrorMap[WSAENETUNREACH
	//	
	//	네트워크에 연결할 수 없습니다.
	//	연결할 수없는 네트워크에 소켓 작업을 시도했습니다.이것은 일반적으로 로컬 소프트웨어가 원격 호스트에 도달 할 경로를 알지 못함을 의미합니다.
	//	SocketErrorMap[WSAENETRESET
	//	
	//	재설정시 네트워크 연결이 끊어졌습니다.
	//	작업이 진행되는 동안 실패를 감지하는 연결 유지 활동으로 인해 연결이 끊어졌습니다.이미 실패한 연결에서 SO_KEEPALIVE 를 설정하려고 시도하는 경우 setsockopt에 의해 반환 될 수도 있습니다 .
	//	SocketErrorMap[WSAECONNABORTED
	//	
	//	소프트웨어로 인해 연결이 중단되었습니다.
	//	데이터 전송 시간 초과 또는 프로토콜 오류로 인해 호스트 컴퓨터의 소프트웨어에 의해 설정된 연결이 중단되었습니다.
	//	SocketErrorMap[WSAECONNRESET
	//	
	//	피어가 연결을 재설정했습니다.
	//	기존 연결이 원격 호스트에 의해 강제로 닫혔습니다.이는 일반적으로 원격 호스트의 피어 응용 프로그램이 갑자기 중지되거나, 호스트가 재부팅되거나, 호스트 또는 원격 네트워크 인터페이스가 비활성화되거나, 원격 호스트가 하드 닫기를 사용하는 경우 발생합니다(원격 호스트 의 SO_LINGER 옵션에 대한 자세한 내용 은 setsockopt 참조).소켓).이 오류는 하나 이상의 작업이 진행중인 동안 실패를 감지하는 연결 유지 활동으로 인해 연결이 끊어진 경우에도 발생할 수 있습니다.진행 중이던 작업이 SocketErrorMap[WSAENETRESET으로 실패합니다.SocketErrorMap[WSAECONNRESET으로 후속 작업이 실패합니다.
	//	SocketErrorMap[WSAENOBUFS
	//	
	//	사용 가능한 버퍼 공간이 없습니다.
	//	시스템에 충분한 버퍼 공간이 부족하거나 큐가 가득 차서 소켓에서 작업을 수행 할 수 없습니다.
	//	SocketErrorMap[WSAEISCONN
	//	
	//	소켓이 이미 연결되었습니다.
	//	이미 연결된 소켓에서 연결 요청이 이루어졌습니다.일부 구현 에서는 연결된 SOCK_DGRAM 소켓에서 sendto 가 호출 된 경우 에도이 오류를 반환 합니다(SOCK_STREAM 소켓의 경우 sendto 의 to 매개 변수 는 무시 됨).다른 구현에서는이를 합법적 인 발생으로 취급합니다.
	//	SocketErrorMap[WSAENOTCONN
	//	
	//	소켓이 연결되지 않았습니다.
	//	소켓이 연결되지 않았고(sendto를 사용하여 데이터 그램 소켓에서 보낼 때) 주소가 제공 되지 않았기 때문에 데이터 전송 또는 수신 요청이 허용되지 않았습니다.다른 유형의 작업도이 오류를 반환 할 수 있습니다.예를 들어, 연결이 재설정 된 경우 setsockopt 설정 SO_KEEPALIVE 가 있습니다.
	//	SocketErrorMap[WSAESHUTDOSocketErrorMap[WN
	//	
	//	소켓 종료 후 보낼 수 없습니다.
	//	소켓이 이전 종료 호출 로 해당 방향으로 이미 종료 되었기 때문에 데이터 전송 또는 수신 요청이 허용되지 않았습니다.shutdoSocketErrorMap[Wn 을 호출 하면 소켓의 부분 닫기가 요청되며, 이는 송신 또는 수신 또는 둘 다 중단되었다는 신호입니다.
	//	SocketErrorMap[WSAETOOMANYREFS
	//	
	//	참조가 너무 많습니다.
	//	일부 커널 개체에 대한 참조가 너무 많습니다.
	//	SocketErrorMap[WSAETIMEDOUT
	//	
	//	연결 시간이 초과되었습니다.
	//	일정 시간이 지나도 접속자가 제대로 응답하지 않아 연결 시도가 실패했거나 연결된 호스트가 응답하지 않아 연결이 설정되지 않았습니다.
	//	SocketErrorMap[WSAECONNREFUSED
	//	
	//	연결이 거부되었습니다.
	//	대상 컴퓨터가 연결을 거부했기 때문에 연결할 수 없습니다.이는 일반적으로 외부 호스트에서 비활성 상태 인 서비스, 즉 실행중인 서버 응용 프로그램이없는 서비스에 연결하려고 할 때 발생합니다.
	//	SocketErrorMap[WSAELOOP
	//	
	//	이름을 번역 할 수 없습니다.
	//	이름을 번역 할 수 없습니다.
	//	SocketErrorMap[WSAENAMETOOLONG
	//	
	//	이름이 너무 깁니다.
	//	이름 구성 요소 또는 이름이 너무 깁니다.
	//	SocketErrorMap[WSAEHOSTDOSocketErrorMap[WN
	//	
	//	호스트가 다운되었습니다.
	//	대상 호스트가 다운되어 소켓 작업이 실패했습니다.소켓 작업에서 데드 호스트가 발생했습니다.로컬 호스트에서 네트워킹 활동이 시작되지 않았습니다.이러한 조건은 SocketErrorMap[WSAETIMEDOUT 오류로 표시 될 가능성이 높습니다.
	//	SocketErrorMap[WSAEHOSTUNREACH
	//	
	//	호스트 경로가 없습니다.
	//	연결할 수없는 호스트에 소켓 작업을 시도했습니다.SocketErrorMap[WSAENETUNREACH를 참조하십시오.
	//	SocketErrorMap[WSAENOTEMPTY
	//	
	//	디렉토리가 비어 있지 않습니다.
	//	비어 있지 않은 디렉토리는 제거 할 수 없습니다.
	//	SocketErrorMap[WSAEPROCLIM
	//	
	//	프로세스가 너무 많습니다.
	//	SocketErrorMap[WindoSocketErrorMap[Ws 소켓 구현에는 동시에 사용할 수있는 응용 프로그램 수에 제한이있을 수 있습니다.제한에 도달하면 SocketErrorMap[WSAStartup 이이 오류와 함께 실패 할 수 있습니다.
	//	SocketErrorMap[WSAEUSERS
	//	
	//	사용자 할당량이 초과되었습니다.
	//	사용자 할당량이 부족했습니다.
	//	SocketErrorMap[WSAEDQUOT
	//	
	//	디스크 할당량을 초과.
	//	디스크 할당량이 부족했습니다.
	//	SocketErrorMap[WSAESTALE
	//	
	//	오래된 파일 핸들 참조.
	//	파일 핸들 참조는 더 이상 사용할 수 없습니다.
	//	SocketErrorMap[WSAEREMOTE
	//	
	//	항목이 원격입니다.
	//	항목은 로컬에서 사용할 수 없습니다.
	//	SocketErrorMap[WSASYSNOTREADY
	//	
	//	네트워크 하위 시스템을 사용할 수 없습니다.
	//	이 오류는 네트워크 서비스를 제공하는 데 사용하는 기본 시스템을 현재 사용할 수 없기 때문에 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 구현이 현재 작동 할 수없는 경우 SocketErrorMap[WSAStartup에 의해 반환됩니다.사용자는 다음 사항을 확인해야합니다.
	//	적절한 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 DLL 파일이 현재 경로에 있는지 확인합니다.
	//	둘 이상의 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 구현을 동시에 사용하려고하지 않습니다.시스템에 둘 이상의 SocketErrorMap[Winsock DLL이있는 경우 경로의 첫 번째 DLL이 현재로드 된 네트워크 하위 시스템에 적합한 지 확인하십시오.
	//	필요한 모든 구성 요소가 현재 올바르게 설치 및 구성되었는지 확인하기위한 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 구현 설명서
	//	SocketErrorMap[WSAVERNOTSUPPORTED
	//	
	//	SocketErrorMap[Winsock.dll 버전이 범위를 벗어났습니다.
	//	현재 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 구현은 응용 프로그램에서 요청한 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 사양 버전을 지원하지 않습니다.이전 SocketErrorMap[WindoSocketErrorMap[Ws 소켓 DLL 파일에 액세스하고 있지 않은지 확인하십시오.
	//	SocketErrorMap[WSANOTINITIALISED
	//	
	//	성공적인 SocketErrorMap[WSAStartup이 아직 수행되지 않았습니다.
	//	어느 응용 프로그램이 호출되지 SocketErrorMap[WSAStartup에 또는 SocketErrorMap[WSAStartup 함수가 실패했습니다.응용 프로그램이 현재 활성 작업이 소유하지 않은 소켓에 액세스하고 있거나(즉, 작업간에 소켓을 공유하려고 함) SocketErrorMap[WSACleanup 이 너무 많이 호출되었을 수 있습니다.
	//	SocketErrorMap[WSAEDISCON
	//	
	//	정상 종료가 진행 중입니다.
	//	원격 당사자가 정상 종료 시퀀스를 시작했음을 나타 내기 위해 SocketErrorMap[WSARecv 및 SocketErrorMap[WSARecvFrom 에 의해 반환됩니다 .
	//	SocketErrorMap[WSAENOMORE
	//	
	//	더 이상 결과가 없습니다.
	//	SocketErrorMap[WSALookupServiceNext 함수 는 더 이상 결과를 반환 할 수 없습니다 .
	//	SocketErrorMap[WSAECANCELLED
	//	
	//	통화가 취소되었습니다.
	//	이 호출이 계속 처리되는 동안 SocketErrorMap[WSALookupServiceEnd 함수를 호출했습니다.통화가 취소되었습니다.
	//	SocketErrorMap[WSAEINVALIDPROCTABLE
	//	
	//	프로 시저 호출 테이블이 유효하지 않습니다.
	//	서비스 공급자 프로 시저 호출 테이블이 잘못되었습니다.서비스 공급자가 가짜 프로 시저 테이블을 SocketErrorMap[Ws_.dll에 반환했습니다.이는 일반적으로 하나 이상의 함수 포인터가 NULL 인 경우 발생합니다 .
	//	SocketErrorMap[WSAEINVALIDPROVIDER
	//	
	//	서비스 제공 업체가 잘못되었습니다.
	//	요청한 서비스 제공 업체가 잘못되었습니다.이 오류는 지정된 프로토콜 항목을 찾을 수없는 경우 SocketErrorMap[WSCGetProviderInfo 및 SocketErrorMap[WSCGetProviderInfo 함수에 의해 반환됩니다.이 오류는 서비스 공급자가 .이 아닌 버전 번호를 반환 한 경우에도 반환됩니다.
	//	SocketErrorMap[WSAEPROVIDERFAILEDINIT
	//	
	//	서비스 제공 업체를 초기화하지 못했습니다.
	//	요청한 서비스 제공 업체를로드하거나 초기화 할 수 없습니다.이 오류는 서비스 공급자의 DLL을로드 할 수 없거나(LoadLibrary 실패) 공급자의 SocketErrorMap[WSPStartup 또는 NSPStartup 함수가 실패한 경우에 반환 됩니다.
	//	SocketErrorMap[WSASYSCALLFAILURE
	//	
	//	시스템 호출 실패.
	//	절대 실패해서는 안되는 시스템 호출이 실패했습니다.다양한 조건에서 반환되는 일반 오류 코드입니다.
	//	절대 실패해서는 안되는 시스템 호출이 실패 할 때 반환됩니다.예를 들어 SocketErrorMap[WaitForMultipleEvents에 대한 호출이 실패하거나 레지스트리 함수 중 하나가 프로토콜 / 네임 스페이스 카탈로그를 조작하는 데 실패하는 경우입니다.
	//	공급자가 SUCCESS를 반환하지 않고 확장 오류 코드를 제공하지 않을 때 반환됩니다.서비스 제공 업체 구현 오류를 나타낼 수 있습니다.
	//	SocketErrorMap[WSASERVICE_NOT_FOUND
	//	
	//	서비스를 찾을 수 없습니다.
	//	그러한 서비스는 알려져 있지 않습니다.지정된 네임 스페이스에서 서비스를 찾을 수 없습니다.
	//	SocketErrorMap[WSATYPE_NOT_FOUND
	//	
	//	클래스 유형을 찾을 수 없습니다.
	//	지정된 클래스를 찾을 수 없습니다.
	//	SocketErrorMap[WSA_E_NO_MORE
	//	
	//	더 이상 결과가 없습니다.
	//	SocketErrorMap[WSALookupServiceNext 함수 는 더 이상 결과를 반환 할 수 없습니다 .
	//	SocketErrorMap[WSA_E_CANCELLED
	//	
	//	통화가 취소되었습니다.
	//	이 호출이 계속 처리되는 동안 SocketErrorMap[WSALookupServiceEnd 함수를 호출했습니다.통화가 취소되었습니다.
	//	SocketErrorMap[WSAEREFUSED
	//	
	//	데이터베이스 쿼리가 거부되었습니다.
	//	데이터베이스 쿼리가 적극적으로 거부 되었기 때문에 실패했습니다.
	//	SocketErrorMap[WSAHOST_NOT_FOUND
	//	
	//	호스트를 찾을 수 없습니다.
	//	그러한 호스트는 알려져 있지 않습니다.이름이 공식 호스트 이름 또는 별명이 아니거나 조회중인 데이터베이스에서 찾을 수 없습니다.이 오류는 프로토콜 및 서비스 쿼리에 대해서도 반환 될 수 있으며 지정된 이름을 관련 데이터베이스에서 찾을 수 없음을 의미합니다.
	//	SocketErrorMap[WSATRY_AGAIN
	//	
	//	신뢰할 수없는 호스트를 찾을 수 없습니다.
	//	이는 일반적으로 호스트 이름 확인 중 일시적인 오류이며 로컬 서버가 권한있는 서버로부터 응답을받지 못했음을 의미합니다.나중에 다시 시도하면 성공할 수 있습니다.
	//	SocketErrorMap[WSANO_RECOVERY
	//	
	//	이것은 복구 할 수없는 오류입니다.
	//	이것은 데이터베이스 조회 중에 일종의 복구 불가능한 오류가 발생했음을 나타냅니다.이는 데이터베이스 파일(예 : BSD 호환 HOSTS, SERVICES 또는 PROTOCOLS 파일)을 찾을 수 없거나 서버에서 심각한 오류와 함께 DNS 요청을 반환했기 때문일 수 있습니다.
	//	SocketErrorMap[WSANO_DATA
	//	
	//	유효한 이름, 요청 된 유형의 데이터 레코드가 없습니다.
	//	요청 된 이름이 유효하고 데이터베이스에서 발견되었지만 확인중인 올바른 관련 데이터가 없습니다.이에 대한 일반적인 예 는 DNS(도메인 이름 서버)를 사용 하는 호스트 이름 대 주소 변환 시도(gethostbyname 또는 SocketErrorMap[WSAAsyncGetHostByName 사용)입니다.MX 레코드가 반환되지만 A 레코드는 없습니다.이는 호스트 자체가 존재하지만 직접 연결할 수 없음을 나타냅니다.
	//	SocketErrorMap[WSA_QOS_RECEIVERS
	//	
	//	QoS 수신기.
	//	최소한 하나의 QoS 예약이 도착했습니다.
	//	SocketErrorMap[WSA_QOS_SENDERS
	//	
	//	QoS 발신자.
	//	하나 이상의 QoS 전송 경로가 도착했습니다.
	//	SocketErrorMap[WSA_QOS_NO_SENDERS
	//	
	//	QoS 발신자가 없습니다.
	//	QoS 발신자가 없습니다.
	//	SocketErrorMap[WSA_QOS_NO_RECEIVERS
	//	
	//	QoS 수신기 없음.
	//	QoS 수신기가 없습니다.
	//	SocketErrorMap[WSA_QOS_REQUEST_CONFIRMED
	//	
	//	QoS 요청이 확인되었습니다.
	//	QoS 예약 요청이 확인되었습니다.
	//	SocketErrorMap[WSA_QOS_ADMISSION_FAILURE
	//	
	//	QoS 승인 오류입니다.
	//	리소스 부족으로 QoS 오류가 발생했습니다.
	//	SocketErrorMap[WSA_QOS_POLICY_FAILURE
	//	
	//	QoS 정책 실패.
	//	정책 시스템이 기존 정책 내에서 요청 된 리소스를 할당 할 수 없기 때문에 QoS 요청이 거부되었습니다.
	//	SocketErrorMap[WSA_QOS_BAD_STYLE
	//	
	//	QoS 잘못된 스타일.
	//	알 수 없거나 충돌하는 QoS 스타일이 발견되었습니다.
	//	SocketErrorMap[WSA_QOS_BAD_OBJECT
	//	
	//	QoS 불량 개체.
	//	일반적으로 filterspec의 일부 또는 공급자 별 버퍼에 문제가 발생했습니다.
	//	SocketErrorMap[WSA_QOS_TRAFFIC_CTRL_ERROR
	//	
	//	QoS 트래픽 제어 오류입니다.
	//	일반 QoS 요청이 TC API에 의해 로컬 적용을 위해 변환되었을 때 기본 트래픽 제어(TC) API에 오류가 발생했습니다.이는 메모리 부족 오류 또는 내부 QoS 제공자 오류 때문일 수 있습니다.
	//	SocketErrorMap[WSA_QOS_GENERIC_ERROR
	//	
	//	QoS 일반 오류입니다.
	//	일반적인 QoS 오류입니다.
	//	SocketErrorMap[WSA_QOS_ESERVICETYPE
	//	
	//	QoS 서비스 유형 오류입니다.
	//	QoS floSocketErrorMap[Wspec에서 유효하지 않거나 인식되지 않는 서비스 유형이 발견되었습니다.
	//	SocketErrorMap[WSA_QOS_EFLOSocketErrorMap[WSPEC
	//	
	//	QoS floSocketErrorMap[Wspec 오류입니다.
	//	QOS 구조 에서 유효하지 않거나 일치하지 않는 floSocketErrorMap[Wspec이 발견되었습니다 .
	//	SocketErrorMap[WSA_QOS_EPROVSPECBUF
	//	
	//	유효하지 않은 QoS 제공자 버퍼.
	//	유효하지 않은 QoS 제공자 별 버퍼입니다.
	//	SocketErrorMap[WSA_QOS_EFILTERSTYLE
	//	
	//	QoS 필터 스타일이 잘못되었습니다.
	//	유효하지 않은 QoS 필터 스타일이 사용되었습니다.
	//	SocketErrorMap[WSA_QOS_EFILTERTYPE
	//	
	//	잘못된 QoS 필터 유형입니다.
	//	유효하지 않은 QoS 필터 유형이 사용되었습니다.
	//	SocketErrorMap[WSA_QOS_EFILTERCOUNT
	//	
	//	QoS 필터 수가 잘못되었습니다.
	//	FLOSocketErrorMap[WDESCRIPTOR에 올바르지 않은 수의 QoS FILTERSPEC이 지정되었습니다.
	//	SocketErrorMap[WSA_QOS_EOBJLENGTH
	//	
	//	QoS 개체 길이가 잘못되었습니다.
	//	유효하지 않은 ObjectLength 필드가있는 개체가 QoS 공급자 별 버퍼에 지정되었습니다.
	//	SocketErrorMap[WSA_QOS_EFLOSocketErrorMap[WCOUNT
	//	
	//	QoS 흐름 수가 잘못되었습니다.
	//	QoS 구조에 잘못된 수의 흐름 설명자가 지정되었습니다.
	//	SocketErrorMap[WSA_QOS_EUNKOSocketErrorMap[WNPSOBJ
	//	
	//	인식 할 수없는 QoS 개체입니다.
	//	QoS 제공자 별 버퍼에서 인식 할 수없는 개체가 발견되었습니다.
	//	SocketErrorMap[WSA_QOS_EPOLICYOBJ
	//	
	//	유효하지 않은 QoS 정책 개체입니다.
	//	QoS 공급자 별 버퍼에서 잘못된 정책 개체가 발견되었습니다.
	//	SocketErrorMap[WSA_QOS_EFLOSocketErrorMap[WDESC
	//	
	//	잘못된 QoS 흐름 설명자입니다.
	//	흐름 설명자 목록에서 잘못된 QoS 흐름 설명자가 발견되었습니다.
	//	SocketErrorMap[WSA_QOS_EPSFLOSocketErrorMap[WSPEC
	//	
	//	QoS 제공자 별 floSocketErrorMap[Wspec이 올바르지 않습니다.
	//	QoS 제공자 별 버퍼에서 유효하지 않거나 일치하지 않는 floSocketErrorMap[Wspec이 발견되었습니다.
	//	SocketErrorMap[WSA_QOS_EPSFILTERSPEC
	//	
	//	QoS 공급자 별 필터 사양이 잘못되었습니다.
	//	QoS 제공자 별 버퍼에서 유효하지 않은 FILTERSPEC이 발견되었습니다.
	//	SocketErrorMap[WSA_QOS_ESDMODEOBJ
	//	
	//	잘못된 QoS 모양 폐기 모드 개체입니다.
	//	QoS 공급자 별 버퍼에서 잘못된 모양 삭제 모드 개체를 찾았습니다.
	//	SocketErrorMap[WSA_QOS_ESHAPERATEOBJ
	//	
	//	QoS 형성 속도 개체가 잘못되었습니다.
	//	QoS 공급자 별 버퍼에서 잘못된 형성 속도 개체가 발견되었습니다.
	//	SocketErrorMap[WSA_QOS_RESERVED_PETYPE
	//	
	//	예약 된 정책 QoS 요소 유형입니다.
	//	QoS 제공자 별 버퍼에서 예약 된 정책 요소를 찾았습니다.

}
