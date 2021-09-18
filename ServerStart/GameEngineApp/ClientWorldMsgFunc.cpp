#include "ClientWorldMsgFunc.h"
#include <World.h>
#include "ClientItem.h"
#include <LogicValue.h>
#include "ClientPotal.h"


// Static Var
// Static Func

// constructer destructer
ClientWorldMsgFunc::ClientWorldMsgFunc() 
{

}

ClientWorldMsgFunc::~ClientWorldMsgFunc() 
{

}
// member Func

void ClientWorldMsgFunc::WaitPlayerCreate(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data)
{
    std::shared_ptr<ClientPlayer> Player = _World->CreateWaitActor<ClientPlayer>(2);

    // ���忡 ����������̱� ������.
    // ���߿� ���ο� ��Ŷ������ �� ���� ������ �𸦼��� �־��.
    // �׷��� ID������ ���� ��Ŷ�� ���ƿ����� �� ID�� ���� �������� �ﰢ������ ������ �ټ� �ְ� ����°�
    // �߿��մϴ�.
    // ��Ŷ�� ���ƿԾ� 2000�� ��������.
    // ��� ���� �ٵ��ͼ� 2000�� ã���� ����?
    // �������� ������Ʈ id�� ���������?
    // Data.UpdateID �̳༮�� ã�Ƴ��� �������ټ��� �ֽ��ϴ�.
    _Connecter->IDPlayerInsert(Data.UpdateID, Player);

}

void ClientWorldMsgFunc::WaitPlayerInWorld(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data)
{
    std::shared_ptr<ClientPlayer> FindPlayer = _Connecter->FindIDPlayer(Data.UpdateID);

    if (nullptr == FindPlayer)
    {
        GameEngineDebug::AssertMsg("if (nullptr == FindPlayer)");
    }

    FindPlayer->SetPos(Data.CurPos);

    _World->WaitActorInWorld(FindPlayer);
}

void ClientWorldMsgFunc::UpdatePlayer(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data)
{
    // ������Ʈ�� �׳� ���ƿ����� ���� �� ������ ��ϵ��� ���� �������
    // �� ������ �׳� ����� ���� ���̴�.
    std::shared_ptr<ClientPlayer> FindPlayer = _Connecter->FindIDPlayer(Data.UpdateID);
    if (nullptr == FindPlayer)
    {
        std::shared_ptr<ClientPlayer> Player =  _World->CreateActor<ClientPlayer>(2);
        _Connecter->IDPlayerInsert(Data.UpdateID, Player);
        Player->SetPos(Data.CurPos);
        return;
    }

    FindPlayer->SetClientPos(Data.CurPos);
}

void ClientWorldMsgFunc::DeathPlayer(World* _World, ClientConnecter* _Connecter, PlayerUpdateData Data) 
{
    std::shared_ptr<ClientPlayer> FindPlayer = _Connecter->FindIDPlayer(Data.UpdateID);
    if (nullptr == FindPlayer)
    {
        // �α� �� �̷��� �߻��Ѵٴ°� ������� ����°� ���ƿ�.
        return;
    }

    _Connecter->RemoveIDPlayer(Data.UpdateID);
    FindPlayer->OldClear();
    FindPlayer->CurClear();
    // ������ ������ ������������ ���忡 �����־ ���������� �ڽ��� ������ �ϹǷ�
    // �ƹ��� �ǹ̰� ����.
    FindPlayer->Death();
}

void ClientWorldMsgFunc::UpdateMonster(World* _World, ClientConnecter* _Connecter, MonsterUpdateData Data)
{
    std::shared_ptr<ClientMonster> FindMonster = _Connecter->FindIDMonster(Data.UpdateID);
    if (nullptr == FindMonster)
    {
        std::shared_ptr<ClientMonster> Monster = _World->CreateActor<ClientMonster>(3);
        _Connecter->IDMonsterInsert(Data.UpdateID, Monster);
        Monster->SetPos(Data.CurPos);
        return;
    }

    FindMonster->SetClientPos(Data.CurPos);


    int a = 0;
}

void ClientWorldMsgFunc::DeathMonster(World* _World, ClientConnecter* _Connecter, MonsterUpdateData Data)
{
    std::shared_ptr<ClientMonster> FindMonster = _Connecter->FindIDMonster(Data.UpdateID);
    if (nullptr == FindMonster)
    {
        // �α� �� �̷��� �߻��Ѵٴ°� ������� ����°� ���ƿ�.
        return;
    }

    _Connecter->RemoveIDMonster(Data.UpdateID);
    FindMonster->OldClear();
    FindMonster->CurClear();
    // ������ ������ ������������ ���忡 �����־ ���������� �ڽ��� ������ �ϹǷ�
    // �ƹ��� �ǹ̰� ����.
    FindMonster->Death();

}

void ClientWorldMsgFunc::UpdateItem(World* _World, ClientConnecter* _Connecter, ItemUpdateData Data)
{
    std::shared_ptr<ClientItem> FindItem = _Connecter->FindIDItem(Data.UpdateID);
    if (nullptr == FindItem)
    {
        std::shared_ptr<ClientItem> NewItem = _World->CreateActor<ClientItem>((int)LogicValue::CollisionLayer::ITEM);
        _Connecter->IDItemInsert(Data.UpdateID, NewItem);
        NewItem->SetPos(Data.CurPos);
        return;
    }

    FindItem->SetClientPos(Data.CurPos);

}

void ClientWorldMsgFunc::DeathItem(World* _World, ClientConnecter* _Connecter, ItemUpdateData Data)
{
    std::shared_ptr<ClientItem> FindItem = _Connecter->FindIDItem(Data.UpdateID);
    if (nullptr == FindItem)
    {
        // �α� �� �̷��� �߻��Ѵٴ°� ������� ����°� ���ƿ�.
        return;
    }

    _Connecter->RemoveIDItem(Data.UpdateID);
    FindItem->OldClear();
    FindItem->CurClear();
    // ������ ������ ������������ ���忡 �����־ ���������� �ڽ��� ������ �ϹǷ�
    // �ƹ��� �ǹ̰� ����.
    FindItem->Death();

}

void ClientWorldMsgFunc::UpdatePotal(World* _World, ClientConnecter* _Connecter, PotalUpdateData Data)
{
    std::shared_ptr<ClientPotal> NewItem = _World->CreateActor<ClientPotal>((int)LogicValue::CollisionLayer::POTAL);
    NewItem->SetPos(Data.CurPos);
}