#include "Monster.h"
#include "LogicValue.h"

// Static Var
// Static Func

// constructer destructer
Monster::Monster() 
{

}

Monster::~Monster() 
{

}
// member Func

void Monster::Start() 
{
    SetColOrder((int)LogicValue::CollisionLayer::MONSTER, {100.0f, 100.0f, 100.0f}, COLTYPE::CT_SPHERE);
}

