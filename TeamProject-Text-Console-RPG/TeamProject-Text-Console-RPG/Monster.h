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
    virtual std::string Getname() = 0;
    virtual int Gethp() = 0;
    virtual int Getattack() = 0;
    virtual void Takedamage(int damage) = 0;

    virtual ~Monster() {}
};

// Goblin
class Goblin : public Monster
{
public:
    Goblin(int level);

    std::string Getname() override;
    int Gethp() override;
    int Getattack() override;
    void Takedamage(int damage) override;
};

// Orc
class Orc : public Monster
{
public:
    Orc(int level);

    std::string Getname() override;
    int Gethp() override;
    int Getattack() override;
    void Takedamage(int damage) override;
};

// Troll
class Troll : public Monster
{
public:
    Troll(int level);

    std::string Getname() override;
    int Gethp() override;
    int Getattack() override;
    void Takedamage(int damage) override;
};

// Slime
class Slime : public Monster
{
public:
    Slime(int level);

    std::string Getname() override;
    int Gethp() override;
    int Getattack() override;
    void Takedamage(int damage) override;
};