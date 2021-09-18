#pragma once
#include <GameEngineMemory.h>
#include <GameEngineString.h>
#include <GameEngineThread.h>
#include <DBRowData.h>

class ItemTableData : public DBRowData
{
public:
    __int64 no                  ;
    __int64 PID                 ;
    char    Name            [45];
    int     Type                ;
    int     InvenOrder          ;
    int     Count               ;
    int     IconResData;

public:
    ItemTableData()
    {
        MemberBind<DB__Int64>(&no);
        MemberBind<DB__Int64>(&PID);
        MemberBind<DBchar<45>>(&Name[0]);
        MemberBind<DBInt>(&Type);
        MemberBind<DBInt>(&InvenOrder);
        MemberBind<DBInt>(&Count);
        MemberBind<DBInt>(&IconResData);
    }
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class ItemTable
{
    // static std::string ArrTableName[10];

private: // Static Var
public: // Static Func
public: // member Var
    static std::string SelectQueryCreate(const std::string& _PID);
    static std::string UpdateQueryCreate(ItemTableData& _Data);
    static std::string InsertQueryCreate(ItemTableData& _Data);

public: // constructer destructer
    ItemTable() {}
    ~ItemTable() {}
};

