#pragma once

#include <vector>
#include <string>
#include "Item.h"
#include "Character.h"

using namespace std;

class Shop
{
private:
    // 상점 아이템 저장
    vector<Item> m_vItem;

    // 반복자
    vector<Item>::iterator m_viItem;

    // 상점 아이템 개수
    int m_itemCount;

    // 플레이어 선택 번호
    int m_shopSelectNum;

public:
    Shop();

    void ShowShopItem();
    void ShopBuyItemPage(Character* player);
    void ShopSellItemPage(Character* player);

    void BuyItem(int itemIdx, Character* player);
    void SellItem(int itemIdx, Character* player);

    int IsItemExist(const string& itemName);
};