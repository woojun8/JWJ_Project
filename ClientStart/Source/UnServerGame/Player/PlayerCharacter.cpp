// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "../UnServerConnect.h"
#include "../UnActorManager.h"
#include <ClientToServer.h>
#include <LogicValue.h>
#include "../UnResManager.h"
#include "PlayerAnim.h"

APlayerCharacter*  APlayerCharacter::MainCharactor = nullptr;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Arm을 Root에 붙인다
	m_Arm->SetupAttachment(RootComponent);

	// Camera를 Arm에 붙인다
	m_Camera->SetupAttachment(m_Arm);

	// Camera 위치 세팅
	//m_Arm->TargetArmLength = 800.f;
	//m_Arm->TargetOffset = FVector(0.f, 200.f, 200.f);

	m_MoveDir = EMoveDir::None;
	m_MoveVector = FVector::ZeroVector;
	m_RotDir = 0.f;
	m_Speed = 500.f;
	m_RotSpeed = 50.f;
	m_IsMove = false;
	m_MoveUpdateCount = 0;
	m_IsAttack = false;
	m_AttackNotify = false;

	m_PlayerAnim = nullptr;

	GetMesh()->SetSkeletalMesh(UnResManager::Inst().GetMeshAsset());
	GetMesh()->SetAnimInstanceClass(UnResManager::Inst().GetAnimAsset());
}

APlayerCharacter::~APlayerCharacter()
{
	UnResManager::Inst().Release();
	UnActorManager::GetInst().Clear();
	UnServerConnect::GetInst().Close();
	UnServerConnect::GetInst().ThreadStop();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GameEngineCollision::Init();
	Super::BeginPlay();
	UnResManager::Inst().ResInit();
	MainCharactor = this;
	UnServerConnect::GetInst().Init(GetWorld());

	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::MONSTER, (int)LogicValue::CollisionLayer::PLAYERBULLET);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::MONSTER, (int)LogicValue::CollisionLayer::PLAYEREXBULLET);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::MONSTER, (int)LogicValue::CollisionLayer::PLAYERATTACK);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::MONSTERBULLET);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::ITEM);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::POTAL);

	m_PlayerAnim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UnActorManager::GetInst().DestoryRelease();

	UnServerConnect::GetInst().MainProcess.MsgUpdate();

	if (0 == UnServerConnect::GetInst().m_GameStart)
	{
		return;
	}

	if (false == UnServerConnect::GetInst().IsServer)
	{
		SingleUpdate(DeltaTime);
	}
	else 
	{
		ServerUpdate(DeltaTime);
	}
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveLeft"), this, &APlayerCharacter::MoveLeft);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveFoward"), this, &APlayerCharacter::MoveFoward);
	PlayerInputComponent->BindAxis(TEXT("MoveBack"), this, &APlayerCharacter::MoveBack);

	PlayerInputComponent->BindAxis(TEXT("RotRight"), this, &APlayerCharacter::RotRight);
	PlayerInputComponent->BindAxis(TEXT("RotLeft"), this, &APlayerCharacter::RotLeft);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::NormalAttack);
}

void APlayerCharacter::SingleUpdate(float DeltaTime)
{
	const FTransform& Data = GetActorTransform();

	// 이동량
	m_MoveVector.Normalize();
	FVector CalMoveVector = m_MoveVector * DeltaTime * m_Speed;
	
	// 이동 했다면
	if (m_MoveVector != FVector(0, 0, 0))
	{
		FVector4 CalPos = Data.GetLocation() + CalMoveVector;
		FVector Dir = CalPos - Data.GetLocation();
		Dir.Normalize();
		//LOG(TEXT("Dir : %.3f, %.3f, %.3f"), Dir.X, Dir.Y, Dir.Z);

		float Dot = FVector::DotProduct(FVector::ForwardVector, Dir);
		float Degree = FMath::RadiansToDegrees(FMath::Acos(Dot));

		// 여기서 두 백터를 크로스 하여 회전할 축을 얻게 된다.
		// 이 크로스 백터는 Axis회전의 회전축이 되며 , 그 양수 음수로 회전 방향 왼쪽(음수), 오른쪽(양수)를 알 수 있다.
		FVector cross = FVector::CrossProduct(FVector::ForwardVector, Dir);
		if (cross.Z < 0)
		{
			Degree *= -1.f;
		}
		//LOG(TEXT("Degree : %.3f"), Degree);

		m_PlayerAnim->SetDirAngle(Degree);
		m_PlayerAnim->SetIsMove(true);
		//LOG(TEXT("SetIsMove(true)"));

		SetActorLocation(CalPos);
		m_MoveVector = FVector(0, 0, 0);
	}
	else
	{
		m_PlayerAnim->SetIsMove(false);
		//LOG(TEXT("SetIsMove(false)"));
	}

	// Camera 위치 세팅
	m_Arm->TargetArmLength = 1000.f;
	m_Arm->TargetOffset = FVector(0.f, 0.f, 100.f);

	//int a = 0;
}

