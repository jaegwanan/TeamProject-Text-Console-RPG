#include "Shop.h"

// 생성자
Shop::Shop() : m_itemCount(0), m_shopSelectNum((int)SHOP::SHOP_TOWN)
{
	Item inputItem1(ITEM::ITEM_WEAPON, "평범한 장검", 10, 5,
		"어느 상점에서나 살 수 있는 장검", 10);

	Item inputItem2(ITEM::ITEM_WEAPON, "바스타드 소드", 30, 20,
		"황무지에서 경험을 쌓은 호인들의 무기", 5);

	Item inputItem3(ITEM::ITEM_WEAPON, "엑스칼리버", 100, 50,
		"선택 받은 자만이 뽑을 수 있다던 그 검", 1);

	Item inputItem4(ITEM::ITEM_ARMOR, "가죽 갑옷", 10, 10,
		"탄탄한 가죽으로 만든 갑옷", 10);

	Item inputItem5(ITEM::ITEM_ACCESSORY, "마법 진주 목걸이", 25, 15,
		"특별한 진주로 세공한 목걸이", 8);

	Item inputItem6(ITEM::ITEM_HP_POTION, "HP 포션", 10, 0,
		"HP를 회복시키는 포션", 10);

	Item inputItem7(ITEM::ITEM_MP_POTION, "MP 포션", 15, 0,
		"MP를 회복시키는 포션", 10);

	Item inputItem8(ITEM::ITEM_ATTACK_POTION, "공격력  포션", 20, 10,
		"공격력을 증가시키는 포션", 10);

	m_vItem.push_back(inputItem1);
	m_vItem.push_back(inputItem2);
	m_vItem.push_back(inputItem3);
	m_vItem.push_back(inputItem4);
	m_vItem.push_back(inputItem5);
	m_vItem.push_back(inputItem6);
	m_vItem.push_back(inputItem7);
	m_vItem.push_back(inputItem8);

}

// 상점 아이템 출력
void Shop::ShowShopItem()
{
	m_itemCount = 0;

	std::cout << "상점 아이템 개수 : "
		<< m_vItem.size() << std::endl;

	for (m_viItem = m_vItem.begin(); m_viItem != m_vItem.end(); ++m_viItem)
	{
		std::cout << "=================================================" << std::endl;
		std::cout << ++m_itemCount << "번째 아이템" << std::endl;
		m_viItem->ShowItemInfo();
		Sleep(1000);
	}

	std::cout << "=================================================" << std::endl;
}

// 물건 사기 페이지
void Shop::ShopBuyItemPage(Player* player)
{
	while (true)
	{
		system("cls");

		std::cout << "=================================================" << std::endl;
		std::cout << "물건 사기" << std::endl;

		ShowShopItem();

		if (m_itemCount == 0)
		{
			std::cout << "상점 주인 : 아! 미안해요... 물건이 이젠 없어..." << std::endl;
			std::cout << "=================================================" << std::endl;
			std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(1000);
			return;
		}

		std::cout << "상점 주인 : 저희는 쓸만한 것만 들여놓습니다!" << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "플레이어의 소지금 : " << player->GetMoney() << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "어느 물건을 사시겠습니까?" << std::endl;
		std::cout << "상점 메뉴로 돌아가려면 0을 입력하세요." << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "입력 : ";
		std::cin >> m_shopSelectNum;

		if (m_shopSelectNum == 0)
		{
			std::cout << "=================================================" << std::endl;
			std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(500);
			return;
		}

		bool WrongSelect = ((m_shopSelectNum < 0) || (m_shopSelectNum > m_itemCount));

		while (WrongSelect)
		{
			system("cls");

			std::cout << "=================================================" << std::endl;
			std::cout << "물건 사기" << std::endl;

			ShowShopItem();

			std::cout << "플레이어의 소지금 : " << player->GetMoney() << std::endl;
			std::cout << "=================================================" << std::endl;
			std::cout << "상점 주인 : 뭘 달라고 하시는 거죠? 거기엔 아무것도 없습니다!" << std::endl;
			std::cout << "다시 입력하세요." << std::endl;
			std::cout << "상점 메뉴로 돌아가려면 0을 입력하세요." << std::endl;
			std::cout << "=================================================" << std::endl;
			std::cout << "입력 : ";
			std::cin >> m_shopSelectNum;

			if (m_shopSelectNum == 0)
			{
				std::cout << "=================================================" << std::endl;
				std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
				std::cout << "=================================================" << std::endl;
				Sleep(500);
				return;
			}

			WrongSelect = ((m_shopSelectNum < 0) || (m_shopSelectNum > m_itemCount));
		}

		bool NotEnoughMoney = m_vItem[m_shopSelectNum - 1].GetPrice() > player->GetMoney();

		if (NotEnoughMoney)
		{
			std::cout << "=================================================" << std::endl;
			std::cout << "상점 주인 : 그냥 드릴 수는 없죠! 돈이 부족하시네요." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(1000);
		}
		else
		{
			BuyItem(m_shopSelectNum - 1, player);
		}
	}
}

