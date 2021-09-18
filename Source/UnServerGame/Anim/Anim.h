// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim.generated.h"

//UENUM(BlueprintType)
//enum class EPlayerAnimType : uint8
//{
//	Idle,
//	Run,
//	Attack,
//	Death,
//	Jump,
//	Skill1,
//	Skill2,
//	Skill3
//};
//
////UENUM(BlueprintType)
////enum class EMoveDir : uint8
////{
////	None,
////	Front,
////	Back,
////	Up,
////	Down
////};
//
//UENUM(BlueprintType)
//enum class EAttackType : uint8
//{
//	None,
//	Attack1,
//	Attack2,
//	Attack3,
//	Attack4
//};

UCLASS()
class UNSERVERGAME_API UAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAnim();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	//EPlayerAnimType m_AnimType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	//EMoveDir m_MoveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	float m_MoveDirAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	float m_Speed;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	//EAttackType  m_AttackType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	//EFallingState  m_FallingState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	float m_JumpEnableTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	bool m_AttackEnable;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
