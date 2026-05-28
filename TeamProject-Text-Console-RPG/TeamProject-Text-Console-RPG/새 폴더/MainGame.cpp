#include "MainGame.h"

MainGame::MainGame() : m_mainSelectNum((int)LOCATION::LOCATION_TOWN)
{
	m_player = new Player();
	m_shop = new Shop();
}

MainGame::~MainGame()
{
	delete m_player;
	delete m_shop;
}

void MainGame::Update()
{
	while (true)
	{
		ShowMainPage();

		std::cin >> m_mainSelectNum;

		switch (m_mainSelectNum)
		{
		case 1:
			ShowShopPage();
			break;

		case 2:
			ShowInventoryPage();
			break;

		case 3:
			Battle();
			break;

		case 4:
			m_player->ShowStat();
			std::cout << "아무 키나 입력하면 마을로 돌아갑니다." << std::endl;
			system("pause");
			break;

		case 0:
			std::cout << "=================================================" << std::endl;
			std::cout << "게임을 종료합니다." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(1000);
			return;

		default:
			std::cout << "=================================================" << std::endl;
			std::cout << "잘못 입력했습니다. 다시 입력하세요." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(1000);
			break;
		}
	}
}

void MainGame::ShowMainPage()
{
	system("cls");

	std::cout << "=================================================" << std::endl;
	std::cout << "당신은 마을에 있습니다." << std::endl;
	std::cout << "당신의 행동을 선택하세요." << std::endl;
	std::cout << "게임을 종료하려면 0을 입력하세요." << std::endl;
	std::cout << "=================================================" << std::endl;
	std::cout << "1. 상점에 가기" << std::endl;
	std::cout << "2. 인벤토리 열기" << std::endl;
	std::cout << "3. 전투 시작" << std::endl;
	std::cout << "4. 스탯 확인" << std::endl;
	std::cout << "=================================================" << std::endl;
	std::cout << "입력 : ";
}

void MainGame::ShowShopPage()
{
	while (true)
	{
		system("cls");

		std::cout << "=================================================" << std::endl;
		std::cout << "상점에 들어왔습니다." << std::endl;
		std::cout << "상점에서 할 행동을 선택하세요." << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "1. 물건 사기" << std::endl;
		std::cout << "2. 물건 팔기" << std::endl;
		std::cout << "0. 마을로 돌아가기" << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "입력 : ";

		std::cin >> m_mainSelectNum;

		switch (m_mainSelectNum)
		{
		case 1:
			m_shop->ShopBuyItemPage(m_player);
			break;

		case 2:
			m_shop->ShopSellItemPage(m_player);
			break;

		case 0:
			std::cout << "=================================================" << std::endl;
			std::cout << "마을로 돌아갑니다." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(500);
			return;

		default:
			std::cout << "=================================================" << std::endl;
			std::cout << "잘못 입력했습니다. 다시 입력하세요." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(1000);
			break;
		}
	}
}

void MainGame::ShowInventoryPage()
{
	while (true)
	{
		system("cls");

		std::cout << "=================================================" << std::endl;
		std::cout << "인벤토리를 열었습니다." << std::endl;
		std::cout << "원하는 행동을 선택하세요." << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "1. 가방 보기" << std::endl;
		std::cout << "2. 장비 확인 / 교체" << std::endl;
		std::cout << "3. 스탯 확인" << std::endl;
		std::cout << "0. 마을로 돌아가기" << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "입력 : ";

		std::cin >> m_mainSelectNum;

		switch (m_mainSelectNum)
		{
		case 1:
			system("cls");
			m_player->GetInventory()->ShowPlayerBag();
			std::cout << "아무 키나 입력하면 인벤토리로 돌아갑니다." << std::endl;
			system("pause");
			break;

		case 2:
			m_player->GetInventory()->ShowPlayerEquip();
			break;

		case 3:
			m_player->ShowStat();
			std::cout << "아무 키나 입력하면 인벤토리로 돌아갑니다." << std::endl;
			system("pause");
			break;

		case 0:
			std::cout << "=================================================" << std::endl;
			std::cout << "마을로 돌아갑니다." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(500);
			return;

		default:
			std::cout << "=================================================" << std::endl;
			std::cout << "잘못 입력했습니다. 다시 입력하세요." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(1000);
			break;
		}
	}
}

