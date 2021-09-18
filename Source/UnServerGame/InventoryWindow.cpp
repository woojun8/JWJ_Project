// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWindow.h"
#include "Components/TileView.h"
#include "InvenItemData.h"
#include "InvenIcon.h"
#include "UnServerConnect.h"

//class ItemResData 
//{
//public:
//    int IconIndex;
//    int UIEffect;
//};
// std::vector<ItemResData> m_ItemResItem;

void UInventoryWindow::ItemClear() 
{
    if (nullptr != m_TileView)
    {
        m_TileView->ClearListItems();
        UE_LOG(LogTemp, Error, L"ClearOK");
    }
}

void UInventoryWindow::InvenInit()
{
    if (nullptr == m_TileView)
    {
        m_TileView = Cast<UTileView>(GetWidgetFromName(TEXT("Icons")));

        for (int i = 0; i < 25; i++)
        {
            UInvenItemData* NewItem = NewObject<UInvenItemData>();
            NewItem->Index = i;
            m_TileView->AddItem(NewItem);
        }

        UE_LOG(LogTemp, Error, L"InitOk");
        // m_TileView->ClearListItems();
    }

    // this->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWindow::NewIconEvent(UObject* _Item, UUserWidget* _Icon)
{
    UInvenIcon* Icon = Cast<UInvenIcon>(_Icon);
    Icon->SetName(TEXT("Name"));
    m_Array.push_back(Icon);

    UE_LOG(LogTemp, Error, TEXT("ICONCreate"));

    if (false == UnServerConnect::GetInst().IsConnect())
    {
        return;
    }
    

    if (m_Array.size() - 1 <= UnServerConnect::GetInst().m_CharacterData.ItemDatas.size())
    {
        SetItemData(UnServerConnect::GetInst().m_CharacterData.ItemDatas[m_Array.size() - 1]);
    }

}

void UInventoryWindow::ItemUpdate() 
{
    //// m_Array.GetData()[0]->SetCount(m_Array.GetData()[0]->GetCount() + 1);
    //for (auto& _Data : m_Array)
    //{
    //    _Data->SetCount(_Data->GetCount() + 1);
    //}
}

void UInventoryWindow::SetItemData(const ItemData& _Data)
{
    if (0 >= m_Array.size())
    {
        return;
    }

    if (_Data.Type == -1)
    {
        return;
    }

    //int     Type;
    //int     InvenOrder;
    //int     Count;
    //int     IconResData;

    UE_LOG(LogTemp, Error, L"%s, %d, %d", _Data.Name.ConstStringPtr(), _Data.InvenOrder, _Data.Count);
    m_Array[_Data.InvenOrder]->SetName(_Data.Name.ConstStringPtr());
    m_Array[_Data.InvenOrder]->SetCount(_Data.Count);
    m_Array[_Data.InvenOrder]->SetIcon(_Data.IconResData);
}

