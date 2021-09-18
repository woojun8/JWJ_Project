#include "ServerItem.h"
#include <GameWorld.h>
#include "WorldMsgFunc.h"
#include <GameEngineRandom.h>
#include <LogManager.h>

// Static Var
// Static Func

// constructer destructer
ServerItem::ServerItem() : ServerActor(*(GameActor*)this)
{
    // random함수는 정말 잘 만들어야 합니다.
    // rand는 아니에요.

    int ItemRandom = GameEngineRandom::GetRandomUint(0, 2);

    // 데이터 리스트에서 가져와야 하는것인데.
    // 그렇게 크게할 생각이 없으니까.


    switch (ItemRandom)
    {
    case 0:
        Data.Name = L"철검";
        Data.IconResData = 0;
        Data.Count = 1;
        Data.Type = 0;

        //Data.Name = L"포션";
        //Data.IconResData = 2;
        //Data.Count = 1;
        //Data.Type = 2;
        break;
    case 1:
        Data.Name = L"갑옷";
        Data.IconResData = 1;
        Data.Count = 1;
        Data.Type = 1;

        //Data.Name = L"포션";
        //Data.IconResData = 2;
        //Data.Count = 1;
        //Data.Type = 2;
        break;
    case 2:

        Data.Name = L"포션";
        Data.IconResData = 2;
        Data.Count = 1;
        Data.Type = 2;
        break;
    default:
        break;
    }

    // Data.Type = ItemRandom;
}

ServerItem::~ServerItem() 
{
}
// member Func

ItemUpdateData ServerItem::GetItemData(ActorState _State)
{
    ItemUpdateData NewItemData;
    NewItemData.CurPos = GetPos();
    NewItemData.UpdateID = reinterpret_cast<__int64>(this);
    NewItemData.m_State = _State;
    NewItemData.EventPlayer = EventPlayer;
    NewItemData.m_Data = Data;
    return NewItemData;
}

//void ServerItem::ColStay(GameActor* _this, GameActor* _Other)
//{
//    int a = 0;
//}

void ServerItem::DeathTask()
{
    // 죽는 순간 나 죽었습니다.
    GetWorld()->MsgInsert(&WorldMsgFunc::ItemDeath, GetItemData(ActorState::Death));
}


