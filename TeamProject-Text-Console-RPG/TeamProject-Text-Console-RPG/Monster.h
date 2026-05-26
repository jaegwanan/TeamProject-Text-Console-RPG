#pragma once
#include <string>
#include <iostream>
#include <random>
class Character;

class Monster
{
protected:
    std::string name;
    int maxhealth;
    int currenthealth; // Takedamage() ���� ���� ���� �߰����ּž� �������ϴ�
    int attack;
    int level;
    int exp;
    int gold;
    std::string itemname;

public:
    Monster(std::string name, int health, int attack)
        : name(name), maxhealth(health), currenthealth(health),attack(attack) {
    } //���� �� ������ �ڽĿ���

    //Get �Լ� ����
    std::string Getname() { return name; }
    int Getlevel() { return level; }
    int Getmaxhealth() { return maxhealth; }
    int Getcurrenthealth() { return currenthealth; }
    int Getattack() { return attack; }
    int Getexp() { return exp; }
    int Getgold() { return gold; }
    std::string Getitemname() { return itemname; }

    //���� �Լ� ����
    virtual void Basicattack(Character* player); //�Ϲݰ��� ����
    virtual void Specialattack(Character* player); //Ư������ ����
        
    void Takedamage(int damage);

    virtual ~Monster() {}
};

// Goblin
class Goblin : public Monster
{
public:
    Goblin(int level)
        : Monster("������", 0, 0) // �ӽð�
    {
        std::random_device rd;  // ���� �õ� ����
        std::mt19937 gen(rd()); // ���� ���� ����

        std::uniform_int_distribution<int> Healthrandom(level * 20, level * 30);
        std::uniform_int_distribution<int> Attackrandom(level * 5, level * 10);

        // �ʱ�ȭ
        int finalhealth = Healthrandom(gen);
        this->maxhealth = finalhealth;
        this->currenthealth = finalhealth;
        this->attack = Attackrandom(gen);

        this->level = level;
        this->exp = 15 + (level * 5);
        this->gold = 10 + (level * 3);
        this->itemname = "�������� ���߱⸧";
    }

    // ���� �ʿ�
    void Basicattack(Character* player) override;
    void Specialattack(Character* player) override;
};

// Orc
class Orc : public Monster
{
public:
    Orc(int level);

    void Basicattack(Character* player) override;
    void Specialattack(Character* player) override;
};

// Troll
class Troll : public Monster
{
public:
    Troll(int level);

    void Basicattack(Character* player) override;
    void Specialattack(Character* player) override;
};

// Slime
class Slime : public Monster
{
public:
    Slime(int level);

    void Basicattack(Character* player) override;
    void Specialattack(Character* player) override;
};