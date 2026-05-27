#pragma once

#include "Header.h"
#include "Item.h"

class Inventory
{
private:
    vector<Item> m_vBag;              // 인벤토리 아이템 저장
    vector<Item>::iterator m_viBag;   // 인벤토리 반복자

    Item* m_equipWeapon;              // 장착 중인 무기
    Item* m_equipArmor;               // 장착 중인 방어구
    Item* m_equipAccessory;           // 장착 중인 장신구

    int m_bagItemCount;               // 인벤토리 아이템 개수
    int m_inventorySelectNum;         // 인벤토리 선택 번호

public:
    Inventory();
    ~Inventory();

    vector<Item>* GetBag()
    {
        return &m_vBag;
    }

    Item* GetWeapon()
    {
        return m_equipWeapon;
    }

    Item* GetArmor()
    {
        return m_equipArmor;
    }

    Item* GetAccessory()
    {
        return m_equipAccessory;
    }

    int GetBagItemCount()
    {
        return m_bagItemCount;
    }

    void ShowPlayerBag();

    void ShowPlayerEquip();
    void ShowEquipText();
    void ChangePlayerEquip(int itemIdx);

    int IsItemExist(const string& itemName);
};