#pragma once

class LogicValue
{
public:
	enum class SERVERTASK
	{
		DBRESULT,
		MAX,
	};

	enum class CollisionLayer
	{
		WALL,
		POTAL,
		PLAYER,
		MONSTER,
		PLAYERATTACK,
		PLAYERBULLET,
		PLAYEREXBULLET,
		MONSTERBULLET,
		ITEM,
		MAX,
	};

	static const float PlayerMoveDelay;
	static const float PlayerAttDelay;
	static const int MaxMonsterCount;
	static const float MonsterRegenTime;

private:
	// static std::atomic_int64_t m_GUI;

public:
	//__int64 GetUID()
	//{
	//	__int64 UID = m_GUI.fetch_add(1);
	//	return UID;
	//}



private:
	LogicValue()
	{
	}

	~LogicValue()
	{
	}
};


enum class AccountResultType
{
	OK, // ���� Error
	OverAccount, // �ο��� �ʰ�
	IDOverlap, // ���̵� ��ħ
	ServerError, // ���� Error
	Wait, // ���� Error
};

enum class LoginResultType
{
	OK, // ���� Error
	IDERROR, // ID�߸��Է�
	PWERROR, // �н����� �߸��Է�
	ServerError, // ���� Error
	Wait, // ���� Error
};