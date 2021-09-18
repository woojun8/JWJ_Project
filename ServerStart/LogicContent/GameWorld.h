#pragma once
#include <World.h>
#include <GEMath.h>
#include "WorldDataParser.h"
#include <map>
#include <set>
#include "GameActor.h"

// X0Y0 X1Y0 X2Y0
// X0Y1 X1Y1 X2Y1
// X0Y2 X1Y2 X2Y2

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class WorldManager;
class GameActor;
class GameWorld : public World
{
    friend GameActor;

private: // Static Var
public: // Static Func
private: // member Var
    Posfloat4 m_Pos;
    Sizefloat4 m_Size;


private:
    // �̳༮�� � �׷��� KD�� ����Ұų� ���ų�.
    std::set<int> m_IsKDTree;

    std::map<int, std::list<GameActor*>> m_ColMap;
    std::map<int, std::set<int>> m_ColLink;

public:
    void SetKDTree(int _Test);
    void ColVectorInit(int _Order);
    void ColLink(int _Left, int _Right);

private:
    void PushColObject(GameActor* _GameActor);

public:
    void CreatePotal(const PotalData& _PotalData);

public:
    void SetSize(const Sizefloat4& _Size);

    Sizefloat4 GetSize()
    {
        return m_Size;
    }

    // ������ Ŭ���̾�Ʈ�� �˾Ƽ� ó����
    // �̰� �����ؼ�

protected:
    virtual void CreateWallPos(const float4& _Pos, const float4& _Size) {}
    virtual void CreatePotalPos(const PotalData& _PotalData) {}

    // virtual �� �ְ��./


public: // constructer destructer
    GameWorld();
    virtual ~GameWorld();

public: // delete constructer 
    GameWorld(const GameWorld& _Other) = delete;
    GameWorld(const GameWorld&& _Other) = delete;

public: // delete operator
    GameWorld& operator=(const GameWorld& _Other) = delete;
    GameWorld& operator=(const GameWorld&& _Other) = delete;

public: // member Func
    void ActorStart(Actor* _Actor) override;
    void WorldStart() override;
    void Release() override;

    void CollisionPrev() override;
    void Collision() override;


    void KDColCheck(std::list<GameActor*>& _KDGroup, std::list<GameActor*>& _OtherGroup);

    void ColCheck(std::list<GameActor*>& _LeftGroup, std::list<GameActor*>& _RightGroup);
    GameActor* CheckCollison(GameActor* _Col, COLTYPE _Type, float4 _Scale, float4 _Move, int _Order);
};

