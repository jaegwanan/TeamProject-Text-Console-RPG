#include "Mage.h"

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