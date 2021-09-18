#include "GameEngineSocket.h"
#include <list>

//class AcceptEvent 
//{
//public:
//    virtual void AcceptEvent();
//};

// 분류1 : Server
// 분류2 : 
// 용도 : 
// 설명 : 
class TcpConnecter;
class GameEngineServer;
class TcpAccepter : public GameEngineSocket
{
    friend GameEngineServer;

private: // Static Var
public: // Static Func
private: // member Var
    bool m_IsAcceptLoop;

    int m_ListenCount;
    // 커넥트를 넘길일이 있다.
    // TcpAccepter 로비역할과 비슷한 역할을 해주는 겁니다.
    // 이녀석은 커넥트를 가지고 있을겁니다.
    // => 엔진수준의 로직이죠?
    // 로비에서 그리고 월드나 로비라고 
    // 연결자를 하나 보관하고 있는 겁니다.
    // 현재까지 만든 접속할수 있는 유저수와 같은 역할을 해줍니다.
    std::list<std::shared_ptr<TcpConnecter>> m_ConnectSocket;

    typedef void(__stdcall* AcceptEvent)(std::shared_ptr<TcpAccepter> _Accpter, std::shared_ptr<TcpConnecter> _NewConnecter);
    AcceptEvent m_pAcceptEvent;

    // void(*m_pAcceptEvent)(std::shared_ptr<TcpAccepter> _Accpter);
    // typedef void(*)(std::shared_ptr<TcpAccepter> _Accpter) AcceptEvent;

public:
    size_t GetListenCount()
    {
        return m_ListenCount;
    }

    size_t ConnectSocketCount() 
    {
        return m_ConnectSocket.size();
    }

public: // constructer destructer
    TcpAccepter();

public: // 외부에서 삭제 호출은 가능하도록 한다.
    ~TcpAccepter();

public: // delete constructer 
    TcpAccepter(const TcpAccepter& _Other) = delete;
    TcpAccepter(const TcpAccepter&& _Other) = delete;

public: // delete operator
    TcpAccepter& operator=(const TcpAccepter& _Other) = delete;
    TcpAccepter& operator=(const TcpAccepter&& _Other) = delete;

public: // member Func
    // void SyncCreate(const char* _Ip, int _Port, IPTYPE _IPType = IPTYPE::IP4);
    bool listenSetting(int _Port, SOCKETSYNCTYPE _Type = SOCKETSYNCTYPE::SYNC, const char* _Ip = "0.0.0.0", int _ListenCount = 512, IPTYPE _IPType = IPTYPE::IP4);

    bool SyncAccept();
    void AcceptLoop(AcceptEvent _Event = nullptr);

public:
    // Create와 동시에 
    template<typename Connecter>
    std::shared_ptr<Connecter> CreateAcceptExConnection()
    {
        std::shared_ptr<Connecter> NewConnection = std::make_shared<Connecter>();
        NewConnection->SetListenSocket(this);
        NewConnection->CreateASyncConnection();
        m_ConnectSocket.push_back(std::dynamic_pointer_cast<TcpConnecter, Connecter>(NewConnection));

        // NewConnection->GetAcceptOverRef()

        // GetSocket() 리스닝 소켓
        // NewConnection->GetSocket() 새로만든 비동기 소켓

        DWORD dwByte = 0;
        BOOL Check = NewConnection->AcceptExConnecter();
        if (TRUE != Check)
        {
            m_ConnectSocket.pop_back();
            return nullptr;
        }

        return NewConnection;
    }

private:
    void Accept();
};

