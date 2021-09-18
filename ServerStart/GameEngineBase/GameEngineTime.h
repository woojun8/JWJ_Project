#pragma once
#include <WinSock2.h>

// 설명 : 
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


	// 함수 선언(내 이름이 불리면 나와 연결된 함수체를 찾아서 함수체의 내용을 실행한다.)
	// static inline float FTime() 

	// 함수체
	//{
	//	return GetInst().m_fDeltaTime;
	//}

	inline float FTime()
	{
		return m_fDeltaTime;
	}

private:	// Member Var
	// 윈도우 플랫폼에서만 가능한 시간재기 방법입니다.
	LARGE_INTEGER m_SecondTime;
	LARGE_INTEGER m_CurTime;
	LARGE_INTEGER m_PrevTime;
	double m_DeltaTime;
	float m_fDeltaTime;

	// 그냥 만들수 있고 1개의 메인 객체도 따로 있다.
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