#include "Inventory.h"

// 생성자
Inventory::Inventory() : m_bagItemCount(0), m_inventorySelectNum(0)
{
	m_equipWeapon = new Item(
		ITEM::ITEM_WEAPON,
		"평범한 장검",
		10,
		5,
		"어느 상점에서나 살 수 있는 장검",
		1
	);

	m_equipArmor = new Item(
		ITEM::ITEM_ARMOR,
		"더러운 옷",
		0,
		0,
		"처음 공장에서 만들어졌을 때는 깨끗했을거야.",
		1
	);

	m_equipAccessory = new Item(
		ITEM::ITEM_ACCESSORY,
		"목걸이",
		0,
		0,
		"어머니의 사진이 들어 있는 목걸이",
		1
	);

	// 시작 인벤토리는 비워둔다.
}

// 소멸자
Inventory::~Inventory()
{
	delete m_equipWeapon;
	delete m_equipArmor;
	delete m_equipAccessory;
}

// 인벤토리 출력
void Inventory::ShowPlayerBag()
{
	m_bagItemCount = 0;

	if (m_vBag.empty())
	{
		std::cout << "=================================================" << std::endl;
		std::cout << "인벤토리가 비어 있습니다." << std::endl;
		std::cout << "=================================================" << std::endl;
		return;
	}

	for (m_viBag = m_vBag.begin();
		m_viBag != m_vBag.end();
		++m_viBag)
	{
		std::cout << "=================================================" << std::endl;
		std::cout << ++m_bagItemCount << "번째 아이템" << std::endl;

		m_viBag->ShowItemInfo();

		Sleep(500);
	}

	std::cout << "=================================================" << std::endl;
}

// 장비 확인 및 교체
void Inventory::ShowPlayerEquip()
{
	ShowEquipText();

	std::cout << "=================================================" << std::endl;
	std::cout << "플레이어의 장비 확인하기를 선택하셨습니다." << std::endl;
	std::cout << "1~3을 입력해 원하는 장비를 교체합니다." << std::endl;
	std::cout << "0을 누르면 이전으로 돌아갑니다." << std::endl;
	std::cout << "=================================================" << std::endl;
	std::cout << "입력 : ";

	std::cin >> m_inventorySelectNum;

	bool WrongSelect =
		((0 > m_inventorySelectNum)
			|| (m_inventorySelectNum > 3));

	while (WrongSelect)
	{
		ShowEquipText();

		std::cout << "=================================================" << std::endl;
		std::cout << "그곳엔 아이템이 없습니다. 다시 입력하세요." << std::endl;
		std::cout << "이전으로 돌아가려면 0을 입력하세요." << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "입력 : ";

		std::cin >> m_inventorySelectNum;

		WrongSelect =
			((0 > m_inventorySelectNum)
				|| (m_inventorySelectNum > 3));
	}

	if (m_inventorySelectNum == 0)
	{
		return;
	}

	if (m_vBag.empty())
	{
		std::cout << "=================================================" << std::endl;
		std::cout << "교체할 아이템이 없습니다." << std::endl;
		std::cout << "=================================================" << std::endl;
		Sleep(1000);
		return;
	}

	ITEM selectItemType =
		(ITEM)m_inventorySelectNum;

	system("cls");

	ShowPlayerBag();

	std::cout << "원하는 아이템을 선택하세요." << std::endl;
	std::cout << "이전으로 돌아가려면 0을 입력하세요." << std::endl;
	std::cout << "=================================================" << std::endl;
	std::cout << "입력 : ";

	std::cin >> m_inventorySelectNum;

	if (m_inventorySelectNum == 0)
	{
		std::cout << "=================================================" << std::endl;
		std::cout << "인벤토리 메뉴로 돌아갑니다." << std::endl;
		std::cout << "=================================================" << std::endl;

		Sleep(500);

		return;
	}

	WrongSelect =
		((0 > m_inventorySelectNum)
			|| (m_inventorySelectNum > m_bagItemCount));

	while (WrongSelect)
	{
		system("cls");

		ShowPlayerBag();

		std::cout << "그곳엔 아이템이 없거나 올바르지 않은 장비 타입입니다." << std::endl;
		std::cout << "다시 입력하세요." << std::endl;
		std::cout << "이전으로 돌아가려면 0을 입력하세요." << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "입력 : ";

		std::cin >> m_inventorySelectNum;

		if (m_inventorySelectNum == 0)
		{
			return;
		}

		WrongSelect =
			((0 > m_inventorySelectNum)
				|| (m_inventorySelectNum > m_bagItemCount));
	}

	bool WrongType =
		selectItemType
		!= m_vBag[m_inventorySelectNum - 1].GetType();

	if (WrongType)
	{
		std::cout << "=================================================" << std::endl;
		std::cout << "아이템 타입이 맞지 않습니다." << std::endl;
		std::cout << "=================================================" << std::endl;

		Sleep(1000);
	}
	else
	{
		ChangePlayerEquip(m_inventorySelectNum - 1);
	}
}

