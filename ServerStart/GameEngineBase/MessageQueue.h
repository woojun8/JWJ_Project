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
        // 이녀석은 효과를 받기전의 값을 리턴하고
        // RecvMsgIndex은 증가한 상태로 둡니다.
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


