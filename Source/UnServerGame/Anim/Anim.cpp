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

	// AMainActor를 얻어온다.
	AMainActor* MainActor = Cast<AMainActor>(TryGetPawnOwner());
	// TryGetPawnOwner : 이 AnimInstance를 가지고있는 메쉬의 Pawn을 가져온다.
	// Cast는 언리얼 형변환. 잘못된 타입으로 형변환시 nullptr을 반환한다.

	if (IsValid(MainActor))
	{
		// MovementComponent를 얻어온다.
		UCharacterMovementComponent* pMovement = MainActor->GetCharacterMovement();

		if (IsValid(pMovement))
		{
			m_Speed = pMovement->Velocity.Size();

			if (m_Speed > 0.f)
			{
				// 속도가 있을 경우 현재 전방벡터와 속도벡터와의 각도를 구하여
				// 반대방향일 경우 방향을 뒤로, 아닐 경우 앞으로 결정한다.
				FVector	vForward = MainActor->GetActorForwardVector();
				FVector	vVelocity = pMovement->Velocity;

				// 둘다 단위벡터로 만들어준다.
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
