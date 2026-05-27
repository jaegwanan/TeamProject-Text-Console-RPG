#pragma once
#include "Character.h"

class Warrior : public Character
{
public:
    Warrior(std::string name);

    std::string Attackmessage() override;

    int Getrequiredexp() override;

    void Applylevelupstats() override;

    bool Skill(Monster* monster) override;

    std::string Getskillname() override;
};
