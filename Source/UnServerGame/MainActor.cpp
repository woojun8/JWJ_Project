// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "Anim/Anim.h"
#include "UnServerConnect.h"
#include "UnActorManager.h"
#include <ClientToServer.h>
#include <LogicValue.h>
#include "UnResManager.h"

AMainActor* AMainActor::MainActor = nullptr;

// Sets default values
AMainActor::AMainActor() : Speed(2000.0f), RotSpeed(180.0f), IsMouseCenter(false), MoveUpdateCount(0), IsFire(false), FireDelay(0.2f), IsExFire(false)
{
	PrimaryActorTick.bCanEverTick = true;
	// m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast.TwinBlast'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
		
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Twinblast/BPTwinblastAnim.BPTwinblastAnim_c'"));
	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}

	m_Cam = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("Camera")));

	if (nullptr == m_Cam)
	{
		UE_LOG(LogTemp, Error, L"if (nullptr == m_Cam)");
	}

	UE_LOG(LogTemp, Error, L"AMainActor::AMainActor()");
}

AMainActor::~AMainActor() 
{
	// ������ �׷��� ���ѰŴϱ�.
	UE_LOG(LogTemp, Error, L"AMainActor::~AMainActor()");

	UnResManager::Inst().Release();
	UnActorManager::GetInst().Clear();
	UnServerConnect::GetInst().Close();
	UnServerConnect::GetInst().ThreadStop();
}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	//CharacterPacket Pacekt;

	////__int64 UpdateID;
	////GameEngineString NICKNAME;
	////GameEngineString EndIndex;
	////int LastX;
	////int LastY;
	////int Att;
	////int Hp;
	////int MaxHp;
	////std::vector<ItemData> ItemDatas;
	//
	//Pacekt.UpdateID = 312312321;
	//Pacekt.NICKNAME = L"AFSDFASDFHJKASLDFJASDKL";
	//Pacekt.EndIndex = L"�����Ӥ����������Ӥ���";
	//Pacekt.LastY = 2000;
	//Pacekt.LastX = 1000;
	//Pacekt.LastY = 2000;
	//Pacekt.Hp = 11;
	//Pacekt.Att = 10;
	//Pacekt.MaxHp = 1022;
	//for (size_t i = 0; i < 6; i++)
	//{
	//	ItemData Data2 = ItemData();

	//	Data2.Count = 10;
	//	Data2.IconResData = 3;
	//	Data2.InvenOrder = 6;
	//	Data2.Name = TEXT("FASDFASD");
	//	Data2.Type = 2222;

	//	Pacekt.ItemDatas.push_back(Data2);
	//}

	//GameEngineSerializer Ser0 = Pacekt.Serialize();
	//CharacterPacket Pacekt2;

	//Pacekt2.DeSerialize(Ser0);
	

	GameEngineCollision::Init();
	Super::BeginPlay(); 
	UnResManager::Inst().ResInit();
	MainActor = this;
	UnServerConnect::GetInst().Init(GetWorld());

	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::MONSTER, (int)LogicValue::CollisionLayer::PLAYERBULLET);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::MONSTER, (int)LogicValue::CollisionLayer::PLAYEREXBULLET);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::MONSTERBULLET);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::ITEM);
	UnActorManager::GetInst().Link((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::POTAL);

	m_Anim = Cast<UAnim>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �츮������ �����ٶ�� �����ϰ� ���⼭ ����̴ϴ�.

	UnActorManager::GetInst().DestoryRelease();

	// �޼��� ������Ʈ���� �˴ϴ�.
	UnServerConnect::GetInst().MainProcess.MsgUpdate();

	if (0 == UnServerConnect::GetInst().m_GameStart)
	{
		return;
	}


	if (false == UnServerConnect::GetInst().IsServer)
	{
		SingleUpdate(DeltaTime);
	}
	else {
		ServerUpdate(DeltaTime);
	}


	// UnActorManager::GetInst().DestoryUpdate();
	// ��� �÷��̳�
	// ƽ��
	// ��������.
	// 

}

