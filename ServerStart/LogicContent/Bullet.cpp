#include "Bullet.h"
#include "LogicValue.h"

// Static Var
// Static Func

// constructer destructer
Bullet::Bullet() 
{

}

Bullet::~Bullet() 
{

}
// member Func

void Bullet::Start() 
{
    SetColOrder((int)LogicValue::CollisionLayer::PLAYERBULLET, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
}