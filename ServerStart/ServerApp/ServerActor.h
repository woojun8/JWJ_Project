#pragma once
#include <GEMath.h>

//     A
// B:A   C:A
// F:B   U:C
//    T:F, U
// 다이아몬드 상속.
// 이것만 피하면 됩니다.
// 누가 이렇게 쓰는데?
// 거의 프로그래머 실격 인증하는건데.
// 설계를 이렇게 한다는 것은
// 그냥 뭐 말도 안되는 
// 여러분들이 그런 설계나 혹은 상속사용을 하는 경우가 생기니까.

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class GameActor;
class ServerActor
{
private: // Static Var
public: // Static Func
private: // member Var
    // 단순한 클래스(이녀석은 상속을 절대 받지 않습니다.)를 만들어서 다중상속을 시켜요
    // 인터페이스(함수나 기능)만 제공하는 용도로 사용한다.
    // 모호성은 기존에 판단합니다.
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