// Called to bind functionality to input
void AMainActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



	// c++�� ���ؼ� �� ���ο��� ��� ���� �Ǿ��ְڱ���

	// IE_Pressed ������ 1��
	// IE_DoubleClick ������ 2��
	// IE_Released �ȴ����� �ִ�
	//PlayerInputComponent->BindAction(TEXT("MoveLeft"), EInputEvent::IE_Axis, this, &AMainActor::MoveLeft);
	//PlayerInputComponent->BindAction(TEXT("MoveRight"), EInputEvent::IE_Axis, this, &AMainActor::MoveRight);
	//PlayerInputComponent->BindAction(TEXT("MoveFoward"), EInputEvent::IE_Axis, this, &AMainActor::MoveFoward);
	PlayerInputComponent->BindAction(TEXT("Shot"), EInputEvent::IE_Pressed, this, &AMainActor::FireShot);
	PlayerInputComponent->BindAction(TEXT("ExShot"), EInputEvent::IE_Pressed, this, &AMainActor::ExShot);
	PlayerInputComponent->BindAction(TEXT("MouseFree"), EInputEvent::IE_Pressed, this, &AMainActor::MouseFree);
	PlayerInputComponent->BindAction(TEXT("ChangeShot"), EInputEvent::IE_Pressed, this, &AMainActor::ChangeShot);

	PlayerInputComponent->BindAxis(TEXT("MoveLeft"), this, &AMainActor::MoveLeft);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainActor::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveFoward"), this, &AMainActor::MoveFoward);
	PlayerInputComponent->BindAxis(TEXT("MoveBack"), this, &AMainActor::MoveBack);

	//PlayerInputComponent->BindAction(TEXT("AttLeft"), EInputEvent::IE_Pressed, this, &AMainActor::AttLeft);
	//PlayerInputComponent->BindAction(TEXT("AttRight"), EInputEvent::IE_Released, this, &AMainActor::AttRight);
	//PlayerInputComponent->BindAction(TEXT("AttUp"), EInputEvent::IE_Pressed, this, &AMainActor::AttUp);
	//PlayerInputComponent->BindAction(TEXT("AttDown"), EInputEvent::IE_Pressed, this, &AMainActor::AttDown);


}

void AMainActor::MoveLeft(float _Scale)
{
	if (_Scale == 0.0f
		|| false == IsMouseCenter)
	{
		return;
	}
	MoveVector += -GetActorRightVector();
}
void AMainActor::MoveRight(float _Scale)
{
	if (_Scale == 0.0f
		|| false == IsMouseCenter)
	{
		return;
	}
	MoveVector += GetActorRightVector();
}
void AMainActor::MoveFoward(float _Scale)
{

	if (_Scale == 0.0f
		|| false == IsMouseCenter)
	{
		return;
	}

	// ȸ����� X Y Z���� �������ͷ� �̵��ؾ� �Ѵ�.

	// const FTransform& Data = GetActorTransform();
	
	
	MoveVector += GetActorForwardVector();
}
void AMainActor::MoveBack(float _Scale)
{
	if (_Scale == 0.0f
		|| false == IsMouseCenter)
	{
		return;
	}
	MoveVector += -GetActorForwardVector();
}

void AMainActor::ChangeShot() 
{
	if(false == IsMouseCenter)
	{
		return;
	}

	Is3Fire = !Is3Fire;
}

void AMainActor::MouseFree() 
{
	IsMouseCenter = !IsMouseCenter;

	MoveVector = FVector(0.0F, 0.0F, 0.0F);
	MousePos = FVector2D(0.0F, 0.0F);
}

void AMainActor::FireShot()
{
	if (false == IsMouseCenter)
	{
		return;
	}

	IsFire = true;

}

void AMainActor::ExShot()
{
	if (false == IsMouseCenter)
	{
		return;
	}

	IsExFire = true;
}


