// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

UCLASS()
class UNSERVERGAME_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> m_AttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	EPlayerAnimType m_AnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	EMoveDir m_MoveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	float m_MoveDirAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	float m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	bool m_IsMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	EAttackType  m_AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	bool m_AttackEnable;

	bool m_AttackLink;

	APlayerCharacter* m_pPlayer;

public:
	bool GetAttackEnable()
	{
		return m_AttackEnable;
	}

	void SetAnimData(ActorAnimData AnimData)
	{
		//m_AnimType = (EPlayerAnimType)AnimData.m_AnimType;
		m_AttackEnable = AnimData.m_AttackEnable;
		m_AttackLink = AnimData.m_AttackLink;
		//m_AttackType = (EAttackType)AnimData.m_AttackType;
		m_IsMove = AnimData.m_IsMove;
		m_MoveDirAngle = AnimData.m_MoveDirAngle;
	}

	void SetSpeed(float Speed)
	{
		m_Speed = Speed;
	}

	void SetDirAngle(float DirAngle)
	{
		m_MoveDirAngle = DirAngle;
	}

	void SetIsMove(bool IsMove)
	{
		m_IsMove = IsMove;
	}

	void SetAttackEnable(bool AttackEnalbe)
	{
		m_AttackEnable = AttackEnalbe;
	}

	void SetAttackLink(bool AttackLink)
	{
		m_AttackLink = AttackLink;
	}
public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void NormalAttack();

public:
	UFUNCTION()
	void AnimNotify_AttackLink();

	UFUNCTION()
	void AnimNotify_AttackLinkEnd();

	UFUNCTION()
	void AnimNotify_Hit();
};
