#include "Warrior.h"

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