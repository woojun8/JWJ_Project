#pragma once
#include <GEMath.h>

//     A
// B:A   C:A
// F:B   U:C
//    T:F, U
// ���̾Ƹ�� ���.
// �̰͸� ���ϸ� �˴ϴ�.
// ���� �̷��� ���µ�?
// ���� ���α׷��� �ǰ� �����ϴ°ǵ�.
// ���踦 �̷��� �Ѵٴ� ����
// �׳� �� ���� �ȵǴ� 
// �����е��� �׷� ���質 Ȥ�� ��ӻ���� �ϴ� ��찡 ����ϱ�.

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class GameActor;
class ServerActor
{
private: // Static Var
public: // Static Func
private: // member Var
    // �ܼ��� Ŭ����(�̳༮�� ����� ���� ���� �ʽ��ϴ�.)�� ���� ���߻���� ���ѿ�
    // �������̽�(�Լ��� ���)�� �����ϴ� �뵵�� ����Ѵ�.
    // ��ȣ���� ������ �Ǵ��մϴ�.
    GameActor& m_GameActor;

protected: // constructer destructer
    ServerActor(GameActor& _GameActor);
    virtual ~ServerActor() = 0;

public: // delete constructer 
    ServerActor(const ServerActor& _Other) = delete;
    ServerActor(const ServerActor&& _Other) = delete;

public: // delete operator
    ServerActor& operator=(const ServerActor& _Other) = delete;
    ServerActor& operator=(const ServerActor&& _Other) = delete;

};

