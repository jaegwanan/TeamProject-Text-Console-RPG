#pragma once
#include "Character.h"

class Mage : public Character
{
public:
    Mage(std::string name);

    std::string Attackmessage() override;
    int Getrequiredexp() override;
    void Applylevelupstats() override;

    std::vector<std::string> Skill(Monster* monster) override;

    std::string Getskillname() override;
    vector<string> GetAsciiArt() override;
};

