#pragma once
#include <memory>
#include "DBVar.h"
#include <vector>


// 한행을 대표합니다.
class DBRowData : std::enable_shared_from_this<DBRowData>
{
private:
    std::vector<DBVar*> m_DbVarVector;

public:
    std::vector<DBVar*>& GetDBVarData() 
    {
        return m_DbVarVector;
    }

protected:
    template<typename DBVarType>
    void MemberBind(void* _Data)
    {
        DBVar* NewBindData = new DBVarType();
        NewBindData->DataBind(_Data);
        m_DbVarVector.push_back(NewBindData);
    }

public:
    ~DBRowData() 
    {
        for (size_t i = 0; i < m_DbVarVector.size(); i++)
        {
            delete m_DbVarVector[i];
        }
    }


};

// '2', 'd', 'd'
