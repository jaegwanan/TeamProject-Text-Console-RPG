// Battle.cpp

#include <iostream>
#include <string>
#include <cstdlib>

#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"

using namespace std;

void Basicattack(Character* player, Monster* monster)
{
    player->Basicattack(monster); //-----------------------------------------------------------------------------------------Character�� void Attack(Monster* monster) �������̵� �䱸�մϴ�.
}

bool Skill(Character* player, Monster* monster)
{
    cout << "��ų�� ����ߴ�.";
    return true; // //---------------------------Character�� bool Skill(Monster* monster); bool�� ������ ��� ������ true ���� �䱸�մϴ�. �������̵� ��Ź�մϴ�.
}

bool Pantierun(Character* player, int monsterlevel)
{
    int playerlevel = player->Getlevel(); // //----------------------------------------------------------------------------------------------Character�� ���� ���� �䱸�Դϴ�.
    int pantierunrate = 65 + (playerlevel - monsterlevel) * 5; // ������ ��ġ

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
    int levelpoint = player->Getlevel(); //---------------------------------------------------------------------------------------------------- ĳ���� ��������

    if (randomvalue2 > 80)
    {
        ++levelpoint; // 20���� Ȯ���� ���� �� ���� ���� ����
        if (levelpoint > 10) // �ִ뷹�� ����
        {
            levelpoint = 10;
        }
        return levelpoint;
    }
    else if(20 < randomvalue2 && randomvalue2 <= 80) // 60���� Ȯ���� ���� ���� ���� ����
    {
        return levelpoint;
    }
    else // 20���� Ȯ���� ���� ������ ����
    {
        --levelpoint;
        if (levelpoint <= 0) //�ּ� ���� ����
        {
            levelpoint = 1;
        }
        return levelpoint;
    }
}

