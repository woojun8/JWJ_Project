#include "ServerBullet.h"
#include <GameEngineTime.h>
#include <iostream>

// Static Var
// Static Func

// constructer destructer
ServerBullet::ServerBullet() : ServerActor(*(GameActor*)this)
{

}

ServerBullet::~ServerBullet() 
{

}

// member Func
void ServerBullet::Update(float _DeltaTime)
{
	// std::cout << "Bullet Update" << std::endl;

	DeathTime -= _DeltaTime;

	if (0.0f >= DeathTime)
	{
		std::cout << "Bullet TimeOut Death" << std::endl;
		Death();
		return;
	}

	// std::cout << "x : " << GetPos().x << " y : "<< GetPos().y << " z : " << GetPos().z << std::endl;

	SetMovePos(Dir * Speed * _DeltaTime);

}

void ServerBullet::ColStay(GameActor* _Left, GameActor* _Right)
{
	// std::cout << "Col Bullet" << std::endl;
}