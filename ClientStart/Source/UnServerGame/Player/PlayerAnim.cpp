// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "PlayerCharacter.h"

UPlayerAnim::UPlayerAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack1Asset(TEXT("AnimMontage'/Game/Greystone/AMGreystoneAttack1.AMGreystoneAttack1'"));
	if (Attack1Asset.Succeeded())
	{
		m_AttackMontageArray.Add(Attack1Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack2Asset(TEXT("AnimMontage'/Game/Greystone/AMGreystoneAttack2.AMGreystoneAttack2'"));
	if (Attack2Asset.Succeeded())
	{
		m_AttackMontageArray.Add(Attack2Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack3Asset(TEXT("AnimMontage'/Game/Greystone/AMGreystoneAttack3.AMGreystoneAttack3'"));
	if (Attack3Asset.Succeeded())
	{
		m_AttackMontageArray.Add(Attack3Asset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack4Asset(TEXT("AnimMontage'/Game/Greystone/AMGreystoneAttack4.AMGreystoneAttack4'"));
	if (Attack4Asset.Succeeded())
	{
		m_AttackMontageArray.Add(Attack4Asset.Object);
	}

	m_AnimType = EPlayerAnimType::Idle;
	m_MoveDir = EMoveDir::None;

	m_AttackType = EAttackType::None;	

	m_MoveDirAngle = 0.0f;
	m_Speed = 0.f;
}

void UPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	// Player�� ���´�.
	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());
	// TryGetPawnOwner : �� AnimInstance�� �������ִ� �޽��� Pawn�� �����´�.
	// Cast�� �𸮾� ����ȯ. �߸��� Ÿ������ ����ȯ�� nullptr�� ��ȯ�Ѵ�.

	if (IsValid(pPlayer))
	{
		// MovementComponent�� ���´�.
		UCharacterMovementComponent* pMovement = pPlayer->GetCharacterMovement();

		if (IsValid(pMovement))
		{	
			//m_AnimType = EPlayerAnimType::Run;
			//m_AttackType = EAttackType::None;
		}
	}
}

void UPlayerAnim::NormalAttack()
{
	m_AttackEnable = true;

	m_AnimType = EPlayerAnimType::Attack;
	if (m_AttackType == EAttackType::None)
	{
		m_AttackType = EAttackType::Attack1;
		if (!Montage_IsPlaying(m_AttackMontageArray[0]))
		{
			Montage_Play(m_AttackMontageArray[0]);
		}
	}
}

void UPlayerAnim::AnimNotify_AttackLink()
{
	m_AttackLink = true;

	// AnimData ����
	ActorAnimData AnimData;
	AnimData.m_AttackLink = m_AttackLink;

	m_pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (IsValid(m_pPlayer))
	{
		m_pPlayer->SetAnimData(AnimData);
	}
}

void UPlayerAnim::AnimNotify_AttackLinkEnd()
{
	m_AttackLink = false;

	m_AnimType = EPlayerAnimType::Idle;
	m_MoveDir = EMoveDir::None;

	m_AttackType = EAttackType::None;

	m_AttackEnable = false;

	// AnimData ����
	ActorAnimData AnimData;
	AnimData.m_AnimType = (int)m_AnimType;
	AnimData.m_AttackType = (int)m_AttackType;
	AnimData.m_AttackEnable = m_AttackEnable;
	AnimData.m_AttackLink = m_AttackLink;

	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (IsValid(pPlayer))
	{
		pPlayer->SetAnimData(AnimData);
	}
}

void UPlayerAnim::AnimNotify_Hit()
{
	APlayerCharacter* pPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (IsValid(pPlayer))
	{		
		pPlayer->SetAttackNotify(true);
		//LOG(TEXT("X : %f, Y : %f, Z : %f"), vLocation.X, vLocation.Y, vLocation.Z);
	}
}