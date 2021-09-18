#include "ClientPlayer.h"
#include "ConosleHelper.h"
#include <GameEngineInput.h>
#include <GameEngineTime.h>
#include <GameWorld.h>
#include <LogicValue.h>
#include <ClientConnecter.h>
#include <ServerToClient.h>
#include <ServerToClientPacketUpdater.h>
#include <conio.h>


// Static Var
// Static Func

// constructer destructer
ClientPlayer::ClientPlayer() : ClientActor(*(GameActor*)this), m_MoveDelay(LogicValue::PlayerMoveDelay), m_MainPlayer(false), m_AttDelay(LogicValue::PlayerAttDelay)
{
	SetRenderChar(L'▣');

	// 키를 사용할 녀석이 플레이어밖에 없어서
	// 여기로 옮겼습니다.
	GameEngineInput::GetInst().CreateKey(L"LEFT", 'A');
	GameEngineInput::GetInst().CreateKey(L"RIGHT", 'D');
	GameEngineInput::GetInst().CreateKey(L"UP", 'W');
	GameEngineInput::GetInst().CreateKey(L"DOWN", 'S');

	// 나는 2가지가 다 될수 있죠?

	// Player: public GameActor
	// : Player,    ClientActor
	//ClientActor* PtrCO = this;
	//Player* PtrP = this;
}

ClientPlayer::~ClientPlayer() 
{

}
// member Func



void ClientPlayer::Update() 
{
	MoveCheck();

}

void ClientPlayer::UpdatePrev()
{
	// 이전에 내가 움직였다면 나의 예전 위치를 지운다.
}

void ClientPlayer::CollisionPrev()
{
	OldClear();
	Render();
}

void ClientPlayer::MoveCheck() 
{
	if (false == m_MainPlayer)
	{
		return;
	}

	// 실질적으로 완벽한 world의 업데이트에
	// 똑같은 구조로 서버와 클라가 돌아가려면
	// 즉각적인 처리는 사실 지양해야 합니다.
	// 문제가 있을수도 있고 없을수도 있어.
	
	
	// 실제 플레이어만 이 입력이 가능해야죠?
	// 
	// 무조건 이동해 버리면
	// 결국에는 연산량도 늘죠?
	float4 MovePos = GetPos();
	float4 MoveDir = GetPos();

	if (0 != _kbhit())
	{
		int input = _getch();

		switch (input)
		{
		case 'W':
		case 'w':
			MoveDir = float4::UP;
			MoveCheckOn();
			break;
		case 'A':
		case 'a':
			MoveDir = float4::LEFT;
			MoveCheckOn();
			break;
		case 'S':
		case 's':
			MoveDir = float4::DOWN;
			MoveCheckOn();
			break;
		case 'D':
		case 'd':
			MoveDir = float4::RIGHT;
			MoveCheckOn();
			break;
		case 'T':
		case 't':
			MoveDir = float4::UP;
			AttCheckOn();
			break;
		case 'F':
		case 'f':
			MoveDir = float4::LEFT;
			AttCheckOn();
			break;
		case 'G':
		case 'g':
			MoveDir = float4::DOWN;
			AttCheckOn();
			break;
		case 'H':
		case 'h':
			MoveDir = float4::RIGHT;
			AttCheckOn();
			break;
		default:
			break;
		}

		MovePos += MoveDir;


		if (0.0f >= m_MoveDelay && true == IsMoveCheck())
		{
			GameWorld* World = dynamic_cast<GameWorld*>(GetWorld());

				SetClientPos(MovePos);
				ClientPlayerPacket NewMovePacekt;
				NewMovePacekt.m_State = ActorState::Update;
				NewMovePacekt.CurPos = MovePos;
				NewMovePacekt.MoveDir = MoveDir;
				ClientConnecter::GetInst().Send(NewMovePacekt);
				m_MoveDelay = LogicValue::PlayerMoveDelay;
				return;


			//if (nullptr == World->ColCheck((int)LogicValue::CollisionLayer::WALL, MovePos))
			//{
			//}
		}

		if (0.0f >= m_AttDelay && true == IsAttCheck())
		{
			ClientPlayerPacket NewAttPacekt;
			NewAttPacekt.m_State = ActorState::Att;
			NewAttPacekt.CurPos = GetPos();
			NewAttPacekt.MoveDir = MoveDir;
			ClientConnecter::GetInst().Send(NewAttPacekt);
			m_AttDelay = LogicValue::PlayerAttDelay;
			return;
		}

	}


	// 이동이 아니죠?

	// 이게 가능한 이유는
	m_MoveDelay -= GameEngineTime::GetInst().FTime();
	m_AttDelay -= GameEngineTime::GetInst().FTime();


	MoveCheckOff();
	AttCheckOff();
}

void ClientPlayer::ColStay(GameActor* _this, GameActor* _Other) 
{
	int a = 0;
}

