#pragma once
#include <WorldDataParser.h>
#include <Potal.h>
#include "ClientActor.h"

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class ClientPotal : public Potal, public ClientActor
{
private: // Static Var
public: // Static Func
private: // member Var
    PotalData m_Data;

public:
    void SetPotalData(const PotalData& _Data);

public: // constructer destructer
    ClientPotal();
    ~ClientPotal();

public: // delete constructer 
    ClientPotal(const ClientPotal& _Other) = delete;
    ClientPotal(const ClientPotal&& _Other) = delete;

public: // delete operator
    ClientPotal& operator=(const ClientPotal& _Other) = delete;
    ClientPotal& operator=(const ClientPotal&& _Other) = delete;

public: // member Func
    void CollisionPrev() override;
};

