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
    // random�Լ��� ���� �� ������ �մϴ�.
    // rand�� �ƴϿ���.

    int ItemRandom = GameEngineRandom::GetRandomUint(0, 2);

    // ������ ����Ʈ���� �����;� �ϴ°��ε�.
    // �׷��� ũ���� ������ �����ϱ�.


    switch (ItemRandom)
    {
    case 0:
        Data.Name = L"ö��";
        Data.IconResData = 0;
        Data.Count = 1;
        Data.Type = 0;

        //Data.Name = L"����";
        //Data.IconResData = 2;
        //Data.Count = 1;
        //Data.Type = 2;
        break;
    case 1:
        Data.Name = L"����";
        Data.IconResData = 1;
        Data.Count = 1;
        Data.Type = 1;

        //Data.Name = L"����";
        //Data.IconResData = 2;
        //Data.Count = 1;
        //Data.Type = 2;
        break;
    case 2:

        Data.Name = L"����";
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
    // �״� ���� �� �׾����ϴ�.
    GetWorld()->MsgInsert(&WorldMsgFunc::ItemDeath, GetItemData(ActorState::Death));
}


