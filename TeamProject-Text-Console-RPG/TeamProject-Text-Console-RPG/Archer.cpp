#include "Archer.h"

Archer::Archer(std::string name) : Character(name)
{
    job = "±Ã¼ö";
}

std::string Archer::Attackmessage()
{
    return "´õºí ¼¦!";
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