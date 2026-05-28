#include "Warrior.h"
#include <iostream>
#include "string.h"

using namespace std;

Warrior::Warrior(std::string name) : Character(name)
{
    job = "전사";
}

std::string Warrior::Attackmessage()
{
    return "양손검 휘두르기!";
}

int Warrior::Getrequiredexp()
{
    return 5 + level * level * level * 9;
}

void Warrior::Applylevelupstats()
{
    maxhp += 30;
    hp = maxhp;
    maxmp += 5;
    mp = maxmp;
    attack += 7;
}

bool Warrior::Skill(Monster* monster)
{
    if (mp < 20)
    {
        return false;
    }

    mp -= 20;

    int damage = attack * 2;

    cout << " 파워 스트라이크!" << endl;

    monster->Takedamage(damage);

    return true;
}

string Warrior::Getskillname()
{
    return "파워 스트라이크";
}

vector<string> Warrior::GetAsciiArt()
{
    return {
  "   /^\\\\      /\\\\",
  "  |###| <==|==|",
  " /|###|\\\\    ||",
  "   / \\\\"
    };
}