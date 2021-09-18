// Fill out your copyright notice in the Description page of Project Settings.


#include "Greystone.h"
#include "PlayerAnim.h"

AGreystone::AGreystone()
{
	PrimaryActorTick.bCanEverTick = true;

										

}

void AGreystone::BeginPlay()
{
	Super::BeginPlay();
}

void AGreystone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGreystone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGreystone::NormalAttack()
{
	m_PlayerAnim->NormalAttack();
}