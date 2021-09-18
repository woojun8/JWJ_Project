#include "GameEngineRandom.h"

// Static Var
// Static Func

std::random_device GameEngineRandom::RandomDevcie;
std::mt19937 GameEngineRandom::Gen;
int GameEngineRandom::StartSeed = 0;

// constructer destructer
GameEngineRandom::GameEngineRandom() 
{

}

GameEngineRandom::~GameEngineRandom() 
{

}
// member Func

void GameEngineRandom::Init(int _Seed)
{
	if (_Seed == -1)
	{
		// 함수객체를 이용해서 지원해준다.
		StartSeed = GameEngineRandom::RandomDevcie();
		Gen = std::mt19937(StartSeed);
	}
	else 
	{
		StartSeed = _Seed;
		Gen = std::mt19937(_Seed);
	}
}

unsigned int GameEngineRandom::GetRandomUint(int _Max) 
{
	std::uniform_int_distribution<unsigned int> dis(_Max);
	return dis(Gen);
}
int GameEngineRandom::GetRandomUint(int Min, int _Max)
{
	std::uniform_int_distribution<int> dis(Min, _Max);
	return dis(Gen);
}

float GameEngineRandom::GetRandomFloat(float Min, float _Max)
{
	std::uniform_real_distribution<float> dis(Min, _Max);
	return dis(Gen);
}