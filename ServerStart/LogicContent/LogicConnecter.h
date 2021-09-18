#pragma once
#include <TcpConnecter.h>
#include <vector>
#include <list>

enum ITEMDBCHECKTYPE
{
    NEW,
    UPDATE,
    NONE,
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class Actor;
class CharacterTableData;
class ItemTableData;
class ItemData;
class FriendTableData;
class PartyTableData;
class LogicConnecter : public TcpConnecter
{
private: // Static Var
public: // Static Func
private: // member Var

    std::shared_ptr<CharacterTableData> m_CharacterData;

    // 중첩되는 포션을 저장해 놓고 검색하기 위한 자료구조 
    std::list<std::shared_ptr<ItemTableData>> m_PotionItemsData;
    std::list<ITEMDBCHECKTYPE*> m_PotionItemsDataUpdateData;

    // 실제 아이템의 자료구조
    std::vector<std::shared_ptr<ItemTableData>> m_ItemsData;
    std::vector<ITEMDBCHECKTYPE> IsUpdate;

    std::vector<std::shared_ptr<FriendTableData>> m_FriendData;

    std::vector<std::shared_ptr<PartyTableData>> m_PartyData;

    // 순환 참조를 막기위해서 weak_ptr로 받는다.
    std::weak_ptr<Actor> m_Actor;

    //
public:
    std::shared_ptr<Actor> GetActor()
    {
        return m_Actor.lock();
    }

    void SetActor(std::shared_ptr<Actor> _Actor)
    {
        m_Actor = _Actor;
    }

    std::shared_ptr<CharacterTableData> GetCharacterData()
    {
        return m_CharacterData;
    }

    std::vector<std::shared_ptr<ItemTableData>> GetItemsData()
    {
        return m_ItemsData;
    }

    std::vector<std::shared_ptr<FriendTableData>>& GetFriendDataRef()
    {
        return m_FriendData;
    }

    std::vector<std::shared_ptr<PartyTableData>>& GetPartyDataRef()
    {
        return m_PartyData;
    }

    std::vector<std::shared_ptr<ItemTableData>>& GetItemsDataRef()
    {
        return m_ItemsData;
    }

    std::vector<ITEMDBCHECKTYPE>& GetItemsDataCheckRef()
    {
        return IsUpdate;
    }

    void SetFriendData(std::vector<std::shared_ptr<FriendTableData>> _FriendData)
    {
        m_FriendData = _FriendData;
    }


    void SetCharacterData(std::shared_ptr<CharacterTableData> _CharacterData)
    {
        m_CharacterData = _CharacterData;
    }

    void SetPartyData(std::vector<std::shared_ptr<PartyTableData>> _PartyData)
    {
        m_PartyData = _PartyData;
    }

    void LogicDataReset()
    {
        m_CharacterData = nullptr;
        ItemDataReset();
    }

    void SetItemsData(std::vector<std::shared_ptr<class ItemTableData>> _ItemsDatas);
    void PushItemData(ItemData& _Data);
    void ItemDataReset();


private:
    void NewItemData(ItemData& _Data);

public: // constructer destructer
    LogicConnecter();
    ~LogicConnecter();

public: // delete constructer 
    LogicConnecter(const LogicConnecter& _Other) = delete;
    LogicConnecter(const LogicConnecter&& _Other) = delete;

public: // delete operator
    LogicConnecter& operator=(const LogicConnecter& _Other) = delete;
    LogicConnecter& operator=(const LogicConnecter&& _Other) = delete;

public: // member Func
};

