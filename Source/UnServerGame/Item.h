// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServerManagemenetActor.h"
#include "GameCol.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API AItem : public AServerManagemenetActor
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ActorEnd();
};
