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

    // ���Ͷ����� ó���ǰ� �ִ� �Լ��� 
    // ���ٽÿ��� ���Ͷ��� �ɾ���� �ϴµ�.
    //  InterlockedExchangeNoFence

    if (0 == m_MsgList[RecvMsgListIndex].size())
    {
        return m_MsgList[RecvMsgListIndex];
    }

    // ���ú긦 �� ���� ����Ʈ�� ó���Ǿ�� �ϴ� ����Ʈ����?
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