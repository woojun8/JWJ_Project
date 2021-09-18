#ifndef UNREALDEFINE
#include "DBManager.h"

// Static Var
// Static Func


DBManager DBManager::m_Inst;

// constructer destructer
DBManager::DBManager(/*int _ThreadCount = 4*/)
{
}

DBManager::~DBManager()
{

}
// member Func

void DBManager::Init(const char* _ID, const char* _Pass, const char* _Schema, int _Count /*= 4*/)
{
    m_TaskPool.Init(_Count * 100);

    // 안전하지 않다고 가정하고
    // 커넥트는 
    for (size_t i = 0; i < _Count; i++)
    {
        std::shared_ptr<DBConnecter> NewCon = std::make_shared<DBConnecter>();
        ArrDBConnecter.push_back(NewCon);
        NewCon->Connect(_ID, _Pass, _Schema);
        DBIocp.ThreadCreate(std::bind(&DBManager::DBThreadFunc, NewCon.get()));
    }
}

void DBManager::DBThreadFunc(DBConnecter* Connecter)
{
    GameEngineIocp::IocpWorker Worker = Inst().DBIocp.CreateWorker();
    ULONG_PTR ComKey;

    while (true)
    {
        Worker.GetQueueWait();
        // 여기에 날아올 
        ComKey = Worker.GetComKey();

        DBTask* Ptr = reinterpret_cast<DBTask*>(ComKey);

        if (nullptr == Ptr->TeskFunc)
        {
            Inst().m_TaskPool.Push(Ptr->shared_from_this());
            continue;
        }

        // 일을 다 처리할 거잖아요?
        Ptr->TeskFunc(Connecter);
        // 여기서 정리해버리면
        // 문제가 패킷처리 쪽에서 쓰고 있는데 봉변 당하는 꼴이 된다.
         
        
        // 쿼리를 받아볼수 있는 자료형을 넣어줘야죠.
        // 쿼리를 처리했다고 하더라도
        // 첫번째 문제 내가 어떤 데이터를 받아올려는지 알수가 없고.
        // Connecter->DynamicQueryTemplate(Ptr->Query.c_str(), );

        // DB의 결과를 도출해내는 쓰레드 일분
        // 그 결과물을 이용하는 쓰레드는 아닙니다.
        // Select가 제일 문제인데.
        // 결과를 받아왔어요
        // 사용하는건 패킷처리용 IOCP쓰레드이다.
        // 알게 하되면 안되고.

    }
}

#endif