void MainGame::Battle()
{
	int monsterHp = 50;
	int monsterAtk = 8;

	while (true)
	{
		system("cls");

		int playerAtk =
			m_player->GetAtk()
			+ m_player->GetInventory()->GetWeapon()->GetAbility();

		int playerDef =
			m_player->GetDef()
			+ m_player->GetInventory()->GetArmor()->GetAbility()
			+ m_player->GetInventory()->GetAccessory()->GetAbility();

		std::cout << "=================================================" << std::endl;
		std::cout << "몬스터가 등장했습니다!" << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "몬스터 HP : " << monsterHp << std::endl;
		std::cout << "플레이어 HP : " << m_player->GetHp() << std::endl;
		std::cout << "플레이어 공격력 : " << playerAtk << std::endl;
		std::cout << "플레이어 방어력 : " << playerDef << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "1. 공격하기" << std::endl;
		std::cout << "2. 랜덤 아이템 사용" << std::endl;
		std::cout << "3. 스탯 확인" << std::endl;
		std::cout << "4. 마을로 도망가기" << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "입력 : ";

		std::cin >> m_mainSelectNum;

		switch (m_mainSelectNum)
		{
		case 1:
		{
			monsterHp -= playerAtk;

			std::cout << "=================================================" << std::endl;
			std::cout << "플레이어가 몬스터를 공격했습니다!" << std::endl;
			std::cout << "몬스터에게 " << playerAtk << "의 데미지!" << std::endl;

			if (monsterHp <= 0)
			{
				std::cout << "몬스터를 처치했습니다!" << std::endl;
				std::cout << "마을로 돌아갑니다." << std::endl;
				std::cout << "=================================================" << std::endl;
				Sleep(1000);
				return;
			}

			int damage = monsterAtk - playerDef;

			if (damage < 0)
			{
				damage = 0;
			}

			m_player->SetHp(m_player->GetHp() - damage);

			std::cout << "몬스터가 반격했습니다!" << std::endl;
			std::cout << "플레이어가 " << damage << "의 데미지를 받았습니다." << std::endl;

			if (m_player->GetHp() <= 0)
			{
				std::cout << "플레이어가 사망했습니다." << std::endl;
				std::cout << "=================================================" << std::endl;
				Sleep(1000);
				return;
			}

			std::cout << "=================================================" << std::endl;
			system("pause");
			break;
		}

		case 2:
			RandomUseItem();
			system("pause");
			break;

		case 3:
			m_player->ShowStat();
			std::cout << "아무 키나 입력하면 전투로 돌아갑니다." << std::endl;
			system("pause");
			break;

		case 4:
			std::cout << "=================================================" << std::endl;
			std::cout << "마을로 도망갑니다." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(500);
			return;

		default:
			std::cout << "=================================================" << std::endl;
			std::cout << "잘못 입력했습니다. 다시 입력하세요." << std::endl;
			std::cout << "=================================================" << std::endl;
			Sleep(1000);
			break;
		}
	}
}

void MainGame::RandomUseItem()
{
	vector<Item>* bag = m_player->GetInventory()->GetBag();

	if (bag->empty())
	{
		std::cout << "=================================================" << std::endl;
		std::cout << "사용할 아이템이 없습니다." << std::endl;
		std::cout << "=================================================" << std::endl;
		return;
	}

	int randomIndex = rand() % bag->size();

	string itemName = bag->at(randomIndex).GetName();

	std::cout << "=================================================" << std::endl;
	std::cout << itemName << "을(를) 랜덤으로 사용했습니다!" << std::endl;

	if (itemName == "HP 포션")
	{
		m_player->SetHp(m_player->GetHp() + 50);
		std::cout << "체력이 50 회복되었습니다." << std::endl;
	}
	else if (itemName == "MP 포션")
	{
		m_player->SetMp(m_player->GetMp() + 30);
		std::cout << "MP가 30 회복되었습니다." << std::endl;
	}
	else if (itemName == "공격력 증가 포션")
	{
		m_player->SetAtk(m_player->GetAtk() + 10);
		std::cout << "공격력이 10 증가했습니다." << std::endl;
	}
	else
	{
		std::cout << "이 아이템은 전투 중 사용할 수 없습니다." << std::endl;
		std::cout << "=================================================" << std::endl;
		return;
	}

	bag->at(randomIndex).SetCount(bag->at(randomIndex).GetCount() - 1);

	if (bag->at(randomIndex).GetCount() <= 0)
	{
		bag->erase(bag->begin() + randomIndex);
	}

	std::cout << "=================================================" << std::endl;
}