#include "GameEnginePath.h"
#include <assert.h>
#include "GameEngineFile.h"
#include "GameEngineDebug.h"


// Constructer Destructer ----------------------------------------------------
GameEnginePath::GameEnginePath() 
{

}

GameEnginePath::GameEnginePath(const EngineString& _String) : m_Path(_String)
{

}

GameEnginePath::GameEnginePath(const wchar_t* _String) : m_Path(_String)
{

}
GameEnginePath::~GameEnginePath() 
{

}
// GameEnginePath::GameEnginePath(const GameEnginePath& _Other) {}
// GameEnginePath::GameEnginePath(GameEnginePath&& _Other) {}

// operator -----------------------------------------------------------------
// GameEnginePath& GameEnginePath::operator=(const GameEnginePath& _Other) {}
// GameEnginePath& GameEnginePath::operator=(GameEnginePath&& _Other) {}


// member Function -----------------------------------------------------------
void GameEnginePath::MoveParent()
{
	size_t LastIndex = m_Path.FindLastOf(L'\\', m_Path.size() - 2);
	m_Path.DeleteString(LastIndex + 1, m_Path.size());
}

void GameEnginePath::MoveParent(const GameEngineString& _Name) 
{
	while (true)
	{
		if (IoName() == _Name)
		{
			break;
		}
		MoveParent();
	}
}

void GameEnginePath::Move(const GameEngineString& _Name) 
{
	GameEnginePath CheckPath = m_Path;
	CheckPath.m_Path += _Name;
	CheckPath.m_Path += L"\\";

	if (false == CheckPath.IsExist())
	{
		assert(false);
	}

	m_Path = CheckPath.m_Path;
}

IOTYPE GameEnginePath::GetIOType() 
{
	wchar_t Arr = m_Path.At(m_Path.size() - 1);

	if (L'\\' == Arr)
	{
		return IOTYPE::DIRECTORY;
	}

	return IOTYPE::FILE;
}

GameEngineString GameEnginePath::IoName() 
{
	size_t LastIndex = m_Path.FindLastOf(L'\\', m_Path.size() - 2);
	return m_Path.GetCutString(LastIndex + 1, m_Path.size() - (LastIndex + 1) - 1);
}

bool GameEnginePath::IsExist()
{
	if (0 == _waccess_s(m_Path.ConstStringPtr(), 0))
	{
		return true;
	}
	return false;
}


GameEngineFile GameEnginePath::GetFile(const GameEngineString& _FileName)
{
	GameEngineString FullPath = GetFullPath();
	FullPath += _FileName;

	GameEngineFile File = GameEngineFile(FullPath);

	if (false == File.IsExist())
	{
		GameEngineDebug::AssertMsg("if (false == File.IsExist())");
	}

	return File;
}