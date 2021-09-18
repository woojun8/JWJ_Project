#include "GameWorldManager.h"
#include <GameEngineDebug.h>
#include "GameWorld.h"

// Static Var
// Static Func

// constructer destructer
GameWorldManager::GameWorldManager() 
{

}

GameWorldManager::~GameWorldManager()
{

}

void GameWorldManager::UpdateCheck(const Posfloat4& _Pos) 
{
	PosToKeyConvert Key = _Pos;
	WorldManager::UpdateCheck(Key.ToString());
}
