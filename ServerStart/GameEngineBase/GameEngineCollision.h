#pragma once
#include "GEMath.h"

enum COLTYPE
{
    CT_POINT, // ��
    CT_SPHERE, // ��
    CT_AABB, // ȸ������ �ʴ� �簢��
    CT_OBB, // ȸ���ϴ� �簢��
    CT_MAX // ȸ���ϴ� �簢��
};

// �̱���ü �ϳ��� �־
// ������ �浹�� �� üũ�Ҽ� �ִٴ� �̴ϴ�.
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
    // �������� ���ϴ� �̴ϴ�.
    GameEngineColData();
};

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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