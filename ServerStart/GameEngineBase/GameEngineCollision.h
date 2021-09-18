#pragma once
#include "GEMath.h"

enum COLTYPE
{
    CT_POINT, // 점
    CT_SPHERE, // 구
    CT_AABB, // 회전하지 않는 사각형
    CT_OBB, // 회전하는 사각형
    CT_MAX // 회전하는 사각형
};

// 이구조체 하나로 있어도
// 세가지 충돌을 다 체크할수 있다는 겁니다.
class GameEngineColData 
{
public:
    union 
    {
        DirectX::BoundingSphere m_Sphere; // SPHERE
        DirectX::BoundingBox m_AABB; // AABB
        DirectX::BoundingOrientedBox m_OBB; // OBB
    };

public:
    void SettingChangeRot();
    void SettingChangeScale();
    void SettingChangePos();

    void SettingChangeSpace();

    void SetScale(float4 _Scale);

public:
    // 반지름을 말하는 겁니다.
    GameEngineColData();
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class GameEngineCollision
{
public:
    static bool (__stdcall *COLFUNC[(int)COLTYPE::CT_MAX][(int)COLTYPE::CT_MAX])(const GameEngineColData& _Left, const GameEngineColData& _Right);

public:
    static void Init();

public:
    static bool SPHEREToPOINT                   (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool SPHEREToOBB                     (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool SPHEREToAABB                    (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool SPHEREToSPHERE                  (const GameEngineColData& _Left, const GameEngineColData& _Right);

    static bool AABBToPOINT                   (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool AABBToOBB                     (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool AABBToAABB                    (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool AABBToSPHERE                  (const GameEngineColData& _Left, const GameEngineColData& _Right);

    static bool OBBToPOINT                   (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool OBBToOBB                     (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool OBBToAABB                    (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool OBBToSPHERE                  (const GameEngineColData& _Left, const GameEngineColData& _Right);

    static bool POINTToPOINT                   (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool POINTToOBB                     (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool POINTToAABB                    (const GameEngineColData& _Left, const GameEngineColData& _Right);
    static bool POINTToSPHERE                  (const GameEngineColData& _Left, const GameEngineColData& _Right);

};