#include "Player.h"
#include "LogicValue.h"

// Static Var
// Static Func

// constructer destructer
Player::Player() : m_MoveCheck(false)
{
	// ���尡 ������ �ȵǾ��־ �Ʒ��� �Լ��� �θ����� ����.
	// SetColOrder((int)CollisionLayer::PLAYER);
}

Player::~Player() 
{

}
// member Func

void Player::Start()
{
	// SetColOrder((int)LogicValue::CollisionLayer::ITEM, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
	SetColOrder((int)LogicValue::CollisionLayer::PLAYER, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
}

