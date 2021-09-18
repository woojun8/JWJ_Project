// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// UCameraComponent�� ����� ����Ϸ���
// EngineMinimal �� ��������� �Ѵ�.
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Block.h" // �𸮾��� ���� �����Ģ��
				   // ������ ���׸����� ����� �� Ŭ������ ���� �Ʒ��� ����� ���� �Ѵ�.
#include "OtherPlayer.h"
#include "Potal.h"
#include "Item.h"
#include "Bullet.h"
#include "ExBullet.h"
#include "Monster.h"
#include "MainActor.generated.h"

// #include "Block.h" �̷������� ���� �Ǹ� 
// �𸮾󿡼� MainActor.generated�� ���� ���������Ͽ� ������ ����� �ֱ� ������ ������� �ʴ´�.



UCLASS()
class UNSERVERGAME_API AMainActor : public ACharacter
{
	GENERATED_BODY()

private:
	static AMainActor* MainActor;

public:
	static AMainActor& GetInst() 
	{
		return *MainActor;
	}

public:
	// ȭ���� �ٶ󺸰� ����� ���� ī�޶� ������Ʈ
	// �׷��� �������Ʈ���� ������ư �ʴ´�.
	// UPROPERTY()�� �̿��ؼ� ������ ����� �𸮾� �������� ���̰� �ȴ�.

	// VisibleAnywhere �������Ʈ���� ������
	// BlueprintReadOnly �������Ʈ���� ������ �ְ� �ض�.
	// AllowPrivateAccess private�̶� �׼��� ����.

	bool IsMouseCenter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Cam;

	//// �����Ϳ����� �����Ҽ� �ִ�.
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


	float FireDelay;
	bool IsFire;
	bool IsExFire;
	bool Is3Fire;
	int MoveUpdateCount;
	FVector MoveVector;
	FVector AttVector;
	float Speed;
	float RotSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector2D MousePos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector2D MouseCenter;

	class UAnim* m_Anim;

	// ���ξ����ʿ��� �޼����� ��Ƽ�
	// �ٸ� ����̳�
	// ������ ���͵���� �� ó���ϰ� ����̴ϴ�.

public:
	// Sets default values for this pawn's properties
	AMainActor();
	~AMainActor();

protected:
	// Called when the game starts or when spawned
	// ������ �����ϰ�
	// ������ ��������
	// �� Ŭ������ ��������ٸ�
	// ����Ǵ� �Լ�
	virtual void BeginPlay() override;

public:	
	// ������ while���� ���� �Ǵµ�
	// �� �������� �������Ӹ��� ����Ǵ� �༮
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void ServerUpdate(float DeltaTime);
	void SingleUpdate(float DeltaTime);


public: // input
	// Input�� �����Ҽ� �ִ� class UInputComponent�� ���ڷ� �޾Ƽ� input�� ���� ó����
	// �̸� �����Ҽ� �ְ� ������ִ� �Լ�.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveLeft(float _Scale);
	void MoveRight(float _Scale);
	void MoveFoward(float _Scale);
	void MoveBack(float _Scale);
	void FireShot();
	void ExShot();
	void MouseFree();
	void ChangeShot();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void MousePosCenterLock(APlayerController* _Con);

};
