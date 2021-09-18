#include "GameEngineTime.h"


GameEngineTime GameEngineTime::Inst;

GameEngineTime& GameEngineTime::GetInst()
{
	return Inst;
}

// Constructer Destructer ----------------------------------------------------
GameEngineTime::GameEngineTime() 
	: m_DeltaTime(0.0), m_fDeltaTime(0.0f), 
	m_SecondTime(), m_CurTime(), m_PrevTime()
{
	QueryPerformanceFrequency(&m_SecondTime);
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_PrevTime);
}

GameEngineTime::~GameEngineTime() 
{

}
// GameEngineTime::GameEngineTime(const GameEngineTime& _Other) {}
// GameEngineTime::GameEngineTime(GameEngineTime&& _Other) {}

// operator -----------------------------------------------------------------
// GameEngineTime& GameEngineTime::operator=(const GameEngineTime& _Other) {}
// GameEngineTime& GameEngineTime::operator=(GameEngineTime&& _Other) {}


// member Function -----------------------------------------------------------
void GameEngineTime::Update()
{
	QueryPerformanceCounter(&m_CurTime);
	__int64 InterCount = m_CurTime.QuadPart - m_PrevTime.QuadPart;
	m_DeltaTime = (double)InterCount / (double)m_SecondTime.QuadPart;
	m_fDeltaTime = static_cast<float>(m_DeltaTime);
	m_PrevTime.QuadPart = m_CurTime.QuadPart;
}