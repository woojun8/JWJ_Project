// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include <list>
#include "PlayUI.generated.h"

/**
 * 
 */
UCLASS()
class UNSERVERGAME_API UPlayUI : public UUserWidget
{
	GENERATED_BODY()

private:
	class UInventoryWindow* m_InvenWindow;
	class URankWindow* m_RankWindow;
	class UPartyWindow* m_PartyWindow;
	class UEditableTextBox* m_ChatTextBox;
	class UPartyInviteWindow* m_PartyInviteWindow;

private:
	TArray<__int64> ArrPID;
	TArray<GameEngineString> ArrName;
	TArray<__int64> ArrConnect;

public:
	void AddPID(__int64 PID)
	{
		ArrPID.Add(PID);
	}

	void AddName(GameEngineString Name)
	{
		ArrName.Add(Name);
	}

	void AddConnect(__int64 Connect)
	{
		ArrConnect.Add(Connect);
	}

	size_t GetSize()
	{
		return ArrPID.Num();
	}

	__int64 GetPID(int Idx)
	{
		return ArrPID[Idx];
	}

	GameEngineString GetName(int Idx)
	{
		return ArrName[Idx];
	}

	__int64 GetConnect(int Idx)
	{
		return ArrConnect[Idx];
	}

	void PartyDataClear()
	{
		ArrPID.Empty();
		ArrName.Empty();		
	}

public:
	class UListView* m_ChatTextList;

public:
	UInventoryWindow* GetInvenWindow() 
	{
		return m_InvenWindow;
	}

	URankWindow* GetRankWindow()
	{
		return m_RankWindow;
	}

	UPartyWindow* GetPartyWindow()
	{
		return m_PartyWindow;
	}

	UPartyInviteWindow* GetPartyInviteWindow()
	{
		return m_PartyInviteWindow;
	}

public:
	static UPlayUI* PlayUIInst;
	FText ChatText;
	
public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void PlayUIInit();

private:
	ESlateVisibility m_eInvenOpenState;
	ESlateVisibility m_eRankOpenState;
	ESlateVisibility m_ePartyOpenState;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_ChatText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FString m_ModeText;

public:
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void InvenOpenCheck();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void RankOpenCheck();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void PartyOpenCheck();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ChatCommit(FText Text, ETextCommit::Type _eType);

public:
	bool m_IsFriend;
	std::list <class UChatObject*> m_ChatList;

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ChatAddEvent(UObject* _Item, UUserWidget* _Icon);

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ChatModeChange();

	void ChatScrollSet();

	void PartyInviteWindow();
	void PartyWindowSetting();

	bool PartyHostCheck();
};
