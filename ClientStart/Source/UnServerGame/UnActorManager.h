// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include <map>
#include <set>
#include <list>
#include <GEMath.h>
#include <GameEngineMemory.h>
#include "GameCol.h"

/**
 * 
 */
// �ʿ��ϴٸ� ���͵� �̳༮�� ������ �ϹǷ�
// ���������� init�� ����
class UNSERVERGAME_API UnActorManager
{
public:
	static UnActorManager Inst;
public:
	static UnActorManager& GetInst() {
		return Inst;
	}




	// ������ �׳� �о� �־��ִ� �κ��� �� ������ ������.
private:
	AActor* MainActor;
	UWorld* MainWorld;
	float4 m_Size;

public:
	void SetMainActor(AActor* _MainActor, float4 _Scale, int _Order = 0, bool _IsCol = true)
	{
		MainActor = _MainActor;
		MainWorld = _MainActor->GetWorld();

		if (true == _IsCol)
		{
			InsertCollison(std::make_shared<GameCol>(_Order, MainActor), _Scale);
		}
	}


// �� ������ �޸𸮸�
	//TArray<AActor*> m_Destroy;

public:
	// �𸮾󿡼� �̱����̳� �̷� ������ ������ ������ ������ 
	// Ư���� �̷� �ڷᱸ������
	// �ظ��ϸ� ���������� clear�� ���ְ�
	void ActorRelease();
	void Clear();

public:
	AActor* GetMainActor() 
	{
		return MainActor;
	}

public:
	void ActorManagerInit(AActor* _MainActor, UWorld* _World);
	void TestMonsterCreate(int Count);
	void SetSize(float4 _Size);

public:
	//void DestoryUpdate() 
	//{
	//	if (0 != m_Destroy.Num())
	//	{
	//		AActor* Ptr = m_Destroy.Pop();
	//		Ptr->Destroy();
	//	}
	//}


private:
	std::map<int, std::set<int>> m_ColLink;

	// ����ȭ �������ϰ� �غ��ڽ��ϴ�.
	std::map<int, std::map<AActor*, std::shared_ptr<GameCol>>> m_ColMap;
	
	// std::map<int, std::list<std::shared_ptr<actor>> m_ColMap;

public:
	GameCol* InsertCollison(std::shared_ptr<GameCol> _Col, float4 _Scale);

	// ���� ���Ҷ� �浹üũ�� �ϰ� ���ִ� �Լ�.
	bool CheckCollison(AActor* _Col, COLTYPE _Type, float4 _Scale, float4 _Move, int _Order);



	// �׷찣�� �浹 üũ�� Ȱ��ȭ �����ִ� �Լ�.
	void Link(int _LeftGroup, int _RightGroup);

	// �׷찣 �浹 üũ�� �����ϸ� �� �浹üũ�� ó�����ִ� �Ѳ�����
	void Collision();

	void ColCheck(std::map<AActor*, std::shared_ptr<GameCol>>& _LeftGroup, std::map<AActor*, std::shared_ptr<GameCol>>& _RightGroup);



	// ���� ������ �Լ�.
public:
	std::list<AActor*> m_Destroy;

	void DestoryRelease();


	std::map<int, TMap<__int64, AActor*>> m_AllGameWaitActor;
	template<typename T>
	T* FindIDWaitActor(int _Order, __int64 _ID)
	{
		AActor** FindPtr = m_AllGameWaitActor[_Order].Find(_ID);
		if (nullptr != FindPtr)
		{
			return Cast<T>(FindPtr[0]);
		}

		return nullptr;
	}

	template<typename T>
	T* CreateServerManagerWaitObject(TSubclassOf<T> _CreateType, FVector _Pos, int _Order, __int64 _ID)
	{

		if (nullptr != m_AllGameWaitActor[_Order].Find(_ID))
		{
			return nullptr;
		}

		T* NewActor = MainWorld->SpawnActor<T>(_CreateType, _Pos, { 0,0,0 });
		if (_ID == -1)
		{
			_ID = reinterpret_cast<__int64>(NewActor);
		}

		// -1�̸� Ŭ���̾�Ʈ������ �����Ǵ� ���� �ڽ��� �ּҰ� �����Ŷ�� �̾߱�ϱ�.
		NewActor->SetUpdateID(_ID);

		m_AllGameWaitActor[_Order].Add(_ID, NewActor);

		return NewActor;
	}

