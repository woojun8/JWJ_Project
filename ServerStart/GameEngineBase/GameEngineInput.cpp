#include "GameEngineInput.h"
#include "GameEngineTime.h"
#include <WinSock2.h>

// class EngineKey ------------------------------------------------------------------------------------------------------------------------------------------------------------
bool GameEngineInput::EngineKey::CheckKey() 
{
	bool Check = true;

	for (size_t i = 0; i < m_KeyVec.size(); i++)
	{
		// 비동기 입력 체크 함수입니다.
		if (0 == GetAsyncKeyState(m_KeyVec[i]))
		{
			return false;
		}
	}

	return true;
}

void GameEngineInput::EngineKey::Update()
{
	if (true == CheckKey())
	{
		if (false == Press)
		{
			Push = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else 
		{
			Push = false;
			Press = true;
			Up = false;
			Free = false;
		}
	}
	else 
	{
		if (true == Press)
		{
			Push = false;
			Press = false;
			Up = true;
			Free = false;
		}
		else
		{
			Push = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}

}


// static ----------------------------------------------------
GameEngineInput GameEngineInput::BaseInput;

GameEngineInput& GameEngineInput::GetInst()
{
	return BaseInput;
}

std::shared_ptr<GameEngineInput::EngineKey> GameEngineInput::FindKey(const EngineString& _Name)
{
	std::map<EngineString, std::shared_ptr<EngineKey>>::iterator FindIter = GetInst().m_AllCheckKey.find(_Name);

	if (FindIter != GetInst().m_AllCheckKey.end())
	{
		return FindIter->second;
	}

	return nullptr;

}

bool GameEngineInput::IsKey(const EngineString& _Name) {
	std::shared_ptr<EngineKey> Key = FindKey(_Name);

	if (nullptr == Key)
	{
		return false;
	}

	return true;
}

bool GameEngineInput::IsUp(const EngineString& _Name) 
{
	std::shared_ptr<EngineKey> Key = FindKey(_Name);

	if (nullptr == Key)
	{
		return false;
	}

	return Key->Up;
}
bool GameEngineInput::IsFree(const EngineString& _Name) 
{
	std::shared_ptr<EngineKey> Key = FindKey(_Name);

	if (nullptr == Key)
	{
		return false;
	}

	return Key->Up;
}
bool GameEngineInput::IsPush(const EngineString& _Name) 
{
	std::shared_ptr<EngineKey> Key = FindKey(_Name);

	if (nullptr == Key)
	{
		return false;
	}

	return Key->Push;
}
bool GameEngineInput::IsPress(const EngineString& _Name) 
{
	std::shared_ptr<EngineKey> Key = FindKey(_Name);

	if (nullptr == Key)
	{
		return false;
	}

	return Key->Press;
}

// Constructer Destructer ----------------------------------------------------
GameEngineInput::GameEngineInput() 
{

}
GameEngineInput::~GameEngineInput() 
{

}
// GameEngineInput::GameEngineInput(const GameEngineInput& _Other) {}
// GameEngineInput::GameEngineInput(GameEngineInput&& _Other) {}

// operator -----------------------------------------------------------------
// GameEngineInput& GameEngineInput::operator=(const GameEngineInput& _Other) {}
// GameEngineInput& GameEngineInput::operator=(GameEngineInput&& _Other) {}


// member Function -----------------------------------------------------------

void GameEngineInput::KeyCheck() 
{
	for (auto& _Key : m_AllCheckKey)
	{
		_Key.second->Update();
	}

	//GameEngineTime::GetInst().DTime();
}