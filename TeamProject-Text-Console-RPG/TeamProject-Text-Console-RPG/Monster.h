#pragma once
#include <string>
#include <iostream>
#include <random>
class Character;

class Monster
{
protected:
    std::string name;
    int maxhp;
    int hp; // Takedamage() ���� ���� ���� �߰����ּž� �������ϴ�
    int attack;
    int level;
    int exp;
    int gold;
    std::string itemname;

public:
    Monster(std::string name, int health, int attack)
        : name(name), maxhp(health), hp(health),attack(attack) {
    } //���� �� ������ �ڽĿ���

    //Get Set
    std::string Getname() { return name; }
    int Getlevel() { return level; }
    int Getmaxhp() { return maxhp; }
    int Gethp() { return hp; }
    int Getattack() { return attack; }
    int Getexp() { return exp; }
    int Getgold() { return gold; }
    std::string Getitemname() { return itemname; }

    void Setname(std::string name) { this->name = name; }
    void Setmaxhp(int maxhp) { this->maxhp = maxhp; }
    void Sethp(int hp) { this->hp = hp; }
    void Setattack(int attack) { this->attack = attack; }
    void Setlevel(int level) { this->level = level; }
    void Setexp(int exp) { this->exp = exp; }
    void Setgold(int gold) { this->gold = gold; }
    void Setitemname(std::string itemname) { this->itemname = itemname; }

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
        this->maxhp = finalhealth;
        this->hp = finalhealth;
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
    Orc(int level)
        : Monster("��ũ", 0, 0) // �ӽð�
    {
        std::random_device rd;  // ���� �õ� ����
        std::mt19937 gen(rd()); // ���� ���� ����

        std::uniform_int_distribution<int> Healthrandom(level * 20, level * 30);
        std::uniform_int_distribution<int> Attackrandom(level * 7, level * 12);

        // �ʱ�ȭ
        int finalhealth = Healthrandom(gen);
        this->maxhp = finalhealth;
        this->hp = finalhealth;
        this->attack = Attackrandom(gen);

        this->level = level;
        this->exp = 15 + (level * 5);
        this->gold = 10 + (level * 3);
        this->itemname = "��ũ�� �ܵ���̶�";
    }

    void Basicattack(Character* player) override;
    void Specialattack(Character* player) override;
};

// Troll
class Troll : public Monster
{
public:
    Troll(int level)
        : Monster("Ʈ��", 0, 0) // �ӽð�
    {
        std::random_device rd;  // ���� �õ� ����
        std::mt19937 gen(rd()); // ���� ���� ����

        std::uniform_int_distribution<int> Healthrandom(level * 20, level * 30);
        std::uniform_int_distribution<int> Attackrandom(level * 3, level * 8);

        // �ʱ�ȭ
        int finalhealth = Healthrandom(gen);
        this->maxhp = finalhealth;
        this->hp = finalhealth;
        this->attack = Attackrandom(gen);

        this->level = level;
        this->exp = 15 + (level * 5);
        this->gold = 10 + (level * 3);
        this->itemname = "Ʈ���� ����";
    }

    void Basicattack(Character* player) override;
    void Specialattack(Character* player) override;
};

// Slime
class Slime : public Monster
{
public:
    Slime(int level)
        : Monster("������", 0, 0) // �ӽð�
    {
        std::random_device rd;  // ���� �õ� ����
        std::mt19937 gen(rd()); // ���� ���� ����

        std::uniform_int_distribution<int> Healthrandom(level * 20, level * 30);
        std::uniform_int_distribution<int> Attackrandom(level * 1, level * 3);

        // �ʱ�ȭ
        int finalhealth = Healthrandom(gen);
        this->maxhp = finalhealth;
        this->hp = finalhealth;
        this->attack = Attackrandom(gen);

        this->level = level;
        this->exp = 15 + (level * 5);
        this->gold = 10 + (level * 3);
        this->itemname = "�������� �����";
    }

    void Basicattack(Character* player) override;
    void Specialattack(Character* player) override;
};