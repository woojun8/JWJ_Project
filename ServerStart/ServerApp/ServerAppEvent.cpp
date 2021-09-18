#include "ServerAppEvent.h"
#include <ServerConnecter.h>
#include <DBManager.h>
#include <ItemTable.h>
#include "DbTaskFunc.h"
#include "ServerPlayer.h"

void ServerAppEvent::DisConnectEvent(ServerConnecter* _Connect) 
{
    // 여기는 같은 쓰레드니까.
    // 진행이 안되어 있겠죠?
    // 이 내부에서 만큼은
    // 아직 스레드가 진행 안됐죠?

    // DB에 올릴데이터가 다 들어있게 됩니다.
    std::shared_ptr<CharacterTableData> CharacterData = _Connect->GetCharacterData();
    CharacterData->LastX = _Connect->GetPlayer()->GetPos().ix();
    CharacterData->LastY = _Connect->GetPlayer()->GetPos().iy();

    std::vector<std::shared_ptr<ItemTableData>>& ItemsDataRef = _Connect->GetItemsDataRef();
    std::vector<ITEMDBCHECKTYPE>& ItemsDataCheckRef = _Connect->GetItemsDataCheckRef();
    std::vector<std::shared_ptr<ItemTableData>> ItemsData;
    std::vector<ITEMDBCHECKTYPE> ItemsDataUpdateCheck;

    for (size_t i = 0; i < ItemsDataCheckRef.size(); i++)
    {
        // 새롭게 변경된 녀석이다.
        if (ItemsDataCheckRef[i] != ITEMDBCHECKTYPE::NONE)
        {
            ItemsDataUpdateCheck.push_back(ItemsDataCheckRef[i]);
            ItemsData.push_back(ItemsDataRef[i]);
        }
    }



    // 구분을 한번 해줘야 하겠죠?

    _Connect->LogicDataReset();

    // 무슨일을 할가?
    DBManager::Inst().PushTask("", &DbTaskFunc::DisConnectDataUpdateProcess, CharacterData, ItemsData, ItemsDataUpdateCheck);

    // _Connect->GetItemsDataRef()

}