#pragma once
#include "Character.h"

class Mage : public Character
{
public:
    Mage(std::string name);

    std::string Attackmessage() override;
    int Getrequiredexp() override;
    void Applylevelupstats() override;
};