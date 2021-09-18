#include "Potal.h"
#include "LogicValue.h"

// Static Var
// Static Func

// constructer destructer
Potal::Potal() 
{
	// SetColOrder((int)CollisionLayer::POTAL);
}

Potal::~Potal() 
{

}
// member Func

void Potal::Start() 
{
	SetColOrder((int)LogicValue::CollisionLayer::POTAL, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE);
}