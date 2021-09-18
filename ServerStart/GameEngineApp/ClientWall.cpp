#include "ClientWall.h"

// Static Var
// Static Func

// constructer destructer
ClientWall::ClientWall() : ClientActor(*(GameActor*)this)
{
	SetRenderChar(L'бс');
}

ClientWall::~ClientWall() 
{

}
// member Func

void ClientWall::CollisionPrev() 
{
	if (true == IsMove())
	{
		Render();
	}
}