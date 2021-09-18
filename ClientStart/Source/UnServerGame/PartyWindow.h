// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyWindow.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API UPartyWindow : public UUserWidget
{
	GENERATED_BODY()

private:
	TArray<class UPartyItem*> PartyList;
	bool IsPartyList;
	bool IsSet;

public:
	class UListView* m_ListView;

public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void PartyInit();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ListAddEvent(UObject* _Item, UUserWidget* _Icon);

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void Update();
	
public:
	void Button();
	void Setting();
};
