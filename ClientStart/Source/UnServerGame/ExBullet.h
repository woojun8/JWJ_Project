// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameCol.h"
#include "ExBullet.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API AExBullet : public AStaticMeshActor
{
	GENERATED_BODY()
	

public:
	__int64 UpdateID;
	GameCol* m_GameCol;
	float UpPower;
	float AccPower;
	float GravityPower;
	bool IsBoom;

public:
	void SetGameCol(GameCol* _GameCol)
	{
		m_GameCol = _GameCol;
	}

	GameCol* GetGameCol()
	{
		return m_GameCol;
	}

	void SetUpdateID(__int64 _UpdateID)
	{
		UpdateID = _UpdateID;
	}

public:

	FVector DirVector;
	float Speed;
	float DeathTime;


	UFUNCTION(BlueprintCallable, Category = Attachment)
		void ActorEnd();


public:
	AExBullet();
	~AExBullet();

public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
		void Update(float _DeltaTime);
};
