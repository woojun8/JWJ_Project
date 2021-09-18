#include "Item.h"
#include "LogicValue.h"
// Static Var
// Static Func

// constructer destructer
Item::Item() 
{

}

Item::~Item() 
{

}
// member Func

void Item::Start() 
{
    SetColOrder((int)LogicValue::CollisionLayer::ITEM, {100.0f, 100.0f, 100.0f}, COLTYPE::CT_SPHERE);
}