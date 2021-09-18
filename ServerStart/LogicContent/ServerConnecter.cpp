#ifndef UNREALDEFINE
#include "ServerConnecter.h"
#include <LogManager.h>
#include "ServerToClientPacketUpdater.h"
#include <DBManager.h>
#include "ItemTable.h"

// Static Var
// Static Func

// constructer destructer
ServerConnecter::ServerConnecter() : m_Player(nullptr) /*: m_CharacterData(nullptr)*/
{

}

ServerConnecter::~ServerConnecter() 
{

}
// member Func

int ServerConnecter::Send(ServerToClient& _SendData)
{
    GameEngineSerializer Ser = _SendData.Serialize();

    // rtti를 통해서 수없이 상속받은 패킷들의 본체가 어떤 녀석인지 알아낼수있다.
    // 가상함수 테이블을 통해서 실제 생성된 객체의 정보를 얻어오되
    // 컴파일러 수준에서 이미 결정을 하기 때문에
    // 속력이 느려질 걱정을 하지 않아도 됩니다.
    if (0 != strcmp(typeid(_SendData).name(), "class PlayerUpdatePacket") &&
        0 != strcmp(typeid(_SendData).name(), "class PlayerUpdateDataPacket") &&
        0 != strcmp(typeid(_SendData).name(), "class MonsterUpdateDataPacket"))
    {
        LogManager::Inst().PushLog(typeid(_SendData).name());
    }

    // 이녀석안에 m_Buffer만 날리면 됩니다.
    return SyncSend(Ser.GetBuffer(), Ser.GetOffsetInt());
}


#endif