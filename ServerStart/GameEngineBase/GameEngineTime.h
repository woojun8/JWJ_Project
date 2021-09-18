#pragma once
#include <WinSock2.h>

// ���� : 
class GameEngineTime
{
private:	// static Var
	static GameEngineTime Inst;

public:		// static Func
	static GameEngineTime& GetInst();

	inline double DTime()
	{
		return m_DeltaTime;
	}


	// �Լ� ����(�� �̸��� �Ҹ��� ���� ����� �Լ�ü�� ã�Ƽ� �Լ�ü�� ������ �����Ѵ�.)
	// static inline float FTime() 

	// �Լ�ü
	//{
	//	return GetInst().m_fDeltaTime;
	//}

	inline float FTime()
	{
		return m_fDeltaTime;
	}

private:	// Member Var
	// ������ �÷��������� ������ �ð���� ����Դϴ�.
	LARGE_INTEGER m_SecondTime;
	LARGE_INTEGER m_CurTime;
	LARGE_INTEGER m_PrevTime;
	double m_DeltaTime;
	float m_fDeltaTime;

	// �׳� ����� �ְ� 1���� ���� ��ü�� ���� �ִ�.
public:	// Constructer Destructer
	GameEngineTime();
	~GameEngineTime();
	GameEngineTime(const GameEngineTime& _Other) : 
		m_SecondTime(_Other.m_SecondTime),
		m_CurTime(_Other.m_CurTime),
		m_PrevTime(_Other.m_PrevTime),
		m_DeltaTime(_Other.m_DeltaTime),
		m_fDeltaTime(_Other.m_fDeltaTime)
	{

	}
	GameEngineTime(GameEngineTime&& _Other) :
		m_SecondTime(_Other.m_SecondTime),
		m_CurTime(_Other.m_CurTime),
		m_PrevTime(_Other.m_PrevTime),
		m_DeltaTime(_Other.m_DeltaTime),
		m_fDeltaTime(_Other.m_fDeltaTime)
	{

	}

public:	// operator
	GameEngineTime& operator=(const GameEngineTime& _Other) 
	{
		m_SecondTime = _Other.m_SecondTime;
		m_CurTime = _Other.m_CurTime;
		m_PrevTime = _Other.m_PrevTime;
		m_DeltaTime = _Other.m_DeltaTime;
		m_fDeltaTime = _Other.m_fDeltaTime;
	}
	GameEngineTime& operator=(GameEngineTime&& _Other) {
		m_SecondTime =_Other.m_SecondTime;
			m_CurTime = _Other.m_CurTime;
			m_PrevTime = _Other.m_PrevTime;
			m_DeltaTime = _Other.m_DeltaTime;
			m_fDeltaTime = _Other.m_fDeltaTime;
	}

public: // member Function
	void Update();

};