#pragma once

#include "Header.h"
#include "Player.h"
#include "Shop.h"

class MainGame
{
private:
	Player* m_player;
	Shop* m_shop;

	int m_mainSelectNum;

public:
	MainGame();
	~MainGame();

	Player* GetPlayer() { return m_player; }
	Shop* GetShop() { return m_shop; }

	void Update();

	void ShowMainPage();
	void ShowShopPage();
	void ShowInventoryPage();

	void Battle();

	// 랜덤 아이템 사용 함수 추가
	void RandomUseItem();
};