	// Player Destroy�Ǵ°� �ƴϰ� �ڸ��� �ű�°� ���̶�.
	void EraseServerManagerWaitObject(int _Order, __int64 _ID)
	{
		AActor** Actor = m_AllGameWaitActor[_Order].Find(_ID);
		if (nullptr == Actor)
		{
			return;
		}

		m_AllGameWaitActor[_Order].Remove(_ID);
	}

	// �浹ü ����鼭 �־��ִ°�.
	template<typename T>
	T* WaitActorInActorCol(int _Order, __int64 _ID, float4 _Scale, COLTYPE _Type)
	{
		T* FindActor = FindIDWaitActor<T>(_Order, _ID);
		if (nullptr != FindActor)
		{
			EraseServerManagerWaitObject(_Order, _ID);
			m_AllGameActor[_Order].Add(_ID, FindActor);
			GameCol* GetPtr = InsertCollison(std::make_shared<GameCol>(_Type, _Order, FindActor), _Scale);
			FindActor->SetGameCol(GetPtr);
		}
		return FindActor;
	}



public:


		//       order                UpdateId ������Ʈ
	std::map<int, TMap<__int64, AActor*>> m_AllGameActor;
	template<typename T>
	T* FindIDActor(int _Order, __int64 _ID)
	{
		AActor** FindPtr = m_AllGameActor[_Order].Find(_ID);
		if (nullptr != FindPtr)
		{
			return Cast<T>(FindPtr[0]);
		}
		return nullptr;
	}

	template<typename T>
	T* CreateServerManagerObject(TSubclassOf<T> _CreateType, FVector _Pos, int _Order, __int64 _ID)
	{
		if (nullptr != m_AllGameActor[_Order].Find(_ID))
		{
			UE_LOG(LogTemp, Error, TEXT("if (nullptr != m_AllGameActor[_Order].Find(_ID)), %d, %d"), _Order, _ID);
			return nullptr;
		}

		T* NewActor = MainWorld->SpawnActor<T>(_CreateType, _Pos, { 0,0,0 });

		if (nullptr == NewActor)
		{
			UE_LOG(LogTemp, Error, TEXT("nullptr == NewActor %d, %d"), _Order, _ID);
		}

		if (_ID == -1)
		{
			_ID = reinterpret_cast<__int64>(NewActor);
		}

		// -1�̸� Ŭ���̾�Ʈ������ �����Ǵ� ���� �ڽ��� �ּҰ� �����Ŷ�� �̾߱�ϱ�.
		NewActor->SetUpdateID(_ID);

		m_AllGameActor[_Order].Add(_ID, NewActor);

		return NewActor;
	}

	template<typename T>
	T* CreateServerManagerObjectToCol(TSubclassOf<T> _CreateType, FVector _Pos, int _Order, __int64 _ID, float4 _Scale, COLTYPE _Type)
	{
		T* NewActor = CreateServerManagerObject(_CreateType, _Pos, _Order, _ID);
		if (nullptr != NewActor)
		{
			GameCol* GetPtr = InsertCollison(std::make_shared<GameCol>(_Type, _Order, NewActor), _Scale);
			NewActor->SetGameCol(GetPtr);
		}
		return NewActor;
	}

	void EraseServerManagerObject(int _Order, __int64 _ID)
	{
		// �������� ã�ƿ��� ����̳׿�.
		AActor** Actor = m_AllGameActor[_Order].Find(_ID);
		if (nullptr == Actor)
		{
			UE_LOG(LogTemp, Error, TEXT("Server Erase Fail if (nullptr == Actor) %d %lld"), _Order, _ID);
			return;
		}

		// �浹ü�� ���� ������� �մϴ�.
		std::map<AActor*, std::shared_ptr<GameCol>>::iterator FindIter = m_ColMap[_Order].find(Actor[0]);
		if (m_ColMap[_Order].end() != FindIter)
		{
			FindIter->second->Death();
		}


		UE_LOG(LogTemp, Error, TEXT("Server Erase OK %d %lld"), _Order, _ID);
		m_AllGameActor[_Order].Remove(_ID);
	}

public:
	UnActorManager();
	~UnActorManager();
};
