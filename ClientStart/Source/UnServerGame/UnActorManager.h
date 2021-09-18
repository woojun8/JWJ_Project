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
// 필요하다면 몬스터등등도 이녀석이 만들어야 하므로
// 마찬가지로 init을 만들어서
class UNSERVERGAME_API UnActorManager
{
public:
	static UnActorManager Inst;
public:
	static UnActorManager& GetInst() {
		return Inst;
	}




	// 기존에 그냥 밀어 넣어주던 부분은 다 에러가 나겠죠.
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


// 이 세개의 메모리를
	//TArray<AActor*> m_Destroy;

public:
	// 언리얼에서 싱글톤이나 이런 데이터 영역에 구조를 잡으면 
	// 특히나 이런 자료구조들은
	// 왠만하면 직접적으로 clear를 해주고
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

	// 최적화 생각안하고 해보겠습니다.
	std::map<int, std::map<AActor*, std::shared_ptr<GameCol>>> m_ColMap;
	
	// std::map<int, std::list<std::shared_ptr<actor>> m_ColMap;

public:
	GameCol* InsertCollison(std::shared_ptr<GameCol> _Col, float4 _Scale);

	// 내가 원할때 충돌체크를 하게 해주는 함수.
	bool CheckCollison(AActor* _Col, COLTYPE _Type, float4 _Scale, float4 _Move, int _Order);



	// 그룹간에 충돌 체크를 활성화 시켜주는 함수.
	void Link(int _LeftGroup, int _RightGroup);

	// 그룹간 충돌 체크를 지시하면 그 충돌체크를 처리해주는 한꺼번에
	void Collision();

	void ColCheck(std::map<AActor*, std::shared_ptr<GameCol>>& _LeftGroup, std::map<AActor*, std::shared_ptr<GameCol>>& _RightGroup);



	// 액터 관리용 함수.
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

		// -1이면 클라이언트에서만 관리되는 모드고 자신의 주소가 들어갔을거라는 이야기니까.
		NewActor->SetUpdateID(_ID);

		m_AllGameWaitActor[_Order].Add(_ID, NewActor);

		return NewActor;
	}

	// Player Destroy되는게 아니고 자리를 옮기는것 뿐이라.
	void EraseServerManagerWaitObject(int _Order, __int64 _ID)
	{
		AActor** Actor = m_AllGameWaitActor[_Order].Find(_ID);
		if (nullptr == Actor)
		{
			return;
		}

		m_AllGameWaitActor[_Order].Remove(_ID);
	}

	// 충돌체 만들면서 넣어주는것.
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


		//       order                UpdateId 오브젝트
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

		// -1이면 클라이언트에서만 관리되는 모드고 자신의 주소가 들어갔을거라는 이야기니까.
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
		// 여러개를 찾아오는 방식이네요.
		AActor** Actor = m_AllGameActor[_Order].Find(_ID);
		if (nullptr == Actor)
		{
			UE_LOG(LogTemp, Error, TEXT("Server Erase Fail if (nullptr == Actor) %d %lld"), _Order, _ID);
			return;
		}

		// 충돌체도 같이 날려줘야 합니다.
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
