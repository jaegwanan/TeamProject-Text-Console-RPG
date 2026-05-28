#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdlib>

#include "Character.h"
#include "GameManager.h"
#include "shop.h"
#include "ShopManager.h"
#include "Inventory.h"

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
    cout << "              [ ���̺� ���� Ȯ�� ]               " << endl;
    cout << "=================================================" << endl;
    for (int i = 1; i <= 4; i++)
    {
        string filename = "save" + to_string(i) + ".txt";
        ifstream fin(filename);
        if (fin) {
            string name, job;
            int level;
            fin >> name >> job >> level;
            cout << "  [" << i << "�� ����] " << name << " (Lv." << level << " " << job << ")" << endl;
            fin.close();
        }
        else {
            cout << "  [" << i << "�� ����] --- �� ���� ---" << endl;
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
    for (char& c : title) { if (c == ' ') c = '_'; }
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
    UIManager::PrintMessage(to_string(slot) + "�� ���Կ� ���������� �ڵ� ����Ǿ����ϴ�!");
}

Character* LoadGame(int slot, AchievementManager* achManager)
{
    string filename = "save" + to_string(slot) + ".txt";
    ifstream fin(filename);
    if (!fin) {
        UIManager::PrintMessage("�ش� ���Կ� ����� �����Ͱ� �����ϴ�!");
        return nullptr;
    }

    string name, job, title;
    int level, hp, maxhp, mp, maxmp, attack, exp, gold;

    fin >> name >> job >> level >> hp >> maxhp >> mp >> maxmp >> attack >> exp >> gold >> title;

    Character* player = nullptr;
    if (job == "����") player = new Warrior(name);
    else if (job == "������") player = new Mage(name);
    else if (job == "����") player = new Thief(name);
    else if (job == "�ü�") player = new Archer(name);
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
        for (char& c : title) { if (c == '_') c = ' '; }
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
    UIManager::PrintMessage(to_string(slot) + "�� ������ ���������� �ҷ��Խ��ϴ�!");
    return player;
}

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
        std::cout << "������ ���Խ��ϴ�." << std::endl;
        std::cout << "�������� �� �ൿ�� �����ϼ���." << std::endl;
        std::cout << "=================================================" << std::endl;
        std::cout << "1. ���� ���" << std::endl;
        std::cout << "2. ���� �ȱ�" << std::endl;
        std::cout << "0. ������ ���ư���" << std::endl;
        std::cout << "=================================================" << std::endl;
        std::cout << "�Է� : ";

        if (!(cin >> Num)) // ���⼭ �Է� �ް�
        {
            system("cls");
            cout << "�߸��� �Է��Դϴ�.\n";
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
            std::cout << "������ ���ư��ϴ�." << std::endl;
            std::cout << "=================================================" << std::endl;
            Sleep(500);
            return;

        default:
            std::cout << "=================================================" << std::endl;
            std::cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���." << std::endl;
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

    cout << " ĳ���� �̸��� �Է��ϼ���: ";
    cin >> name;

    while (true)
    {
        cout << " ������ �����ϼ���." << endl;
        cout << " 1. ����" << endl;
        cout << " 2. ������" << endl;
        cout << " 3. ����" << endl;
        cout << " 4. �ü�" << endl;
        cout << " ����: ";

        if (!(cin >> choice)) // ���⼭ �Է� �ް�
        {
            system("cls");
            cout << "�߸��� �Է��Դϴ�.\n";
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
            cout << "�߸��� �Է��Դϴ�\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();
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

            cout << " ���� ������ ���� ��ȣ�� �����ϼ��� (1~4, 0���� �ڷΰ���) : ";
            int slotChoice;
            if (!(cin >> slotChoice) || slotChoice < 0 || slotChoice > 4) {
                cin.clear(); cin.ignore(1000, '\n');
                UIManager::PrintMessage("�߸��� ���� ��ȣ�Դϴ�.");
                continue;
            }
            if (slotChoice == 0) continue;

            currentSaveSlot = slotChoice;
            system("cls");

            player = CreateCharacter();

            cout << endl << " ĳ���� ���� �Ϸ�! " << endl;
            player->Displaystatus();

            SaveGame(player, &achManager, currentSaveSlot);
            break;
        }
        else if (startMenuChoice == 2) {
            system("cls");
            ShowSaveSlots();

            cout << " �ҷ��� ���� ��ȣ�� �����ϼ��� (1~4, 0���� �ڷΰ���) : ";
            int slotChoice;
            if (!(cin >> slotChoice) || slotChoice < 0 || slotChoice > 4) {
                cin.clear(); cin.ignore(1000, '\n');
                UIManager::PrintMessage("�߸��� ���� ��ȣ�Դϴ�.");
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
        cout << " 1. ���� ����" <<endl;
        cout << " 2. ���� ����" << endl;
        cout << " 3. �κ��丮" << endl;
        cout << " 4. ����" << endl;
        cout << " 5. �޽�" << endl;
        cout << " 6. Īȣ ���� �� ���� Ȯ��" << endl;
        cout << " 7. ���� �����ϱ� (���� ����: " << currentSaveSlot << "��)" << endl;
        cout << " 72. ���ռ����� ���Ѵ�." << endl;
        cout << " 0. ���� ����" << endl;
        cout << "============================" << endl;
        cout << " ����: ";

        int menu;

        if (!(cin >> menu)) // ���⼭ �Է� �ް�
        {
            system("cls");
            cout << "�߸��� �Է��Դϴ�.\n";
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
            int battel = gameManager.Battle(player, 1, &achManager);
            cin.clear();
            cin.ignore(1000, '\n');


            if (battel == 1)
            {
                cout << "�¸�\n";
            }
            else if (battle == 2)
            {
                cout << "����\n";
            }
            else if (battle == 3)
            {
                cout << "�й�\n";
            }
            else if (battle == 4)
            {
                cout << "����\n";
            }
            else
            {
                cout << "�߸��� �Է�\n";
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
        case 6:
            achManager.EquipTitleMenu(player);
            break;
        case 7:
            system("cls");
            ShowSaveSlots();
            cout << " ��� ���Կ� �����ðڽ��ϱ�? (1~4, 0���� ���) : ";
            int saveChoice;
            if (!(cin >> saveChoice) || saveChoice < 0 || saveChoice > 4) {
                cin.clear(); cin.ignore(1000, '\n');
                UIManager::PrintMessage("�߸��� �Է��Դϴ�.");
                break;
            }
            if (saveChoice == 0) break;

            currentSaveSlot = saveChoice;
            SaveGame(player, &achManager, currentSaveSlot);
            break;
        case 72:
        {
            int ending = gameManager.Battle(player, 2, &achManager);
            cin.ignore(1000, '\n');

            if (ending == 1)
            {
                cout << "�� ����\n";
                cin.get();
            }
            else if (ending == 2)
            {
                cout << "��� ����\n";
                cin.get();
            }
            else if (ending == 3)
            {
                cout << "���� ����\n";
                cin.get();
            }
            else
            {
                cout << "�� �ʸ� ���� �� �ʿ��ϴ�.\n";
                cin.get();
            }

            break;
        }
        case 0:
            delete player;
            cout << " ������ �����մϴ�." << endl;
            return 0;

        default: 
            system("cls");
            cout << " �߸��� �Է��Դϴ�." << endl;
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
        std::cout << "�κ��丮�� �������ϴ�." << std::endl;
        std::cout << "���ϴ� �ൿ�� �����ϼ���." << std::endl;
        std::cout << "=================================================" << std::endl;
        std::cout << "1. ���� ����" << std::endl;
        std::cout << "2. ��� Ȯ�� / ��ü" << std::endl;
        std::cout << "3. ���� Ȯ��" << std::endl;
        std::cout << "0. ������ ���ư���" << std::endl;
        std::cout << "=================================================" << std::endl;
        std::cout << "�Է� : ";

        std::cin >> m_mainSelectNum;

        switch (m_mainSelectNum)
        {
        case 1:
            system("cls");
            m_player->GetInventory()->ShowPlayerBag();
            std::cout << "�ƹ� Ű�� �Է��ϸ� �κ��丮�� ���ư��ϴ�." << std::endl;
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
            std::cout << "������ ���ư��ϴ�." << std::endl;
            std::cout << "=================================================" << std::endl;
            Sleep(500);
            return;

        default:
            std::cout << "=================================================" << std::endl;
            std::cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���." << std::endl;
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
        std::cout << "����� �������� �����ϴ�." << std::endl;
        std::cout << "=================================================" << std::endl;
        return;
    }

    int randomIndex = rand() % bag->size();

    string itemName = bag->at(randomIndex).GetName();

    std::cout << "=================================================" << std::endl;
    std::cout << itemName << "��(��) �������� ����߽��ϴ�!" << std::endl;

    if (itemName == "HP ����")
    {
        m_player->Sethp(m_player->Gethp() + 50);
        std::cout << "ü���� 50 ȸ���Ǿ����ϴ�." << std::endl;
    }
    else if (itemName == "MP ����")
    {
        m_player->Setmp(m_player->Getmp() + 30);
        std::cout << "MP�� 30 ȸ���Ǿ����ϴ�." << std::endl;
    }
    else if (itemName == "���ݷ� ���� ����")
    {
        m_player->Setattack(m_player->Getattack() + 10);
        std::cout << "���ݷ��� 10 �����߽��ϴ�." << std::endl;
    }
    else
    {
        std::cout << "�� �������� ���� �� ����� �� �����ϴ�." << std::endl;
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
    std::cout << "����� ������ �ֽ��ϴ�." << std::endl;
    std::cout << "����� �ൿ�� �����ϼ���." << std::endl;
    std::cout << "������ �����Ϸ��� 0�� �Է��ϼ���." << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "1. ������ ����" << std::endl;
    std::cout << "2. �κ��丮 ����" << std::endl;
    std::cout << "3. ���� ����" << std::endl;
    std::cout << "4. ���� Ȯ��" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "�Է� : ";
}