// Monster

#pragma once

#include<string>

class Monster
{
protected:
    std::string name;
    int health;
    int attack;

public:
    virtual std::string getName() = 0;
    virtual int getHealth() = 0;
    virtual int getAttack() = 0;
    virtual void takeDamage(int damage) = 0;

    virtual ~Monster() {}
};

// Goblin
class Goblin : public Monster
{
public:
    Goblin(int level);

    std::string getName() override;
    int getHealth() override;
    int getAttack() override;
    void takeDamage(int damage) override;
};

// Orc
class Orc : public Monster
{
public:
    Orc(int level);

    std::string getName() override;
    int getHealth() override;
    int getAttack() override;
    void takeDamage(int damage) override;
};

// Troll
class Troll : public Monster
{
public:
    Troll(int level);

    std::string getName() override;
    int getHealth() override;
    int getAttack() override;
    void takeDamage(int damage) override;
};

// Slime
class Slime : public Monster
{
public:
    Slime(int level);

    std::string getName() override;
    int getHealth() override;
    int getAttack() override;
    void takeDamage(int damage) override;
};