void AMainActor::ServerUpdate(float DeltaTime)
{
	UnActorManager::GetInst().Collision();

	if (false == IsMouseCenter)
	{
		return;
	}

	FireDelay -= DeltaTime;

	// �浹�� �� �տ��� �ǰ�.


	// ������ ġ�� ������Ʈ��?
	const FTransform& Trans = GetActorTransform();
	FVector2D RotScale = MouseCenter - MousePos;
	float RotX = -RotScale.X * DeltaTime * RotSpeed;

	// �̵���
	MoveVector.Normalize();
	FVector CalMoveVector = MoveVector * DeltaTime * Speed;
	FRotator RRot = Trans.Rotator();

	// �̵�
	if (CalMoveVector != FVector(0, 0, 0))
	{
		float4 Move = &CalMoveVector.X;
		if (true == UnActorManager::GetInst().CheckCollison(this, COLTYPE::CT_SPHERE, float4(100.0f, 100.0f, 100.0f), Move, 0))
		{
			UE_LOG(LogTemp, Error, L"WallCol", DeltaTime);
			MoveVector = FVector(0, 0, 0);
			return;
		}
		else
		{
			FVector4 CalPos = Trans.GetLocation() + CalMoveVector;
			SetActorLocation(CalPos);
		}
	}


	// ȸ��
	if (true == IsMouseCenter && RotX != 0.0f)
	{
		RRot.Add(0.0f, RotX, 0.0f);
		SetActorRotation(RRot);
	}

	if (
		MoveVector != FVector(0, 0, 0) ||  // �̵�������
		RotX != 0.0f || // ȸ���߰ų�
		(0 >= FireDelay && IsFire == true) ||// �Ѿ� ���ų�
		(0 >= FireDelay && IsExFire == true)
		)
	{
		// ������Ʈ ��Ŷ�� ������.
		ClientPlayerPacket NewMovePacekt;
		NewMovePacekt.m_State = ActorState::Update;
		NewMovePacekt.ActorData.Count = MoveUpdateCount++;
		NewMovePacekt.ActorData.DeltaTime = DeltaTime;
		NewMovePacekt.ActorData.Rot = { RotX, RotScale.Y };
		NewMovePacekt.ActorData.Pos = { GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z };
		NewMovePacekt.ActorData.Dir = { GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z };
		NewMovePacekt.ActorData.Right = { GetActorRightVector().X, GetActorRightVector().Y, GetActorRightVector().Z };
		NewMovePacekt.ActorData.Move = { CalMoveVector.X, CalMoveVector.Y, CalMoveVector.Z };
		NewMovePacekt.ActorData.Scale = {100.0f, 100.0f, 100.0f};
		// UE_LOG(LogTemp, Error, L"Move %d", NewMovePacekt.ActorData.Count);

		//UE_LOG(LogTemp, Error, L"Move %f %f %f,    %f %f %f"
		//	, NewMovePacekt.ActorData.Pos.x, NewMovePacekt.ActorData.Pos.y, NewMovePacekt.ActorData.Pos.z
		//	, NewMovePacekt.ActorData.Move.x, NewMovePacekt.ActorData.Move.y, NewMovePacekt.ActorData.Move.z);

		if (0 >= FireDelay && IsFire == true && false == Is3Fire)
		{
				UE_LOG(LogTemp, Error, L"Is3Fire");
				NewMovePacekt.m_State = ActorState::Att;
				FVector Dir = GetActorForwardVector();
				FVector StartBulletPos = GetActorLocation() + Dir * 50.0f;
				ABullet* NewBullet = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABullet>(m_BulletCreateType
					, StartBulletPos, (int)LogicValue::CollisionLayer::PLAYERBULLET, -1, { 50.0f, 50.0f, 50.0f }, COLTYPE::CT_SPHERE);
				NewBullet->DirVector = Dir;
				// �׷� ���߿� �������� �������� �淿�� �׾��� �̷��� ������ ������ �˴ϴ�.
				NewMovePacekt.UpdateID = reinterpret_cast<__int64>(NewBullet);
				NewMovePacekt.ActorData.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewBullet));
				NewMovePacekt.ActorData.SubType = 1;
				FireDelay = 0.2f;
		}
		else if (0 >= FireDelay && IsFire == true && true == Is3Fire)
		{
			NewMovePacekt.m_State = ActorState::Att;
			FVector Dir[3] = { GetActorForwardVector(), GetActorForwardVector() + GetActorRightVector(), GetActorForwardVector() + -GetActorRightVector() };

			for (size_t i = 0; i < 3; i++)
			{
				Dir[i].Normalize();
				FVector StartBulletPos = GetActorLocation() + Dir[i] * 50.0f;
				ABullet* NewBullet = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABullet>(m_BulletCreateType
					, StartBulletPos, (int)LogicValue::CollisionLayer::PLAYERBULLET, -1, { 50.0f, 50.0f, 50.0f }, COLTYPE::CT_SPHERE);
				NewBullet->DirVector = Dir[i];
				NewMovePacekt.ActorData.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewBullet));
				// �׷� ���߿� �������� �������� �淿�� �׾��� �̷��� ������ ������ �˴ϴ�.
				FireDelay = 0.2f;
			}

			NewMovePacekt.ActorData.SubType = 3;
			NewMovePacekt.UpdateID = 3;
			
		}
		else if ((0 >= FireDelay && IsExFire == true))
		{
			NewMovePacekt.m_State = ActorState::Att;
			FVector Dir = GetActorForwardVector();
			// �� z�� ���� ��.
			// ���� �ö󰡷��� ���� �������� ������?

			FVector StartBulletPos = GetActorLocation() + Dir * 50.0f;
			AExBullet* NewBullet = UnActorManager::GetInst().CreateServerManagerObjectToCol<AExBullet>(m_ExBulletCreateType
				, StartBulletPos, (int)LogicValue::CollisionLayer::PLAYEREXBULLET, -1, { 50.0f, 50.0f, 50.0f }, COLTYPE::CT_SPHERE);
			//Dir.Z = 0.1f;
			//Dir.Normalize();

			NewBullet->GetGameCol()->Off();

			NewBullet->DirVector = Dir;

			// �׷� ���߿� �������� �������� �淿�� �׾��� �̷��� ������ ������ �˴ϴ�.
			NewMovePacekt.UpdateID = reinterpret_cast<__int64>(NewBullet);
			NewMovePacekt.ActorData.SubType = 2;
			NewMovePacekt.ActorData.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewBullet));

			

			FireDelay = 0.2f;
			UE_LOG(LogTemp, Error, L"EXFire Start", DeltaTime);
		}


		UnServerConnect::GetInst().Send(NewMovePacekt);


	}


	IsFire = false;
	IsExFire = false;

	if (MoveVector != FVector(0, 0, 0) || RotScale != FVector2D(0, 0))
	{
		MoveVector = FVector(0, 0, 0);
		RotScale = FVector2D(0, 0);
	}

}

