// Fill out your copyright notice in the Description page of Project Settings.


#include "AttCol.h"
#include "UnActorManager.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerAnim.h"
#include <LogicValue.h>

AAttCol::AAttCol() : DeathTime(1.0f)
{
}

AAttCol::~AAttCol()
{
}

void AAttCol::ActorEnd()
{
	UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::PLAYERATTACK, UpdateID);
}

void AAttCol::Update(float _DeltaTime)
{	
	if (0 >= (DeathTime -= _DeltaTime))
	{
		m_GameCol->Death();
		Destroy();
		return;
	}

	FVector Pos = APlayerCharacter::GetInst().GetPlayerAnim()->GetSkelMeshComponent()->GetSocketLocation(TEXT("sword_top_socket"));
	float4 Move = &Pos.X;	
	if (true == UnActorManager::GetInst().CheckCollison(this, COLTYPE::CT_SPHERE, float4(100.0f, 100.0f, 100.0f), Move, 0))
	{
		// Destroy();
		return;
	}

	SetActorLocation(Pos);

	LOG(TEXT("X : %f, Y : %f, Z : %f"), Pos.X, Pos.Y, Pos.Z);
}
