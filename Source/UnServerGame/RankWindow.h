// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <ServerToClient.h>
#include "RankWindow.generated.h"
/**
 * 
 */
UCLASS()
class UNSERVERGAME_API URankWindow : public UUserWidget
{
	GENERATED_BODY()
	
private:
	TArray<class URankItem*> RankList;
	
public:
	class UListView* m_ListView;

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void RankInit();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ListAddEvent(UObject* _Item, UUserWidget* _Icon);

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void SettingTopRank();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void SettingUserRank();

public:
	void SetRank(int Index, RankData& _Data);


};
