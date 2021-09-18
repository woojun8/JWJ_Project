// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "ChatObject.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API UChatObject : public UObject
{
	GENERATED_BODY()

public:
	__int64 PID;
	FString Name;
	FString Text;
	bool Filter;
};
