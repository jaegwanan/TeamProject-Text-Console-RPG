#pragma once
#include "Character.h"

class Archer : public Character
{
public:
    Archer(std::string name);

    std::string Attackmessage() override;
    int Getrequiredexp() override;
    void Applylevelupstats() override;
};