// 물건 팔기 페이지
void Shop::ShopSellItemPage(Player* player)
{
	while (true)
	{
		system("cls");

		std::cout << "=================================================" << std::endl;
		std::cout << "물건 팔기" << std::endl;

		player->GetInventory()->ShowPlayerBag();

		if (player->GetInventory()->GetBagItemCount() == 0)
		{
			std::cout << "상점 주인 : 자네는 내가 살 물건을 가지고 오는게 좋겠어." << std::endl;
			std::cout << "=================================================" << std::endl;
			std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(1000);
			return;
		}

		std::cout << "상점 주인 : 어떤 물건을 파실 건가요!" << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "플레이어의 소지금 : " << player->GetMoney() << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "어느 물건을 파시겠습니까?" << std::endl;
		std::cout << "상점 메뉴로 돌아가려면 0을 입력하세요." << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "입력 : ";
		std::cin >> m_shopSelectNum;

		int bagItemCount = player->GetInventory()->GetBagItemCount();

		if (m_shopSelectNum == 0)
		{
			std::cout << "=================================================" << std::endl;
			std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(500);
			return;
		}

		bool WrongSelect = ((m_shopSelectNum < 0) || (m_shopSelectNum > bagItemCount));

		while (WrongSelect)
		{
			system("cls");

			std::cout << "=================================================" << std::endl;
			std::cout << "물건 팔기" << std::endl;

			player->GetInventory()->ShowPlayerBag();

			std::cout << "플레이어의 소지금 : " << player->GetMoney() << std::endl;
			std::cout << "=================================================" << std::endl;
			std::cout << "그곳엔 아이템이 없습니다." << std::endl;
			std::cout << "다시 입력하세요." << std::endl;
			std::cout << "상점 메뉴로 돌아가려면 0을 입력하세요." << std::endl;
			std::cout << "=================================================" << std::endl;
			std::cout << "입력 : ";
			std::cin >> m_shopSelectNum;

			if (m_shopSelectNum == 0)
			{
				std::cout << "=================================================" << std::endl;
				std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
				std::cout << "=================================================" << std::endl;
				Sleep(500);
				return;
			}

			WrongSelect = ((m_shopSelectNum < 0) || (m_shopSelectNum > bagItemCount));
		}

		SellItem(m_shopSelectNum - 1, player);
	}
}

// 아이템 구매
void Shop::BuyItem(int itemIdx, Player* player)
{
	vector<Item>* playerBag = player->GetInventory()->GetBag();

	int existItem = player->GetInventory()->IsItemExist(m_vItem[itemIdx].GetName());

	if (existItem > -1)
	{
		playerBag->at(existItem).SetCount(playerBag->at(existItem).GetCount() + 1);
	}
	else
	{
		Item tempItem = m_vItem[itemIdx];
		tempItem.SetCount(1);
		playerBag->push_back(tempItem);
	}

	player->SetMoney(player->GetMoney() - m_vItem[itemIdx].GetPrice());

	m_vItem[itemIdx].SetCount(m_vItem[itemIdx].GetCount() - 1);

	if (m_vItem[itemIdx].GetCount() == 0)
	{
		m_vItem.erase(m_vItem.begin() + itemIdx);
	}

	std::cout << "=================================================" << std::endl;
	std::cout << "아이템을 구매했습니다." << std::endl;
	std::cout << "=================================================" << std::endl;
	Sleep(1000);
}

// 아이템 판매
void Shop::SellItem(int itemIdx, Player* player)
{
	vector<Item>* playerBag = player->GetInventory()->GetBag();

	int sellPrice = playerBag->at(itemIdx).GetPrice() * 60 / 100;

	int existItem = IsItemExist(playerBag->at(itemIdx).GetName());

	if (existItem > -1)
	{
		m_vItem[existItem].SetCount(m_vItem[existItem].GetCount() + 1);
	}
	else
	{
		Item tempItem = playerBag->at(itemIdx);
		tempItem.SetCount(1);
		m_vItem.push_back(tempItem);
	}

	player->SetMoney(player->GetMoney() + sellPrice);

	playerBag->at(itemIdx).SetCount(playerBag->at(itemIdx).GetCount() - 1);

	if (playerBag->at(itemIdx).GetCount() == 0)
	{
		playerBag->erase(playerBag->begin() + itemIdx);
	}

	std::cout << "=================================================" << std::endl;
	std::cout << "아이템을 판매했습니다." << std::endl;
	std::cout << "판매 금액 : " << sellPrice << " 골드" << std::endl;
	std::cout << "=================================================" << std::endl;
	Sleep(1000);
}

// 상점에 같은 아이템이 있는지 확인
int Shop::IsItemExist(const string& itemName)
{
	int result = -1;
	int itemCount = 0;

	for (m_viItem = m_vItem.begin(); m_viItem != m_vItem.end(); ++m_viItem)
	{
		if (m_viItem->GetName() == itemName)
		{
			result = itemCount;
			break;
		}

		++itemCount;
	}

	return result;
}