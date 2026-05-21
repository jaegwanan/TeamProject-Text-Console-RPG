// Item

#pragma once

#include<string>

class Item
{
protected:
    std::string name;

public:
    virtual std::string getName() = 0;
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

    std::string getName() override;
    void use(Character* character) override;
};

// AttackBoost
class AttackBoost : public Item
{
private:
    int attackIncrease;

public:
    AttackBoost();

    std::string getName() override;
    void use(Character* character) override;
};