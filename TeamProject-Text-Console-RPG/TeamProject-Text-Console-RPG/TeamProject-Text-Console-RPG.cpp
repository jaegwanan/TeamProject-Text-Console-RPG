#include <iostream>
#include <string>
#include <ctime>

#include "Character.h"
#include "GameManager.h"
#include "shop.h"
#include "ShopManager.h"
#include "Inventory.h"

#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Archer.h"

using namespace std;

class Warrior;
class Mage;
class Thief;
class Archer;

MainGame::MainGame(Character* player) : m_player(player), m_shop(new Shop()), m_mainSelectNum((int)LOCATION::LOCATION_TOWN)
{
}

MainGame::~MainGame()
{
    delete m_shop;
}

void MainGame::ShowShopPage()
{
    int Num;

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

        if (!(cin >> Num)) // 여기서 입력 받고
        {
            system("cls");
            cout << "잘못된 입력입니다.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();

            continue;
        }

        switch (Num)
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


Character* CreateCharacter()
{
    string name;
    int choice;

    cout << " 캐릭터 이름을 입력하세요: ";
    cin >> name;

    while (true)
    {
        cout << " 직업을 선택하세요." << endl;
        cout << " 1. 전사" << endl;
        cout << " 2. 마법사" << endl;
        cout << " 3. 도적" << endl;
        cout << " 4. 궁수" << endl;
        cout << " 선택: ";

        if (!(cin >> choice)) // 여기서 입력 받고
        {
            system("cls");
            cout << "잘못된 입력입니다.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();

            continue;
        }

        switch (choice)
        {
        case 1:
            return new Warrior(name);
        case 2:
            return new Mage(name);
        case 3:
            return new Thief(name);
        case 4:
            return new Archer(name);
        default:
            system("cls");
            cout << "잘못된 입력입니다\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();
            continue;
        }
    }
}

int main()
{
    GameManager gameManager;
    Character* player = CreateCharacter();
    MainGame mainGame(player);
    
    cout << endl;
    cout << " 캐릭터 생성 완료! " << endl;
    player->Displaystatus();

    cin.get();

    while (true)
    {
        system("cls");

        cout << "============================" << endl;
        cout << "        TEXT RPG" << endl;
        cout << "============================" << endl;
        cout << " 1. 상태 보기" <<endl;
        cout << " 2. 전투 시작" << endl;
        cout << " 3. 인벤토리" << endl;
        cout << " 4. 상점" << endl;
        cout << " 5. 휴식" << endl;
        cout << " 72. 마왕성으로 향한다." << endl;
        cout << " 0. 게임 종료" << endl;
        cout << "============================" << endl;
        cout << " 선택: ";

        int menu;

        if (!(cin >> menu)) // 여기서 입력 받고
        {
            system("cls");
            cout << "잘못된 입력입니다.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();

            continue;
        }

        cin.ignore(1000, '\n');

        switch (menu)
        {
        case 1:
            system("cls");
            player->Displaystatus();
            cin.get();
            break;

        case 2:
        {
            int battle = gameManager.Battle(player, 1);
            cin.ignore(1000, '\n');

            if (battle == 1)
            {
                cout << "승리\n";
            }
            else if (battle == 2)
            {
                cout << "공멸\n";
            }
            else if (battle == 3)
            {
                cout << "패배\n";
            }
            else if (battle == 4)
            {
                cout << "도망\n";
            }
            else
            {
                cout << "잘못된 입력\n";
            }
            break;
        }
        case 3:
            mainGame.ShowInventoryPage(player);
            break;

        case 4:
            mainGame.ShowShopPage();
            break;
        case 5:
        {
            int hprecovery = static_cast<int>(player->Getmaxhp() * 0.4);
            int mprecovery = static_cast<int>(player->Getmaxmp() * 0.4);

            player->Sethp(player->Gethp() + hprecovery);
            player->Setmp(player->Getmp() + mprecovery);
            cout << "당신은 휴식을 취해 체력을 " << hprecovery << ", 마나를 " << mprecovery << " 회복했다.\n";
            cin.get();
            break;
        }
        case 72:
        {
            int ending = gameManager.Battle(player, 2);
            cin.ignore(1000, '\n');

            if (ending == 1)
            {
                cout << "진 엔딩\n";
                cin.get();
            }
            else if (ending == 2)
            {
                cout << "배드 엔딩\n";
                cin.get();
            }
            else if (ending == 3)
            {
                cout << "게임 오버\n";
                cin.get();
            }
            else
            {
                cout << "이 너머 레벨 업 필요하다.\n";
                cin.get();
            }

            break;
        }
        case 0:
            delete player;
            cout << " 게임을 종료합니다." << endl;
            return 0;

        default: 
            system("cls");
            cout << " 잘못된 입력입니다." << endl;
            cin.ignore();
            cin.get();
            continue;
        }
    }
}


void MainGame::ShowInventoryPage(Character* player)
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
            m_player->GetInventory()->ShowPlayerEquip(m_player);
            break;

        case 3:
            system("cls");
            player->Displaystatus();
            cin.ignore();
            cin.get();
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
        m_player->Sethp(m_player->Gethp() + 50);
        std::cout << "체력이 50 회복되었습니다." << std::endl;
    }
    else if (itemName == "MP 포션")
    {
        m_player->Setmp(m_player->Getmp() + 30);
        std::cout << "MP가 30 회복되었습니다." << std::endl;
    }
    else if (itemName == "공격력 증가 포션")
    {
        m_player->Setattack(m_player->Getattack() + 10);
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