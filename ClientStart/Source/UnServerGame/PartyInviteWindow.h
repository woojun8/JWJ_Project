// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyInviteWindow.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API UPartyInviteWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void AcceptButton();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void RefuseButton();
};
