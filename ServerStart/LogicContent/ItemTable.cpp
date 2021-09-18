#include "ItemTable.h"

// Static Var
// Static Func

// constructer destructer

std::string ItemTable::SelectQueryCreate(const std::string& _PID)
{
    std::string ID = _PID;
    std::string NewQuery = "SELECT no, PID, Name, Type, InvenOrder, Count, IconResData FROM server11.itemtable WHERE PID = '";
    NewQuery += ID + "'";
    return NewQuery;
}

std::string ItemTable::InsertQueryCreate(ItemTableData& _Data) {

    std::vector<DBVar*>& Data = _Data.GetDBVarData();

    // INSERT INTO `server11`.`itemtable` (`PID`, `Name`, `Type`, `InvenOrder`, `Count`, `IconResData`) VALUES('2', '°©¿Ê', '1', '1', '1', '1');

    //std::string NewQuery = "INSERT INTO server11.itemtable(PID, Name, Type, InvenOrder, Count, IconResData) VALUES('"
    //    + Data[1]->ToString() + "', '"
    //    + Data[2]->ToString() + "', '"
    //    + Data[3]->ToString() + "', '"
    //    + Data[4]->ToString() + "', '"
    //    + Data[5]->ToString() + "', '"
    //    + Data[6]->ToString() + "')";

    GameEngineString Name;

    // ¾Æ¸¶ ¾øÀ»°Å¿¡¿ä.
    Name = GameEngineString::GlobalSetConvertMultiByteString(Data[2]->ToString());
    std::string ConvertName = Name.GetConvertMultiByteString(CP_UTF8);

    std::string NewQuery = "INSERT INTO server11.itemtable(PID, Name, Type, InvenOrder, Count, IconResData) VALUES('"
        + Data[1]->ToString() + "', '"
        + ConvertName.c_str() + "', '"
        + Data[3]->ToString() + "', '"
        + Data[4]->ToString() + "', '"
        + Data[5]->ToString() + "', '"
        + Data[6]->ToString() + "')";

    return NewQuery;
}

std::string ItemTable::UpdateQueryCreate(ItemTableData& _Data) 
{
    std::vector<DBVar*>& Data = _Data.GetDBVarData();

    std::string NewQuery = "UPDATE server11.itemtable SET PID = '"
        + Data[1]->ToString() + "', Name = '"
        + Data[2]->ToString() + "', Type = '"
        + Data[3]->ToString() + "', InvenOrder = '"
        + Data[4]->ToString() + "', Count = '"
        + Data[5]->ToString() + "', IconResData = '"
        + Data[6]->ToString() + "' WHERE(no = '"
        + Data[0]->ToString() + "');";

    return NewQuery;
}