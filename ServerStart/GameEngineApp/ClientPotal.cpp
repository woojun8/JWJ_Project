#include "ClientPotal.h"

// Static Var
// Static Func

// constructer destructer
ClientPotal::ClientPotal() : ClientActor(*(GameActor*)this)
{
	SetRenderChar(L'¡Ý');
}

ClientPotal::~ClientPotal() 
{

}
// member Func

void ClientPotal::CollisionPrev() {
	Render();
}

void ClientPotal::SetPotalData(const PotalData& _Data)
{
	m_Data = _Data;

	SetPos(m_Data.Pos);
}