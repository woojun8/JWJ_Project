// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim.h"
#include "../MainActor.h"

UAnim::UAnim()
{
//	m_AnimType = EPlayerAnimType::Idle;
	//m_MoveDir = EMoveDir::None;

	m_MoveDirAngle = 0.0f;
	m_Speed = 0.f;


}

void UAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// AMainActor�� ���´�.
	AMainActor* MainActor = Cast<AMainActor>(TryGetPawnOwner());
	// TryGetPawnOwner : �� AnimInstance�� �������ִ� �޽��� Pawn�� �����´�.
	// Cast�� �𸮾� ����ȯ. �߸��� Ÿ������ ����ȯ�� nullptr�� ��ȯ�Ѵ�.

	if (IsValid(MainActor))
	{
		// MovementComponent�� ���´�.
		UCharacterMovementComponent* pMovement = MainActor->GetCharacterMovement();

		if (IsValid(pMovement))
		{
			m_Speed = pMovement->Velocity.Size();

			if (m_Speed > 0.f)
			{
				// �ӵ��� ���� ��� ���� ���溤�Ϳ� �ӵ����Ϳ��� ������ ���Ͽ�
				// �ݴ������ ��� ������ �ڷ�, �ƴ� ��� ������ �����Ѵ�.
				FVector	vForward = MainActor->GetActorForwardVector();
				FVector	vVelocity = pMovement->Velocity;

				// �Ѵ� �������ͷ� ������ش�.
				vForward.Normalize();
				vVelocity.Normalize();

				float fDot = FVector::DotProduct(vForward, vVelocity);

				//m_MoveDirAngle = FMath::RadiansToDegrees(FMath::Acos(fDot));

				if (fDot < 0.f)
				{
					//m_MoveDir = EMoveDir::Back;
					m_MoveDirAngle = 180.f;
				}
				else
				{
					//m_MoveDir = EMoveDir::Front;
					m_MoveDirAngle = 0.f;
				}

				//m_AnimType = EPlayerAnimType::Run;
			}
			else
			{
				//m_AnimType = EPlayerAnimType::Idle;
				//m_MoveDir = EMoveDir::None;
			}
		}
	}
}
