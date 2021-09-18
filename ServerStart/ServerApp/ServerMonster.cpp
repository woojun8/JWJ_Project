#include "ServerMonster.h"
#include "LogicThread.h"
#include <World.h>
#include <GameWorld.h>
#include "WorldMsgFunc.h"
#include <iostream>
#include <LogManager.h>
#include "ServerWorld.h"
#include <LogicValue.h>

// Static Var
// Static Func

// constructer destructer
ServerMonster::ServerMonster() : ServerActor(*(GameActor*)this), m_eMonsterState(MONSTERSTATE::FIND), FindRange(5000.0f), AttRange(1000.0f), MoveSpeed(500.0f)
{

}

ServerMonster::~ServerMonster() 
{

}
// member Func

void ServerMonster::Setting() 
{
    MonsterData.UpdateID = reinterpret_cast<__int64>(this);
    MonsterData.m_Data.Pos = GetPos();
    MonsterData.m_Data.Rot = GetPos();
    MonsterData.m_Data.Scale = { 100.0f, 100.0f, 100.0f };
}

void ServerMonster::DeathTask()
{
    ServerWorld* World = dynamic_cast<ServerWorld*>(GetWorld());
    if (nullptr != World)
    {
        --World->CurMonsterCount;
    }

    Setting();
    MonsterData.m_State = ActorState::Death;
    GetWorld()->MsgInsert(&WorldMsgFunc::MonsterDeath, MonsterData);
}


void ServerMonster::ColStay(GameActor* _Left, GameActor* _Right)
{
    if (_Right->GetColOrder() == (int)LogicValue::CollisionLayer::PLAYERBULLET)
    {
        Death();
        _Right->Death();
    }
    else if (_Right->GetColOrder() == (int)LogicValue::CollisionLayer::PLAYERATTACK)
    {
        int a = 0;
        Death();
        _Right->Death();
    }
    else 
    {
        Death();
    }
    // LogManager::Inst().PushLog("Col Monster");
}


void ServerMonster::Update(float _DeltaTime)
{
    switch (m_eMonsterState)
    {
    case MONSTERSTATE::FIND:
        Find(_DeltaTime);
        break;
    case MONSTERSTATE::MOVE:
        Move(_DeltaTime);
        break;
    case MONSTERSTATE::ATT:
        Att(_DeltaTime);
        break;
    default:
        break;
    }
}

void ServerMonster::Att(float _DeltaTime)
{
    MonsterUpdateDataPacket Packet;

    std::list<std::shared_ptr<Actor>>& GetActor = GetWorld()->GetActorList(2);

    Packet.UpdateID = reinterpret_cast<__int64>(this);
    Packet.m_State = ActorState::Update;
    Packet.m_Data.Dir = Target->GetPos() - GetPos();
    Packet.m_Data.DeltaTime = _DeltaTime;

    float Len = Packet.m_Data.Dir.Len();
    Packet.m_Data.Dir.Normalize();

    // 만들고 브로드 캐스트
    for (auto& _Actor : GetActor)
    {
        if (_Actor.get() == this)
        {
            continue;
        }

        std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
        Ptr->GetConnecter()->Send(Packet);
    }


    if (Len >= AttRange)
    {
        m_eMonsterState = MONSTERSTATE::MOVE;
        return;
    }
}

void ServerMonster::Find(float _DeltaTime)
{
    // std::cout << "Find" << std::endl;

    GameWorld* GetGameWorld = reinterpret_cast<GameWorld*>(GetWorld());

    // 죽이는 연산이 충돌 연산보다는 낮을테니까
    // 빠르게 빠르게 죽여서 충돌연산에 대한 부담을 줄여주는게 좋습니다.
    if (nullptr != GetGameWorld)
    {
        Target = GetGameWorld->CheckCollison(this, COLTYPE::CT_SPHERE, float4(FindRange, FindRange, FindRange), float4::ZERO, (int)LogicValue::CollisionLayer::PLAYER);

        if (nullptr != Target)
        {
            m_eMonsterState = MONSTERSTATE::MOVE;
            return;
        }
    }

}

void ServerMonster::Move(float _DeltaTime)
{
    if (nullptr == Target)
    {
        m_eMonsterState = MONSTERSTATE::FIND;
        return;
    }

    if (true == Target->IsDeath())
    {
        Target = nullptr;
        m_eMonsterState = MONSTERSTATE::FIND;
        return;
    }

    MonsterUpdateDataPacket Packet;

    std::list<std::shared_ptr<Actor>>& GetActor = GetWorld()->GetActorList(2);



    Packet.UpdateID = reinterpret_cast<__int64>(this);
    Packet.m_State = ActorState::Update;
    Packet.m_Data.Dir = Target->GetPos() - GetPos();
    Packet.m_Data.DeltaTime = _DeltaTime;

    float Len = Packet.m_Data.Dir.Len();
    Packet.m_Data.Dir.Normalize();

    Packet.m_Data.Move = Packet.m_Data.Dir * MoveSpeed * _DeltaTime;
    SetMovePos(Packet.m_Data.Dir * MoveSpeed * _DeltaTime);

    Packet.m_Data.Rot.x = float4::Angle(GetPos(), Target->GetPos());

    // 만들고 브로드 캐스트
    for (auto& _Actor : GetActor)
    {
        if (_Actor.get() == this)
        {
            continue;
        }

        std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
        Ptr->GetConnecter()->Send(Packet);
    }
    if (Len >= FindRange)
    {
        Target = nullptr;
        m_eMonsterState = MONSTERSTATE::FIND;
        return;
    }

    if (Len <= AttRange)
    {
        m_eMonsterState = MONSTERSTATE::ATT;
        return;
    }
}

void ServerMonster::AttNext(float _DeltaTime) 
{
}