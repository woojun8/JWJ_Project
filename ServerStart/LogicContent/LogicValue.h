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
	OK, // 서버 Error
	OverAccount, // 인원수 초과
	IDOverlap, // 아이디 겹침
	ServerError, // 서버 Error
	Wait, // 서버 Error
};

enum class LoginResultType
{
	OK, // 서버 Error
	IDERROR, // ID잘못입력
	PWERROR, // 패스워드 잘못입력
	ServerError, // 서버 Error
	Wait, // 서버 Error
};