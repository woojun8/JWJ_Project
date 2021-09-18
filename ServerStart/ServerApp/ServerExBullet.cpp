#include "ServerExBullet.h"
#include <LogicValue.h>
#include <GameWorld.h>
#include <iostream>

ServerExBullet::ServerExBullet() : ServerActor(*(GameActor*)this)
	, Speed(3000.0f), DeathTime(5.0f), UpPower(1000.0f), GravityPower(0.0f), AccPower(3000.0f), IsBoom(false)
{
	
}

ServerExBullet::~ServerExBullet()
{
}

void ServerExBullet::Start()
{
	SetColOrder((int)LogicValue::CollisionLayer::PLAYEREXBULLET, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
}

void ServerExBullet::Update(float _DeltaTime) 
{
	if (true == IsBoom && 0 >= (DeathTime -= _DeltaTime))
	{
		Death();
		return;
	}
	else if (true == IsBoom && 0 < (DeathTime -= _DeltaTime))
	{
		return;
	}

	if (true == IsBoom)
	{
		return;
	}

	if (0 >= (DeathTime -= _DeltaTime))
	{
		SetScale({ 2000.0F, 2000.0F, 2000.0f });
		SetColOn();
		IsBoom = true;
		DeathTime = 0.2f;
		return;
	}

	float4 MovePos = DirVector * Speed * _DeltaTime;
	float4 UpDir = float4(0.0f, 0.0f, 1.0f) * UpPower * _DeltaTime;
	float4 Gravity = float4(0.0f, 0.0f, -1.0f) * GravityPower * _DeltaTime;
	GravityPower += AccPower * _DeltaTime;

	float4 Move = MovePos;

	
	GameWorld* GetGameWorld = reinterpret_cast<GameWorld*>(GetWorld());

	// 죽이는 연산이 충돌 연산보다는 낮을테니까
	// 빠르게 빠르게 죽여서 충돌연산에 대한 부담을 줄여주는게 좋습니다.
	if (nullptr != GetGameWorld)
	{
		if (nullptr != GetGameWorld->CheckCollison(this, COLTYPE::CT_SPHERE, float4(100.0f, 100.0f, 100.0f), Move, 0))
		{
			// std::cout << "ExBullet Ground!!" << std::endl;
			return;
		}
	}

	SetMovePos(MovePos + UpDir + Gravity);
}


void ServerExBullet::ColStay(GameActor* _Left, GameActor* _Right) 
{

}