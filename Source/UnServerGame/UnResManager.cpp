// Fill out your copyright notice in the Description page of Project Settings.


#include "UnResManager.h"

UnResManager::UnResManager()
{
    // GreyStone �޽��� �ҷ��´�.												
    ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
    if (MeshAsset.Succeeded())
    {
        m_MeshAsset = MeshAsset.Object;
    }

    // FObjectFinder, FClassFinder�� �����ڿ����� ����� �����ϴ�
    // class ������ �о�ö��� ����� �������� _c�� �߰��ؾ��Ѵ�.
    // static���� ������ ���� GreyStone�� �ƹ��� ���� �����ȴ� �ص�
    // ������ �� 1���� �ҷ��ͼ� ��� GreyStone�� �����ؼ� ����Ҽ� �ֵ��� ������ش�.		
    ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Greystone/BPGreystoneAnim.BPGreystoneAnim_c'"));
    if (AnimAsset.Succeeded())
    {
        m_AnimAsset = AnimAsset.Class;
    }
}

UnResManager::~UnResManager()
{
}

UTexture2D* UnResManager::GetIconImage(int _Index) 
{
    if (0 > _Index || _Index >= m_ItemIconArray.Num())
    {
        return nullptr;
    }


    return m_ItemIconArray[_Index];
}

USkeletalMesh* UnResManager::GetMeshAsset()
{
    return m_MeshAsset;
}

TSubclassOf<UAnimInstance> UnResManager::GetAnimAsset()
{
    return m_AnimAsset;
}

void UnResManager::ResInit() 
{
    UE_LOG(LogTemp, Error, L"UnResManager::ResInit()");
    m_ItemIconArray.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Sprite/item_ax.item_ax'")));
    m_ItemIconArray.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Sprite/item_shield.item_shield'")));
    m_ItemIconArray.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Sprite/item_life.item_life'")));

    for (size_t i = 0; i < m_ItemIconArray.Num(); i++)
    {
        if (nullptr != m_ItemIconArray[i])
        {
            UE_LOG(LogTemp, Error, TEXT("Res Load OK %d"), i);
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Res Load %d"), m_ItemIconArray.Num());

}

void UnResManager::Release() 
{
    UE_LOG(LogTemp, Error, L"UnResManager::Release()");
    m_ItemIconArray.Empty();
}