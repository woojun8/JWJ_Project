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

    // rtti�� ���ؼ� ������ ��ӹ��� ��Ŷ���� ��ü�� � �༮���� �˾Ƴ����ִ�.
    // �����Լ� ���̺��� ���ؼ� ���� ������ ��ü�� ������ ������
    // �����Ϸ� ���ؿ��� �̹� ������ �ϱ� ������
    // �ӷ��� ������ ������ ���� �ʾƵ� �˴ϴ�.
    if (0 != strcmp(typeid(_SendData).name(), "class PlayerUpdatePacket") &&
        0 != strcmp(typeid(_SendData).name(), "class PlayerUpdateDataPacket") &&
        0 != strcmp(typeid(_SendData).name(), "class MonsterUpdateDataPacket"))
    {
        LogManager::Inst().PushLog(typeid(_SendData).name());
    }

    // �̳༮�ȿ� m_Buffer�� ������ �˴ϴ�.
    return SyncSend(Ser.GetBuffer(), Ser.GetOffsetInt());
}


#endif