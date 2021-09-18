#include "GameEngineCollision.h"


GameEngineColData::GameEngineColData() : m_OBB({ 0,0,0 }, { 0.5,0.5,0.5 }, { 0,0,0,1 }) 
{
}

void GameEngineColData::SetScale(float4 _Scale) 
{
    _Scale *= 0.5f;
    m_OBB.Extents = _Scale.Dxfloat3;
    SettingChangeScale();
}

void GameEngineColData::SettingChangeRot() 
{
    //m_OBB.Center.z = Data.Center.x;
    //m_OBB.Center.x = Data.Center.y;
    //m_OBB.Center.y = Data.Center.z;
}

void GameEngineColData::SettingChangeScale() 
{
    DirectX::XMFLOAT3 Scale = m_OBB.Extents;

    m_OBB.Extents.z = Scale.x;
    m_OBB.Extents.x = Scale.y;
    m_OBB.Extents.y = Scale.z;
}

void GameEngineColData::SettingChangePos() 
{
    DirectX::XMFLOAT3 Pos = m_OBB.Center;
    m_OBB.Center.z = Pos.x;
    m_OBB.Center.x = Pos.y;
    m_OBB.Center.y = Pos.z;
}

void GameEngineColData::SettingChangeSpace() 
{
    SettingChangePos();
}

bool (__stdcall * GameEngineCollision::COLFUNC[(int)COLTYPE::CT_MAX][(int)COLTYPE::CT_MAX])(const GameEngineColData& _Left, const GameEngineColData& _Right) = {nullptr};

void GameEngineCollision::Init() 
{
    COLFUNC[(int)COLTYPE::CT_SPHERE][(int)COLTYPE::CT_POINT ] =  &GameEngineCollision::SPHEREToPOINT     ;
    COLFUNC[(int)COLTYPE::CT_SPHERE][(int)COLTYPE::CT_OBB   ] =  &GameEngineCollision::SPHEREToOBB       ;
    COLFUNC[(int)COLTYPE::CT_SPHERE][(int)COLTYPE::CT_AABB  ] =  &GameEngineCollision::SPHEREToAABB      ;
    COLFUNC[(int)COLTYPE::CT_SPHERE][(int)COLTYPE::CT_SPHERE ] = &GameEngineCollision::SPHEREToSPHERE    ;
    COLFUNC[(int)COLTYPE::CT_AABB][(int)COLTYPE::CT_POINT ]    = &GameEngineCollision::AABBToPOINT       ;
    COLFUNC[(int)COLTYPE::CT_AABB][(int)COLTYPE::CT_OBB   ]    = &GameEngineCollision::AABBToOBB         ;
    COLFUNC[(int)COLTYPE::CT_AABB][(int)COLTYPE::CT_AABB  ]    = &GameEngineCollision::AABBToAABB        ;
    COLFUNC[(int)COLTYPE::CT_AABB][(int)COLTYPE::CT_SPHERE]    = &GameEngineCollision::AABBToSPHERE      ;
    COLFUNC[(int)COLTYPE::CT_OBB][(int)COLTYPE::CT_POINT ]     = &GameEngineCollision::OBBToPOINT        ;
    COLFUNC[(int)COLTYPE::CT_OBB][(int)COLTYPE::CT_OBB   ]     = &GameEngineCollision::OBBToOBB          ;
    COLFUNC[(int)COLTYPE::CT_OBB][(int)COLTYPE::CT_AABB  ]     = &GameEngineCollision::OBBToAABB         ;
    COLFUNC[(int)COLTYPE::CT_OBB][(int)COLTYPE::CT_SPHERE]     = &GameEngineCollision::OBBToSPHERE       ;
    COLFUNC[(int)COLTYPE::CT_POINT][(int)COLTYPE::CT_POINT ]   = &GameEngineCollision::POINTToPOINT      ;
    COLFUNC[(int)COLTYPE::CT_POINT][(int)COLTYPE::CT_OBB   ]   = &GameEngineCollision::POINTToOBB        ;
    COLFUNC[(int)COLTYPE::CT_POINT][(int)COLTYPE::CT_AABB  ]   = &GameEngineCollision::POINTToAABB       ;
    COLFUNC[(int)COLTYPE::CT_POINT][(int)COLTYPE::CT_SPHERE]   = &GameEngineCollision::POINTToSPHERE     ;
}

bool GameEngineCollision::SPHEREToPOINT(const GameEngineColData& _Left, const GameEngineColData& _Right)
{
    return _Left.m_Sphere.Intersects(_Right.m_Sphere);
}
bool GameEngineCollision::SPHEREToOBB(const GameEngineColData& _Left, const GameEngineColData& _Right)
{
    return _Left.m_Sphere.Intersects(_Right.m_OBB);
}
bool GameEngineCollision::SPHEREToAABB(const GameEngineColData& _Left, const GameEngineColData& _Right)
{
    return _Left.m_Sphere.Intersects(_Right.m_AABB);
}
bool GameEngineCollision::SPHEREToSPHERE(const GameEngineColData& _Left, const GameEngineColData& _Right)
{
    return _Left.m_Sphere.Intersects(_Right.m_Sphere);
}

bool GameEngineCollision::AABBToPOINT(const GameEngineColData& _Left, const GameEngineColData& _Right)
{
    return _Left.m_AABB.Intersects(_Right.m_Sphere);
}
bool GameEngineCollision::AABBToOBB(const GameEngineColData& _Left, const GameEngineColData& _Right)
{
    return _Left.m_AABB.Intersects(_Right.m_OBB);
}
bool GameEngineCollision::AABBToAABB(const GameEngineColData& _Left, const GameEngineColData& _Right)
{
    return _Left.m_AABB.Intersects(_Right.m_Sphere);
}
bool GameEngineCollision::AABBToSPHERE(const GameEngineColData& _Left, const GameEngineColData& _Right)
{
    return _Left.m_AABB.Intersects(_Right.m_Sphere);
}

bool GameEngineCollision::OBBToPOINT(const GameEngineColData& _Left, const GameEngineColData& _Right) {
    return _Left.m_OBB.Intersects(_Right.m_Sphere);
}
bool GameEngineCollision::OBBToOBB(const GameEngineColData& _Left, const GameEngineColData& _Right) {
    return _Left.m_OBB.Intersects(_Right.m_OBB);
}
bool GameEngineCollision::OBBToAABB(const GameEngineColData& _Left, const GameEngineColData& _Right) {
    return _Left.m_OBB.Intersects(_Right.m_AABB);
}
bool GameEngineCollision::OBBToSPHERE(const GameEngineColData& _Left, const GameEngineColData& _Right) {
    return _Left.m_OBB.Intersects(_Right.m_Sphere);
}

bool GameEngineCollision::POINTToPOINT(const GameEngineColData& _Left, const GameEngineColData& _Right) {
    return _Left.m_Sphere.Intersects(_Right.m_Sphere);
}
bool GameEngineCollision::POINTToOBB(const GameEngineColData& _Left, const GameEngineColData& _Right) {
    return _Left.m_Sphere.Intersects(_Right.m_OBB);
}
bool GameEngineCollision::POINTToAABB(const GameEngineColData& _Left, const GameEngineColData& _Right) 
{
    return _Left.m_Sphere.Intersects(_Right.m_AABB);
}
bool GameEngineCollision::POINTToSPHERE(const GameEngineColData& _Left, const GameEngineColData& _Right) 
{
    return _Left.m_Sphere.Intersects(_Right.m_Sphere);
}