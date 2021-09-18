// Fill out your copyright notice in the Description page of Project Settings.


#include "UnActorManager.h"
#include "Player/PlayerCharacter.h"
#include "UnServerConnect.h"
#include "MainActor.h"
#include <ClientToServer.h>
#include <LogicValue.h>
#include <GameEngineRandom.h>
#include <Monster.h>


UnActorManager UnActorManager::Inst;

UnActorManager::UnActorManager() : MainActor(nullptr)
{
}

UnActorManager::~UnActorManager()
{
}

void UnActorManager::Clear() 
{
	UE_LOG(LogTemp, Error, TEXT("UnActorManager::Clear()"));

	m_Destroy.clear();
	m_AllGameActor.clear();
	m_ColMap.clear();
}

void UnActorManager::DestoryRelease() 
{
	for (auto& _Actor : m_Destroy)
	{
		_Actor->Destroy();
	}

	m_Destroy.clear();
}

void UnActorManager::ActorRelease()
{
	for (auto& _Var : m_AllGameActor)
	{

		TMap<__int64, AActor*>& Actors = _Var.second;

		//if (0 >= Actors.Num())
		//{
		//	continue;
		//}

		for (auto& Entry : Actors)
		{
			UE_LOG(LogTemp, Error, TEXT("%s Hidden"), *Entry.Value->GetName());
			Entry.Value->SetHidden(true);
			m_Destroy.push_back(Entry.Value);
		}
	}

	m_AllGameActor.clear();
	m_ColMap.clear();

	//Clear();
}


