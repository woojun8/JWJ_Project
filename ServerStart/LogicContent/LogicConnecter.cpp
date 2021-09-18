#include "LogicConnecter.h"
#include "CharacterTable.h"
#include "ItemTable.h"
#include "PartyTable.h"
#include "ServerToClient.h"
// Static Var
// Static Func

// constructer destructer
LogicConnecter::LogicConnecter() 
{
}

LogicConnecter::~LogicConnecter() 
{

}
// member Func

void LogicConnecter::SetItemsData(std::vector<std::shared_ptr<ItemTableData>> _ItemsDatas)
{
    // 최초시작
    m_ItemsData.clear();
    IsUpdate.clear();
    m_ItemsData.resize(25);
    IsUpdate.resize(25);

    // 최초에는 모두다 업데이트할 필요가 없다.
    for (size_t i = 0; i < IsUpdate.size(); i++)
    {
        IsUpdate[i] = ITEMDBCHECKTYPE::NONE;
    }

    for (size_t i = 0; i < _ItemsDatas.size(); i++)
    {
        // 이 오더의 아이템은 업데이트 해야한다.

        int Order = _ItemsDatas[i]->InvenOrder;

        m_ItemsData[Order] = _ItemsDatas[i];

        if (2 == _ItemsDatas[i]->Type)
        {
            m_PotionItemsData.push_back(m_ItemsData[Order]);
            m_PotionItemsDataUpdateData.push_back(&IsUpdate[Order]);
        }

        // IsUpdate[_ItemsDatas[i]->InvenOrder] = ITEMDBCHECKTYPE::NEW;
    }
}

void LogicConnecter::NewItemData(ItemData& _Data) 
{
    for (int i = 0; i < m_ItemsData.size(); i++)
    {
        if (nullptr == m_ItemsData[i])
        {
            m_ItemsData[i] = std::make_shared<ItemTableData>();
            m_ItemsData[i]->Count = _Data.Count;
            m_ItemsData[i]->IconResData = _Data.IconResData;
            m_ItemsData[i]->InvenOrder = i;
            m_ItemsData[i]->PID = m_CharacterData->PID;
            m_ItemsData[i]->Type = _Data.Type;
            std::string NameConvert = _Data.Name.GetConvertMultiByteString();
            strcpy_s(m_ItemsData[i]->Name, NameConvert.c_str());
            IsUpdate[i] = ITEMDBCHECKTYPE::NEW;

            // 중첩되는 포션이라는 소리이므로
            if (2 == _Data.Type)
            {
                m_PotionItemsData.push_back(m_ItemsData[i]);
                m_PotionItemsDataUpdateData.push_back(&IsUpdate[i]);
            }

            _Data.InvenOrder = i;

            return;
        }
    }

}

void LogicConnecter::PushItemData(ItemData& _Data) 
{

    // 중첩되는 아이템이라면
    if (_Data.Type == 2)
    {
        // 중첩되는 아이템들만 모아놓은 이 자료구조에서 한번 돌아야 합니다.
        std::list<std::shared_ptr<ItemTableData>>::iterator Start = m_PotionItemsData.begin();
        std::list<std::shared_ptr<ItemTableData>>::iterator End = m_PotionItemsData.end();
        std::list<ITEMDBCHECKTYPE*>::iterator StartCheck = m_PotionItemsDataUpdateData.begin();
        std::list<ITEMDBCHECKTYPE*>::iterator EndCheck = m_PotionItemsDataUpdateData.end();

        bool UpdateCheck = false;

        // 이미 max인 아이템들은 꽉차있기 때문에
        // 빼주는 역할도 같이 합니다.
        for (; Start != End;)
        {
            // Max에 다달았으므로
            if (3 <= (*Start)->Count)
            {
                // erase한다.
                Start = m_PotionItemsData.erase(Start);
                StartCheck = m_PotionItemsDataUpdateData.erase(StartCheck);
            }
            else 
            {
                // 그러면 Update인지 New인지 제대로 체크 해줘야겠죠?
                // 한개를 증가시킨다.

                m_ItemsData;
                IsUpdate;

                ++(*Start)->Count;
                _Data.Count = (*Start)->Count;
                _Data.InvenOrder = (*Start)->InvenOrder;
                UpdateCheck = true;
                // 새로운 포션일수도 있다.
                if (ITEMDBCHECKTYPE::NEW != *(*StartCheck))
                {
                    *(*StartCheck) = ITEMDBCHECKTYPE::UPDATE;
                }

                // (*Start)->InvenOrder = 
                return;
            }
        }

        // 위쪽에서 중첩되는 아이템들을 모두 돌았음에도 중첩시킬 아이템이 없었다.
        if (false == UpdateCheck)
        {
            NewItemData(_Data);
        }

    }
    else {
        NewItemData(_Data);
    }


    

    return;
}

void LogicConnecter::ItemDataReset() 
{
    m_PotionItemsData.clear();
    m_PotionItemsDataUpdateData.clear();
    m_ItemsData.clear();
    IsUpdate.clear();
}