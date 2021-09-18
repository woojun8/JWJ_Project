#pragma once
#ifndef UNREALDEFINE
#include "GameEngineIocp.h"
#include "DBConnecter.h"
#include <LockThreadSafeObjectPool.h>
#include <functional>

// 중요
class DBTask : public  std::enable_shared_from_this<DBTask>
{
public:
    std::string Query;
    // 쿼리만 알고 있을뿐 어떤 데이터를 받아와서 처리해야할지는 모르게 되는거니.
    std::function<void(DBConnecter*)> TeskFunc;
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
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
    // 음 한 1000개 정도 task를 만들고 
    std::vector<std::shared_ptr<DBConnecter>> ArrDBConnecter;
    GameEngineIocp DBIocp;

   public:
    LockThreadSafeObjectPool<DBTask> m_TaskPool;
public:
    // DBTask는 지속적으로 살아있는 메모리여야 하고
    // 그걸 살리는건
    // 이 내부에서 메모리를 유지시켜 주겠습니다.

public:
    void Init(const char* _ID, const char* _Pass, const char* _Schema,  int _Count = 4);

    // 어떤 함수가 들어올지 알수가 없다.
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