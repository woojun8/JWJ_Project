// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "UnActorManager.h"
#include <LogicValue.h>

ABullet::ABullet() : Speed(8000.0f), DeathTime(5.0f)
{
}

ABullet::~ABullet() 
{
// 	UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::PLAYERBULLET, reinterpret_cast<__int64>(this));
}

void ABullet::ActorEnd()
{
	UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::PLAYERBULLET, UpdateID);
}

void ABullet::Update(float _DeltaTime)
{
	if (0 >= (DeathTime -= _DeltaTime))
	{
		m_GameCol->Death();
		Destroy();
		return;
	}

	FVector MovePos = DirVector* Speed* _DeltaTime;
	float4 Move = &MovePos.X;
	// 죽이는 연산이 충돌 연산보다는 낮을테니까
	// 빠르게 빠르게 죽여서 충돌연산에 대한 부담을 줄여주는게 좋습니다.
	if (true == UnActorManager::GetInst().CheckCollison(this, COLTYPE::CT_SPHERE, float4(100.0f, 100.0f, 100.0f), Move, 0))
	{
		// Destroy();
		return;
	}


	SetActorLocation(GetActorLocation() + DirVector * Speed * _DeltaTime);

}