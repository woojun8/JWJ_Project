#pragma once
#include <list>
#include <set>
#include "GameEngineThread.h"
#include "GameEngineDebug.h"


// � ������Ʈ�� �ټ� ����� �޸𸮸� �������ִ� 
// Ŭ����

//class ObjectType 
//{
//
//};

// �����ϰ� �׳� lock�� ����ؼ�
// ó���ϰڽ��ϴ�.
template<typename ObjectType>
class LockThreadSafeObjectPool 
{
private:
    // �Ʒ��� 2���� ����Ʈ�� ���ÿ� ��ȣ���ִ� lock
    CRITICAL_SECTION_OBJ PoolLock;

    // Ǯ�� ���� �ִ� ������Ʈ��
    std::list<std::shared_ptr<ObjectType>> PoolList;
    // �ܺο��� Ȱ������ ������Ʈ��.
    std::set<std::shared_ptr<ObjectType>> ActiveSet;

    // 
    //CRITICAL_SECTION_OBJ PoolLock;
    //// Ǯ�� ���� �ִ� ������Ʈ��
    //std::list<std::shared_ptr<ObjectType>> PoolList2;

public:
    std::shared_ptr<ObjectType> Pop() 
    {
        // ���Ͷ��� �Ἥ �����
        // ����� ������ ����� �Ǵ°Ű�
        // �� ����Դϴ�.
        PoolLock.Lock();

        if (0 == PoolList.size())
        {
            return nullptr;
        }

        // �ټ��� �����尡 �̰� ��û�ϸ�
        // �翬�� �޸𸮰� ���̰ų� ������ �ִ�.
        std::shared_ptr<ObjectType> PopObj = *PoolList.begin();
        PoolList.pop_front(); 
        ActiveSet.insert(PopObj);
        return PopObj;
    }

    void Push(std::shared_ptr<ObjectType> _Object)
    {
        PoolLock.Lock();

        // ��Ǯ���� ���� ������Ʈ�� �ƴ϶�� ���̵˴ϴ�.
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