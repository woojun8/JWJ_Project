#include "Wall.h"
#include "LogicValue.h"

// Static Var
// Static Func

// constructer destructer
Wall::Wall() 
{
	// �����ڿ����� ���ټ��� �����.
	// SetColOrder((int)CollisionLayer::WALL);
}

Wall::~Wall() 
{

}
// member Func

void Wall::Start() 
{
	SetColOrder((int)LogicValue::CollisionLayer::WALL, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
}