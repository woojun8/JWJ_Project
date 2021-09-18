// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include <GEMath.h>
#include <GameEngineCollision.h>
#include <functional>

/**
 * 
 */
class UNSERVERGAME_API GameCol
{
private:
	bool IsDeath;
	bool IsUpdate;
	int Order;
	AActor* m_Actor;
	COLTYPE m_Type;
	int IntType;

public:
	void On() {
		IsUpdate = true;
	}

	void Off() {
		IsUpdate = false;
	}

public:
	GameEngineColData Data;

private:
	std::function<void(GameCol*, GameCol*)> m_ColEvent;

public:
	bool GetIsDeath() {
		return IsDeath;
	}

	bool GetIsUpdate() {
		return IsUpdate;
	}

	void Death() {
		IsDeath = true;
	}

	bool IsColEvent() {
		return nullptr != m_ColEvent;
	}

public:
	// 충돌했을때 뭔가를 하고 싶다.
	template<typename ColObjectType>
	void SetEvent(ColObjectType* _Eventer, void(ColObjectType::*_Func)(GameCol*, GameCol*))
	{
		m_ColEvent = std::bind(_Func, _Eventer, std::placeholders::_1, std::placeholders::_2);
	}

	void ColEvent(GameCol* _Left, GameCol* _Right)
	{
		m_ColEvent(_Left, _Right);
	}

public:
	COLTYPE GetType() 
	{
		return m_Type;
	}

	int GetTypeInt()
	{
		return IntType;
	}

	void SetScale(float4 _Scale);
	void SetOrder(int _Order) 
	{
		Order = _Order;
	}

	int GetOrder() 
	{
		return Order;
	}

	AActor* GetActor()
	{
		return m_Actor;
	}

public:
	void Setting();

public:
	GameCol();
	GameCol(int _Order, AActor* _Actor);
	GameCol(COLTYPE _Type, int _Order, AActor* _Actor);
	~GameCol();
};
