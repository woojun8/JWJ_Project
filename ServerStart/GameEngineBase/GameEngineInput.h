#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "GameEngineString.h"

// lib
// dll

// Ό³Έν : 
class GameEngineInput
{

private:	// Member Var
	// "LeftMove" 'a'
	// "RightMove" 'd'

private:
	class EngineKey 
	{
	private:
		friend GameEngineInput;
	private:
		bool Push;
		bool Press;
		bool Up;
		bool Free;
		float PressTime;

	public:
		std::vector<int> m_KeyVec;

	public:
		bool CheckKey();
		void Update();

	public:
		void ReserveKey(size_t _Size)
		{
			m_KeyVec.reserve(_Size);
		}

		template<typename ...REST>
		void PushKey(char _Value, REST ... _Arg) 
		{
			if ('a' <= _Value && 'z' >= _Value)
			{
				_Value = toupper(_Value);
			}

			m_KeyVec.push_back(_Value);
			PushKey(_Arg...);
		}

		void PushKey()
		{
			m_KeyVec;
			int a = 0;
		}

		EngineKey() : Push(false), Press(false), Up(false), Free(true)
		{

		}
	};



private:	// static Var
	static GameEngineInput BaseInput;

private:
	static std::shared_ptr<EngineKey> FindKey(const EngineString& _Name);

public:		// static Func
	static GameEngineInput& GetInst();
	static bool IsKey(const EngineString& _Name);
	static bool IsUp(const EngineString& _Name);
	static bool IsFree(const EngineString& _Name);
	static bool IsPush(const EngineString& _Name);
	static bool IsPress(const EngineString& _Name);


private:
	std::map<EngineString, std::shared_ptr<EngineKey>> m_AllCheckKey;

public:
	template<typename ...REST>
	void CreateKey(const EngineString& _Name, REST ... _Arg)
	{
		std::shared_ptr<EngineKey> NewKey = std::make_shared<EngineKey>();
		NewKey->ReserveKey(sizeof...(_Arg));
		NewKey->PushKey(_Arg...);
		m_AllCheckKey.insert(std::map<EngineString, std::shared_ptr<EngineKey>>::value_type(_Name, NewKey));
	}

private:	// Constructer Destructer
	GameEngineInput();
	~GameEngineInput();
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) = delete;

public:	// operator
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) = delete;

public: // member Function
	void KeyCheck();
};