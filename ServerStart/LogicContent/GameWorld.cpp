#include "GameWorld.h"
#include "Wall.h"
#include <GameEngineDebug.h>
#include "LogicValue.h"
#include <KDTREE.h>

// Static Var
// Static Func

// constructer destructer
GameWorld::GameWorld() 
{
}

GameWorld::~GameWorld() 
{

}
// member Func

// 외곽에 벽을 만들어준다.
void GameWorld::SetSize(const Sizefloat4& _Size)
{
	m_Size = _Size;

	CreateWallPos({ _Size.x, 0.0f,0.0f }, { 100.0f, m_Size.y * 2.0f, 1000.0f });
	CreateWallPos({ -m_Size.x, 0.0f,0.0f }, { 100.0f, m_Size.y * 2.0f, 1000.0f });
	CreateWallPos({ 0.0f, m_Size.y,0.0f }, { m_Size.x * 2, 100.0f , 1000.0f });
	CreateWallPos({ 0.0f, -m_Size.y,0.0f }, { m_Size.x * 2, 100.0f , 1000.0f });
	CreateWallPos({ 0.0f, 0.0f,-200.0f }, { m_Size.x * 2, m_Size.y * 2, 100.0f });
}

void GameWorld::WorldStart()
{
	for (int i = 0; i < (int)LogicValue::CollisionLayer::MAX; i++)
	{
		ColVectorInit(i);
	}

	SetKDTree((int)LogicValue::CollisionLayer::MONSTER);

	ColLink((int)LogicValue::CollisionLayer::MONSTER, (int)LogicValue::CollisionLayer::PLAYERBULLET);
	ColLink((int)LogicValue::CollisionLayer::MONSTER, (int)LogicValue::CollisionLayer::PLAYEREXBULLET);
	ColLink((int)LogicValue::CollisionLayer::MONSTER, (int)LogicValue::CollisionLayer::PLAYERATTACK);
	ColLink((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::PLAYERBULLET);
	ColLink((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::PLAYEREXBULLET);
	ColLink((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::POTAL);
	ColLink((int)LogicValue::CollisionLayer::PLAYER, (int)LogicValue::CollisionLayer::ITEM);
}

void GameWorld::CreatePotal(const PotalData& _PotalData)
{
	CreatePotalPos(_PotalData);
}

void GameWorld::PushColObject(GameActor* _GameActor) 
{
	if (_GameActor->GetColOrder() == (int)LogicValue::CollisionLayer::PLAYERATTACK)
	{
		int a = 0;
	}

	int a = 0;

	m_ColMap[_GameActor->GetColOrder()].push_back(_GameActor);
}

void GameWorld::CollisionPrev()
{
	World::CollisionPrev();

}

void GameWorld::ActorStart(Actor* _Actor) 
{
	GameActor* m_pActor = dynamic_cast<GameActor*>(_Actor);

	if (nullptr == m_pActor)
	{
		GameEngineDebug::AssertMsg("if (nullptr == m_pActor)");
	}

	// GameActor들은
	// 전부다 GameWorld를 알수 있게 되용
	m_pActor->SetWorld(this);
	m_pActor->Start();
}




void GameWorld::ColVectorInit(int _Order) 
{
}

void GameWorld::ColLink(int _Left, int _Right) 
{
	if (_Left == _Right)
	{
		GameEngineDebug::AssertMsg("if (_Left == _Right)");
		return;
	}

	std::set<int>& OtherSet = m_ColLink[_Left];

	if (OtherSet.end() != OtherSet.find(_Right))
	{
		return;
	}

	OtherSet.insert(_Right);
}


void GameWorld::ColCheck(std::list<GameActor*>& _LeftGroup, std::list<GameActor*>& _RightGroup)
{

	for (auto& _LeftCol : _LeftGroup)
	{
		if (true == _LeftCol->IsDeath())
		{
			continue;
		}

		if (false == _LeftCol->GetIsCol())
		{
			continue;
		}

		for (auto& _RightCol : _RightGroup)
		{
			// 상대의 충돌 타입과
			// 나의 충돌타입에 맞는.
			// 충돌 체크를 해줘야 한다는 겁니다.

			if (true == _RightCol->IsDeath())
			{
				continue;
			}

			if (false == _RightCol->GetIsCol())
			{
				continue;
			}

			int LeftType = static_cast<int>(_LeftCol->GetColType());
			int RightType = static_cast<int>(_RightCol->GetColType());

			_LeftCol->Setting();
			_RightCol->Setting();

			if (true == GameEngineCollision::COLFUNC[LeftType][RightType](_LeftCol->GetCollisionDataRef(), _RightCol->GetCollisionDataRef()))
			{
				_LeftCol->ColStay(_LeftCol, _RightCol);
				_RightCol->ColStay(_RightCol, _LeftCol);
			}

		}
	}
}

void GameWorld::KDColCheck(std::list<GameActor*>& _Left, std::list<GameActor*>& _Right) 
{
	
	std::vector<GameActor*> m_GroupVector;
	std::vector<float4> m_GroupPos;

	for (auto& _Value : _Left)
	{
		m_GroupVector.push_back(_Value);
		m_GroupPos.push_back(_Value->GetPos());
	}

	KDTree<float4> _KDTree = &m_GroupPos;

	for (auto& _RightCol : _Right)
	{
		if (true == _RightCol->IsDeath())
		{
			continue;
		}

		if (false == _RightCol->GetIsCol())
		{
			continue;
		}

		_RightCol->Setting();

		// 내 위치랑 내 
		std::vector<int> Check = _KDTree.RadiusSearch(_RightCol->GetPos(), _RightCol->GetCollisionDataRef().m_OBB.Extents.x);

		if (0 >= Check.size())
		{
			continue;
		}

		for (size_t i = 0; i < Check.size(); i++)
		{
			GameActor* _LeftCol = m_GroupVector[Check[i]];

			int LeftType = static_cast<int>(_LeftCol->GetColType());
			int OtherType = static_cast<int>(_RightCol->GetColType());

			if (OtherType == COLTYPE::CT_SPHERE)
			{
				_LeftCol->ColStay(_LeftCol, _RightCol);
				_RightCol->ColStay(_RightCol, _LeftCol);
				continue;
			}

			// _LeftCol->Setting();

			if (true == GameEngineCollision::COLFUNC[LeftType][OtherType](_LeftCol->GetCollisionDataRef(), _RightCol->GetCollisionDataRef()))
			{
				_LeftCol->ColStay(_LeftCol, _RightCol);
				_RightCol->ColStay(_RightCol, _LeftCol);
			}
		}
	}

}


void GameWorld::Collision()
{
	for (auto& LeftGroup : m_ColLink)
	{
		int LeftOrder = LeftGroup.first;
		std::set<int> RightGorups = LeftGroup.second;

		for (int RightOrder : RightGorups)
		{
			// 서버는 액터에 역여있지도 않기 때문에 그냥 리스트로 받아오면 충돌체크가 가능하다.
			std::list<GameActor*>& _LeftCollisions = m_ColMap[LeftOrder];
			std::list<GameActor*>& _RightCollisions = m_ColMap[RightOrder];

			if (_RightCollisions.size() != 0 && RightOrder == (int)LogicValue::CollisionLayer::PLAYERATTACK)
			{
				int a = 0;
			}

			if (m_IsKDTree.end() != m_IsKDTree.find(LeftOrder))
			{
				KDColCheck(_LeftCollisions, _RightCollisions);
				continue;
			}

			if (m_IsKDTree.end() != m_IsKDTree.find(RightOrder))
			{
				KDColCheck(_RightCollisions, _LeftCollisions);
				continue;
			}

			ColCheck(_LeftCollisions, _RightCollisions);
		}
	}
}

void GameWorld::SetKDTree(int _Test)
{
	if (m_IsKDTree.end() != m_IsKDTree.find(_Test))
	{
		return;
	}

	m_IsKDTree.insert(_Test);
}

void GameWorld::Release()
{
	// 이거때문에 터진겁니다.
	// 	   // 지역변수로 선언해놓으면 지역변수가 우선되기 때문에
	// 	   // 맴버변수 m_ColMap을 뺀게 아니고 
	// 	   // m_ColMap에서 빼주고 있었네요 ㅠㅠ
	// std::map<int, std::list<GameActor*>> m_ColMap;
	for (auto& _Data : m_ColMap)
	{
		std::list<GameActor*>::iterator Start = _Data.second.begin();
		std::list<GameActor*>::iterator End = _Data.second.end();

		for (; Start != End;)
		{
			if (true == (*Start)->IsDeath())
			{
				Start = _Data.second.erase(Start);
			}
			else if (true == (*Start)->IsWorldMove())
			{
				// 충돌체도 빼줘야 합니다.
				Start = _Data.second.erase(Start);
			}
			else 
			{
				++Start;
			}
		}

	}

	World::Release();
}

GameActor* GameWorld::CheckCollison(GameActor* _Col, COLTYPE _Type, float4 _Scale, float4 _Move, int _Order)
{
	GameEngineColData Data;

	float4 OriPos = _Col->GetPos();
	OriPos += _Move;
	Data.m_OBB.Center = OriPos.Dxfloat3;
	Data.SetScale(_Scale);

	Data.SettingChangeSpace();

	std::list<GameActor*>& _GolGroup = m_ColMap[_Order];

	int LeftType = static_cast<int>(_Type);

	for (auto& Col : _GolGroup)
	{

		Col->Setting();
		if (true == GameEngineCollision::COLFUNC[LeftType][(int)Col->GetColType()](Data, Col->GetCollisionDataRef()))
		{
			return Col;
		}
	}

	return nullptr;
}