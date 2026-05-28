// Battle.cpp

#include <iostream>
#include <string>
#include <cstdlib>

#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"

#include "UIManager.h"
#include "AchievementManager.h"

using namespace std;

void Basicattack(Character* player, Monster* monster)
{
    player->Basicattack(monster);
}

bool Pantierun(Character* player, int monsterlevel)
{
    int playerlevel = player->Getlevel();
    int pantierunrate = 65 + (playerlevel - monsterlevel) * 5;

    int randomvalue2 = rand() % 100 + 1;
    return randomvalue2 <= pantierunrate;
}

int Generatemonsterlevel(Character* player)
{
    int randomvalue2 = rand() % 100 + 1;
    int levelpoint = player->Getlevel();

    if (randomvalue2 > 80)
    {
        ++levelpoint;
        if (levelpoint > 10) levelpoint = 10;
        return levelpoint;
    }
    else if (20 < randomvalue2 && randomvalue2 <= 80) return levelpoint;
    else
    {
        --levelpoint;
        if (levelpoint <= 0) levelpoint = 1;
        return levelpoint;
    }
}

Monster* Generatemonster(Character* player)
{
    int randomvalue4 = rand() % 100 + 1;
    int level = Generatemonsterlevel(player);
    if (randomvalue4 <= 35) return new Goblin(level);
    else if (randomvalue4 <= 65) return new Orc(level);
    else if (randomvalue4 <= 85) return new Troll(level);
    else return new Slime(level);
}

int Percent(Monster* monster)
{
    int monsterhp = monster->Gethp();
    int monstermaxhp = monster->Getmaxhp();
    if (monstermaxhp <= 0) return 0;
    return (monsterhp * 100) / monstermaxhp;
}

void Monsterattack(Character* player, Monster* monster)
{
    int randomvalue6 = rand() % 100 + 1;
    if (randomvalue6 <= 60) monster->Basicattack(player);
    else
    {
        if (Percent(monster) < 50) monster->Specialattack(player);
        else monster->Basicattack(player);
    }
}

// ★ 에러 해결: Useitem이 achManager를 받도록 완벽 수정됨
bool Useitem(Character* player, AchievementManager* achManager)
{
    vector<Item>* bag = player->GetInventory()->GetBag();

    if (bag->empty())
    {
        cout << "사용할 아이템이 없습니다.\n";
        return false;
    }

    cout << "===== 아이템 목록 =====\n";
    for (int i = 0; i < bag->size(); ++i)
    {
        cout << i + 1 << ". " << bag->at(i).GetName() << " x" << bag->at(i).GetCount() << "\n";
    }

    int select;
    cout << "사용할 아이템 번호 : ";
    cin >> select;

    if (select <= 0 || select > bag->size()) return false;

    Item& item = bag->at(select - 1);
    string usedItemName = item.GetName();

    switch (item.GetType())
    {
    case ITEM::ITEM_HP_POTION:
        player->Sethp(player->Gethp() + item.GetAbility());
        cout << "HP가 " << item.GetAbility() << " 회복되었다.\n";
        break;
    case ITEM::ITEM_MP_POTION:
        player->Setmp(player->Getmp() + item.GetAbility());
        cout << "MP가 " << item.GetAbility() << " 회복되었다.\n";
        break;
    case ITEM::ITEM_ATTACK_POTION:
        player->Setattack(player->Getattack() + item.GetAbility());
        cout << "공격력이 " << item.GetAbility() << " 증가했다.\n";
        break;
    default:
        cout << "사용할 수 없는 아이템이다.\n";
        return false;
    }

    item.SetCount(item.GetCount() - 1);
    if (item.GetCount() <= 0) bag->erase(bag->begin() + (select - 1));

    // 업적 시스템 아이템 사용 카운트!
    achManager->UpdateItem(usedItemName);

    cin.clear();
    cin.ignore(1000, '\n');
    cin.get();
    return true;
}

void AddDropItem(Character* player, Item item)
{
    vector<Item>* playerBag = player->GetInventory()->GetBag();
    int existItem = player->GetInventory()->IsItemExist(item.GetName());

    if (existItem > -1)
    {
        playerBag->at(existItem).SetPrice(item.GetPrice());
        playerBag->at(existItem).SetCount(playerBag->at(existItem).GetCount() + 1);
    }
    else
    {
        item.SetCount(1);
        playerBag->push_back(item);
    }
}

Item CreateDropItem(string itemName)
{
    if (itemName == "고블린의 고추기름") return Item(ITEM::ITEM_EMPTY, "고블린의 고추기름", 5, 0, "고블린에게서 얻은 전리품", 1);
    else if (itemName == "슬라임 젤") return Item(ITEM::ITEM_EMPTY, "슬라임 젤", 3, 0, "슬라임에게서 얻은 끈적한 젤", 1);
    return Item(ITEM::ITEM_EMPTY, itemName, 1, 0, "정체불명의 전리품", 1);
}

