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
class ClientActor
{
private: // Static Var
public: // Static Func
private: // member Var
    // �ܼ��� Ŭ����(�̳༮�� ����� ���� ���� �ʽ��ϴ�.)�� ���� ���߻���� ���ѿ�
    // �������̽�(�Լ��� ���)�� �����ϴ� �뵵�� ����Ѵ�.
    // ��ȣ���� ������ �Ǵ��մϴ�.
    GameActor& m_GameActor;
    float4  m_OldPos;
    wchar_t m_RenderChar;

public:
    void SetRenderChar(wchar_t _RenderChar)
    {
        m_RenderChar = _RenderChar;
    }
    void PosReset() {}

protected: // constructer destructer
    ClientActor(GameActor& _GameActor);
    virtual ~ClientActor() = 0;

public: // delete constructer 
    ClientActor(const ClientActor& _Other) = delete;
    ClientActor(const ClientActor&& _Other) = delete;

public: // delete operator
    ClientActor& operator=(const ClientActor& _Other) = delete;
    ClientActor& operator=(const ClientActor&& _Other) = delete;

public: // member Func
    void Render();
    void OldClear();
    void CurClear();

    void SetClientMove(float4 _Pos);
    void SetClientPos(float4 _Pos);
};

