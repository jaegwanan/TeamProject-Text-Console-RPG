#pragma once

#include "Header.h"
#include "Character.h"
#include "Item.h"

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

    // 상점 아이템 출력
    void ShowShopItem();

    // 아이템 구매 / 판매 페이지
    void ShopBuyItemPage(Character* player);
    void ShopSellItemPage(Character* player);

    // 실제 구매 / 판매
    void BuyItem(int itemIdx, Character* player);
    void SellItem(int itemIdx, Character* player);

    // 같은 아이템 존재 확인
    int IsItemExist(const string& itemName);
};