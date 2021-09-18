#include "WorldManager.h"
#include <GameEngineTime.h>

// Static Var
// Static Func

// constructer destructer
WorldManager::WorldManager() : FrameRateDeltaTime(0.0f)
{

}

WorldManager::~WorldManager() 
{

}
// member Func

std::shared_ptr<World> WorldManager::FindWorld(std::string _Name)
{
	if (m_AllWorld.end() == m_AllWorld.find(_Name))
	{
		return nullptr;
	}

	// �̰� ���� ������ ���������ϴ�.
	return m_AllWorld[_Name];
}


void WorldManager::UpdateCheck(std::string _Name) 
{
	if (m_AllWorld.end() == m_AllWorld.find(_Name))
	{
		return;
	}

	if (m_UpdateWorldMap.end() != m_UpdateWorldMap.find(_Name))
	{
		return;
	}

	std::shared_ptr<World> FindWorld = m_AllWorld[_Name];

	m_UpdateWorldList.push_back(FindWorld);
	m_UpdateWorldMap[_Name] = FindWorld;
	return;
}

void WorldManager::Progress(float _DeltaTime)
{
	// CurFrameRateTime -= GameEngineTime::GetInst().FTime();
	// �׷��� ���⿡�� ������Ʈ ������ ������ �־��� �̴ϴ�.

	// ���� ���ڳ� ���Ϳ� ��ȭ�� �� ���� ����°���
	// �����Ӵ����� ��Ƴ��ٰ�.

	// �� �������� �����ϱ�����
	// �� ���͵�� ����鿡 �� �����ְ�
	// ó���ϰ� �ϴ°��� �ǹ��մϴ�.
	// �ϵ��� �ް� �˰̴ϴ�.
	// ���Ϳ� �������

		// ��� ���� �����ϱ� ���� ó���մϴ�.
	for (auto& UpdateWorld : m_UpdateWorldList)
	{
		UpdateWorld->MsgUpdate();
	}


	for (auto& UpdateWorld : m_UpdateWorldList)
	{
		UpdateWorld->WorldMoveCheck();
	}

	CurFrameRateTime -= _DeltaTime;
	FrameRateDeltaTime += _DeltaTime;

	if (0.0f >= CurFrameRateTime)
	{
		for (auto& UpdateWorld : m_UpdateWorldList)
		{
			UpdateWorld->CollisionPrev();
		}

		for (auto& UpdateWorld : m_UpdateWorldList)
		{
			UpdateWorld->Collision();
		}

		for (auto& UpdateWorld : m_UpdateWorldList)
		{
			UpdateWorld->CollisionNext();
		}
	}

	// ���� ��� ������ �� ���� ������Ʈ
	for (auto& UpdateWorld : m_UpdateWorldList)
	{
		UpdateWorld->WorldUpdate();
	}


	{

		// CurFrameRateTime 0.00001f

		if (0.0f >= CurFrameRateTime)
		{
			// ������������ �ɷȴٸ� �׳� ��ŸŸ���� �־��ָ� �ȵȴ�.

			// float AbsTime = FrameRateTime + (CurFrameRateTime + FrameRateTime);

			for (auto& UpdateWorld : m_UpdateWorldList)
			{
				UpdateWorld->UpdatePrev(FrameRateDeltaTime);
			}
			for (auto& UpdateWorld : m_UpdateWorldList)
			{
				UpdateWorld->Update(FrameRateDeltaTime);
			}
			for (auto& UpdateWorld : m_UpdateWorldList)
			{
				UpdateWorld->UpdateNext(FrameRateDeltaTime);
			}
		}

	}

	if (0.0f >= CurFrameRateTime)
	{
		CurFrameRateTime += FrameRateTime;
		FrameRateDeltaTime = 0.0f;
	}

	// �������� ��Ģ�� �ִµ�.
	// ����� ���� �߿� ����� ���� ���� �ʽ��ϴ�.
	for (auto& UpdateWorld : m_UpdateWorldList)
	{
		UpdateWorld->Release();
	}

	// ���̻� ����� ������Ʈ ���°� �ƴϴ� ����� ���ټ� �ִ� ��ɵ� �����ؾ� �մϴ�.
}