#include "GameActor.h"
#include "GameWorld.h"

// Static Var
// Static Func

// constructer destructer
GameActor::GameActor() : m_IsMove(false), m_ParentWorld(nullptr), m_Type(COLTYPE::CT_SPHERE), ColOnOff(true)
{

}

GameActor::~GameActor() 
{

}
// member Func

void GameActor::SetColOrder(int _ColOrder, float4 _Scale, COLTYPE _ColType)
{
    m_ColOrder = _ColOrder;
    m_Scale = _Scale;
    m_Type = _ColType;
    Data.m_OBB.Extents = m_Scale.Dxfloat3;
    Data.SettingChangeScale();
    m_ParentWorld = dynamic_cast<GameWorld*>(GetWorld());
    m_ParentWorld->PushColObject(this);
}

void GameActor::Setting()
{
    Data.m_OBB.Center = m_Pos.Dxfloat3;
    Data.SettingChangeSpace();
}