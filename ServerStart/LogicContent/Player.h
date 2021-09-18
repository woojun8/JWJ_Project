#pragma once
#include "GameActor.h"
#include <queue>

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : ���ӿ��� �÷��̾� ������ �Ѵ�.
class ActorUpdateData;
class Player : public GameActor
{
private: // Static Var
public: // Static Func
private: // member Var
    // �÷��̾ �ڽ��� �����ϴ� ����Ű�� �˰� �־�� �Ѵ�.
    int Hp;
    bool m_MoveCheck;
    bool m_AttCheck;
    // �׾Ƴ��� ���� Queue�Դϴ�.
public:
    bool IsMoveCheck() 
    {
        return m_MoveCheck;
    }

    void MoveCheckOn() 
    {
        m_MoveCheck = true;
    }

    void MoveCheckOff() {
        m_MoveCheck = false;
    }

    bool IsAttCheck()
    {
        return m_AttCheck;
    }

    void AttCheckOn()
    {
        m_AttCheck = true;
    }

    void AttCheckOff() {
        m_AttCheck = false;
    }


public: // constructer destructer
    Player();
    ~Player();

public: // delete constructer 
    Player(const Player& _Other) = delete;
    Player(const Player&& _Other) = delete;

public: // delete operator
    Player& operator=(const Player& _Other) = delete;
    Player& operator=(const Player&& _Other) = delete;

public: // member Func
    virtual void Start() override;
};