void AMainActor::SingleUpdate(float DeltaTime)
{
	if (false == IsMouseCenter)
	{
		return;
	}

	UE_LOG(LogTemp, Error, L"Update %f", DeltaTime);

	UnActorManager::GetInst().Collision();
	// �浹�� �� �տ��� �ǰ�.


	const FTransform& Data = GetActorTransform();
	FVector2D RotScale = MouseCenter - MousePos;

	// �̵���
	MoveVector.Normalize();
	FVector CalMoveVector = MoveVector * DeltaTime * Speed;
	FRotator RRot = Data.Rotator();

	if (true == IsMouseCenter && RotScale != FVector2D(0, 0))
	{
		RRot.Add(0.0f, -RotScale.X * DeltaTime * RotSpeed, 0.0f);
		SetActorRotation(RRot);
	}

	// �̵� �ߴٸ�
	if (MoveVector != FVector(0, 0, 0))
	{
		float4 Move = &CalMoveVector.X;
		if (true == UnActorManager::GetInst().CheckCollison(this, COLTYPE::CT_SPHERE, float4(100.0f, 100.0f, 100.0f), Move, 0))
		{
			MoveVector = FVector(0, 0, 0);
			return;
		}
		else 
		{
			FVector4 CalPos = Data.GetLocation() + CalMoveVector;
			SetActorLocation(CalPos);
			MoveVector = FVector(0, 0, 0);
		}
	}
}

void AMainActor::MousePosCenterLock(APlayerController* _Con) 
{
	if (false == IsMouseCenter)
	{
		return;
	}


	if (nullptr != _Con)
	{
		const ULocalPlayer* LPlayer = _Con->GetLocalPlayer();
		if (nullptr != LPlayer && nullptr != LPlayer->ViewportClient)
		{
			FViewport* ViewPtr = LPlayer->ViewportClient->Viewport;

			LPlayer->ViewportClient->GetMousePosition(MousePos);

			if (nullptr != ViewPtr)
			{
				LPlayer->ViewportClient->GetViewportSize(MouseCenter);
				//UE_LOG(LogTemp, Error, L"MousePos %f %f", Pos.X, Pos.Y);
				//UE_LOG(LogTemp, Error, L"ScreenSize %f %f", MouseCenter.X, MouseCenter.Y);
				const int32 X = static_cast<int32>(MouseCenter.X * 0.5f);
				const int32 Y = static_cast<int32>(MouseCenter.Y * 0.5f);
				ViewPtr->SetMouse(X, Y);
				MouseCenter.X = X;
				MouseCenter.Y = Y;
			}

		}

	}
}
