#pragma once
#include <Monster.h>
#include "ServerActor.h"
#include <ServerToClient.h>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 

enum class MONSTERSTATE
{
    FIND,
    MOVE,
    ATT,
};

class ServerMonster : public Monster, public ServerActor
{
private: // Static Var
public: // Static Func

public:
    MonsterUpdateDataPacket MonsterData;
    MONSTERSTATE m_eMonsterState;

public:
    float AttRange;
    float FindRange;
    float MoveSpeed;
    GameActor* Target;

public:
    void Setting();

private:
    void Update(float _DeltaTime) override;
    void Att(float _DeltaTime);
    void Find(float _DeltaTime);
    void Move(float _DeltaTime);
    void AttNext(float _DeltaTime);



public: // constructer destructer
    ServerMonster();
    ~ServerMonster();

public: // delete constructer 
    ServerMonster(const ServerMonster& _Other) = delete;
    ServerMonster(const ServerMonster&& _Other) = delete;

public: // delete operator
    ServerMonster& operator=(const ServerMonster& _Other) = delete;
    ServerMonster& operator=(const ServerMonster&& _Other) = delete;

public: // member Func
    void DeathTask() override;

    void ColStay(GameActor* _Left, GameActor* _Right) override;
};

