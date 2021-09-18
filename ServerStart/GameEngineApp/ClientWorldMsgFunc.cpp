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

    // 월드에 만들어진것이기 때문에.
    // 나중에 새로운 패킷왔을때 이 유저 것인지 모를수가 있어요.
    // 그래서 ID저장해 놓고 패킷이 날아왓을때 그 ID를 가진 유저에게 즉각적으로 영향을 줄수 있게 만드는게
    // 중요합니다.
    // 패킷이 날아왔어 2000번 유저래요.
    // 모든 액터 다들고와서 2000번 찾을수 없죠?
    // 이유저의 업데이트 id로 등록해주죠?
    // Data.UpdateID 이녀석을 찾아내서 조작해줄수가 있습니다.
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
    // 업데이트가 그냥 날아왔을때 만약 그 유저가 등록되지 않은 유저라면
    // 그 유저를 그냥 만들어 버릴 것이다.
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
        // 로그 찍어서 이런게 발생한다는걸 기록으로 남기는게 좋아요.
        return;
    }

    _Connecter->RemoveIDPlayer(Data.UpdateID);
    FindPlayer->OldClear();
    FindPlayer->CurClear();
    // 지워도 어차피 죽이지안으면 월드에 남아있어서 지속적으로 자신을 랜더링 하므로
    // 아무런 의미가 없다.
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
        // 로그 찍어서 이런게 발생한다는걸 기록으로 남기는게 좋아요.
        return;
    }

    _Connecter->RemoveIDMonster(Data.UpdateID);
    FindMonster->OldClear();
    FindMonster->CurClear();
    // 지워도 어차피 죽이지안으면 월드에 남아있어서 지속적으로 자신을 랜더링 하므로
    // 아무런 의미가 없다.
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
        // 로그 찍어서 이런게 발생한다는걸 기록으로 남기는게 좋아요.
        return;
    }

    _Connecter->RemoveIDItem(Data.UpdateID);
    FindItem->OldClear();
    FindItem->CurClear();
    // 지워도 어차피 죽이지안으면 월드에 남아있어서 지속적으로 자신을 랜더링 하므로
    // 아무런 의미가 없다.
    FindItem->Death();

}

void ClientWorldMsgFunc::UpdatePotal(World* _World, ClientConnecter* _Connecter, PotalUpdateData Data)
{
    std::shared_ptr<ClientPotal> NewItem = _World->CreateActor<ClientPotal>((int)LogicValue::CollisionLayer::POTAL);
    NewItem->SetPos(Data.CurPos);
}