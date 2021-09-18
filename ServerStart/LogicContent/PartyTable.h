#pragma once
#include <GameEngineMemory.h>
#include <GameEngineString.h>
#include <GameEngineThread.h>
#include <map>
#include <DBRowData.h>


class PartyTableData : public DBRowData
{
public:
    __int64     no;
    __int64     ID1;
    char        Name1[45];
    __int64     Connect1;
    __int64     ID2;
    char        Name2[45];
    __int64     Connect2;
    __int64     ID3;
    char        Name3[45];
    __int64     Connect3;

public:
    PartyTableData()
    {
        MemberBind<DB__Int64>(&no);
        MemberBind<DB__Int64>(&ID1);
        MemberBind<DBchar<45>>(&Name1[0]);
        MemberBind<DB__Int64>(&Connect1);
        MemberBind<DB__Int64>(&ID2);
        MemberBind<DBchar<45>>(&Name2[0]);
        MemberBind<DB__Int64>(&Connect2);
        MemberBind<DB__Int64>(&ID3);
        MemberBind<DBchar<45>>(&Name3[0]);
        MemberBind<DB__Int64>(&Connect3);
    }
};

class PartyTable
{
private:
public:
public:
    static std::string SelectQuery(_int64 _ID);
    static std::string SelectQueryCreate(__int64 _ID);
    //static std::string SelectQueryCreate(__int64 _ID, __int64 _FID);
    static std::string InsertQueryCreate(__int64 _ID1, GameEngineString& _Name1, __int64 _Connect1, __int64 _ID2, GameEngineString& _Name2, __int64 _Connect2);
    static std::string UpdateQueryCreate(PartyTableData& _PartyData);

private:
    PartyTable();
    ~PartyTable();

public: // delete constructer 
    PartyTable(const PartyTable& _Other) = delete;
    PartyTable(const PartyTable&& _Other) = delete;

public: // delete operator
    PartyTable& operator=(const PartyTable& _Other) = delete;
    PartyTable& operator=(const PartyTable&& _Other) = delete;
};


