#include "World.h"
#include "Actor.h"
#include "WorldManager.h"
#include <GameEngineDebug.h>

// Static Var
// Static Func

// constructer destructer
World::World()  : RecvMsgListIndex(0)
{

}

World::~World() 
{

}
// member Func

void World::WorldMoveCheck() 
{
	std::list<std::shared_ptr<Actor>>::iterator Start = m_MoveActorList.begin();
	std::list<std::shared_ptr<Actor>>::iterator End = m_MoveActorList.end();

	// 내부에서 처리가 되어야 합니다.
	for (; Start != End;)
	{
		// 이동하기전에 처리할 패킷을 쏜다.
		// 현재 내 월드의 유저들에게 나의 월드 이동을 알리면서
		// 나를 삭제하라고 해야하고.
		(*Start)->WorldPrevMoveTask();
		// 자신이 월드 이동전에 처리해야할 일들을 처리하고
		std::shared_ptr<World> NextWorld = m_pManager->FindWorld((*Start)->GetNextWorldName());
		if (nullptr != NextWorld)
		{
			// 여기서 꼭 자신의 다음 월드에 넣어줘야 하는 이유가 있다.
			// 액터의 레퍼런스카운트가 0되서 삭제가 됩니다.
			// 레퍼런스 카운트를 유지시키기 위해서 넣어주고 삭제해야 합니다.
			// 이 (*Start) std::sheard_ptr<Actor>가 삭제가 되므로
			// 꼭 넣어준다.
			NextWorld->PushWaitActor((*Start), (*Start)->GetLayer());
			(*Start)->SetWorld(NextWorld.get());
			(*Start)->WorldNextMoveTask();

			// 여기에 들어가게 됩니다.
			// 이 웨이트 액터가 진짜 월드에 진입하게 되면 처리하겠습니다.
			// NextWorld->PushWaitActor((*Start), (*Start)->GetLayer());
			// 내가 월드를 이동하고 난후니까.
			// 이 월드에 유저들이 있을수 있으므로 이 월드안에 있는 유저들에게 내가 이제 이 월드로 들어왔다는
			// 것을 알려줘야 합니다.
			// 
		}
		else 
		{
			GameEngineDebug::AssertMsg("if (nullptr == NextWorld)");
		}

		// 이건 확정.
		Start = m_MoveActorList.erase(Start);
	}

}

void World::MsgUpdate() 
{
	// 이 메세지 리스트는 처리가 되는 도중에는 
	// 당연히 리시브를 못받으니까.
	std::vector<std::function<void()>>& MsgList = GetProcessMsgList();

	for (size_t i = 0; i < MsgList.size(); i++)
	{
		// 메세지 처리.
		if (NULL != MsgList[i])
		{
			MsgList[i]();
		}		
	}

	MsgList.clear();

}

void World::UpdatePrev(float _DeltaTime)
{
	for (auto& _ActorList : m_ActorList)
	{
		for (std::shared_ptr<Actor>& _Actor : _ActorList.second)
		{
			if (true == _Actor->IsDeath())
			{
				continue;
			}
			_Actor->UpdatePrev(_DeltaTime);
		}
	}
}


void World::Update(float _DeltaTime)
{
	for (auto& _ActorList : m_ActorList)
	{
		for (std::shared_ptr<Actor>& _Actor : _ActorList.second)
		{
			if (true == _Actor->IsDeath())
			{
				continue;
			}
			_Actor->Update(_DeltaTime);
		}
	}
}
void World::UpdateNext(float _DeltaTime)
{
	for (auto& _ActorList : m_ActorList)
	{
		for (std::shared_ptr<Actor>& _Actor : _ActorList.second)
		{
			if (true == _Actor->IsDeath())
			{
				continue;
			}
			_Actor->UpdateNext(_DeltaTime);
		}
	}
}


void World::CollisionPrev()
{
	for (auto& _ActorList : m_ActorList)
	{
		for (std::shared_ptr<Actor>& _Actor : _ActorList.second)
		{
			if (true == _Actor->IsDeath())
			{
				continue;
			}
			_Actor->CollisionPrev();
		}
	}
}


void World::Collision()
{
	for (auto& _ActorList : m_ActorList)
	{
		for (std::shared_ptr<Actor>& _Actor : _ActorList.second)
		{
			if (true == _Actor->IsDeath())
			{
				continue;
			}

			_Actor->Collision();
		}
	}
}


void World::CollisionNext()
{
	for (auto& _ActorList : m_ActorList)
	{
		for (std::shared_ptr<Actor>& _Actor : _ActorList.second)
		{
			if (true == _Actor->IsDeath())
			{
				continue;
			}
			_Actor->CollisionNext();
		}
	}
}


void World::Release() 
{
	for (auto& _ActorList : m_ActorList)
	{
		std::list<std::shared_ptr<Actor>>::iterator Start = _ActorList.second.begin();
		std::list<std::shared_ptr<Actor>>::iterator End = _ActorList.second.end();

		for (; Start != End; )
		{
			if (true == (*Start)->IsDeath())
			{
				// 이순간 다른 유저들에게 내가 죽었다는걸 알려줘야 한다.
				(*Start)->DeathTask();
				Start = _ActorList.second.erase(Start);
			}
			else if (true == (*Start)->IsWorldMove())
			{
				// 살아는 있죠? 레퍼런스 카운트 체크겸
				// 월드를 이동할 액터들을 모아 놓는 역할.
				m_MoveActorList.push_back((*Start));
				Start = _ActorList.second.erase(Start);
			}
			else {
				++Start;
			}
		}
	}
}

void World::MsgListInit(int _Count, int _Size) 
{
	m_MsgList.resize(_Count);
	MaxMsgListCount = _Count;
	RecvMsgListIndex = 0;
	for (size_t i = 0; i < m_MsgList.size(); i++)
	{
		m_MsgList[i].reserve(_Size);
	}
}

void World::PushActor(std::shared_ptr<Actor> _Actor, int _LayerIndex)
{
	// std::shared_ptr<T> Ptr = std::make_shared<T>();

	if (m_ActorList.end() == m_ActorList.find(_LayerIndex))
	{
		// 자동으로 그 레이어가 생기죠?
		m_ActorList[_LayerIndex];
	}
	_Actor->SetLayer(_LayerIndex);
	_Actor->SetWorld(this);

	m_ActorList[_LayerIndex].push_back(_Actor);
}

void World::PushWaitActor(std::shared_ptr<Actor> _Actor, int _LayerIndex)
{
	if (m_WaitActor.end() == m_WaitActor.find(_LayerIndex))
	{
		// 자동으로 그 레이어가 생기죠?
		m_WaitActor[_LayerIndex];
	}

	_Actor->SetLayer(_LayerIndex);
	// std::shared_ptr<T> Ptr = std::make_shared<T>();
	m_WaitActor[_Actor->GetLayer()].insert(_Actor);
}

bool World::WaitActorInWorld(std::shared_ptr<Actor> _Ptr)
{
	// std::shared_ptr<Actor> FindPtr(_Ptr);
	std::set<std::shared_ptr<Actor>>::iterator FindIter = m_WaitActor[_Ptr->GetLayer()].find(_Ptr);

	if (m_WaitActor[_Ptr->GetLayer()].end() == FindIter)
	{
		return false;
	}

	m_WaitActor[_Ptr->GetLayer()].erase(FindIter);
	ActorStart(_Ptr.get());
	PushActor(_Ptr, _Ptr->GetLayer());
	return true;
}
