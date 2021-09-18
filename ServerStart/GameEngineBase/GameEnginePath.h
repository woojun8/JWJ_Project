#pragma once
#include <iostream>
#include "GameEngineString.h"

enum class IOTYPE 
{
	FILE,
	DIRECTORY,
	NONE,
};

enum IOCONSTVALUE
{
	MAXPATHLEN = 256,
};

class GameEngineFile;
// Ό³Έν : 
class GameEnginePath
{

private:	// static Var
public:		// static Func
protected:	// Member Var
	GameEngineString m_Path;

public:	// Constructer Destructer
	GameEnginePath();
	GameEnginePath(const EngineString& _String);
	GameEnginePath(const wchar_t* _String);

	~GameEnginePath();
	GameEnginePath(const GameEnginePath& _Other) : m_Path(_Other.m_Path)
	{
		
	}
	GameEnginePath(GameEnginePath&& _Other) : m_Path(_Other.m_Path)
	{

	}

public:	// operator
	GameEnginePath& operator=(const GameEnginePath& _Other) {
		m_Path = _Other.m_Path;
	}
	GameEnginePath& operator=(GameEnginePath&& _Other) {
		m_Path = _Other.m_Path;
	}

public: // GetSet
	EngineString GetFullPath() {
		return m_Path;
	}

public: // member Function
	void MoveParent();
	void MoveParent(const GameEngineString& _Name);
	void Move(const GameEngineString& _Name);

	bool IsExist();

	IOTYPE GetIOType();

	GameEngineString IoName();

	GameEngineFile GetFile(const GameEngineString& _Name);

};