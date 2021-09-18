// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCol.h"

GameCol::GameCol() : m_Type(COLTYPE::CT_SPHERE), IsDeath(false), IsUpdate(true)
{
    IsUpdate = true;
}

GameCol::GameCol(int _Order, AActor* _Actor) : Order(_Order), m_Actor(_Actor), m_Type(COLTYPE::CT_SPHERE), IntType(static_cast<int>(m_Type)), IsDeath(false), IsUpdate(true)
{
    IsUpdate = true;
}

GameCol::GameCol(COLTYPE _Type, int _Order, AActor* _Actor) : Order(_Order), m_Actor(_Actor), m_Type(_Type), IntType(static_cast<int>(_Type)), IsDeath(false), IsUpdate(true)
{
    IsUpdate = true;
}

GameCol::~GameCol()
{
}


void GameCol::SetScale(float4 _Scale)
{
    Data.SetScale(_Scale);
}

void GameCol::Setting() 
{
    if (nullptr == m_Actor)
    {
        UE_LOG(LogTemp, Error, L"GameCol if (nullptr == m_Actor)");
        Death();
        return;
    }

    if (false == m_Actor->IsValidLowLevel())
    {
        UE_LOG(LogTemp, Error, L"if (false == m_Actor->IsValidLowLevel())");
        Death();
        return;
    }

    FVector Pos = m_Actor->GetTransform().GetLocation();
    float4 OriPos = &Pos.X;
    Data.m_OBB.Center = OriPos.Dxfloat3;

    Data.SettingChangeSpace();

    // 초기에 설정해주고 바꾸지 않는다.
    // m_Data.m_OBB.Extents = { m_Scale.x * 0.5f, m_Scale.y * 0.5f, m_Scale.z * 0.5f };
}