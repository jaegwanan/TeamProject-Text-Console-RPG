#include "Mage.h"
#include <iostream>
#include "string.h"

using namespace std;

Mage::Mage(std::string name) : Character(name)
{
    job = "마법사";
}

std::string Mage::Attackmessage()
{
    return "파이어 볼!";
}

int Mage::Getrequiredexp()
{
    return 20 + level * level * level * 3;
}

void Mage::Applylevelupstats()
{
    maxhp += 10;
    hp = maxhp;
    maxmp += 30;
    mp = maxmp;
    attack += 9;
}

bool Mage::Skill(Monster* monster)
{
    if (mp < 30)
    {
        return false;
    }

    mp -= 30;

    int damage = attack * (3 + rand() % 3);

    cout << " 파이어 볼!" << endl;

    monster->Takedamage(damage);

    return true;
}

string Mage::Getskillname()
{
    return "파이어 볼";
}

vector<string> Mage::GetAsciiArt()
{
    return {
 "    /\\\\      *",
 "   /__\\\\    /|",
 "  |####|   /_|",
 "    /\\\\"
    };
}
