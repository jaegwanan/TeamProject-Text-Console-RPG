#include "Archer.h"
#include <iostream>
#include "string.h"

using namespace std;

Archer::Archer(std::string name) : Character(name)
{
    job = "궁수";
}

std::string Archer::Attackmessage()
{
    return "더블 샷!";
}

int Archer::Getrequiredexp()
{
    return 15 + level * level * level * 4;
}

void Archer::Applylevelupstats()
{
    maxhp += 15;
    hp = maxhp;
    maxmp += 12;
    mp = maxmp;
    attack += 10;
}

bool Archer::Skill(Monster* monster)
{
    if (mp < 20)
    {
        return false;
    }

    mp -= 20;

    cout << " 집중 사격!" << endl;

    int damage = attack * 2;

    int critChance = rand() % 100 + 1;

    if (critChance <= 40)
    {
        damage *= 2;

        cout << " 급소 적중!! 치명타!" << endl;
    }

    cout << damage << " 데미지!" << endl;

    monster->Takedamage(damage);

    return true;
}

string Archer::Getskillname()
{
    return "집중 사격";
}