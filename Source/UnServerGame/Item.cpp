// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UnActorManager.h"
#include <LogicValue.h>

void AItem::ActorEnd()
{
    UnActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::ITEM, UpdateID);
}