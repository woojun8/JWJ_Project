#pragma once
#include <GameEngineMemory.h>
#include <GameEngineString.h>
#include <GameEngineThread.h>
#include <map>
#include <DBRowData.h>


struct AccountTableData : public DBRowData
{
    __int64 PID;
    char Name[45];
    char Password[45];

public:
    AccountTableData()
    {
        // ��������� �Ǹ� �̳༮�� �ɹ��� �� ���ε� �Ǿ� �ִ�.
        MemberBind<DB__Int64>(&PID);
        MemberBind<DBchar<45>>(&Name[0]);
        MemberBind<DBchar<45>>(&Password[0]);
    }
};

// ���̺��� ������ ������ִ� �뵵�� ����ϰڽ��ϴ�.
class AccountTable 
{
private:
public: 
public: 
    // �̰� �̸����� ã�� ������ ������ִ� ����Դϴ�.
    static std::string SelectQueryCreate(GameEngineString _Name);
    static std::string SelectQueryCreateStr(std::string& _Name);

    static std::string InsertQueryCreate(GameEngineString _Name, GameEngineString _Pass);
    //static std::string UpdateQueryCreate(GameEngineString _Name);
    // static std::string DeleteQueryCreate(GameEngineString _PID);

private: 
    AccountTable();
    ~AccountTable();

public: // delete constructer 
    AccountTable(const AccountTable& _Other) = delete;
    AccountTable(const AccountTable&& _Other) = delete;

public: // delete operator
    AccountTable& operator=(const AccountTable& _Other) = delete;
    AccountTable& operator=(const AccountTable&& _Other) = delete;
};

