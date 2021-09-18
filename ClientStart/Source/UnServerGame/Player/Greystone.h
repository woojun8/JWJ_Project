// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerCharacter.h"
#include "Greystone.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API AGreystone : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AGreystone();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void NormalAttack();

};
