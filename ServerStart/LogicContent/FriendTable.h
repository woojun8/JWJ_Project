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
        // ��������� �Ǹ� �̳༮�� �ɹ��� �� ���ε� �Ǿ� �ִ�.
        MemberBind<DB__Int64>(&no);
        MemberBind<DB__Int64>(&PID);
        MemberBind<DB__Int64>(&FID);
    }
};

// ���̺��� ������ ������ִ� �뵵�� ����ϰڽ��ϴ�.
class FriendTable
{
private:
public:
public:
    // �̰� �̸����� ã�� ������ ������ִ� ����Դϴ�.
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


