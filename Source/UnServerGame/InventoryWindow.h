// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <vector>
#include <ServerToClient.h>
#include "InventoryWindow.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API UInventoryWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	class UTileView* m_TileView;

public:
	std::vector<class UInvenIcon*> m_Array;

public:
	bool IsInit() 
	{
		return 0 == m_Array.size();
	}

public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void InvenInit();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void NewIconEvent(UObject* _Item, UUserWidget* _Icon);

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ItemClear();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ItemUpdate();

public:
	void SetItemData(const ItemData& _Data);

};
