#pragma once
#include <GameActor.h>
#include "ServerActor.h"

//분류 1 :
//분류 2 :
//용도 :
//설명 :

class ServerExBullet : public GameActor, public ServerActor
{
private: // static var

public: // static func
	float4 DirVector;
	float UpPower;
	float AccPower;
	float GravityPower;
	float Speed;
	float DeathTime;
	bool IsBoom;
	GameActor* m_Actor;

public:
	GameActor* Master() 
	{
		return m_Actor;
	}

public:
	void BulletSetting
	(
		float _Speed,
		float4 _Dir,
		float _Death,
		GameActor* _Actor
	)
	{
		Speed = _Speed;
		DirVector = _Dir;
		DeathTime = _Death;
		m_Actor = _Actor;
	}

private: // mem var

public: // constructor destructor
	ServerExBullet();
	~ServerExBullet();

public: // delete constructor

	ServerExBullet(const ServerExBullet& _other) = delete;
	ServerExBullet(const ServerExBullet&& _other) = delete;

public: // delete operator
	ServerExBullet& operator=(const ServerExBullet& _other) = delete;
	ServerExBullet& operator=(const ServerExBullet&& _other) = delete;

public: // member Func
	void Start() override;
	void Update(float _DeltaTime) override;
	void ColStay(GameActor* _Left, GameActor* _Right);

};

