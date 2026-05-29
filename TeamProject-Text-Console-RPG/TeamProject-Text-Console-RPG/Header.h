#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

// 플레이어 위치
enum class LOCATION
{
	LOCATION_TOWN,
	LOCATION_SHOP,
	LOCATION_INVENTORY
};

// 상점 행동
enum class SHOP
{
	SHOP_TOWN,
	SHOP_BUY,
	SHOP_SELL
};

// 아이템 타입
enum class ITEM
{
	ITEM_EMPTY,
	ITEM_WEAPON,
	ITEM_ARMOR,
	ITEM_ACCESSORY,
	ITEM_HP_POTION,
	ITEM_MP_POTION,
	ITEM_ATTACK_POTION,
	ITEM_DETOX_POTION
};

// 인벤토리 행동
enum class INVENTORY
{
	INVENTORY_TOWN,
	INVENTORY_SHOWBAG,
	INVENTORY_EQUIP,
	INVENTORY_SHOWSTAT
};