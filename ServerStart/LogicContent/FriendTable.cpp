#include "FriendTable.h"


// Static Var
// Static Func

// constructer destructer
FriendTable::FriendTable()
{

}

FriendTable::~FriendTable()
{

}

std::string FriendTable::SelectQueryCreate(__int64 _ID)
{
    std::string Name = std::to_string(_ID);
    std::string NewQuery = "SELECT no, PID, FID FROM server11.friendtable WHERE PID = '";
    NewQuery += Name + "'";
    return NewQuery;
}

std::string FriendTable::SelectQueryCreate(__int64 _ID, __int64 _FID)
{
    std::string Name = std::to_string(_ID);
    std::string NewQuery = "SELECT no, PID, FID FROM server11.friendtable WHERE PID = '";
    NewQuery += std::to_string(_ID) + "' AND FID = '";
    NewQuery += std::to_string(_FID) + "'";
    return NewQuery;
}

std::string FriendTable::InsertQueryCreate(__int64 _ID, std::string& _Name, __int64 _FID, std::string& _FName)
{
    // INSERT INTO `server11`.`accounttable` (`Name`, `Password`) VALUES('j', 'j');


    std::string PID = std::to_string(_ID);;
    std::string PName = _Name;

    std::string FID = std::to_string(_FID);
    std::string FName = _FName;

    std::string NewQuery = "INSERT INTO server11.friendtable (PID, PName, FID, FName) VALUES('";
    NewQuery += PID + "', '";
    NewQuery += PName + "', '";
    NewQuery += FID + "', '";
    NewQuery += FName + "')";
    return NewQuery;
}