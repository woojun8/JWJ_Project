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
	// �ܺο� ������ ġ�� ����� �̳༮�� ���Ӱ� �����ְ� �Ǿ���� �Ŵ� ����������
	static void Init();

	// �Լ��� ���鶧��
	// ���� ��ɵ��� �Լ��� �����
	// �װ͵��� ȥ���ؼ� ū�Լ��� �����
	static void ConsolePosMove(const GEVector& _Pos);
	static void ConsolePosPrint(const GEVector& _Pos, wchar_t _Text, bool _IsWallCheck = true);
	static void ConsolePosPrint(const GEVector& _Pos, const wchar_t* _Text, bool _IsWallCheck = true);
	static void ConsolePosClear(const GEVector& _Pos);

private:
	ConosleHelper();
	virtual ~ConosleHelper() = 0;
};