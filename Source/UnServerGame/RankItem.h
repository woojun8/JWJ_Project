// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RankItem.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API URankItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_Rank;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_Score;

	void SetName(FString _Name)
	{
		m_Name = _Name;
	}

	void SetRank(int _Rank) 
	{
		m_Rank = FString::FromInt(_Rank);
	}
	void SetScore(int _Score) 
	{
		m_Score = FString::FromInt(_Score);
	}
};
