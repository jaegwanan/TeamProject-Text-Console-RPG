// Character

#pragma once

#include<string>
#include<vector>

#include "Item.h"

class Character
{
private:
    static Character* instance;

    std::string name;
    int level;
    int hp;
    int maxhp;
    int attack;
    int experience;
    int gold;

    std::vector<Item*> inventory;

public:
    Character(std::string name);

    static Character* getInstance(std::string name = "");

    void displayStatus();
    void levelUp();
    void useItem(int index);
};