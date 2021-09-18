// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include <LogicValue.h>
#include "UnActorManager.h"
#include <functional>
	
AMonster::AMonster() 
{
}

AMonster::~AMonster()
{
}


void AMonster::CollisonEvent(GameCol* _This, GameCol* _Other) 
{
	UE_LOG(LogTemp, Error, L"Monster Col!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

	if (_Other->GetOrder() == (int)LogicValue::CollisionLayer::PLAYERBULLET)
	{
		// _This->GetActor()->Destroy();
		_Other->GetActor()->Destroy();
		UE_LOG(LogTemp, Error, L"void AMonster::CollisonEvent");
	}
	//} else if (_Other->GetOrder() == (int)LogicValue::CollisionLayer::PLAYEREXBULLET)
	//{
	//	// _This->GetActor()->Destroy();
	//	// _Other->GetActor()->Destroy();
	//	UE_LOG(LogTemp, Error, L"if (_This->GetOrder() == (int)LogicValue::CollisionLayer::PLAYERBULLET)");
	//}
}

void AMonster::MonsterUpdate()
{
	if (true == m_UpdateQueue.empty())
	{
		return;
	}

	// UE_LOG(LogTemp, Error, L"MonsterUpdate");

	const FTransform& Trans = GetActorTransform();
	FRotator RRot = Trans.Rotator();

	ActorUpdateData& Data = m_UpdateQueue.front();

	if (true == Data.IsSet)
	{
		UE_LOG(LogTemp, Error, L"SetUpdate %f, %f, %f  Rot : %f", Data.Pos.x, Data.Pos.y, Data.Pos.z, Data.Rot.x);
		FRotator NewRRot;
		NewRRot.Add(0.0f, Data.Rot.x, 0.0f);
		SetActorRotation(NewRRot);

		FVector MoveVector = { Data.Pos.x, Data.Pos.y, Data.Pos.z };
		SetActorLocation(MoveVector);
		m_UpdateQueue.pop();
		return;
	}

	if (Data.Rot != float4::ZERO)
	{
		UE_LOG(LogTemp, Error, L"SetUpdate %f ", Data.Rot.x);

		FVector Vec = { Data.Dir .x, Data.Dir.y, Data.Dir.z};

		SetActorRotation(Vec.Rotation());
	}

	if (Data.Move != float4::ZERO)
	{
		// UE_LOG(LogTemp, Error, L"Move Monster %f, %f, %f", Data.Move.x, Data.Move.y, Data.Move.z);
		FVector MoveVector = { Data.Move.x, Data.Move.y, Data.Move.z };
		SetActorLocation(GetActorLocation() + MoveVector);
	}

	m_UpdateQueue.pop();
}

void AMonster::ActorStart() 
{
	// std::function<void(GameCol*, GameCol*) > FuncTest;

	// FuncTest = std::bind(&AMonster::CollisonEvent, this, std::placeholders::_1, std::placeholders::_2);

	if (nullptr != m_GameCol)
	{
		m_GameCol->SetEvent(this, &AMonster::CollisonEvent);
	}
}

void AMonster::ActorEnd() 
{
	// UE_LOG(LogTemp, Error, TEXT("Monster Death"));

	// 클라이언트 때였기 때문에
	// UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::MONSTER, reinterpret_cast<__int64>(this));
	// UpdateID 싱글이라면 이 ID를 자기 껄로 하면 되
	UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::MONSTER, UpdateID);
}