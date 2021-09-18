#include "ServerPlayer.h"
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameWorld.h>
#include <LogicValue.h>
#include "LogicThread.h"
#include "WorldMsgFunc.h"
#include "ServerPotal.h"
#include "ServerItem.h"
#include "ServerBullet.h"
#include "ServerExBullet.h"
#include "ServerAttCol.h"
#include <iostream>
#include <LogManager.h>


// Static Var
// Static Func

// constructer destructer
ServerPlayer::ServerPlayer() : ServerActor(*(GameActor*)this), m_MoveDelay(LogicValue::PlayerMoveDelay)
{
}

ServerPlayer::~ServerPlayer() 
{

}
// member Func



void ServerPlayer::Update(float _DeltaTime)
{
	if (true == m_UpdateData.empty())
	{
		return;
	}

	ActorUpdateData& Data = m_UpdateData.front();
	PlayerUpdateDataPacket ActorPacket; // ���� �˷��ִ� ��Ŷ

	ActorPacket.UpdateID = reinterpret_cast<__int64>(this);
	ActorPacket.m_State = ActorState::Update;

	// �Ȱ��� ��� �÷��̾�� ���ϴ�.
	if (0 != Data.CreateUpdateID.size() && 1 == Data.SubType)
	{
		LogManager::Inst().PushLog("Bullet Fire");

		std::shared_ptr<ServerBullet> NewBullet = GetWorld()->CreateActor<ServerBullet>((int)LogicValue::CollisionLayer::PLAYERBULLET);
		ActorPacket.m_State = ActorState::Att;
		ActorPacket.m_Data = Data;
		ActorPacket.m_Data.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewBullet.get()));
		ActorPacket.UpdateID = reinterpret_cast<__int64>(GetConnecter()->GetPlayer());
		std::list<std::shared_ptr<Actor>>& GetActor = GetWorld()->GetActorList(2);
		NewBullet->BulletSetting(8000.0f, Data.Dir, 5.0f, this);
		NewBullet->SetPos(GetPos() + Data.Dir * 50.0f);
	}
	else if (0 != Data.CreateUpdateID.size() && 3 == Data.SubType)
	{
		LogManager::Inst().PushLog("3Bullet Fire");

		float4 ArrBulletDir[3] = { Data.Dir , Data.Dir + Data.Right, Data.Dir + -Data.Right };
		ActorPacket.m_State = ActorState::Att;
		ActorPacket.m_Data = Data;
		ActorPacket.m_Data.CreateUpdateID.clear();
		ActorPacket.UpdateID = reinterpret_cast<__int64>(GetConnecter()->GetPlayer());

		// ActorPacket.m_Data.CreateUpdateID.push_back(32131232);

		for (size_t i = 0; i < 3; i++)
		{
			ArrBulletDir[i].Normalize();
			std::shared_ptr<ServerBullet> NewBullet = GetWorld()->CreateActor<ServerBullet>((int)LogicValue::CollisionLayer::PLAYERBULLET);
			ActorPacket.m_Data.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewBullet.get()));
			NewBullet->BulletSetting(8000.0f, ArrBulletDir[i], 5.0f, this);
			NewBullet->SetPos(GetPos() + ArrBulletDir[i] * 50.0f);
		}
	}
	else if(0 != Data.CreateUpdateID.size() && 2 == Data.SubType)
	{
		LogManager::Inst().PushLog("ExBullet Fire");

		std::shared_ptr<ServerExBullet> NewBullet = GetWorld()->CreateActor<ServerExBullet>((int)LogicValue::CollisionLayer::PLAYEREXBULLET);

		// �̶� �Ѿ��� ��������� �ϴ���....
		ActorPacket.m_State = ActorState::Att;
		ActorPacket.m_Data = Data;
		ActorPacket.m_Data.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewBullet.get()));
		ActorPacket.UpdateID = reinterpret_cast<__int64>(GetConnecter()->GetPlayer());
		std::list<std::shared_ptr<Actor>>& GetActor = GetWorld()->GetActorList(2);
		NewBullet->BulletSetting(3000.0f, Data.Dir, 5.0f, this);
		NewBullet->SetPos(GetPos() + Data.Dir * 50.0f);
		NewBullet->SetColOff();
	}
	else if (0 != Data.CreateUpdateID.size() && 4 == Data.SubType)
	{
		LogManager::Inst().PushLog("AttCol");

		std::shared_ptr<ServerAttCol> NewAttCol = GetWorld()->CreateActor<ServerAttCol>((int)LogicValue::CollisionLayer::PLAYERATTACK);
		ActorPacket.m_State = ActorState::Att;
		ActorPacket.m_Data = Data;
		ActorPacket.m_Data.CreateUpdateID.push_back(reinterpret_cast<__int64>(NewAttCol.get()));
		ActorPacket.UpdateID = reinterpret_cast<__int64>(GetConnecter()->GetPlayer());
		std::list<std::shared_ptr<Actor>>& GetActor = GetWorld()->GetActorList(2);		
		NewAttCol->SetPos(ActorPacket.m_Data.AttPos);
	}

	if (Data.Rot != float4::ZERO)
	{
		SetAddRotX(Data.Rot.x);
	}

	if (Data.Move != float4::ZERO)
	{
		SetMovePos(Data.Move);
	}

	std::list<std::shared_ptr<Actor>>& GetActor = GetWorld()->GetActorList(2);

	// ����� ��ε� ĳ��Ʈ
	for (auto& _Actor : GetActor)
	{
		if (_Actor.get() == this)
		{
			continue;
		}

		std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
		Ptr->GetConnecter()->Send(ActorPacket);
	}

	m_UpdateData.pop();

	// MoveCheck();

}

