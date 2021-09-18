// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServerManagemenetActor.h"
#include "GameCol.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API AMonster : public AServerManagemenetActor
{
	GENERATED_BODY()

public:
	void ActorStart();

	void CollisonEvent(GameCol* _This, GameCol* _Other);


	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ActorEnd();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void MonsterUpdate();

public:
	AMonster();
	~AMonster();
};
