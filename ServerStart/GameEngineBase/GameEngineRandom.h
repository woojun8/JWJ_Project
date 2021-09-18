#pragma once
#include <random>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class GameEngineRandom
{
private: // Static Var
public: // Static Func
private: // member Var
    // �õ尪 
    // �̰� 
    // �����忡 �����ұ��?
    // �� ������?
    // ThreadSafeRandom�� �� ������ �ϴϱ�.
    // �̸� 10000���� �������� ������
    // pop�ϴ� ���
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