void ServerPlayer::UpdatePrev(float _DeltaTime)
{
	// ������ ���� �������ٸ� ���� ���� ��ġ�� �����.
}

void ServerPlayer::CollisionPrev()
{
}

void ServerPlayer::MoveCheck() 
{
}

void ServerPlayer::ColStay(GameActor* _this, GameActor* _Other) 
{
	if ((int)LogicValue::CollisionLayer::ITEM == _Other->GetColOrder())
	{
		// 
		ServerItem* GetItem = dynamic_cast<ServerItem*>(_Other);

		// �����ۿ� �ڽ��� ���� ������ �˷��ְ� 
		GetItem->EventPlayer = reinterpret_cast<__int64>(this);
		Connecter->PushItemData(GetItem->Data);
		// ���������� ���ΰ̴ϴ�.
		_Other->Death();
	}
	else if ((int)LogicValue::CollisionLayer::POTAL == _Other->GetColOrder())
	{
		ServerPotal* Potal = dynamic_cast<ServerPotal*>(_Other);
		PotalData Data = Potal->GetWorldMoveData();
		 
		std::string Name = std::to_string(Data.Index.ix());
		Name += ',';
		Name += std::to_string(Data.Index.iy());

		std::shared_ptr<World> FindWorld = LogicThread::GetWorldManager().FindWorld(Name);
		WorldMoveOn(Name);
	}
	else if ((int)LogicValue::CollisionLayer::PLAYERBULLET == _Other->GetColOrder())
	{
		ServerBullet* BulletPtr = dynamic_cast<ServerBullet*>(_Other);

		if (nullptr != BulletPtr
			&& this != BulletPtr->Master())
		{
			std::cout << "Player Die" << std::endl;
		}

	}
}

void ServerPlayer::DeathTask() 
{
	if (nullptr == GetWorld())
	{
		return;
	}

	// ���͵��� �ڽ��� ���带 ���� �޾Ҵµ�.
	GetWorld()->MsgInsert(&WorldMsgFunc::PlayerDeath, reinterpret_cast<__int64>(this));
}

void ServerPlayer::WorldPrevMoveTask()
{
	// ����� ���� �������� ������ �ǰ���?
	ClientPlayerPacket Packet;
	Packet.m_State = ActorState::WorldMove;
	GetWorld()->MsgInsert(&WorldMsgFunc::PlayerUpdate, GetConnecter(), Packet);
}

void ServerPlayer::WorldNextMoveTask()
{
	// World* Ptr = GetWorld();
	GetWorld()->MsgInsert(&WorldMsgFunc::WorldMoveOk, GetConnecter());
	GetWorld()->MsgInsert(&WorldMsgFunc::WaitPlayerInWorld, GetConnecter());
	WorldMoveOff();
}