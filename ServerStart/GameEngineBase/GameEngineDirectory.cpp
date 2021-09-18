#include "GameEngineDirectory.h"
#include <WinSock2.h>

EngineString GameEngineDirectory::GetCurrentDirectoryPath() 
{
	wchar_t Arr[MAXPATHLEN];
	GetCurrentDirectoryW(MAXPATHLEN, Arr);
	EngineString String = Arr;
	String += L"\\";
	return String;
}

// Constructer Destructer ----------------------------------------------------
GameEngineDirectory::GameEngineDirectory() 
{
	m_Path = GetCurrentDirectoryPath();

}
GameEngineDirectory::~GameEngineDirectory() 
{

}
// GameEngineDirectory::GameEngineDirectory(const GameEngineDirectory& _Other) {}
// GameEngineDirectory::GameEngineDirectory(GameEngineDirectory&& _Other) {}

// operator -----------------------------------------------------------------
// GameEngineDirectory& GameEngineDirectory::operator=(const GameEngineDirectory& _Other) {}
// GameEngineDirectory& GameEngineDirectory::operator=(GameEngineDirectory&& _Other) {}


// member Function -----------------------------------------------------------





