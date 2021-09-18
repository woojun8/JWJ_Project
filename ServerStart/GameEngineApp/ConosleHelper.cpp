#include "ConosleHelper.h"
#include <WinSock2.h>
#include <iostream>

HANDLE ConosleHelper::ConsoleHandle;


GEVector ConosleHelper::m_Size = {3, 3};
int ConosleHelper::m_LineSize = 1;

Sizefloat4 ConosleHelper::GetSize() 
{
	return m_Size;
}

GEVector ConosleHelper::GetCenter() 
{
	return { m_Size .hix() + m_LineSize, m_Size.hiy() + m_LineSize };
}


// 012345678
//0&&&&&&&&&
//1&&&&&&&&&
//2&&*****&&
//3&&*****&&
//4&&*****&&
//5&&*****&&
//6&&*****&&
//7&&&&&&&&&
//8&&&&&&&&&
// Line2

bool ConosleHelper::IsOut(Posfloat4 _Pos)
{
	if (m_Size.ix() <= _Pos.ix())
	{
		return true;
	}

	if (m_Size.iy() <= _Pos.iy())
	{
		return true;
	}

	//    5              2
	if (0 > _Pos.ix())
	{
		return true;
	}

	if (0 > _Pos.iy())
	{
		return true;
	}

	return false;
}


void ConosleHelper::Init()
{
	setlocale(LC_ALL, "KOR");

	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);


	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(ConsoleHandle, &cursorInfo);
}

void ConosleHelper::ConsolePosMove(const GEVector& _Pos)
{
	COORD Cur;
	Cur.X = _Pos.ix() * 2;
	Cur.Y = _Pos.iy();
	SetConsoleCursorPosition(ConsoleHandle, Cur);
}

void ConosleHelper::ConsolePosPrint(const GEVector& _Pos, const wchar_t* _Text, bool _IsWallCheck)
{
	if (true == IsOut(_Pos))
	{
		return;
	}

	ConsolePosMove(_Pos);
	wprintf_s(_Text);
}

void ConosleHelper::ConsolePosPrint(const GEVector& _Pos, wchar_t _Text, bool _IsWallCheck)
{
	wchar_t Arr[2] = { _Text, };
	ConsolePosPrint(_Pos, Arr, _IsWallCheck);
}

void ConosleHelper::ConsolePosClear(const GEVector& _Pos)
{
	ConsolePosPrint(_Pos, L"　");
}