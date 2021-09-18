// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <PacketType.h>
#include <queue>
#include "ServerManagemenetActor.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API AServerManagemenetActor : public ACharacter
{
	GENERATED_BODY()

protected:
	std::queue<ActorUpdateData> m_UpdateQueue;

public:
	void PushUpdateData(const ActorUpdateData& _Data) 
	{
		m_UpdateQueue.push(_Data);
	}
	
public:
	__int64 UpdateID;
	class GameCol* m_GameCol;

public:
	void SetGameCol(GameCol* _GameCol)
	{
		m_GameCol = _GameCol;
	}

	void SetUpdateID(__int64 _UpdateID)
	{
		UpdateID = _UpdateID;
	}
};
