// Character

#pragma once

#include<string>
#include<vector>

#include "Item.h"

using namespace std;

class Character
{
private:
    static Character* instance;

    string name;
    int level;
    int health;
    int maxHealth;
    int attack;
    int experience;
    int gold;

    vector<Item*> inventory;

public:
    Character(string name);

    static Character* getInstance(string name = "");

    void displayStatus();
    void levelUp();
    void useItem(int index);
};