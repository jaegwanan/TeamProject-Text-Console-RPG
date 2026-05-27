// Battle.cpp

#include <iostream>
#include <string>
#include <cstdlib>

#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"

#include "UIManager.h"

using namespace std;

void Basicattack(Character* player, Monster* monster)
{
    player->Basicattack(monster); //-----------------------------------------------------------------------------------------Character의 void Attack(Monster* monster) 오버라이드 요구합니다.
}


bool Pantierun(Character* player, int monsterlevel)
{
    int playerlevel = player->Getlevel(); // //----------------------------------------------------------------------------------------------Character의 레벨 게터 요구합니다.
    int pantierunrate = 65 + (playerlevel - monsterlevel) * 5; // 빤스런 수치

    int randomvalue2 = rand() % 100 + 1;

    if (randomvalue2 <= pantierunrate)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Generatemonsterlevel(Character* player)
{
    int randomvalue2 = rand() % 100 + 1;
    int levelpoint = player->Getlevel(); //---------------------------------------------------------------------------------------------------- 캐릭터 레벨게터

    if (randomvalue2 > 80)
    {
        ++levelpoint; // 20프로 확률로 가끔 더 강한 적과 전투
        if (levelpoint > 10) // 최대레벨 제한
        {
            levelpoint = 10;
        }
        return levelpoint;
    }
    else if (20 < randomvalue2 && randomvalue2 <= 80) // 60프로 확률로 같은 레벨 적과 전투
    {
        return levelpoint;
    }
    else // 20프로 확률로 적은 레벨과 전투
    {
        --levelpoint;
        if (levelpoint <= 0) //최소 레벨 제한
        {
            levelpoint = 1;
        }
        return levelpoint;
    }
}

Monster* Generatemonster(Character* player) // 몬스터 랜덤 생성 함수
{
    int randomvalue4 = rand() % 100 + 1;
    int level = Generatemonsterlevel(player); // 적 레벨 +-1 랜덤 함수
    if (randomvalue4 <= 35)
    {
        return new Goblin(level); // 35프로
    }

    else if (randomvalue4 <= 65)
    {
        return new Goblin(level); // 30프로
    }

    else if (randomvalue4 <= 85)
    {
        return new Goblin(level); // 20프로
    }
    else
    {
        return new Goblin(level); // 15프로
    }
}

int Percent(Monster* monster)
{
    int monsterhp = monster->Gethp();
    int monstermaxhp = monster->Getmaxhp();
    if (monstermaxhp <= 0)
    {
        return 0;
    }
    return (monsterhp * 100) / monstermaxhp;
}

void Monsterattack(Character* player, Monster* monster) // 이 함수 하나로 몬스터 AI를 완성
{
    int randomvalue6 = rand() % 100 + 1;
    if (randomvalue6 <= 60) // 60 퍼센트 확률로 일반공격
    {
        monster->Basicattack(player); // -----------------------------------------------------------------------------------------[몬스터]의 void Basicattack(Character* player) 요구
        //------------------------------------------------------------------------------------------------------플레이어에게 주는 데미지 판정과 공격이름 텍스트 등 전부 안에서 해결 할 것
    }
    else
    {
        if (Percent(monster) < 50) // 40 퍼센트 확률로 자신의 체력을 보고 5할 이하일 경우 특수 공격 사용
        {
            monster->Specialattack(player); // -----------------------------------------------------------------------------------------[몬스터]의 void Specialattack(Character* player) 요구
            //------------------------------------------------------------------------------------------------------플레이어에게 주는 데미지 판정과 공격이름 텍스트 등 전부 안에서 해결 할 것
        }
        else
        {
            monster->Basicattack(player); // 일반공격
        }
    }

}

bool Useitem(Character* player)
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
        cout << i + 1 << ". ";
        cout << bag->at(i).GetName();
        cout << " x" << bag->at(i).GetCount() << "\n";
    }

    int select;

    cout << "사용할 아이템 번호 : ";
    cin >> select;

    if (select <= 0 || select > bag->size())
    {
        return false;
    }

    Item& item = bag->at(select - 1);

    switch (item.GetType())
    {
    case ITEM::ITEM_HP_POTION:
        player->Sethp(player->Gethp() + item.GetAbility());
        cout << "HP가" << item.GetAbility() << "회복되었다.\n";
        break;

    case ITEM::ITEM_MP_POTION:
        player->Setmp(player->Getmp() + item.GetAbility());
        cout << "MP가" << item.GetAbility() << "회복되었다.\n";
        break;

    case ITEM::ITEM_ATTACK_POTION:
        player->Setattack(player->Getattack() + item.GetAbility());
        cout << "공격력이" << item.GetAbility() << "증가했다.\n";
        break;

    default:
        cout << "사용할 수 없는 아이템이다.\n";
        return false;
    }

    item.SetCount(item.GetCount() - 1);

    if (item.GetCount() <= 0)
    {
        bag->erase(bag->begin() + (select - 1));
    }
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
    if (itemName == "고블린의 고추기름")
    {
        return Item(ITEM::ITEM_EMPTY, "고블린의 고추기름", 5, 0, "고블린에게서 얻은 전리품", 1);
    }
    else if (itemName == "슬라임 젤")
    {
        return Item(ITEM::ITEM_EMPTY, "슬라임 젤", 3, 0, "슬라임에게서 얻은 끈적한 젤", 1);
    }

    return Item(ITEM::ITEM_EMPTY, itemName, 1, 0, "정체불명의 전리품", 1);
}

