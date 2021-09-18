#include "MessageQueue.h"

MessageQueue::MessageQueue(int _Count, int _Size) :
    MaxMsgListCount(0),
    RecvMsgListIndex(0)
{
    MsgListInit(_Count, _Size);
}

MessageQueue::~MessageQueue()
{
}


std::vector<std::function<void()>>& MessageQueue::GetProcessMsgList()
{
    LockObj.Lock();
    // MsgListChange();

    // 인터락으로 처리되고 있는 함수는 
    // 접근시에도 인터락을 걸어줘야 하는데.
    //  InterlockedExchangeNoFence

    if (0 == m_MsgList[RecvMsgListIndex].size())
    {
        return m_MsgList[RecvMsgListIndex];
    }

    // 리시브를 다 받은 리스트가 처리되어야 하는 리스트겠죠?
    int CurIndex = RecvMsgListIndex;
    RecvMsgListIndex.fetch_add(1);
    // InterlockedIncrement(&RecvMsgListIndex);

    if (MaxMsgListCount >= RecvMsgListIndex)
    {
        RecvMsgListIndex.exchange(0);
    }

    // InterlockedExchange(&RecvMsgIndex, 0);
    return m_MsgList[CurIndex];
}

std::vector<std::function<void()>>& MessageQueue::GetRecvList()
{
    return m_MsgList[RecvMsgListIndex];
}

void MessageQueue::MsgListInit(int _Count, int _Size)
{
    m_MsgList.clear();

    m_MsgList.resize(_Count);
    MaxMsgListCount = _Count;
    RecvMsgListIndex = 0;
    for (size_t i = 0; i < m_MsgList.size(); i++)
    {
        m_MsgList[i].reserve(_Size);
    }

}


void MessageQueue::MsgUpdate()
{
    LockObj.Lock();
    std::vector<std::function<void()>>& MsgList = GetProcessMsgList();

    for (size_t i = 0; i < MsgList.size(); i++)
    {
        MsgList[i]();
    }

    MsgList.clear();
}