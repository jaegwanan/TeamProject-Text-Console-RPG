#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#include "Character.h"
#include "GameManager.h"
#include "shop.h"
#include "ShopManager.h"

#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Archer.h"

#include "UIManager.h"
#include "AchievementManager.h"

using namespace std;

class Warrior;
class Mage;
class Thief;
class Archer;


void ShowSaveSlots()
{
    cout << "=================================================" << endl;
    cout << "              [ 세이브 슬롯 확인 ]               " << endl;
    cout << "=================================================" << endl;
    for (int i = 1; i <= 4; i++)
    {
        string filename = "save" + to_string(i) + ".txt";
        ifstream fin(filename);
        if (fin) {
            string name, job;
            int level;
            fin >> name >> job >> level;
            cout << "  [" << i << "번 슬롯] " << name << " (Lv." << level << " " << job << ")" << endl;
            fin.close();
        }
        else {
            cout << "  [" << i << "번 슬롯] --- 빈 슬롯 ---" << endl;
        }
    }
    cout << "=================================================" << endl;
}

void SaveGame(Character* player, AchievementManager* achManager, int slot)
{
    string filename = "save" + to_string(slot) + ".txt";
    ofstream fout(filename);
    if (!fout) return;

    fout << player->Getname() << endl;
    fout << player->Getjob() << endl;
    fout << player->Getlevel() << endl;
    fout << player->Gethp() << endl;
    fout << player->Getmaxhp() << endl;
    fout << player->Getmp() << endl;
    fout << player->Getmaxmp() << endl;
    fout << player->Getattack() << endl;
    fout << player->Getexp() << endl;
    fout << player->Getgold() << endl;

    string title = player->getActiveTitle();
    if (title.empty()) title = "None";
    for (char& c : title) { if (c == ' ') c = '_'; } // 띄어쓰기 보호
    fout << title << endl;

    fout << achManager->GetRunAwayCount() << endl;

    auto& killStats = achManager->GetKillStats();
    fout << killStats.size() << endl;
    for (auto& pair : killStats) {
        string safeName = pair.first;
        for (char& c : safeName) { if (c == ' ') c = '_'; }
        fout << safeName << " " << pair.second << endl;
    }

    auto& itemStats = achManager->GetItemStats();
    fout << itemStats.size() << endl;
    for (auto& pair : itemStats) {
        string safeName = pair.first;
        for (char& c : safeName) { if (c == ' ') c = '_'; }
        fout << safeName << " " << pair.second << endl;
    }

    auto& achList = achManager->GetAchievementList();
    fout << achList.size() << endl;
    for (auto& ach : achList) {
        fout << ach.isUnlocked << " ";
    }
    fout << endl;

    fout.close();
    UIManager::PrintMessage(to_string(slot) + "번 슬롯에 성공적으로 자동 저장되었습니다!");
}

Character* LoadGame(int slot, AchievementManager* achManager)
{
    string filename = "save" + to_string(slot) + ".txt";
    ifstream fin(filename);
    if (!fin) {
        UIManager::PrintMessage("해당 슬롯에 저장된 데이터가 없습니다!");
        return nullptr;
    }

    string name, job, title;
    int level, hp, maxhp, mp, maxmp, attack, exp, gold;

    fin >> name >> job >> level >> hp >> maxhp >> mp >> maxmp >> attack >> exp >> gold >> title;

    Character* player = nullptr;
    if (job == "전사") player = new Warrior(name);
    else if (job == "마법사") player = new Mage(name);
    else if (job == "도적") player = new Thief(name);
    else if (job == "궁수") player = new Archer(name);
    else player = new Warrior(name);

    player->Setlevel(level);
    player->Setmaxhp(maxhp);
    player->Sethp(hp);
    player->Setmaxmp(maxmp);
    player->Setmp(mp);
    player->Setattack(attack);
    player->Setexp(exp);
    player->Setgold(gold);

    if (title != "None") {
        for (char& c : title) { if (c == '_') c = ' '; } // 띄어쓰기 복구
        player->setActiveTitle(title);
    }

    int runAway, killSize, itemSize, achSize;
    if (fin >> runAway) {
        achManager->GetRunAwayCount() = runAway;

        fin >> killSize;
        for (int i = 0; i < killSize; i++) {
            string safeName; int count;
            fin >> safeName >> count;
            for (char& c : safeName) { if (c == '_') c = ' '; }
            achManager->GetKillStats()[safeName] = count;
        }

        fin >> itemSize;
        for (int i = 0; i < itemSize; i++) {
            string safeName; int count;
            fin >> safeName >> count;
            for (char& c : safeName) { if (c == '_') c = ' '; }
            achManager->GetItemStats()[safeName] = count;
        }

        fin >> achSize;
        auto& achList = achManager->GetAchievementList();
        for (int i = 0; i < achSize; i++) {
            bool unlocked;
            fin >> unlocked;
            if (i < achList.size()) achList[i].isUnlocked = unlocked;
        }
    }

    fin.close();
    UIManager::PrintMessage(to_string(slot) + "번 슬롯을 성공적으로 불러왔습니다!");
    return player;
}

