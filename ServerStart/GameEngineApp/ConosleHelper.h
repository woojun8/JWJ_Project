#pragma once
#include <GEMath.h>
#include <WinSock2.h>

class ConosleHelper
{
private:
	static GEVector m_Size;
	static int m_LineSize;
	static HANDLE ConsoleHandle;

public:
	static void SetSize(float4 _Size) 
	{
		m_Size = _Size;
	}

public:
	static Sizefloat4 GetSize();
	static Posfloat4 GetCenter();
	static bool IsOut(Posfloat4 _Pos);

public:
	// 외부에 라인을 치는 기능은 이녀석이 게임과 연관있게 되어버린 거니 빼버릴께요
	static void Init();

	// 함수를 만들때는
	// 작은 기능들의 함수로 만들고
	// 그것들을 혼합해서 큰함수를 만들어
	static void ConsolePosMove(const GEVector& _Pos);
	static void ConsolePosPrint(const GEVector& _Pos, wchar_t _Text, bool _IsWallCheck = true);
	static void ConsolePosPrint(const GEVector& _Pos, const wchar_t* _Text, bool _IsWallCheck = true);
	static void ConsolePosClear(const GEVector& _Pos);

private:
	ConosleHelper();
	virtual ~ConosleHelper() = 0;
};