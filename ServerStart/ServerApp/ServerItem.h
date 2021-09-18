#pragma once
#include <Item.h>
#include "ServerActor.h"
#include <ServerToClient.h>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class ServerItem : public Item, public ServerActor
{
private: // Static Var
public: // Static Func
private: // member Var
    // �ڽ��� ���� ȹ���� ������ ������ ���� ������ UpdateId�� ����س��� �����ϰ���.

    // �ڽ��� ���� ������ id�� ����س���
    // �� �������Դ� �ٸ� ������ �����ش�.

public:
    __int64 EventPlayer;
    ItemData Data;


public:
    ItemUpdateData GetItemData(ActorState _State = ActorState::Update);

public: // constructer destructer
    ServerItem();
    ~ServerItem();

public: // delete constructer 
    ServerItem(const ServerItem& _Other) = delete;
    ServerItem(const ServerItem&& _Other) = delete;

public: // delete operator
    ServerItem& operator=(const ServerItem& _Other) = delete;
    ServerItem& operator=(const ServerItem&& _Other) = delete;

public:
    void DeathTask() override;
};

