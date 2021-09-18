// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameCol.h"
#include "Potal.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API APotal : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	__int64 UpdateID;
	GameCol* m_GameCol;

public:
	void SetGameCol(GameCol* _GameCol)
	{
		m_GameCol = _GameCol;
	}

	void SetUpdateID(__int64 _UpdateID)
	{
		UpdateID = _UpdateID;
	}

};