void UnActorManager::TestMonsterCreate(int Count) 
{
	for (int i = 0; i < Count; i++)
	{
		float RandomX = GameEngineRandom::GetRandomFloat(-4000.0f, 4000.0f);
		float RandomY = GameEngineRandom::GetRandomFloat(-4000.0f, 4000.0f);

		//AMonster* NewMonster = CreateServerManagerObjectToCol<AMonster>(AMainActor::GetInst().m_MonsterCreateType, FVector{ RandomX , RandomY, 0.0f }, (int)LogicValue::CollisionLayer::MONSTER, -1, {100.0f, 100.0f, 100.0f}, COLTYPE::CT_SPHERE);
		AMonster* NewMonster = CreateServerManagerObjectToCol<AMonster>(APlayerCharacter::GetInst().m_MonsterCreateType, FVector{ RandomX , RandomY, 0.0f }, (int)LogicValue::CollisionLayer::MONSTER, -1, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
		NewMonster->SetActorScale3D({100.0f, 100.0f, 100.0f});
		NewMonster->ActorStart();
	}
}

void UnActorManager::SetSize(float4 _Size) 
{
	m_Size = _Size;

	AActor* Wall = nullptr;
	FVector FFBSize = { 100.0f, m_Size.y * 2.0f, 1000.0f }; 
	float4 FBSize = &FFBSize.X;

	//// 앞쪽
	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_WallCreateType, { m_Size.x, 0.0f,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, FBSize, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D(FFBSize);
	//// 뒤쪽
	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_WallCreateType, { -m_Size.x, 0.0f,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, FBSize, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D(FFBSize);

	//FVector FLRSize = { m_Size.x * 2, 100.0f , 1000.0f };	
	//float4 LRSize = &FLRSize.X;

	//// 왼쪽
	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_WallCreateType, { 0.0f, m_Size.y,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, LRSize, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D(FLRSize);
	//// 오른쪽
	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_WallCreateType, { 0.0f, -m_Size.y,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, LRSize, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D(FLRSize);

	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_FloorCreateType, { 0.0f, 0.0f,-200.0f }, (int)LogicValue::CollisionLayer::WALL, -1, { m_Size.x * 2, m_Size.y * 2, 100.0f }, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D({ m_Size.x * 2, m_Size.y * 2, 100.0f });

	// 앞쪽
	Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(APlayerCharacter::GetInst().m_WallCreateType, { m_Size.x, 0.0f,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, FBSize, COLTYPE::CT_OBB);
	Wall->SetActorScale3D(FFBSize);
	// 뒤쪽
	Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(APlayerCharacter::GetInst().m_WallCreateType, { -m_Size.x, 0.0f,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, FBSize, COLTYPE::CT_OBB);
	Wall->SetActorScale3D(FFBSize);

	FVector FLRSize = { m_Size.x * 2, 100.0f , 1000.0f };
	float4 LRSize = &FLRSize.X;

	// 왼쪽
	Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(APlayerCharacter::GetInst().m_WallCreateType, { 0.0f, m_Size.y,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, LRSize, COLTYPE::CT_OBB);
	Wall->SetActorScale3D(FLRSize);
	// 오른쪽
	Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(APlayerCharacter::GetInst().m_WallCreateType, { 0.0f, -m_Size.y,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, LRSize, COLTYPE::CT_OBB);
	Wall->SetActorScale3D(FLRSize);

	Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(APlayerCharacter::GetInst().m_FloorCreateType, { 0.0f, 0.0f,-200.0f }, (int)LogicValue::CollisionLayer::WALL, -1, { m_Size.x * 2, m_Size.y * 2, 100.0f }, COLTYPE::CT_OBB);
	Wall->SetActorScale3D({ m_Size.x * 2, m_Size.y * 2, 100.0f });
}

void UnActorManager::ActorManagerInit(AActor* _MainActor, UWorld* _World) 
{
	MainActor = _MainActor;
	MainWorld = _World;

	// SetSize({ UnServerConnect::GetInst().m_CharacterData.MapX, UnServerConnect::GetInst().m_CharacterData.MapY });


	ClientReadyPacket NewPacket;
	NewPacket.m_Code = 1;
	UnServerConnect::GetInst().Send(NewPacket);
	// 클라이언트는 이제부터 서버가 스타트 해도 좋다는 패킷을 날려주는것을 기다리면 됩니다.

}

GameCol* UnActorManager::InsertCollison(std::shared_ptr<GameCol> _Col, float4 _Scale)
{
	if (m_ColMap.end() == m_ColMap.find(_Col->GetOrder()))
	{
		m_ColMap.insert(std::map<int, std::map<AActor*, std::shared_ptr<GameCol>>>::value_type(
			_Col->GetOrder(), std::map<AActor*, std::shared_ptr<GameCol>>()));
	}

	if (m_ColMap[_Col->GetOrder()].end() != m_ColMap[_Col->GetOrder()].find(_Col->GetActor()))
	{
		// UE_LOG(LogTemp, Error, L"if (nullptr == m_ColMap[_Col->GetOrder()].Find(_Col->GetActor()))");
		return nullptr;
	}

	_Col->SetScale(_Scale);

	// UE_LOG(LogTemp, Error, L"m_ColMap[_Col->GetOrder()].Add(_Col->GetActor(), _Col)");
	m_ColMap[_Col->GetOrder()].insert(std::map<AActor*, std::shared_ptr<GameCol>>::value_type(_Col->GetActor(), _Col));

	return _Col.get();
}

//                                  내가           OBB로        회전하거나     이동하면      이 그룹과 충돌해?
bool UnActorManager::CheckCollison(AActor* _Col, COLTYPE _Type, float4 _Scale, float4 _Move, int _Order)
{
	GameEngineColData Data;

	FVector Pos = _Col->GetActorLocation();
	float4 OriPos = &Pos.X;
	OriPos += _Move;
	Data.m_OBB.Center = OriPos.Dxfloat3;
	Data.SetScale(_Scale);

	Data.SettingChangeSpace();

	std::map<AActor*, std::shared_ptr<GameCol>>& ColGroup = m_ColMap[_Order];

	int LeftType = static_cast<int>(_Type);

	for (auto& Col: ColGroup)
	{

		Col.second->Setting();
		//UE_LOG(LogTemp, Error, TEXT("Right Scale : %f, %f, %f, Pos : %f, %f, %f"),
		//	Col.second->Data.m_OBB.Extents.x, Col.second->Data.m_OBB.Extents.y, Col.second->Data.m_OBB.Extents.z,
		//	Col.second->Data.m_OBB.Center.x, Col.second->Data.m_OBB.Center.y , Col.second->Data.m_OBB.Center.z);
		// 
		// if (true == Data.m_OBB.Intersects(Col.second->Data.m_OBB))
		if (true == GameEngineCollision::COLFUNC[LeftType][Col.second->GetTypeInt()](Data, Col.second->Data))
		{
			GameEngineColData& ColData = Col.second->Data;
			//UE_LOG(LogTemp, Error, TEXT("Left Scale : %f, %f, %f, Pos : %f, %f, %f"),
			//	Data.m_OBB.Extents.x, Data.m_OBB.Extents.y, Data.m_OBB.Extents.z,
			//	Data.m_OBB.Center.x, Data.m_OBB.Center.y, Data.m_OBB.Center.z);


			// UE_LOG(LogTemp, Error, TEXT("Left Scale : %f, Pos : %f, %f, %f"),
			//	Data.m_Sphere.Radius,
			//	 Data.m_Sphere.Center.x, Data.m_Sphere.Center.y, Data.m_Sphere.Center.z);
			//UE_LOG(LogTemp, Error, TEXT("Right Scale : %f, %f, %f, Pos : %f, %f, %f"),
			//	ColData.m_OBB.Extents.x, ColData.m_OBB.Extents.y, ColData.m_OBB.Extents.z,
			//	ColData.m_OBB.Center.x,  ColData.m_OBB.Center.y , ColData.m_OBB.Center.z);
			//UE_LOG(LogTemp, Error, L"Col!");
			return true;
		}
	}

	return false;
}

void UnActorManager::Link(int _LeftGroup, int _RightGroup) 
{
	if (m_ColLink[_LeftGroup].end() == m_ColLink[_LeftGroup].find(_RightGroup))
	{
		m_ColLink[_LeftGroup].insert(_RightGroup);
	}
}

void UnActorManager::Collision() 
{
	// 내부에서 이런식으로 관리하고 있으니까.
	// std::map<int, std::map<AActor*, std::shared_ptr<GameCol>>> m_ColMap;

	// 충돌체크
	for (auto& LeftGroup : m_ColLink)
	{
		int LeftOrder = LeftGroup.first;
		std::set<int> RightGorups = LeftGroup.second;

		for (int RightOrder : RightGorups)
		{
			std::map<AActor*, std::shared_ptr<GameCol>>& _LeftCollisions = m_ColMap[LeftOrder];
			std::map<AActor*, std::shared_ptr<GameCol>>& _RightCollisions = m_ColMap[RightOrder];

			ColCheck(_LeftCollisions, _RightCollisions);
		}
	}

	// 충돌이 다 끝난다음에
	// 죽인다. 정리.
	for (auto& _ColGroup : m_ColMap)
	{
		// UE_LOG(LogTemp, Error, TEXT("Death Check %d"), _ColGroup.first);

		std::map<AActor*, std::shared_ptr<GameCol>>::iterator StartCol = _ColGroup.second.begin();
		std::map<AActor*, std::shared_ptr<GameCol>>::iterator EndCol = _ColGroup.second.end();

		for (; StartCol != EndCol;)	
		{
			if (true == StartCol->second->GetIsDeath())
			{
				UE_LOG(LogTemp, Error, TEXT("Death ColData"))
				StartCol = _ColGroup.second.erase(StartCol);
			}
			else 
			{
				++StartCol;
			}
		
		}
	}
}

void UnActorManager::ColCheck(std::map<AActor*, std::shared_ptr<GameCol>>& _LeftGroup, std::map<AActor*, std::shared_ptr<GameCol>>& _RightGroup)
{
	// 왼쪽그룹과 오른쪽그룹이 적용되었고.
	// LeftGroup이 우선순위가 있다고 보고

	for (auto& _LeftCol : _LeftGroup)
	{
		if (true == _LeftCol.second->GetIsDeath())
		{
			continue;
		}
		if (false == _LeftCol.second->GetIsUpdate())
		{
			continue;
		}


		for (auto& _RightCol : _RightGroup)
		{
			// 상대의 충돌 타입과
			// 나의 충돌타입에 맞는.
			// 충돌 체크를 해줘야 한다는 겁니다.

			if (true == _RightCol.second->GetIsDeath())
			{
				continue;
			}

			if (false == _RightCol.second->GetIsUpdate())
			{
				continue;
			}

			int LeftType = static_cast<int>(_LeftCol.second->GetType());
			int RightType = static_cast<int>(_RightCol.second->GetType());

			_LeftCol.second->Setting();
			_RightCol.second->Setting();

			if (50.0f <= _RightCol.second->Data.m_OBB.Extents.x || 50.0f <= _LeftCol.second->Data.m_OBB.Extents.x)
			{
				// UE_LOG(LogTemp, Error, TEXT("BulletEX"))
			}
			

			if (true == GameEngineCollision::COLFUNC[LeftType][RightType](_LeftCol.second->Data, _RightCol.second->Data))
			{
				if (true == _LeftCol.second->IsColEvent())
				{
					_LeftCol.second->ColEvent(_LeftCol.second.get(), _RightCol.second.get());
				}

				if (true == _RightCol.second->IsColEvent())
				{
					_RightCol.second->ColEvent(_RightCol.second.get(), _LeftCol.second.get());
				}
				// UE_LOG(LogTemp, Error, L"Col! %f %f", _LeftCol.second->Data.m_Sphere.Radius, _RightCol.second->Data.m_Sphere.Radius);
				// 충돌하면 여기로 들어오게 될것이다.
				// UE_LOG(LogTemp, Error, L"Col! %f %f", _LeftCol.second->Data.m_Sphere.Radius, _RightCol.second->Data.m_Sphere.Radius);
			}

		}
	}

}