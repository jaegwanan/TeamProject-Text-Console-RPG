#pragma once
#include "Character.h"

class Thief : public Character
{
public:
    Thief(std::string name);

    std::string Attackmessage() override;
    int Getrequiredexp() override;
    void Applylevelupstats() override;
};