// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

/**
 * 
 */
class UNSERVERGAME_API UnResManager
{
public:
	static UnResManager& Inst() 
	{
		static UnResManager NewInst;
		return NewInst;
	}

private:
	TArray<UTexture2D*> m_ItemIconArray;
	USkeletalMesh* m_MeshAsset;
	TSubclassOf<UAnimInstance> m_AnimAsset;

public:
	UTexture2D* GetIconImage(int _Index);
	USkeletalMesh* GetMeshAsset();
	TSubclassOf<UAnimInstance> GetAnimAsset();

public:
	void ResInit();
	void Release();

public:
	UnResManager();
	~UnResManager();
};
