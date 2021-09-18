#include "ClientItem.h"

ClientItem::ClientItem() : ClientActor(*(GameActor*)this)
{
    SetRenderChar(L'¢½');
}

ClientItem::~ClientItem()
{
}


void ClientItem::CollisionPrev() {
	Render();
}