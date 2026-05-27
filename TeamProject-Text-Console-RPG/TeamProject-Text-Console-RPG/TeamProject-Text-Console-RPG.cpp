#include <iostream>
#include <string>
#include <ctime>

#include "Character.h"
#include "GameManager.h"

#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Archer.h"

using namespace std;

class Warrior;
class Mage;
class Thief;
class Archer;

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
    
    cout << endl;
    cout << " 캐릭터 생성 완료! " << endl;
    player->Displaystatus();

    cin.ignore();
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
        cout << " 4. 게임 종료" << endl;
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

        switch (menu)
        {
        case 1:
            system("cls");
            player->Displaystatus();
            cin.ignore();
            cin.get();
            break;

        case 2:
            gameManager.Battle(player);
            break;

        case 3:
            // gameManager.displayInventory(player);
            break;

        case 4:
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
