#pragma once
#include "GameEnginePath.h"

// Ό³Έν : 
class GameEngineDirectory : public GameEnginePath
{
private:	// static Var
public:		// static Func
	static EngineString GetCurrentDirectoryPath();

private:	// Member Var

public:	// Constructer Destructer
	GameEngineDirectory();
	~GameEngineDirectory();
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) = delete;

public:	// operator
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) = delete;

public:
	void Func() {
		int a = 0;
	}
};