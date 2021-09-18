// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
//#include "DestructibleComponent.h"

DECLARE_LOG_CATEGORY_EXTERN(UE8, Log, All);
#define	LOG_CALLINFO		(FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))
#define	LOG(Format, ...)	UE_LOG(UE8, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

void PrintViewport(float Duration, const FColor& Color, const FString& strText);

UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Idle,
	Run,
	Attack,
	Death,
	Jump,
	Skill1,
	Skill2,
	Skill3
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	None,
	Attack1,
	Attack2,
	Attack3,
	Attack4
};

UENUM(BlueprintType)
enum class EMoveDir : uint8
{
	None,
	Front,
	Back,
	Up,
	Down
};

UENUM(BlueprintType)
enum class EFallingState : uint8
{
	None,
	Falling,
	Landing
};

UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death
};

UENUM(BlueprintType)
enum class EGruxAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death	
};