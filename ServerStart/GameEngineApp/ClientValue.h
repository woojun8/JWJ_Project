#pragma once
#include <GEMath.h>
#include <LogicValue.h>
#include <WinSock2.h>


enum class ClientMode
{
    Client,
    ConnectClient,
};


// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class ClientValue
{
public: // Static Var
    static ClientMode mClientMode;
    // ����ȭ �ɰ� �ʹٸ�
    static unsigned __int64 m_AccountCheck;
    static unsigned __int64 m_LoginCheck;
    static DWORD m_GameStartCheck;

private: // Static Var
public: // Static Func
    // static void CurWorldSizeSet(const float4& _CurWorldSize);

private: // member Var
    // static float4 m_CurWorldSize;

public: // constructer destructer
    ClientValue();
    ~ClientValue();

public: // delete constructer 
    ClientValue(const ClientValue& _Other) = delete;
    ClientValue(const ClientValue&& _Other) = delete;

public: // delete operator
    ClientValue& operator=(const ClientValue& _Other) = delete;
    ClientValue& operator=(const ClientValue&& _Other) = delete;

public: // member Func
};

