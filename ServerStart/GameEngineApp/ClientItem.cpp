#include "ClientItem.h"

ClientItem::ClientItem() : ClientActor(*(GameActor*)this)
{
    SetRenderChar(L'��');
}

ClientItem::~ClientItem()
{
}


void ClientItem::CollisionPrev() {
	Render();
}