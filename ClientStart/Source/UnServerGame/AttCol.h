// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/StaticMeshActor.h"
#include "GameCol.h"
#include "AttCol.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API AAttCol : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	__int64 UpdateID;
	GameCol* m_GameCol;

	float DeathTime;

public:
	void SetGameCol(GameCol* _GameCol)
	{
		m_GameCol = _GameCol;
	}

	void SetUpdateID(__int64 _UpdateID)
	{
		UpdateID = _UpdateID;
	}

public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ActorEnd();


public:
	AAttCol();
	~AAttCol();

public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void Update(float _DeltaTime);
	
};