void APlayerCharacter::ServerUpdate(float DeltaTime)
{
	UnActorManager::GetInst().Collision();

	// 서버로 치면 업데이트죠?
	const FTransform& Data = GetActorTransform();
		
	float Rot = m_RotDir * DeltaTime * m_RotSpeed;

	// 이동량
	m_MoveVector.Normalize();
	FVector CalMoveVector = m_MoveVector * DeltaTime * m_Speed;
	FRotator RRot = Data.Rotator();

	// 이동
	if (CalMoveVector != FVector(0, 0, 0))
	{
		float4 Move = &CalMoveVector.X;
		if (true == UnActorManager::GetInst().CheckCollison(this, COLTYPE::CT_SPHERE, float4(100.0f, 100.0f, 100.0f), Move, 0))
		{
			UE_LOG(LogTemp, Error, L"WallCol", DeltaTime);
			m_MoveVector = FVector(0, 0, 0);
			return;
		}
		else
		{
			FVector4 CalPos = Data.GetLocation() + CalMoveVector;
			SetActorLocation(CalPos);
		}
	}

	// 회전
	if (Rot != 0.0f)
	{
		RRot.Add(0.0f, Rot, 0.0f);
		SetActorRotation(RRot);
	}

	if (m_MoveVector != FVector(0, 0, 0) ||			// 이동	
		Rot != 0.0f ||								// 회전
		m_IsAttack == true)							// 공격
	{
		FVector4 CalPos = Data.GetLocation() + CalMoveVector;
		FVector Dir = CalPos - Data.GetLocation();
		Dir.Normalize();

		float Dot = FVector::DotProduct(GetActorForwardVector(), Dir);
		float Degree = FMath::RadiansToDegrees(FMath::Acos(Dot));

		FVector cross = FVector::CrossProduct(GetActorForwardVector(), Dir);
		if (cross.Z < 0)
		{
			Degree *= -1.f;
		}
		
		// 업데이트 패킷을 보낸다.
		ClientPlayerPacket NewMovePacket;
		NewMovePacket.m_State = ActorState::Update;
		NewMovePacket.ActorData.Count = m_MoveUpdateCount++;
		NewMovePacket.ActorData.DeltaTime = DeltaTime;
		NewMovePacket.ActorData.Rot = { 0.f, Rot , 0.f };
		NewMovePacket.ActorData.Pos = { GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z };
		NewMovePacket.ActorData.Dir = { GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z };
		NewMovePacket.ActorData.Right = { GetActorRightVector().X, GetActorRightVector().Y, GetActorRightVector().Z };
		NewMovePacket.ActorData.Move = { CalMoveVector.X, CalMoveVector.Y, CalMoveVector.Z };
		NewMovePacket.ActorData.Scale = { Data.GetScale3D().X, Data.GetScale3D().Y, Data.GetScale3D().Z };

		// 이동상태인지 확인
		if (m_MoveVector == FVector(0, 0, 0))
		{
			NewMovePacket.ActorData.AnimData.m_AnimType = m_AnimData.m_AnimType;
			NewMovePacket.ActorData.AnimData.m_AttackType = m_AnimData.m_AttackType;
			NewMovePacket.ActorData.AnimData.m_MoveDirAngle = 0.f;
			NewMovePacket.ActorData.AnimData.m_IsMove = false;
			//NewMovePacket.ActorData.AnimData.m_AttackEnable = m_AnimData.m_AttackEnable;
			NewMovePacket.ActorData.AnimData.m_AttackEnable = m_IsAttack;

			m_PlayerAnim->SetDirAngle(0.f);
			m_PlayerAnim->SetIsMove(false);
		}
		else
		{
			NewMovePacket.ActorData.AnimData.m_AnimType = m_AnimData.m_AnimType;
			NewMovePacket.ActorData.AnimData.m_AttackType = m_AnimData.m_AttackType;
			NewMovePacket.ActorData.AnimData.m_MoveDirAngle = Degree;
			NewMovePacket.ActorData.AnimData.m_IsMove = true;
			//NewMovePacket.ActorData.AnimData.m_AttackEnable = m_AnimData.m_AttackEnable;
			NewMovePacket.ActorData.AnimData.m_AttackEnable = m_IsAttack;

			m_PlayerAnim->SetDirAngle(Degree);
			m_PlayerAnim->SetIsMove(true);
		}	

		// 공격가능한 상황
		/*if (m_AttackNotify)
		{						
			NewMovePacket.m_State = ActorState::Att;
			FVector vLocation = m_PlayerAnim->GetSkelMeshComponent()->GetSocketLocation(TEXT("sword_top_socket"));
			AAttCol* NewAttCol = UnActorManager::GetInst().CreateServerManagerObjectToCol<AAttCol>(m_AttColCreateType
				, vLocation, (int)LogicValue::CollisionLayer::PLAYERATTACK, -1, { 50.0f, 50.0f, 50.0f }, COLTYPE::CT_SPHERE);
			NewMovePacket.UpdateID = reinterpret_cast<__int64>(NewAttCol);
			NewMovePacket.ActorData.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewAttCol));
			NewMovePacket.ActorData.SubType = 4;
			float4 vPos = { vLocation.X, vLocation.Y, vLocation.Z };
			NewMovePacket.ActorData.AttPos = vPos;

			LOG(TEXT("X : %f, Y : %f, Z : %f"), vPos.x, vPos.y, vPos.z);

			m_AttackNotify = false;
		}*/

		if (m_IsAttack)
		{
			NewMovePacket.m_State = ActorState::Att;
			FVector vLocation = m_PlayerAnim->GetSkelMeshComponent()->GetSocketLocation(TEXT("sword_top_socket"));
			AAttCol* NewAttCol = UnActorManager::GetInst().CreateServerManagerObjectToCol<AAttCol>(m_AttColCreateType
				, vLocation, (int)LogicValue::CollisionLayer::PLAYERATTACK, -1, { 20.0f, 20.0f, 20.0f }, COLTYPE::CT_SPHERE);
			NewMovePacket.UpdateID = reinterpret_cast<__int64>(NewAttCol);
			NewMovePacket.ActorData.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewAttCol));
			NewMovePacket.ActorData.SubType = 4;
			float4 vPos = { vLocation.X, vLocation.Y, vLocation.Z };
			NewMovePacket.ActorData.AttPos = vPos;

			//LOG(TEXT("X : %f, Y : %f, Z : %f"), vPos.x, vPos.y, vPos.z);

			//m_AttackNotify = false;
		}
			
		UnServerConnect::GetInst().Send(NewMovePacket);
	}
	else
	{
		m_PlayerAnim->SetIsMove(false);
	}

	if (m_MoveVector != FVector(0, 0, 0))
	{
		m_MoveVector = FVector(0, 0, 0);
	}

	if (m_RotDir != 0)
	{
		m_RotDir = 0;
	}

	if (true == m_IsAttack)
	{
		m_IsAttack = false;
	}

	//if (true == m_AttackNotify)
	//{
	//	m_AttackNotify = false;
	//}
}

