#include "ServerAttCol.h"
#include <GameEngineTime.h>
#include <LogicValue.h>
#include <iostream>

// Static Var
// Static Func

// constructer destructer
ServerAttCol::ServerAttCol() : ServerActor(*(GameActor*)this)
{

}

ServerAttCol::~ServerAttCol()
{

}

void ServerAttCol::Start()
{
	SetColOrder((int)LogicValue::CollisionLayer::PLAYERATTACK, { 500.0f, 500.0f, 500.0f }, COLTYPE::CT_SPHERE);
}

// member Func
void ServerAttCol::Update(float _DeltaTime)
{
	int a = 0;
}

void ServerAttCol::ColStay(GameActor* _Left, GameActor* _Right)
{
	// std::cout << "Col Bullet" << std::endl;
}