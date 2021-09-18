// Fill out your copyright notice in the Description page of Project Settings.


#include "ExBullet.h"
#include "UnActorManager.h"
#include <LogicValue.h>

AExBullet::AExBullet() : Speed(3000.0f), DeathTime(5.0f), UpPower(1000.0f), GravityPower(0.0f), AccPower(3000.0f), IsBoom(false)
{
}

AExBullet::~AExBullet()
{
}

void AExBullet::ActorEnd()
{
	UE_LOG(LogTemp, Error, L"EXFire Death");
	UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::PLAYEREXBULLET, UpdateID);
}

void AExBullet::Update(float _DeltaTime)
{
// 	UE_LOG(LogTemp, Error, L"EXFire");

	if (true == IsBoom && 0 >= (DeathTime -= _DeltaTime))
	{
		UE_LOG(LogTemp, Error, L"Boom End");
		Destroy();
		return;
	} else if (true == IsBoom && 0 < (DeathTime -= _DeltaTime))
	{
		UE_LOG(LogTemp, Error, L"Boom Stay");
		return;
	}

	if (true == IsBoom)
	{
		return;
	}

	if (0 >= (DeathTime -= _DeltaTime))
	{

		UE_LOG(LogTemp, Error, L"Boom Start");
		SetActorScale3D({ 10.0f, 10.0f, 10.0f });
		m_GameCol->On();
		m_GameCol->SetScale({ 2000.0F, 2000.0F, 2000.0f });
		IsBoom = true;
		DeathTime = 0.5f;
		return;
	}

	FVector MovePos = DirVector * Speed * _DeltaTime;
	FVector UpDir = FVector4(0.0f, 0.0f, 1.0f) * UpPower * _DeltaTime;
	FVector Gravity = FVector4(0.0f, 0.0f, -1.0f) * GravityPower * _DeltaTime;
	GravityPower += AccPower * _DeltaTime;

	FVector ResultPos = MovePos + UpDir + Gravity;
	float4 CheckPos = &ResultPos.X;
	// 죽이는 연산이 충돌 연산보다는 낮을테니까
	// 빠르게 빠르게 죽여서 충돌연산에 대한 부담을 줄여주는게 좋습니다.
	if (true == UnActorManager::GetInst().CheckCollison(this, COLTYPE::CT_SPHERE, float4(100.0f, 100.0f, 100.0f), CheckPos, 0))
	{
		// Destroy();
		return;
	}

	SetActorLocation(GetActorLocation() + ResultPos);
}