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

	//// ����
	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_WallCreateType, { m_Size.x, 0.0f,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, FBSize, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D(FFBSize);
	//// ����
	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_WallCreateType, { -m_Size.x, 0.0f,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, FBSize, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D(FFBSize);

	//FVector FLRSize = { m_Size.x * 2, 100.0f , 1000.0f };	
	//float4 LRSize = &FLRSize.X;

	//// ����
	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_WallCreateType, { 0.0f, m_Size.y,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, LRSize, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D(FLRSize);
	//// ������
	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_WallCreateType, { 0.0f, -m_Size.y,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, LRSize, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D(FLRSize);

	//Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(AMainActor::GetInst().m_FloorCreateType, { 0.0f, 0.0f,-200.0f }, (int)LogicValue::CollisionLayer::WALL, -1, { m_Size.x * 2, m_Size.y * 2, 100.0f }, COLTYPE::CT_OBB);
	//Wall->SetActorScale3D({ m_Size.x * 2, m_Size.y * 2, 100.0f });

	// ����
	Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(APlayerCharacter::GetInst().m_WallCreateType, { m_Size.x, 0.0f,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, FBSize, COLTYPE::CT_OBB);
	Wall->SetActorScale3D(FFBSize);
	// ����
	Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(APlayerCharacter::GetInst().m_WallCreateType, { -m_Size.x, 0.0f,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, FBSize, COLTYPE::CT_OBB);
	Wall->SetActorScale3D(FFBSize);

	FVector FLRSize = { m_Size.x * 2, 100.0f , 1000.0f };
	float4 LRSize = &FLRSize.X;

	// ����
	Wall = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABlock>(APlayerCharacter::GetInst().m_WallCreateType, { 0.0f, m_Size.y,0.0f }, (int)LogicValue::CollisionLayer::WALL, -1, LRSize, COLTYPE::CT_OBB);
	Wall->SetActorScale3D(FLRSize);
	// ������
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
	// Ŭ���̾�Ʈ�� �������� ������ ��ŸƮ �ص� ���ٴ� ��Ŷ�� �����ִ°��� ��ٸ��� �˴ϴ�.

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

//                                  ����           OBB��        ȸ���ϰų�     �̵��ϸ�      �� �׷�� �浹��?
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
	// ���ο��� �̷������� �����ϰ� �����ϱ�.
	// std::map<int, std::map<AActor*, std::shared_ptr<GameCol>>> m_ColMap;

	// �浹üũ
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

	// �浹�� �� ����������
	// ���δ�. ����.
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
	// ���ʱ׷�� �����ʱ׷��� ����Ǿ���.
	// LeftGroup�� �켱������ �ִٰ� ����

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
			// ����� �浹 Ÿ�԰�
			// ���� �浹Ÿ�Կ� �´�.
			// �浹 üũ�� ����� �Ѵٴ� �̴ϴ�.

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
				// �浹�ϸ� ����� ������ �ɰ��̴�.
				// UE_LOG(LogTemp, Error, L"Col! %f %f", _LeftCol.second->Data.m_Sphere.Radius, _RightCol.second->Data.m_Sphere.Radius);
			}

		}
	}

}