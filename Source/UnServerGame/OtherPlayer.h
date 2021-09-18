// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServerManagemenetActor.h"
#include "OtherPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API AOtherPlayer : public AServerManagemenetActor
{
	GENERATED_BODY()

public:
	AOtherPlayer();

protected:
	virtual void BeginPlay() override;

protected:
	// 얘도 애니메이션을 재생해야 하니까
	class UPlayerAnim* m_PlayerAnim;

public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void OtherPlayerUpdate();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ActorEnd();
};