void GameManager::Battle(Character* player, AchievementManager* achManager)
{
    Monster* monster = Generatemonster(player);
    int choice;
    bool autobattle = false;
    string skillname = player->Getskillname();
    string monstername = monster->Getname();
    int monsterlevel = monster->Getlevel();

    UIManager::PrintMonsterAppear(monstername);

    while (player->Gethp() > 0 && monster->Gethp() > 0)
    {
        system("cls");

        UIManager::DrawMonsterStatus(monster);
        UIManager::DrawPlayerStatus(player);
        UIManager::DrawBattleMenu();

        if (autobattle) choice = 5;
        else
        {
            if (!(cin >> choice))
            {
                system("cls");
                UIManager::PrintWrongInput();
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            cin.ignore(1000, '\n');
        }

        switch (choice)
        {
        case 1:
            Basicattack(player, monster);
            cin.get();
            break;
        case 2:
            if (player->Skill(monster)) cin.get();
            else
            {
                system("cls");
                cout << "MP가 부족해 스킬을 사용 할 수 없다.\n";
                cin.get();
                continue;
            }
            break;
        case 3:
            system("cls");
            // ★ 수동 아이템 사용 연동
            if (Useitem(player, achManager)) break;
            else
            {
                system("cls");
                cout << "아이템을 사용하지 않았다.\n";
                cin.get();
                continue;
            }
        case 4:
            if (Pantierun(player, monsterlevel))
            {
                system("cls");
                UIManager::PrintRunSuccess();
                achManager->UpdateRunAway();
                delete monster;
                return;
            }
            else
            {
                system("cls");
                UIManager::PrintRunFail();
                cin.get();
                break;
            }
        case 5: // ★ 에러 해결: case 5 내부에 중괄호 { } 추가됨
        {
            autobattle = true;
            int playerhp = player->Gethp();
            int playermp = player->Getmp();
            int monsterhp = monster->Gethp();
            int randomvalue = rand() % 100 + 1;
            int mp = 100;

            if (monsterhp < playerhp && playermp < mp)
            {
                Basicattack(player, monster);
                cin.get();
                break;
            }
            else if (monsterhp < playerhp && playermp >= mp)
            {
                if (player->Skill(monster)) { cin.get(); break; }
                else { system("cls"); cout << "MP가 부족해 스킬을 사용 할 수 없다.\n"; cin.get(); continue; }
            }
            else if (monsterhp >= playerhp && playermp < mp)
            {
                if (randomvalue > 70)
                {
                    system("cls");
                    // ★ 자동 아이템 사용 연동
                    if (Useitem(player, achManager)) break;
                    else { system("cls"); cout << "아이템을 사용하지 않았다.\n"; cin.get(); continue; }
                }
                else
                {
                    if (Pantierun(player, monsterlevel))
                    {
                        system("cls");
                        UIManager::PrintRunSuccess();
                        achManager->UpdateRunAway();
                        delete monster;
                        return;
                    }
                    else { system("cls"); UIManager::PrintRunFail(); cin.get(); break; }
                }
            }
            else if (monsterhp >= playerhp && playermp >= 100)
            {
                if (player->Skill(monster)) { cin.get(); break; }
                else { system("cls"); cout << "MP가 부족해 스킬을 사용 할 수 없다.\n"; cin.get(); continue; }
            }
            break;
        } // ★ case 5 중괄호 닫기
        default:
            system("cls");
            UIManager::PrintWrongInput();
            continue;
        }

        int hprecovery = (int)(player->Getmaxhp() * 0.05);
        int mprecovery = (int)(player->Getmaxmp() * 0.05);
        player->Sethp(player->Gethp() + hprecovery);
        player->Setmp(player->Getmp() + mprecovery);
        cout << "\n시간 경과에 따라 당신의 체력이 " << hprecovery << ", 마나가 " << mprecovery << " 회복 되었다.\n\n";
        cin.get();

        if (monster->Gethp() > 0) Monsterattack(player, monster);
    }

    if (player->Gethp() <= 0 && monster->Gethp() <= 0)
    {
        system("cls");
        cout << "당신은 " << monstername << "과(와) 공멸했다.\n";
        cin.get();
        player->Sethp(1);
    }
    else if (player->Gethp() <= 0)
    {
        system("cls");
        cout << "당신은 " << monstername << "에게 패배했다.\n";
        cin.get();
        player->Sethp(1);
    }
    else if (monster->Gethp() <= 0)
    {
        double randomvalue5 = (rand() % 41 + 80) / 100.0;
        system("cls");
        cout << "당신은 " << monstername << "에게 승리했다.\n";
        cin.get();

        // 몬스터 처치 업적 연동!
        achManager->UpdateKill(monstername);

        string item = monster->Getitemname();
        int exp = monster->Getexp();
        int gold = monster->Getgold();

        player->Gainexp(exp);

        // 레벨 업 업적 연동!
        achManager->UpdateLevel(player->Getlevel());

        int earnedGold = (int)(gold * randomvalue5);
        player->Setgold(player->Getgold() + earnedGold);
        cout << "당신은 " << exp << " 만큼의 경험치와 " << earnedGold << " 골드를 획득했다.\n";

        int randomvalue3 = rand() % 100 + 1;
        if (randomvalue3 >= 30)
        {
            Item dropItem = CreateDropItem(item);
            AddDropItem(player, dropItem);
            cout << "잘 찾아보니 " << monstername << "에게서 " << dropItem.GetName() << "을(를) 얻을 수 있었다.\n";
        }
        cin.get();
    }
    else
    {
        cout << "잘못된 접근 입니다.";
        delete monster;
        return;
    }
    delete monster;
    return;
}