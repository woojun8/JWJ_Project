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
        // 만들어지게 되면 이녀석은 맴버가 다 바인드 되어 있다.
        MemberBind<DB__Int64>(&PID);
        MemberBind<DBchar<45>>(&Name[0]);
        MemberBind<DBchar<45>>(&Password[0]);
    }
};

// 테이블은 쿼리를 만들어주는 용도로 사용하겠습니다.
class AccountTable 
{
private:
public: 
public: 
    // 이건 이름으로 찾는 쿼리를 만들어주는 기능입니다.
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

