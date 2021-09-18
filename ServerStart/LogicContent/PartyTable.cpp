#include "PartyTable.h"

PartyTable::PartyTable()
{

}

PartyTable::~PartyTable()
{

}

std::string PartyTable::SelectQuery(__int64 _ID)
{
    std::string Name = std::to_string(_ID);
    std::string NewQuery = "SELECT no, ID1, Name1, Connect1, ID2, Name2, Connect2, ID3, Name3, Connect3 FROM server11.partytable WHERE ID1 = '";
    NewQuery += Name + "' or ID2 = '";
    NewQuery += Name + "' or ID3 = '";
    NewQuery += Name + "'";
    return NewQuery;
}

std::string PartyTable::SelectQueryCreate(__int64 _ID)
{
    std::string Name = std::to_string(_ID);
    std::string NewQuery = "SELECT no, ID1, Name1, Connect1, ID2, Name2, Connect2 FROM server11.partytable WHERE ID1 = '";
    NewQuery += Name + "'";
    return NewQuery;
}

//std::string PartyTable::SelectQueryCreate(__int64 _ID, __int64 _FID)
//{
//    std::string Name = std::to_string(_ID);
//    std::string NewQuery = "SELECT no, PID, FID FROM server11.partytable WHERE PID = '";
//    NewQuery += std::to_string(_ID) + "' AND FID = '";
//    NewQuery += std::to_string(_FID) + "'";
//    return NewQuery;
//}

std::string PartyTable::InsertQueryCreate(__int64 _ID1, GameEngineString& _Name1, __int64 _Connect1, __int64 _ID2, GameEngineString& _Name2, __int64 _Connect2)
{
    std::string ID1 = std::to_string(_ID1);
    std::string Name1 = _Name1.GetConvertMultiByteString();
    std::string Connect1 = std::to_string(_Connect1);

    std::string ID2 = std::to_string(_ID2);
    std::string Name2 = _Name2.GetConvertMultiByteString();
    std::string Connect2 = std::to_string(_Connect2);


    std::string NewQuery = "INSERT INTO server11.partytable (ID1, Name1, Connect1, ID2, Name2, Connect2) VALUES('";
    NewQuery += ID1 + "', '";
    NewQuery += Name1 + "', '";
    NewQuery += Connect1 + "', '";
    NewQuery += ID2 + "', '";
    NewQuery += Name2 + "', '";
    NewQuery += Connect2 + "')";
    return NewQuery;
}

std::string PartyTable::UpdateQueryCreate(PartyTableData& _PartyData)
{
    std::vector<DBVar*>& Data = _PartyData.GetDBVarData();

    std::string NewQuery = "UPDATE server11.partytable SET ID1 = '"
        + Data[1]->ToString() + "', Name1 = '"
        + Data[2]->ToString() + "', Connect1 = '"
        + Data[3]->ToString() + "', ID2 = '"
        + Data[4]->ToString() + "', Name2 = '"
        + Data[5]->ToString() + "', Connect2 = '"
        + Data[6]->ToString() + "', ID3 = '"
        + Data[7]->ToString() + "', Name3 = '"
        + Data[8]->ToString() + "', Connect3 = '"
        + Data[9]->ToString() + "' WHERE(no = '"
        + Data[0]->ToString() + "');";

    return NewQuery;
}