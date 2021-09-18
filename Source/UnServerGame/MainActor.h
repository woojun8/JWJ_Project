// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// UCameraComponent의 헤더를 사용하려면
// EngineMinimal 로 변경해줘야 한다.
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Block.h" // 언리얼이 정한 헤더규칙은
				   // 언제나 제네리이터 헤더는 그 클래스의 가장 아래쪽 헤더로 들어가야 한다.
#include "OtherPlayer.h"
#include "Potal.h"
#include "Item.h"
#include "Bullet.h"
#include "ExBullet.h"
#include "Monster.h"
#include "MainActor.generated.h"

// #include "Block.h" 이런식으로 들어가게 되면 
// 언리얼에서 MainActor.generated를 통한 프리컴파일에 문제가 생길수 있기 때문에 허용하지 않는다.



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
	// 화면을 바라보게 만들기 위한 카메라 컴포넌트
	// 그런데 블루프린트에서 보이진튼 않는다.
	// UPROPERTY()를 이용해서 설정을 해줘야 언리얼 엔진에서 보이게 된다.

	// VisibleAnywhere 블루프린트에서 보여라
	// BlueprintReadOnly 블루프린트에서 볼수만 있게 해라.
	// AllowPrivateAccess private이라도 액세스 가능.

	bool IsMouseCenter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Cam;

	//// 에디터에서만 설정할수 있다.
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

	// 메인액터쪽에서 메세지를 모아서
	// 다른 블록이나
	// 아이템 몬스터등등을 다 처리하게 만들겁니다.

public:
	// Sets default values for this pawn's properties
	AMainActor();
	~AMainActor();

protected:
	// Called when the game starts or when spawned
	// 엔진이 시작하고
	// 루프를 돌기전에
	// 이 클래스가 만들어진다면
	// 실행되는 함수
	virtual void BeginPlay() override;

public:	
	// 게임은 while문을 돌게 되는데
	// 그 한프레임 한프레임마다 실행되는 녀석
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void ServerUpdate(float DeltaTime);
	void SingleUpdate(float DeltaTime);


public: // input
	// Input을 제어할수 있는 class UInputComponent을 인자로 받아서 input에 대한 처리를
	// 미리 정의할수 있게 만들어주는 함수.
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
