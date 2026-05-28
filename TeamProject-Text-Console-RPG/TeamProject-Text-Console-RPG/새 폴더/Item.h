#pragma once
#include"Header.h"

class Item
{
private:
	// 아이템의 정보에 대한 변수들
	// 변수 이름으로 뜻을 알 수 있도록 한다.
	ITEM m_itemType;
	string m_name;
	int m_price;
	int m_ability;
	string m_description;
	int m_count;
public:
	Item(ITEM, string, int, int, string, int);

	ITEM GetType() { return m_itemType; }
	void SetType(const ITEM itemType) { m_itemType = itemType; }

	string GetName() { return m_name; }
	void SetName(const string name) { m_name = name; }

	int GetPrice() { return m_price; }
	void SetPrice(const int price) { m_price = price; }

	int GetAbility() { return m_ability; }
	void SetAbility(const int ability) { m_ability = ability; }

	string GetDescription() { return m_description; }
	void SetDescription(const string description) { m_description = description; }

	int GetCount() { return m_count; }
	void SetCount(const int count) { m_count = count; }

	void ShowItemInfo();
};

