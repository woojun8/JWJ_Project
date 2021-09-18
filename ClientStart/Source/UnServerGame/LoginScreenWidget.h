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
	// FString�� �ƴ� ������
	// VisibleAnywhere �������Ʈ���� ���̰� �ϰ� �ʹ�.
	// 	BlueprintReadWrite �������Ʈ���� �������� �ְ� ������ ���������� ���ڴ�.
	// 	   meta = (AllowPrivateAccess = "true") �ڵ忡�� ����Ҷ��� 
	// private ������ �������Ʈ������ publicó�� �����ؼ� ����� �����ϰ� ��������� ���ڴ�.
	// 
	// ui���� �������ִ� String������ Ftext�̱� �����Դϴ�.
	//  meta = (AllowPrivateAccess = "true")

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FText m_IP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FText m_ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FText m_Password;


public:
	// �÷�����Ʈ���� ����ϰ� �;�
	// BlueprintCallable == �������Ʈ���� ȣ���� �����ϰ�
	// Attachment == ���μ� �ٿ��ټ� �ִ� ����̸� ���ھ�.
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
