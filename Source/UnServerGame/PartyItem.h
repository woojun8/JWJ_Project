// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyItem.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API UPartyItem : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_Number;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_Connect;
		
public:
	void SetNumber(FString _Number)
	{
		m_Number = _Number;
	}

	void SetName(FString _Name)
	{
		m_Name = _Name;
	}

	void SetConnect(FString _Connect)
	{
		m_Connect = _Connect;
	}
};
