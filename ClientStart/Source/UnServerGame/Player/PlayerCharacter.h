// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"

#include "../Block.h" 				   
#include "../OtherPlayer.h"
#include "../Potal.h"
#include "../Item.h"
#include "../Bullet.h"
#include "../ExBullet.h"
#include "../Monster.h"
#include "../AttCol.h"

#include "PlayerCharacter.generated.h"

//UENUM(BlueprintType)
//enum class EMoveDir : uint8
//{
//	None,
//	Front,
//	Back,
//	Up,
//	Down
//};

UCLASS()
class UNSERVERGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	static APlayerCharacter* MainCharactor;	

public:
	static APlayerCharacter& GetInst()
	{
		return *MainCharactor;
	}

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	~APlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_Arm;

	EMoveDir m_MoveDir;
	FVector m_MoveVector;
	float m_RotDir;
	float m_Speed;
	float m_RotSpeed;
	bool m_IsMove;
	int m_MoveUpdateCount;
	bool m_IsAttack;
	bool m_AttackNotify;

	class UPlayerAnim* m_PlayerAnim;
	ActorAnimData m_AnimData;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABlock> m_MainPlayerCreateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AOtherPlayer> m_OtherPlayerCreateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMonster> m_MonsterCreateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABlock> m_WallCreateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABlock> m_FloorCreateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APotal> m_PotalCreateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AItem> m_ItemCreateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABullet> m_BulletCreateType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AExBullet> m_ExBulletCreateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAttCol> m_AttColCreateType;

public:
	EMoveDir GetMoveDir() const
	{
		return m_MoveDir;
	}

	void SetAnimData(ActorAnimData AnimData)
	{
		m_AnimData = AnimData;
	}

	void SetAttackNotify(bool AttackNotify)
	{
		m_AttackNotify = AttackNotify;
	}

	UPlayerAnim* GetPlayerAnim()
	{
		return m_PlayerAnim;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void SingleUpdate(float DeltaTime);
	void ServerUpdate(float DeltaTime);

public:
	void MoveLeft(float _Scale);
	void MoveRight(float _Scale);
	void MoveFoward(float _Scale);
	void MoveBack(float _Scale);

	void RotRight(float _Scale);
	void RotLeft(float _Scale);

	void NormalAttack();
};
