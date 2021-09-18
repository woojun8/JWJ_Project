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

	// ���ο��� ó���� �Ǿ�� �մϴ�.
	for (; Start != End;)
	{
		// �̵��ϱ����� ó���� ��Ŷ�� ���.
		// ���� �� ������ �����鿡�� ���� ���� �̵��� �˸��鼭
		// ���� �����϶�� �ؾ��ϰ�.
		(*Start)->WorldPrevMoveTask();
		// �ڽ��� ���� �̵����� ó���ؾ��� �ϵ��� ó���ϰ�
		std::shared_ptr<World> NextWorld = m_pManager->FindWorld((*Start)->GetNextWorldName());
		if (nullptr != NextWorld)
		{
			// ���⼭ �� �ڽ��� ���� ���忡 �־���� �ϴ� ������ �ִ�.
			// ������ ���۷���ī��Ʈ�� 0�Ǽ� ������ �˴ϴ�.
			// ���۷��� ī��Ʈ�� ������Ű�� ���ؼ� �־��ְ� �����ؾ� �մϴ�.
			// �� (*Start) std::sheard_ptr<Actor>�� ������ �ǹǷ�
			// �� �־��ش�.
			NextWorld->PushWaitActor((*Start), (*Start)->GetLayer());
			(*Start)->SetWorld(NextWorld.get());
			(*Start)->WorldNextMoveTask();

			// ���⿡ ���� �˴ϴ�.
			// �� ����Ʈ ���Ͱ� ��¥ ���忡 �����ϰ� �Ǹ� ó���ϰڽ��ϴ�.
			// NextWorld->PushWaitActor((*Start), (*Start)->GetLayer());
			// ���� ���带 �̵��ϰ� ���Ĵϱ�.
			// �� ���忡 �������� ������ �����Ƿ� �� ����ȿ� �ִ� �����鿡�� ���� ���� �� ����� ���Դٴ�
			// ���� �˷���� �մϴ�.
			// 
		}
		else 
		{
			GameEngineDebug::AssertMsg("if (nullptr == NextWorld)");
		}

		// �̰� Ȯ��.
		Start = m_MoveActorList.erase(Start);
	}

}

void World::MsgUpdate() 
{
	// �� �޼��� ����Ʈ�� ó���� �Ǵ� ���߿��� 
	// �翬�� ���ú긦 �������ϱ�.
	std::vector<std::function<void()>>& MsgList = GetProcessMsgList();

	for (size_t i = 0; i < MsgList.size(); i++)
	{
		// �޼��� ó��.
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
				// �̼��� �ٸ� �����鿡�� ���� �׾��ٴ°� �˷���� �Ѵ�.
				(*Start)->DeathTask();
				Start = _ActorList.second.erase(Start);
			}
			else if (true == (*Start)->IsWorldMove())
			{
				// ��ƴ� ����? ���۷��� ī��Ʈ üũ��
				// ���带 �̵��� ���͵��� ��� ���� ����.
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
		// �ڵ����� �� ���̾ ������?
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
		// �ڵ����� �� ���̾ ������?
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
