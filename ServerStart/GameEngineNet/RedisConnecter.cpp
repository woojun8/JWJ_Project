#include "RedisConnecter.h"
#ifndef UNREALDEFINE
#include <GameEngineDebug.h>

// Static Var
// Static Func

// constructer destructer
RedisConnecter::RedisConnecter() : GameEngineSocket(SOCKETTYPE::TCP)
{

}

RedisConnecter::~RedisConnecter() 
{

}
// member Func

void RedisConnecter::Connect(const char* _Ip, int _Port) 
{
    AddressSetting(_Ip, _Port);
    CreateSyncConnection();

    if (SOCKET_ERROR == GameEngineSocket::Connect())
    {
        GameEngineDebug::AssertMsg("Redis connect error");
    }
}

void RedisConnecter::Command(const RedisCommand::CommandBase& _Command) const
{
    GameEngineSocket::ConstSyncSend(_Command.GetCommandPtr(), static_cast<int>(_Command.GetCommandSize()));
}

std::string RedisConnecter::WaitResult() 
{
    int Result = SyncRecv();

    if (-1 == Result)
    {
        return "ServerError";
    }

    if (0 == Result)
    {
        return "ServerError";
    }

    return GetRecvBuffer().RealBuffer;
}

void RedisManager::RedisThread(RedisConnecter* _Con)
{
    while (true == GetInst().IsProcess)
    {
        Sleep(1);

        {
            GetInst().LockObj.Lock();
            if (0 != GetInst().m_FrontTaskQueue.size())
            {
                GetInst().ProcessCheck();
            }
        }



        while (false == GetInst().m_ProcessTaskQueue.empty())
        {
            std::shared_ptr<RedisTask> Task = GetInst().m_ProcessTaskQueue.front();

            _Con->Command(*Task->m_Commend);
            Task->m_Request({ _Con, _Con->WaitResult() });

            GetInst().m_ProcessTaskQueue.pop();
        }


        // 큐에서 빼서 처리

    }

}


#endif

