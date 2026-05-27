#include "Thief.h"

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