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

	// 이걸 쓰면 없으면 만들어버립니다.
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
	// 그래서 여기에서 업데이트 월드라는 개념을 넣어준 겁니다.

	// 뭔가 숫자나 액터에 변화를 줄 일이 생기는것을
	// 프레임단위로 모아놨다가.

	// 한 프레임이 시작하기전에
	// 각 액터들과 월드들에 다 나눠주고
	// 처리하게 하는것을 의미합니다.
	// 일들을 받게 됩겁니다.
	// 액터와 월드들은

		// 모든 일을 시작하기 전에 처리합니다.
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

	// 씬만 사용 가능한 씬 전용 업데이트
	for (auto& UpdateWorld : m_UpdateWorldList)
	{
		UpdateWorld->WorldUpdate();
	}


	{

		// CurFrameRateTime 0.00001f

		if (0.0f >= CurFrameRateTime)
		{
			// 프레임제한이 걸렸다면 그냥 델타타임을 넣어주면 안된다.

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

	// 선생님의 규칙이 있는데.
	// 절대로 도는 중에 지우는 일을 하지 않습니다.
	for (auto& UpdateWorld : m_UpdateWorldList)
	{
		UpdateWorld->Release();
	}

	// 더이상 여기는 업데이트 상태가 아니다 등등을 해줄수 있는 기능도 존재해야 합니다.
}