MainGame::MainGame(Character* player) : m_player(player), m_shop(new Shop()), m_mainSelectNum(0) {}
MainGame::~MainGame() { delete m_shop; }

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

        if (!(cin >> Num))
        {
            system("cls");
            cout << "잘못된 입력입니다.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (Num)
        {
        case 1: m_shop->ShopBuyItemPage(m_player); break;
        case 2: m_shop->ShopSellItemPage(m_player); break;
        case 0:
            std::cout << "=================================================" << std::endl;
            std::cout << "마을로 돌아갑니다." << std::endl;
            std::cout << "=================================================" << std::endl;
            return;
        default:
            std::cout << "=================================================" << std::endl;
            std::cout << "잘못 입력했습니다. 다시 입력하세요." << std::endl;
            std::cout << "=================================================" << std::endl;
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

        if (!(cin >> choice))
        {
            system("cls");
            cout << "잘못된 입력입니다.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1: return new Warrior(name);
        case 2: return new Mage(name);
        case 3: return new Thief(name);
        case 4: return new Archer(name);
        default:
            system("cls");
            cout << "잘못된 입력입니다\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
    }
}

int main()
{
    AchievementManager achManager;
    GameManager gameManager;
    Character* player = nullptr;

    int currentSaveSlot = 1;

    while (true)
    {
        int startMenuChoice = UIManager::ShowTitleScreen();

        if (startMenuChoice == 1) {
            system("cls");
            ShowSaveSlots();

            cout << " 새로 시작할 슬롯 번호를 선택하세요 (1~4, 0번은 뒤로가기) : ";
            int slotChoice;
            if (!(cin >> slotChoice) || slotChoice < 0 || slotChoice > 4) {
                cin.clear(); cin.ignore(1000, '\n');
                UIManager::PrintMessage("잘못된 슬롯 번호입니다.");
                continue;
            }
            if (slotChoice == 0) continue;

            currentSaveSlot = slotChoice;
            system("cls");

            player = CreateCharacter();

            cout << endl << " 캐릭터 생성 완료! " << endl;
            player->Displaystatus();

            SaveGame(player, &achManager, currentSaveSlot);

            break;
        }
        else if (startMenuChoice == 2) {
            system("cls");
            ShowSaveSlots();

            cout << " 불러올 슬롯 번호를 선택하세요 (1~4, 0번은 뒤로가기) : ";
            int slotChoice;
            if (!(cin >> slotChoice) || slotChoice < 0 || slotChoice > 4) {
                cin.clear(); cin.ignore(1000, '\n');
                UIManager::PrintMessage("잘못된 슬롯 번호입니다.");
                continue;
            }
            if (slotChoice == 0) continue;

            currentSaveSlot = slotChoice;

            player = LoadGame(currentSaveSlot, &achManager);

            if (player != nullptr) break;
        }
        else if (startMenuChoice == 3) {
            achManager.DisplayStatsAndTitles();
        }
        else if (startMenuChoice == 4) {
            return 0;
        }
        else {
            UIManager::PrintWrongInput();
        }
    }

    MainGame mainGame(player);

    while (true)
    {
        system("cls");

        cout << "============================" << endl;
        cout << "        TEXT RPG" << endl;
        cout << "============================" << endl;

        if (player != nullptr) {
            if (!player->getActiveTitle().empty())
                cout << "  " << player->getActiveTitle() << " " << player->Getname() << "님 환영합니다!" << endl;
            else
                cout << "  " << player->Getname() << "님 환영합니다!" << endl;
        }

        cout << "----------------------------" << endl;
        cout << " 1. 상태 보기" << endl;
        cout << " 2. 전투 시작" << endl;
        cout << " 3. 인벤토리" << endl;
        cout << " 4. 상점" << endl;
        cout << " 5. 칭호 장착 및 업적 확인" << endl;
        cout << " 6. 게임 저장하기 (현재 슬롯: " << currentSaveSlot << "번)" << endl;
        cout << " 0. 게임 종료" << endl;
        cout << "============================" << endl;
        cout << " 선택: ";

        int menu;

        if (!(cin >> menu))
        {
            system("cls");
            cout << "잘못된 입력입니다.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (menu)
        {
        case 1:
            system("cls");
            player->Displaystatus();
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\n(돌아가려면 아무 키나 누르세요) ▼";
            cin.get();
            break;
        case 2:
            gameManager.Battle(player, &achManager);
            break;
        case 3:
            mainGame.ShowInventoryPage(player);
            break;
        case 4:
            mainGame.ShowShopPage();
            break;
        case 5:
            achManager.EquipTitleMenu(player);
            break;
        case 6: // 수동 게임 저장 (업적 매니저 포함)
            system("cls");
            ShowSaveSlots();
            cout << " 어느 슬롯에 덮어씌우시겠습니까? (1~4, 0번은 취소) : ";
            int saveChoice;
            if (!(cin >> saveChoice) || saveChoice < 0 || saveChoice > 4) {
                cin.clear(); cin.ignore(1000, '\n');
                UIManager::PrintMessage("잘못된 입력입니다.");
                break;
            }
            if (saveChoice == 0) break;

            currentSaveSlot = saveChoice;
            SaveGame(player, &achManager, currentSaveSlot);
            break;
        case 0:
            delete player;
            cout << " 게임을 종료합니다." << endl;
            return 0;
        default:
            system("cls");
            cout << " 잘못된 입력입니다." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
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
        case 2: m_player->GetInventory()->ShowPlayerEquip(); break;
        case 3:
            system("cls");
            player->Displaystatus();
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();
            break;
        case 0:
            std::cout << "=================================================" << std::endl;
            std::cout << "마을로 돌아갑니다." << std::endl;
            std::cout << "=================================================" << std::endl;
            return;
        default:
            std::cout << "=================================================" << std::endl;
            std::cout << "잘못 입력했습니다. 다시 입력하세요." << std::endl;
            std::cout << "=================================================" << std::endl;
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