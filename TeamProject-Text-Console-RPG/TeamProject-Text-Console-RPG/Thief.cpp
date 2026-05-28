#include "Thief.h"
#include <iostream>
#include "string.h"

using namespace std;

Thief::Thief(std::string name) : Character(name)
{
    job = "도적";
}

std::string Thief::Attackmessage()
{
    return "수리검 던지기!";
}

int Thief::Getrequiredexp()
{
    return 10 + level * level * level * 6;
}

void Thief::Applylevelupstats()
{
    maxhp += 20;
    hp = maxhp;
    maxmp += 10;
    mp = maxmp;
    attack += 15;
}

bool Thief::Skill(Monster* monster)
{
    if (mp < 25)
    {
        return false;
    }

    mp -= 25;

    cout << " 연속베기!" << endl;

    int totalDamage = 0;

    for (int i = 0; i < 3; i++)
    {
        int damage = attack * 0.7; 

        int critChance = rand() % 100 + 1;

        if (critChance <= 30)
        {
            damage *= 2;
            cout << " 치명타! ";
        }

        cout << damage << " 데미지!" << endl;
        monster->Takedamage(damage);

        totalDamage += damage;
    }

    cout << " 총 " << totalDamage << " 데미지!" << endl;
    return true;
}

string Thief::Getskillname()
{
    return "연속베기";
}

vector<string> Thief::GetAsciiArt()
{
    return {
"   .--.    /\\\\",
"  |####|  /__\\\\",
" /|####|\\\\  ||",
"    /\\\\"
    };
}
