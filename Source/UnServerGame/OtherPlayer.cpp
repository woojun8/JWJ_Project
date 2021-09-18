// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherPlayer.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerAnim.h"
#include <LogicValue.h>
#include "UnActorManager.h"
#include "MainActor.h"
#include "UnResManager.h"

AOtherPlayer::AOtherPlayer()
{
	GetMesh()->SetSkeletalMesh(UnResManager::Inst().GetMeshAsset());
	GetMesh()->SetAnimInstanceClass(UnResManager::Inst().GetAnimAsset());
}

void AOtherPlayer::ActorEnd()
{
	UE_LOG(LogTemp, Error, TEXT("Player Death"));

	// 클라이언트 때였기 때문에
	// UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::MONSTER, reinterpret_cast<__int64>(this));
	// UpdateID 싱글이라면 이 ID를 자기 껄로 하면 되
	UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::PLAYER, UpdateID);
}

void AOtherPlayer::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerAnim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
}

void AOtherPlayer::OtherPlayerUpdate()
{
	if (true == m_UpdateQueue.empty())
	{
		// 큐가 비었다는것은 아무것도 안한다?
		m_PlayerAnim->SetIsMove(false);
		return;
	}

	const FTransform& Trans = GetActorTransform();
	FRotator RRot = Trans.Rotator();

	ActorUpdateData& Data = m_UpdateQueue.front();

	if (true == Data.IsSet)
	{
		UE_LOG(LogTemp, Error, L"SetUpdate %f, %f, %f  Rot : %f", Data.Pos.x, Data.Pos.y, Data.Pos.z, Data.Rot.x);
		FRotator NewRRot;
		NewRRot.Add( 0.0f, Data.Rot.x, 0.0f );
		SetActorRotation(NewRRot);

		FVector MoveVector = { Data.Pos.x, Data.Pos.y, Data.Pos.z };
		SetActorLocation(MoveVector);
		m_UpdateQueue.pop();
		return;
	}

	if (Data.Rot != float4::ZERO)
	{
		RRot.Add(0.0f, Data.Rot.y, 0.0f);
		SetActorRotation(RRot);
	}

	if (Data.Move != float4::ZERO)
	{
		FVector MoveVector = { Data.Move.x, Data.Move.y, Data.Move.z };

		/*FVector4 CalPos = Trans.GetLocation() + MoveVector;
		FVector Dir = CalPos - Trans.GetLocation();
		Dir.Normalize();

		float Dot = FVector::DotProduct(FVector::ForwardVector, Dir);
		float Degree = FMath::RadiansToDegrees(FMath::Acos(Dot));

		FVector cross = FVector::CrossProduct(FVector::ForwardVector, Dir);
		if (cross.Z < 0)
		{
			Degree *= -1.f;
		}*/
		//Data.AnimData;
		m_PlayerAnim->SetDirAngle(Data.AnimData.m_MoveDirAngle);
		m_PlayerAnim->SetIsMove(Data.AnimData.m_IsMove);
		
		SetActorLocation(GetActorLocation() + MoveVector);
	}

	if (Data.AnimData.m_AttackEnable)
	{				
		m_PlayerAnim->NormalAttack();
	}

	//m_PlayerAnim->SetAnimData(Data.AnimData);
	
	m_UpdateQueue.pop();
}
