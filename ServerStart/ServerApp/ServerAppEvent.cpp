#include "ServerAppEvent.h"
#include <ServerConnecter.h>
#include <DBManager.h>
#include <ItemTable.h>
#include "DbTaskFunc.h"
#include "ServerPlayer.h"

void ServerAppEvent::DisConnectEvent(ServerConnecter* _Connect) 
{
    // ����� ���� ������ϱ�.
    // ������ �ȵǾ� �ְ���?
    // �� ���ο��� ��ŭ��
    // ���� �����尡 ���� �ȵ���?

    // DB�� �ø������Ͱ� �� ����ְ� �˴ϴ�.
    std::shared_ptr<CharacterTableData> CharacterData = _Connect->GetCharacterData();
    CharacterData->LastX = _Connect->GetPlayer()->GetPos().ix();
    CharacterData->LastY = _Connect->GetPlayer()->GetPos().iy();

    std::vector<std::shared_ptr<ItemTableData>>& ItemsDataRef = _Connect->GetItemsDataRef();
    std::vector<ITEMDBCHECKTYPE>& ItemsDataCheckRef = _Connect->GetItemsDataCheckRef();
    std::vector<std::shared_ptr<ItemTableData>> ItemsData;
    std::vector<ITEMDBCHECKTYPE> ItemsDataUpdateCheck;

    for (size_t i = 0; i < ItemsDataCheckRef.size(); i++)
    {
        // ���Ӱ� ����� �༮�̴�.
        if (ItemsDataCheckRef[i] != ITEMDBCHECKTYPE::NONE)
        {
            ItemsDataUpdateCheck.push_back(ItemsDataCheckRef[i]);
            ItemsData.push_back(ItemsDataRef[i]);
        }
    }



    // ������ �ѹ� ����� �ϰ���?

    _Connect->LogicDataReset();

    // �������� �Ұ�?
    DBManager::Inst().PushTask("", &DbTaskFunc::DisConnectDataUpdateProcess, CharacterData, ItemsData, ItemsDataUpdateCheck);

    // _Connect->GetItemsDataRef()

}