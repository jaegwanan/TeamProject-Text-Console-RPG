// Item

#pragma once

#include<string>

using namespace std;

class Item
{
protected:
    string name;

public:
    virtual string getName() = 0;
    virtual void use(Character* character) = 0;

    virtual ~Item() {}
};

// HealthPotion
class HealthPotion : public Item
{
private:
    int healthRestore;

public:
    HealthPotion();

    string getName() override;
    void use(Character* character) override;
};

// AttackBoost
class AttackBoost : public Item
{
private:
    int attackIncrease;

public:
    AttackBoost();

    string getName() override;
    void use(Character* character) override;
};