Monster* Generatemonster(Character* player) // ���� ���� ���� �Լ�
{
    int randomvalue4 = rand() % 100 + 1;
    int level = Generatemonsterlevel(player); // �� ���� +-1 ���� �Լ�
    if (randomvalue4 <= 35)
    {
        return new Goblin(level); // 35����
    }

    else if (randomvalue4 <= 65)
    {
        return new Goblin(level); // 30����
    }

    else if (randomvalue4 <= 85)
    {
        return new Goblin(level); // 20����
    }
    else
    {
        return new Goblin(level); // 15����
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

void Monsterattack(Character* player, Monster* monster) // �� �Լ� �ϳ��� ���� AI�� �ϼ�
{
    int randomvalue6 = rand() % 100 + 1;
    if (randomvalue6 <= 60) // 60 �ۼ�Ʈ Ȯ���� �Ϲݰ���
    {
        monster->Basicattack(player); // -----------------------------------------------------------------------------------------[����]�� void Basicattack(Character* player) �䱸
        //------------------------------------------------------------------------------------------------------�÷��̾�� �ִ� ������ ������ �����̸� �ؽ�Ʈ �� ���� �ȿ��� �ذ� �� ��
    }
    else
    {
        if (Percent(monster) < 50) // 40 �ۼ�Ʈ Ȯ���� �ڽ��� ü���� ���� 5�� ������ ��� Ư�� ���� ���
        {
            monster->Specialattack(player); // -----------------------------------------------------------------------------------------[����]�� void Specialattack(Character* player) �䱸
            //------------------------------------------------------------------------------------------------------�÷��̾�� �ִ� ������ ������ �����̸� �ؽ�Ʈ �� ���� �ȿ��� �ذ� �� ��
        }
        else
        {
            monster->Basicattack(player); // �Ϲݰ���
        }
    }

}

bool Useitem()
{
    cout << "�������� ����ߴ�.\n";
    return true;
}// ���߿� ���� ��----------------------------------------------------------------------------------------------------------------------Useiitem(); �Լ� �䱸�մϴ�.
void Additem(string item)
{
    cout << item << "\n";
}//---------------------------------------------------------------------------------------------------------------------------Additem() �Լ� �䱸�մϴ�.


void GameManager::Battle(Character* player)
{
    Monster* monster = Generatemonster(player); // ���� ���� ���� �Լ��� �� ���� ���� Ȯ���� ����

    int choice;// �Լ� ������ ����� ���� ����

    string skillname = player->Getskillname();

    string monstername = monster->Getname(); //���� �������� ���͸� �����Լ��� ����
    int monsterlevel = monster->Getlevel();

    cout << monstername << "��(��) ��Ÿ����.";
    cin.clear();
    cin.ignore(1000, '\n');
    cin.get();

    while (player->Gethp() > 0 && monster->Gethp() > 0) // //---------------------------------------------------------------------------------------------- �÷��̾� ü�°��� ���� ü�� ���� �䱸�մϴ�.
        // ���Ϲ����� �ݺ�, ���ο��� continue ���� ����� �ٽ� ����
    {
        system("cls"); // �ѹ� ���� ����

        // //---------------------------------------------------------------------------------------------- �� UI + �ƽ�Ű��Ʈ �Լ��䱸�մϴ�.


        // //---------------------------------------------------------------------------------------------- �Ʊ� UI + �ƽ�Ű��Ʈ �Լ� �䱸�մϴ�.

        cout << "1. ����\n";
        cout << "2. " << skillname << "\n";
        cout << "3. �������� ���\n";
        cout << "4. ����\n";
        cout << "5. �ڵ����\n";

        if (!(cin >> choice)) // ���⼭ �Է� �ް�
        {
            system("cls");
            cout << "�߸��� �Է��Դϴ�.\n";
            cin.clear();
            cin.ignore(1000, '\n');

            continue;
        }

    switch (choice)
    {
    case 1: // ������ ����
    {
        int randomvalue = rand() % 100 + 1;

        if (randomvalue > 50)
        {
        case 1:
            Basicattack(player, monster); // �Ϲ� ���� �Լ�
            break;

        case 2:
        {
            if (Skill(player, monster)) // ��ų ��� ������ break�� �� �Ѿ
            {
                break;
            }
            else // ��ų ��� ���н� �� �Ҹ� ���� continue���� �ٽ� ����
            {
                system("cls");
                cout << "MP�� ������ ��ų�� ��� �� �� ����.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                cin.get();
                continue;
            }
        }
        case 3:
        {
            system("cls");
            //------------------------------------------------------------------------------------------������ ��� �Լ� bool UseItem(); ��� ������ ���� true �䱸�մϴ�.
            if (Useitem()) // ������ ��� ������ break�� �� �Ѿ
            {
                break;
            }
            else // ������ ��� ���н� �� �Ҹ� ���� continue���� �ٽ� ����
            {
                system("cls");
                cout << "�������� ������� �ʾҴ�.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                cin.get();
                continue;
            }
        }

        case 4:
        {
            if (Pantierun(player, monsterlevel))
            {
                system("cls");
                cout << "������ �����ƴ�.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                cin.get();
                delete monster;
                return;
            }
            else // ���� ���� �� �� �Ҹ�
            {
                system("cls");
                cout << "����ġ�� �� �ߴ�.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                cin.get();
                break;
            }
        }
        case 5: // ������ �ڵ�
        {
            int playerhp = player->Gethp(); //----------------------------------------------------------------------------------------------Character�� ���� HP ���� �䱸�Դϴ�.
            int playermp = player->Getmp(); // //----------------------------------------------------------------------------------------------Character�� ���� HP ���� �䱸�Դϴ�.
            int monsterhp = monster->Gethp(); // //----------------------------------------------------------------------------------------------monster�� ���� HP ���� �䱸�Դϴ�.
            int randomvalue = rand() % 100 + 1;
            int mp = 100; // �� ģ���� �ٲ۴ٸ�

            if (monsterhp < playerhp && playermp < mp) // ���� ü���� �÷��̾�� ����&& �÷��̾� MP�� 100���� ������ �Ϲݰ���
            {
                Basicattack(player, monster);
                break;
            }
            else if (monsterhp < playerhp && playermp >= mp) // ���� ü���� �÷��̾� ���� ����&& �÷��̾� MP�� 100���� ������ ��ų���
            {
                if (Skill(player, monster))
                {
                    break;
                }
                else
                {
                    system("cls");
                    cout << "MP�� ������ ��ų�� ��� �� �� ����.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin.get();
                    continue;
                }
            }
            else if (monsterhp >= playerhp && playermp < mp) // ���� ü���� �÷��̾� ���� ����&& �÷��̾� MP�� 100���� ������
            {
                if (randomvalue > 70) // 70 �ۼ�Ʈ Ȯ���� ������ ���
                {
                    system("cls");
                    if (Useitem()) // ������ ��� ������ break�� �� �Ѿ
                    {
                        break;
                    }
                    else
                    {
                        system("cls");
                        cout << "�������� ������� �ʾҴ�.\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin.get();
                        continue;
                    }
                }
                else
                {
                    if (Pantierun(player, monsterlevel)) // 30�ۼ�Ʈ Ȯ���� ���� ����
                    {
                        system("cls");
                        cout << "������ �����ƴ�.\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin.get();
                        delete monster;
                        return;
                    }
                    else // ���� ���� �� �� �Ҹ�
                    {
                        system("cls");
                        cout << "����ġ�� �� �ߴ�.\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin.get();
                        break;
                    }
                }
            }
            else if (monsterhp >= playerhp && playermp >= 100) // ���� ü���� �÷��̾� ���� ����&& �÷��̾� MP�� 100���� ������ ��ų���
            {
                if (Skill(player, monster))
                {
                    break;
                }
                else
                {
                    system("cls");
                    cout << "MP�� ������ ��ų�� ��� �� �� ����.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin.get();
                    continue;
                }
            }

            break;
        } // �ڵ����� ���� �ϼ�
        default:
        {
            system("cls");
            cout << "�߸��� �Է��Դϴ�.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();
            continue;
        }
        } // ����ġ ��
        if (monster->Gethp() > 0)
        {
            Monsterattack(player, monster);
        }
    } // ���Ϲ� ��


    if (player->Gethp() <= 0 && monster->Gethp() <= 0) // ���࿡ ���࿡ ���� �����ε� ���ÿ� ü���� 0�� �ǰ� ���´ٸ�...? �� �̳� ü���� �ڿ����� ����ϴ� ��ų?
    {
        system("cls");
        cout << "����� " << monstername << "��(��) �����ߴ�.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cin.get();
        player->Sethp(1);
    }
    else if (player->Gethp() <= 0)
    {
        system("cls");
        cout << "����� " << monstername << "���� �й��ߴ�.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cin.get();
        player->Sethp(1);//-----------------------------------------------------------------------------------------------------------------------ĳ���� hp ����
    }
    else if (monster->Gethp() <= 0)
    {
        int randomvalue3 = rand() % 100 + 1;
        double randomvalue5 = (rand() % 41 + 80) / 100.0;
        system("cls");
        //  --------------------------------------------------------------------------------------------------------------------------------------------------���� �ý���[����] ī���� �Լ�
        cout << "����� " << monstername << "���� �¸��ߴ�.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cin.get();
        string item = monster->Getitemname(); //-------------------------------------------------------------------------------------------------���Ϳ��� ������ �̸� �޾ƿ��� �Լ� �䱸�մϴ�.
        int exp = monster->Getexp(); // //---------------------------------------------------------------------------------------------------------------------- ���� ����ġ ���� �䱸�մϴ�.
        int gold = monster->Getgold(); // //-------------------------------------------------------------------------------------------------------------------- ���� ����ġ ���� �䱸�մϴ�.
        player->Gainexp(exp); //-------------------------------------------------------------------------------------------------------------- ����ġ ����/���� �䱸�մϴ�.
        ////-------------------------------------------------------------------------------------------------------------------------------------- ���Ϳ� maxexp ������ ������ �Լ� �ҷ����ּ���.
        player->Setgold(player->Getgold() + gold * randomvalue5); //���� ��Ʈ���̱⿡ �Ҽ��� �ڵ� ��ȯ----------------------------------------------------------------- ��� ����/���� �䱸�մϴ�.
        cout << "����� " << exp << " ��ŭ�� ����ġ�� " << gold << " ��带 ȹ���ߴ�.\n";
        if (randomvalue3 >= 30)
        {
            player->Additem(item);
            cout << "�� ã�ƺ��� " << monstername << "���Լ�" << item << "��(��) ���� �� �־���.\n";
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cin.get();
    }
    else
    {
        cout << "�߸��� ���� �Դϴ�.";
        delete monster;
        return;
    }
    delete monster;
    return;
}
