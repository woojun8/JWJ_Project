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
    // ���ʽ���
    m_ItemsData.clear();
    IsUpdate.clear();
    m_ItemsData.resize(25);
    IsUpdate.resize(25);

    // ���ʿ��� ��δ� ������Ʈ�� �ʿ䰡 ����.
    for (size_t i = 0; i < IsUpdate.size(); i++)
    {
        IsUpdate[i] = ITEMDBCHECKTYPE::NONE;
    }

    for (size_t i = 0; i < _ItemsDatas.size(); i++)
    {
        // �� ������ �������� ������Ʈ �ؾ��Ѵ�.

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

            // ��ø�Ǵ� �����̶�� �Ҹ��̹Ƿ�
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

    // ��ø�Ǵ� �������̶��
    if (_Data.Type == 2)
    {
        // ��ø�Ǵ� �����۵鸸 ��Ƴ��� �� �ڷᱸ������ �ѹ� ���ƾ� �մϴ�.
        std::list<std::shared_ptr<ItemTableData>>::iterator Start = m_PotionItemsData.begin();
        std::list<std::shared_ptr<ItemTableData>>::iterator End = m_PotionItemsData.end();
        std::list<ITEMDBCHECKTYPE*>::iterator StartCheck = m_PotionItemsDataUpdateData.begin();
        std::list<ITEMDBCHECKTYPE*>::iterator EndCheck = m_PotionItemsDataUpdateData.end();

        bool UpdateCheck = false;

        // �̹� max�� �����۵��� �����ֱ� ������
        // ���ִ� ���ҵ� ���� �մϴ�.
        for (; Start != End;)
        {
            // Max�� �ٴ޾����Ƿ�
            if (3 <= (*Start)->Count)
            {
                // erase�Ѵ�.
                Start = m_PotionItemsData.erase(Start);
                StartCheck = m_PotionItemsDataUpdateData.erase(StartCheck);
            }
            else 
            {
                // �׷��� Update���� New���� ����� üũ ����߰���?
                // �Ѱ��� ������Ų��.

                m_ItemsData;
                IsUpdate;

                ++(*Start)->Count;
                _Data.Count = (*Start)->Count;
                _Data.InvenOrder = (*Start)->InvenOrder;
                UpdateCheck = true;
                // ���ο� �����ϼ��� �ִ�.
                if (ITEMDBCHECKTYPE::NEW != *(*StartCheck))
                {
                    *(*StartCheck) = ITEMDBCHECKTYPE::UPDATE;
                }

                // (*Start)->InvenOrder = 
                return;
            }
        }

        // ���ʿ��� ��ø�Ǵ� �����۵��� ��� ���������� ��ø��ų �������� ������.
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