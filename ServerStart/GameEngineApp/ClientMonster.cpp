#include "ClientMonster.h"

// Static Var
// Static Func

// constructer destructer
ClientMonster::ClientMonster() : ClientActor(*(GameActor*)this)
{
    SetRenderChar(L'��');
}

ClientMonster::~ClientMonster() 
{

}
// member Func

void ClientMonster::CollisionPrev() 
{
    OldClear();
    Render();

}