#pragma once
#include <vector>
#include <functional>
#include <atomic>
#include "GameEngineThread.h"

class MessageQueue
{
public: // msg
    CRITICAL_SECTION_OBJ LockObj;
    // std::atomic_uint32_t MaxMsgListCount;
    // atomic<uint32_t> 
    std::atomic_uint32_t MaxMsgListCount;
    std::atomic_uint32_t RecvMsgListIndex;
    std::vector<std::vector<std::function<void()>> > m_MsgList;

public:
    std::vector<std::function<void()>>& GetRecvList();
    std::vector<std::function<void()>>& GetProcessMsgList();

public:
    void MsgUpdate();
    void MsgListInit(int _Count, int _Size);

    template<typename FuncType, typename ... Rest>
    void MsgInsert(FuncType _Func, Rest ... _Arg)
    {
        LockObj.Lock();
        // �̳༮�� ȿ���� �ޱ����� ���� �����ϰ�
        // RecvMsgIndex�� ������ ���·� �Ӵϴ�.
        std::vector<std::function<void()>>& RecvList = GetRecvList();
        RecvList.push_back(std::bind(_Func, _Arg...));
    }

public: // constructor destructor
    MessageQueue() :
        MaxMsgListCount(0),
        RecvMsgListIndex(0)
    {}
    MessageQueue(int _Count, int _Size);
    ~MessageQueue();

};


