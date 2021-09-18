#include "GameEngineSocket.h"
#include <list>

//class AcceptEvent 
//{
//public:
//    virtual void AcceptEvent();
//};

// �з�1 : Server
// �з�2 : 
// �뵵 : 
// ���� : 
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
    // Ŀ��Ʈ�� �ѱ����� �ִ�.
    // TcpAccepter �κ��Ұ� ����� ������ ���ִ� �̴ϴ�.
    // �̳༮�� Ŀ��Ʈ�� ������ �����̴ϴ�.
    // => ���������� ��������?
    // �κ񿡼� �׸��� ���峪 �κ��� 
    // �����ڸ� �ϳ� �����ϰ� �ִ� �̴ϴ�.
    // ������� ���� �����Ҽ� �ִ� �������� ���� ������ ���ݴϴ�.
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

public: // �ܺο��� ���� ȣ���� �����ϵ��� �Ѵ�.
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
    // Create�� ���ÿ� 
    template<typename Connecter>
    std::shared_ptr<Connecter> CreateAcceptExConnection()
    {
        std::shared_ptr<Connecter> NewConnection = std::make_shared<Connecter>();
        NewConnection->SetListenSocket(this);
        NewConnection->CreateASyncConnection();
        m_ConnectSocket.push_back(std::dynamic_pointer_cast<TcpConnecter, Connecter>(NewConnection));

        // NewConnection->GetAcceptOverRef()

        // GetSocket() ������ ����
        // NewConnection->GetSocket() ���θ��� �񵿱� ����

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

