// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "InvenIcon.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API UInvenIcon : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_Count;

	UImage* m_Image;

public:
	void SetName(FString _Name)
	{
		m_Name = _Name;
	}

	void SetCount(int _Number) 
	{
		m_Count = FString::FromInt(_Number);
	}

	void SetIcon(int _Index);

	int GetCount()
	{
		return FCString::Atoi(*m_Count);
	}

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void IconInit();


};
