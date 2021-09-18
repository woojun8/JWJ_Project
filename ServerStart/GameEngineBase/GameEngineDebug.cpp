#include "GameEngineDebug.h"
#include <assert.h>
#include <crtdbg.h>

// Static Var
// Static Func

void GameEngineDebug::LeckCheck() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void GameEngineDebug::AssertMsg(const char* _Msg) 
{
	if (nullptr == _Msg)
	{
		assert(!"nullptr Msg");
	}

	assert(!_Msg);
}

// constructer destructer
GameEngineDebug::GameEngineDebug() 
{

}

GameEngineDebug::~GameEngineDebug() 
{

}
// member Func

