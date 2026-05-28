#pragma once

#include "Header.h"
#include "Player.h"
#include "Item.h"

class Shop
{
private:
	vector<Item> m_vItem; // 상점에 진열된 아이템을 저장할 vector
	vector<Item>::iterator m_viItem; // 위 vector의 반복자

	int m_itemCount; // 진열된 아이템의 갯수를 저장할 변수
	int m_shopSelectNum; // 상점 클래스의 함수 내에서 선택을 저장할 변수

public:
	Shop();

	void ShowShopItem();

	void ShopBuyItemPage(Player* player);
	void ShopSellItemPage(Player* player);

	void BuyItem(int itemIdx, Player* player);
	void SellItem(int itemIdx, Player* player);

	int IsItemExist(const string& itemName);
};