void GameManager::Battle(Character* player)
{
    Monster* monster = Generatemonster(player);

    int choice;
    bool autobattle = false;

    string monstername = monster->Getname();
    int monsterlevel = monster->Getlevel();
    string battleMessage = monstername + "이(가) 나타났다!";

    while (player->Gethp() > 0 && monster->Gethp() > 0)
    {
        // 매 턴마다 현재 HP/MP가 반영된 배틀 화면 + 선택 메뉴 출력
        UIManager::DrawBattleScreen(player, monster, battleMessage, true);

        if (autobattle == true)
        {
            choice = 5;
        }
        else
        {
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                battleMessage = "잘못된 입력입니다.";
                UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                cin.get();

                continue;
            }

            cin.ignore(1000, '\n');
        }

        switch (choice)
        {
        case 1:
        {
            Basicattack(player, monster);

            battleMessage = player->Getname() + "의 공격!";
            UIManager::DrawBattleScreen(player, monster, battleMessage, false);
            cin.get();

            break;
        }

        case 2:
        {
            if (player->Skill(monster))
            {
                battleMessage = player->Getskillname() + "을(를) 사용했다!";
                UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                cin.get();

                break;
            }
            else
            {
                battleMessage = "MP가 부족해 스킬을 사용할 수 없다.";
                UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                cin.get();

                continue;
            }
        }

        case 3:
        {
            system("cls");

            if (Useitem(player))
            {
                battleMessage = "아이템을 사용했다!";
                UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                cin.get();

                break;
            }
            else
            {
                battleMessage = "아이템을 사용하지 않았다.";
                UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                cin.get();

                continue;
            }
        }

        case 4:
        {
            if (Pantierun(player, monsterlevel))
            {
                battleMessage = "무사히 도망쳤다!";
                UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                cin.get();

                delete monster;
                return;
            }
            else
            {
                battleMessage = "도망치지 못했다.";
                UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                cin.get();

                break;
            }
        }

        case 5:
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

                battleMessage = "자동 전투: " + player->Getname() + "이(가) 공격했다!";
                UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                cin.get();

                break;
            }
            else if (monsterhp < playerhp && playermp >= mp)
            {
                if (player->Skill(monster))
                {
                    battleMessage = "자동 전투: " + player->Getskillname() + "을(를) 사용했다!";
                    UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                    cin.get();

                    break;
                }
                else
                {
                    battleMessage = "MP가 부족해 스킬을 사용할 수 없다.";
                    UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                    cin.get();

                    continue;
                }
            }
            else if (monsterhp >= playerhp && playermp < mp)
            {
                if (randomvalue > 70)
                {
                    system("cls");

                    if (Useitem(player))
                    {
                        battleMessage = "자동 전투: 아이템을 사용했다!";
                        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                        cin.get();

                        break;
                    }
                    else
                    {
                        battleMessage = "아이템을 사용하지 않았다.";
                        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                        cin.get();

                        continue;
                    }
                }
                else
                {
                    if (Pantierun(player, monsterlevel))
                    {
                        battleMessage = "자동 전투: 무사히 도망쳤다!";
                        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                        cin.get();

                        delete monster;
                        return;
                    }
                    else
                    {
                        battleMessage = "자동 전투: 도망치지 못했다.";
                        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                        cin.get();

                        break;
                    }
                }
            }
            else if (monsterhp >= playerhp && playermp >= 100)
            {
                if (player->Skill(monster))
                {
                    battleMessage = "자동 전투: " + player->Getskillname() + "을(를) 사용했다!";
                    UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                    cin.get();

                    break;
                }
                else
                {
                    battleMessage = "MP가 부족해 스킬을 사용할 수 없다.";
                    UIManager::DrawBattleScreen(player, monster, battleMessage, false);
                    cin.get();

                    continue;
                }
            }

            break;
        }

        default:
        {
            battleMessage = "잘못된 입력입니다.";
            UIManager::DrawBattleScreen(player, monster, battleMessage, false);
            cin.get();

            continue;
        }
        }

        // 플레이어 행동으로 몬스터가 죽었으면 바로 전투 종료 판정으로 이동
        if (monster->Gethp() <= 0)
        {
            break;
        }

        // 턴 종료 회복
        int hprecovery = static_cast<int>(player->Gethp() * 0.05);
        int mprecovery = static_cast<int>(player->Getmp() * 0.05);

        player->Sethp(player->Gethp() + hprecovery);
        player->Setmp(player->Getmp() + mprecovery);

        battleMessage =
            "시간 경과에 따라 체력 " +
            to_string(hprecovery) +
            ", 마나 " +
            to_string(mprecovery) +
            " 회복!";

        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
        cin.get();

        // 몬스터 턴
        if (monster->Gethp() > 0)
        {
            Monsterattack(player, monster);

            battleMessage = monster->Getname() + "의 공격!";
            UIManager::DrawBattleScreen(player, monster, battleMessage, false);
            cin.get();
        }
    }

    if (player->Gethp() <= 0 && monster->Gethp() <= 0)
    {
        battleMessage = "당신은 " + monstername + "과(와) 공멸했다.";
        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
        cin.get();

        player->Sethp(1);
    }
    else if (player->Gethp() <= 0)
    {
        battleMessage = "당신은 " + monstername + "에게 패배했다.";
        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
        cin.get();

        player->Sethp(1);
    }
    else if (monster->Gethp() <= 0)
    {
        int randomvalue3 = rand() % 100 + 1;
        double randomvalue5 = (rand() % 41 + 80) / 100.0;

        battleMessage = "당신은 " + monstername + "에게 승리했다!";
        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
        cin.get();

        string item = monster->Getitemname();
        int exp = monster->Getexp();
        int gold = monster->Getgold();

        player->Gainexp(exp);
        player->Setgold(player->Getgold() + gold * randomvalue5);

        battleMessage =
            "경험치 " +
            to_string(exp) +
            ", 골드 " +
            to_string(gold) +
            " 획득!";

        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
        cin.get();

        if (randomvalue3 >= 30)
        {
            Item dropItem = CreateDropItem(item);
            AddDropItem(player, dropItem);

            battleMessage =
                monstername +
                "에게서 " +
                dropItem.GetName() +
                "을(를) 얻었다!";

            UIManager::DrawBattleScreen(player, monster, battleMessage, false);
            cin.get();
        }
    }
    else
    {
        battleMessage = "잘못된 접근입니다.";
        UIManager::DrawBattleScreen(player, monster, battleMessage, false);
        cin.get();

        delete monster;
        return;
    }

    delete monster;
    return;
}
