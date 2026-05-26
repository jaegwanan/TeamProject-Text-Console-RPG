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
    int currenthp; // Takedamage() 에서 관련 로직 추가해주셔야 ㅎㅏㅂ니다
    int attack;
    int level;
    int exp;
    int gold;
    std::string itemname;

public:
    Monster(std::string name, int health, int attack)
        : name(name), maxhp(health), currenthp(health),attack(attack) {
    } //레벨 별 스탯은 자식에서

    //Get 함수 묶음
    std::string Getname() { return name; }
    int Getlevel() { return level; }
    int Getmaxhealth() { return maxhp; }
    int Getcurrenthealth() { return currenthp; }
    int Getattack() { return attack; }
    int Getexp() { return exp; }
    int Getgold() { return gold; }
    std::string Getitemname() { return itemname; }

    //공격 함수 선언
    virtual void Basicattack(Character* player); //일반공격 가상
    virtual void Specialattack(Character* player); //특수공격 가상
        
    void Takedamage(int damage);

    virtual ~Monster() {}
};

// Goblin
class Goblin : public Monster
{
public:
    Goblin(int level)
        : Monster("고블린", 0, 0) // 임시값
    {
        std::random_device rd;  // 난수 시드 생성
        std::mt19937 gen(rd()); // 난수 생성 엔진

        std::uniform_int_distribution<int> Healthrandom(level * 20, level * 30);
        std::uniform_int_distribution<int> Attackrandom(level * 5, level * 10);

        // 초기화
        int finalhealth = Healthrandom(gen);
        this->maxhp = finalhealth;
        this->currenthp = finalhealth;
        this->attack = Attackrandom(gen);

        this->level = level;
        this->exp = 15 + (level * 5);
        this->gold = 10 + (level * 3);
        this->itemname = "고블린의 고추기름";
    }

    // 구현 필요
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