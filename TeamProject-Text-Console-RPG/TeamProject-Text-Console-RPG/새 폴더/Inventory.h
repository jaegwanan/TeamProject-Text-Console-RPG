#pragma once
#include "Header.h"
#include "Item.h"

class Inventory
{
private:
	vector<Item> m_vBag; // 인벤토리의 물건을 저장할 vector
	vector<Item>::iterator m_viBag; // 위 vector의 반복자

	// 포인터로 선언한 이유는 훗날 있을
	// Item을 상속으로 구현하여 타입을 구분할 때,
	// 다형성을 구현할 목적으로 미리 이렇게 만듦
	Item* m_equipWeapon; // 무기를 저장할 Item 포인터
	Item* m_equipArmor; // 갑옷을 저장할 Item 포인터
	Item* m_equipAccessory; // 장신구를 저장할 Item 포인터

	int m_bagItemCount; // 인벤토리 안의 물건의 갯수를 표현할 변수
	int m_inventorySelectNum; // 인벤토리 클래스 함수 내에서의 플레이어의 선택을 저장할 변수

public:
	Inventory();
	~Inventory();

	vector<Item>* GetBag() { return &m_vBag; }

	Item* GetWeapon() { return m_equipWeapon; }
	Item* GetArmor() { return m_equipArmor; }
	Item* GetAccessory() { return m_equipAccessory; }

	int GetBagItemCount() { return m_bagItemCount; }

	void ShowPlayerBag();

	void ShowPlayerEquip();
	void ShowEquipText();
	void ChangePlayerEquip(int itemIdx);

	int IsItemExist(const string& itemName);
};