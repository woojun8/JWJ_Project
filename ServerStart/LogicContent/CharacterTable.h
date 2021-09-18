#pragma once
#include <GameEngineMemory.h>
#include <GameEngineString.h>
#include <GameEngineThread.h>
#include <map>
#include <DBRowData.h>


class CharacterTableData : public DBRowData
{
public:
    __int64 no              ;  // 0
    __int64 PID             ;  // 1
    char    Name        [45];  // 2 
    char    EndIndex    [45];  // 3
    int     LastX           ;  // 4
    int     LastY           ;  // 5 
    int     ATT             ;  // 6
    int     HP              ;  // 7
    int     MAXHP           ;  // 8
    int     Score           ;  // 8

public:
    CharacterTableData()
    {
        MemberBind<DB__Int64>(&no);
        MemberBind<DB__Int64>(&PID);
        MemberBind<DBchar<45>>(&Name[0]);
        MemberBind<DBchar<45>>(&EndIndex[0]);
        MemberBind<DBInt>(&LastX);
        MemberBind<DBInt>(&LastY);
        MemberBind<DBInt>(&ATT);
        MemberBind<DBInt>(&HP);
        MemberBind<DBInt>(&MAXHP);
        MemberBind<DBInt>(&Score);
    }
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class CharacterTable
{
private: // Static Var
public: // Static Func
public: // member Var
    static std::string SelectQueryCreate(const std::string& _PID);
    static std::string InsertQueryCreate(CharacterTableData& _Data);
    static std::string UpdateQueryCreate(CharacterTableData& _Data);

public: // constructer destructer
    CharacterTable() {}
    ~CharacterTable() {}
};

