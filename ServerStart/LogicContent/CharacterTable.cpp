#include "CharacterTable.h"


std::string CharacterTable::SelectQueryCreate(const std::string& _PID)
{
    std::string ID = _PID;
    std::string NewQuery = "SELECT no, PID, Name, EndIndex, LastX, LastY, ATT, HP, MAXHP, Score FROM server11.characterdatatable WHERE PID = '";
    NewQuery += ID + "'";
    return NewQuery;
}

std::string CharacterTable::InsertQueryCreate(CharacterTableData& _Data) 
{
    // INSERT INTO server11.characterdatatable (PID, Name, EndIndex, LastX, LastY, ATT, HP, MAXHP) VALUES('2', 'f', '0,0', '5', '5', '100', '100', '100');

    // INSERT INTO server11.characterdatatable(PID, Name, EndIndex, LastX, LastY, ATT, HP, MAXHP) VALUES('2', 'f', '0,0', '5', '5', '100', '100', '100');
    std::string NewQuery = "INSERT INTO server11.characterdatatable(PID, Name, EndIndex, LastX, LastY, ATT, HP, MAXHP, Score) VALUES(";
    std::vector<DBVar*>& Data = _Data.GetDBVarData();
    for (size_t i = 1; i < Data.size(); i++)
    {
        NewQuery += "'";
        NewQuery += Data[i]->ToString();
        NewQuery += "'";

        if (i == Data.size()-1)
        {
            break;
        }

        NewQuery += ",";
    }

    NewQuery += ")";

    return NewQuery;
}

std::string CharacterTable::UpdateQueryCreate(CharacterTableData& _Data) 
{
    std::vector<DBVar*>& Data = _Data.GetDBVarData();

    //std::string Query =
    //    "UPDATE server11.characterdatatable SET EndIndex = '"
    //    + Data[3]->ToString() + "', ATT = '"
    //    + Data[4]->ToString() + "', HP = '"
    //    + Data[5]->ToString() + "', MAXHP = '"
    //    + Data[6]->ToString() + "' WHERE(no = '"
    //    + Data[0]->ToString() + "');";


    // UPDATE server11.characterdatatable SET LastX = '7', LastY = '3' WHERE(no = 2);

    return "UPDATE server11.characterdatatable SET EndIndex = '"
        + Data[3]->ToString() + "', LastX = '"
        + Data[4]->ToString() + "', LastY = '"
        + Data[5]->ToString() + "', ATT = '"
        + Data[6]->ToString() + "', HP = '"
        + Data[7]->ToString() + "', MAXHP = '"
        + Data[8]->ToString() + "', Score = '"
        + Data[9]->ToString() + "' WHERE(no = '"
        + Data[0]->ToString() + "');";
}