#include "AccountTable.h"

// Static Var
// Static Func

// constructer destructer
AccountTable::AccountTable() 
{

}

AccountTable::~AccountTable() 
{

}

std::string AccountTable::SelectQueryCreate(GameEngineString _Name) 
{
    std::string Name = _Name.GetConvertMultiByteString();
    std::string NewQuery = "SELECT PID, Name, Password FROM server11.accounttable WHERE Name = '";
    NewQuery += Name + "'";
    return NewQuery;
}

std::string AccountTable::SelectQueryCreateStr(std::string& _Name)
{
    std::string NewQuery = "SELECT PID, Name, Password FROM server11.accounttable WHERE Name = '";
    NewQuery += _Name + "'";
    return NewQuery;
}

std::string AccountTable::InsertQueryCreate(GameEngineString _Name, GameEngineString _Pass)
{
    // INSERT INTO `server11`.`accounttable` (`Name`, `Password`) VALUES('j', 'j');


    std::string Name = _Name.GetConvertMultiByteString();
    std::string Password = _Name.GetConvertMultiByteString();

    std::string NewQuery = "INSERT INTO server11.accounttable (Name, Password) VALUES('";
    NewQuery += Name + "', '";
    NewQuery += Password + "')";
    return NewQuery;
}