// 장비 출력
void Inventory::ShowEquipText()
{
	system("cls");

	std::cout << "=================================================" << std::endl;
	std::cout << "플레이어의 장비" << std::endl;
	std::cout << "=================================================" << std::endl;

	std::cout << "1.무      기" << std::endl;

	m_equipWeapon->ShowItemInfo();

	Sleep(500);

	std::cout << "=================================================" << std::endl;
	std::cout << "2.방  어  구" << std::endl;

	m_equipArmor->ShowItemInfo();

	Sleep(500);

	std::cout << "=================================================" << std::endl;
	std::cout << "3.장  신  구" << std::endl;

	m_equipAccessory->ShowItemInfo();

	Sleep(500);
}

// 장비 교체
void Inventory::ChangePlayerEquip(int itemIdx)
{
	int existItem;

	// 무기
	if (m_vBag[itemIdx].GetType() == ITEM::ITEM_WEAPON)
	{
		existItem =
			IsItemExist(m_equipWeapon->GetName());

		if (existItem > -1)
		{
			m_vBag[existItem].SetCount(
				m_vBag[existItem].GetCount() + 1
			);
		}
		else
		{
			m_vBag.push_back(*m_equipWeapon);
		}

		delete m_equipWeapon;

		m_equipWeapon =
			new Item(m_vBag[itemIdx]);
	}

	// 방어구
	else if (m_vBag[itemIdx].GetType() == ITEM::ITEM_ARMOR)
	{
		existItem =
			IsItemExist(m_equipArmor->GetName());

		if (existItem > -1)
		{
			m_vBag[existItem].SetCount(
				m_vBag[existItem].GetCount() + 1
			);
		}
		else
		{
			m_vBag.push_back(*m_equipArmor);
		}

		delete m_equipArmor;

		m_equipArmor =
			new Item(m_vBag[itemIdx]);
	}

	// 장신구
	else if (m_vBag[itemIdx].GetType() == ITEM::ITEM_ACCESSORY)
	{
		existItem =
			IsItemExist(m_equipAccessory->GetName());

		if (existItem > -1)
		{
			m_vBag[existItem].SetCount(
				m_vBag[existItem].GetCount() + 1
			);
		}
		else
		{
			m_vBag.push_back(*m_equipAccessory);
		}

		delete m_equipAccessory;

		m_equipAccessory =
			new Item(m_vBag[itemIdx]);
	}

	m_vBag[itemIdx].SetCount(
		m_vBag[itemIdx].GetCount() - 1
	);

	if (m_vBag[itemIdx].GetCount() == 0)
	{
		m_vBag.erase(m_vBag.begin() + itemIdx);
	}

	std::cout << "=================================================" << std::endl;
	std::cout << "장비를 교체했습니다." << std::endl;
	std::cout << "=================================================" << std::endl;

	Sleep(1000);
}

// 아이템 존재 확인
int Inventory::IsItemExist(const string& itemName)
{
	int result = -1;

	int itemCount = 0;

	for (m_viBag = m_vBag.begin();
		m_viBag != m_vBag.end();
		++m_viBag)
	{
		if (m_viBag->GetName() == itemName)
		{
			result = itemCount;

			break;
		}

		++itemCount;
	}

	return result;
}