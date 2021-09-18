#pragma once
#ifndef UNREALDEFINE
#include "GameEngineIocp.h"
#include "DBConnecter.h"
#include <LockThreadSafeObjectPool.h>
#include <functional>

// �߿�
class DBTask : public  std::enable_shared_from_this<DBTask>
{
public:
    std::string Query;
    // ������ �˰� ������ � �����͸� �޾ƿͼ� ó���ؾ������� �𸣰� �Ǵ°Ŵ�.
    std::function<void(DBConnecter*)> TeskFunc;
};

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class DBManager
{
private: // Static Var
    static DBManager m_Inst;

public: // Static Func
    static DBManager& Inst() 
    {
        return m_Inst;
    }

private: // member Var
    // �� �� 1000�� ���� task�� ����� 
    std::vector<std::shared_ptr<DBConnecter>> ArrDBConnecter;
    GameEngineIocp DBIocp;

   public:
    LockThreadSafeObjectPool<DBTask> m_TaskPool;
public:
    // DBTask�� ���������� ����ִ� �޸𸮿��� �ϰ�
    // �װ� �츮�°�
    // �� ���ο��� �޸𸮸� �������� �ְڽ��ϴ�.

public:
    void Init(const char* _ID, const char* _Pass, const char* _Schema,  int _Count = 4);

    // � �Լ��� ������ �˼��� ����.
    template<typename DBFunc, typename ... REST>
    void PushTask(const std::string& _Query, DBFunc* _Func, REST ... _Arg)
    {
        std::shared_ptr<DBTask> NewTask = m_TaskPool.Pop();
        NewTask->Query = _Query;
        NewTask->TeskFunc = std::bind(_Func, std::placeholders::_1, NewTask.get(), _Arg...);
        DBIocp.IocpPost(reinterpret_cast<ULONG_PTR>(NewTask.get()), 0, nullptr);
    }

    void PushTaskBind(const std::string& _Query, std::function<void(DBConnecter*)> _Func)
    {
        std::shared_ptr<DBTask> NewTask = m_TaskPool.Pop();
        NewTask->Query = _Query;
        NewTask->TeskFunc = _Func;
        DBIocp.IocpPost(reinterpret_cast<ULONG_PTR>(NewTask.get()), 0, nullptr);
    }

private:
    static void DBThreadFunc(DBConnecter* Connecter);



public: // constructer destructer
    DBManager();
    ~DBManager();

public: // delete constructer 
    DBManager(const DBManager& _Other) = delete;
    DBManager(const DBManager&& _Other) = delete;

public: // delete operator
    DBManager& operator=(const DBManager& _Other) = delete;
    DBManager& operator=(const DBManager&& _Other) = delete;

public: // member Func
};

#endif