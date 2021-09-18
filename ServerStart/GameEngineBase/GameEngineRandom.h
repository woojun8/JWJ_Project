#pragma once
#include <random>

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class GameEngineRandom
{
private: // Static Var
public: // Static Func
private: // member Var
    // 시드값 
    // 이걸 
    // 쓰레드에 안전할까요?
    // 모를 일이죠?
    // ThreadSafeRandom을 또 만들어야 하니까.
    // 미리 10000개의 랜덤값을 만들어내고
    // pop하는 방법
    static std::random_device RandomDevcie;
    static std::mt19937 Gen;
    static int StartSeed;


public:
    static void Init(int _Seed = -1);
    static unsigned int GetRandomUint(int _Max);
    static int GetRandomUint(int Min, int _Max);
    static float GetRandomFloat(float Min, float _Max);

public: // constructer destructer
    GameEngineRandom();
    ~GameEngineRandom();

public: // delete constructer 
    GameEngineRandom(const GameEngineRandom& _Other) = delete;
    GameEngineRandom(const GameEngineRandom&& _Other) = delete;

public: // delete operator
    GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
    GameEngineRandom& operator=(const GameEngineRandom&& _Other) = delete;

public: // member Func
};

