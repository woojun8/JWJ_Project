#include "ServerPotal.h"

// Static Var
// Static Func

// constructer destructer
ServerPotal::ServerPotal() : ServerActor(*(GameActor*)this)
{
}

ServerPotal::~ServerPotal() 
{

}
// member Func

void ServerPotal::CollisionPrev() {
}

void ServerPotal::SetPotalData(const PotalData& _Data)
{
	m_Data = _Data;
	SetPos(m_Data.Pos);
}

PotalUpdateData ServerPotal::GetPotalData(ActorState _State)
{
    PotalUpdateData NewItemData;
    NewItemData.CurPos = GetPos();
    NewItemData.UpdateID = reinterpret_cast<__int64>(this);
    NewItemData.m_State = _State;
    return NewItemData;

}