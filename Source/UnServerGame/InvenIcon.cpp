// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenIcon.h"
#include "UnResManager.h"



void UInvenIcon::IconInit() 
{
    m_Image = Cast<UImage>(GetWidgetFromName("Front"));

	if (nullptr == m_Image)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == m_Image)"));
	}
}



void UInvenIcon::SetIcon(int _Index) 
{
	UTexture2D* SetTex = UnResManager::Inst().GetIconImage(_Index);

	if (nullptr == SetTex)
	{
		UE_LOG(LogTemp, Error, TEXT("void UInvenIcon::SetIcon(int _Index)  if (nullptr == SetTex) %d"), _Index);
		return;
	}

	m_Image->SetBrushFromTexture(SetTex);
}