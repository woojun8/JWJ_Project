#pragma once
#include <list>
#include <set>
#include "GameEngineThread.h"
#include "GameEngineDebug.h"


// 어떤 오브젝트를 다수 만들고 메모리를 관리해주는 
// 클래스

//class ObjectType 
//{
//
//};

// 순수하게 그냥 lock을 사용해서
// 처리하겠습니다.
template<typename ObjectType>
class LockThreadSafeObjectPool 
{
private:
    // 아래의 2개의 리스트를 동시에 보호해주는 lock
    CRITICAL_SECTION_OBJ PoolLock;

    // 풀에 잠들어 있는 오브젝트들
    std::list<std::shared_ptr<ObjectType>> PoolList;
    // 외부에서 활동중인 오브젝트들.
    std::set<std::shared_ptr<ObjectType>> ActiveSet;

    // 
    //CRITICAL_SECTION_OBJ PoolLock;
    //// 풀에 잠들어 있는 오브젝트들
    //std::list<std::shared_ptr<ObjectType>> PoolList2;

public:
    std::shared_ptr<ObjectType> Pop() 
    {
        // 인터락을 써서 만들면
        // 여기는 프리락 방식이 되는거고
        // 락 방식입니다.
        PoolLock.Lock();

        if (0 == PoolList.size())
        {
            return nullptr;
        }

        // 다수의 쓰레드가 이걸 요청하면
        // 당연히 메모리가 꼬이거나 터질수 있다.
        std::shared_ptr<ObjectType> PopObj = *PoolList.begin();
        PoolList.pop_front(); 
        ActiveSet.insert(PopObj);
        return PopObj;
    }

    void Push(std::shared_ptr<ObjectType> _Object)
    {
        PoolLock.Lock();

        // 이풀에서 나간 오브젝트가 아니라는 뜻이됩니다.
        if (ActiveSet.end() == ActiveSet.find(_Object))
        {
            GameEngineDebug::AssertMsg("if (ActiveSet.end() != ActiveSet.find(_Object))");
        }

        ActiveSet.erase(_Object);
        PoolList.push_front(_Object);
        return;
    }

    void Init(int _Size) 
    {
        for (size_t i = 0; i < _Size; i++)
        {
            PoolList.push_back(std::make_shared<ObjectType>());
        }
    }

public:
    LockThreadSafeObjectPool() 
    {

    }
    ~LockThreadSafeObjectPool() 
    {

    }

};