void APlayerCharacter::MoveLeft(float _Scale)
{
	if (0.f !=_Scale)
	{
		m_MoveVector += -GetActorRightVector();
		//LOG(TEXT("MoveLeft"));
		m_Speed = 500.f;
	}	
}
void APlayerCharacter::MoveRight(float _Scale)
{
	if (0.f != _Scale)
	{
		m_MoveVector += GetActorRightVector();
		//LOG(TEXT("MoveRight"));
		m_Speed = 500.f;
	}
}
void APlayerCharacter::MoveFoward(float _Scale)
{
	if (0.f != _Scale)
	{
		m_MoveVector += GetActorForwardVector();
		//LOG(TEXT("MoveFoward"));
		m_Speed = 500.f;
	}
}

void APlayerCharacter::MoveBack(float _Scale)
{
	if (0.f != _Scale)
	{
		m_MoveVector += -GetActorForwardVector();
		//LOG(TEXT("MoveBack"));
		m_Speed = 500.f;
	}
}

void APlayerCharacter::RotRight(float _Scale)
{
	if (0.f != _Scale)
	{
		m_RotDir = 1.f;
	}
}

void APlayerCharacter::RotLeft(float _Scale)
{
	if (0.f != _Scale)
	{
		m_RotDir = -1.f;
	}
}

void APlayerCharacter::NormalAttack()
{
	m_IsAttack = true;
	m_PlayerAnim->NormalAttack();
}
