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

    // �������� �ʴٰ� �����ϰ�
    // Ŀ��Ʈ�� 
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
        // ���⿡ ���ƿ� 
        ComKey = Worker.GetComKey();

        DBTask* Ptr = reinterpret_cast<DBTask*>(ComKey);

        if (nullptr == Ptr->TeskFunc)
        {
            Inst().m_TaskPool.Push(Ptr->shared_from_this());
            continue;
        }

        // ���� �� ó���� ���ݾƿ�?
        Ptr->TeskFunc(Connecter);
        // ���⼭ �����ع�����
        // ������ ��Ŷó�� �ʿ��� ���� �ִµ� ���� ���ϴ� ���� �ȴ�.
         
        
        // ������ �޾ƺ��� �ִ� �ڷ����� �־������.
        // ������ ó���ߴٰ� �ϴ���
        // ù��° ���� ���� � �����͸� �޾ƿ÷����� �˼��� ����.
        // Connecter->DynamicQueryTemplate(Ptr->Query.c_str(), );

        // DB�� ����� �����س��� ������ �Ϻ�
        // �� ������� �̿��ϴ� ������� �ƴմϴ�.
        // Select�� ���� �����ε�.
        // ����� �޾ƿԾ��
        // ����ϴ°� ��Ŷó���� IOCP�������̴�.
        // �˰� �ϵǸ� �ȵǰ�.

    }
}

#endif