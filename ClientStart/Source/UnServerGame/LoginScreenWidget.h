// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginScreenWidget.generated.h"
/**
 * 
 */
UCLASS()
class UNSERVERGAME_API ULoginScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	static FString IPText;

private:
	// FString이 아닌 이유는
	// VisibleAnywhere 블루프린트에서 보이게 하고 싶다.
	// 	BlueprintReadWrite 블루프린트에서 읽을수도 있고 수정도 가능했으면 좋겠다.
	// 	   meta = (AllowPrivateAccess = "true") 코드에서 사용할때는 
	// private 하지만 블루프린트에서는 public처럼 간섭해서 사용이 가능하게 만들었으면 좋겠다.
	// 
	// ui에서 지원해주는 String형식이 Ftext이기 때문입니다.
	//  meta = (AllowPrivateAccess = "true")

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FText m_IP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FText m_ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FText m_Password;


public:
	// 플루프린트에서 사용하고 싶어
	// BlueprintCallable == 블루프린트에서 호출이 가능하고
	// Attachment == 노드로서 붙여줄수 있는 기능이면 좋겠어.
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void LoginProgress();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void ConnectProgress();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void AccountProgress();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void SingleProgress();

	void NativeTick(const FGeometry& _MyGeometry, float _Delta) override;

	void IPSave();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void IPLoad();

public:
	~ULoginScreenWidget();
};
