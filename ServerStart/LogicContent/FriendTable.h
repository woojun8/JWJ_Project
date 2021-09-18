#pragma once
#include <GameEngineMemory.h>
#include <GameEngineString.h>
#include <GameEngineThread.h>
#include <map>
#include <DBRowData.h>


class FriendTableData : public DBRowData
{
public:
    __int64 no;
    __int64 PID;
    __int64 FID;

public:
    FriendTableData()
    {
        // 만들어지게 되면 이녀석은 맴버가 다 바인드 되어 있다.
        MemberBind<DB__Int64>(&no);
        MemberBind<DB__Int64>(&PID);
        MemberBind<DB__Int64>(&FID);
    }
};

// 테이블은 쿼리를 만들어주는 용도로 사용하겠습니다.
class FriendTable
{
private:
public:
public:
    // 이건 이름으로 찾는 쿼리를 만들어주는 기능입니다.
    static std::string SelectQueryCreate(__int64 _ID);
    static std::string SelectQueryCreate(__int64 _ID, __int64 _FID);
    static std::string InsertQueryCreate(__int64 _ID, std::string& _Name, __int64 _FID, std::string& _FName);
    //static std::string UpdateQueryCreate(GameEngineString _Name);
    // static std::string DeleteQueryCreate(GameEngineString _PID);

private:
    FriendTable();
    ~FriendTable();

public: // delete constructer 
    FriendTable(const FriendTable& _Other) = delete;
    FriendTable(const FriendTable&& _Other) = delete;

public: // delete operator
    FriendTable& operator=(const FriendTable& _Other) = delete;
    FriendTable& operator=(const FriendTable&& _Other) = delete;
};


