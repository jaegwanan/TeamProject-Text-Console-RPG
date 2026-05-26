#include "Character.h"
#include <iostream>
#include <string>

using namespace std;



class Warrior : public Character 
{public:
    Warrior(std::string name) : Character(name)
    {
        job =  "전사";
    }
   
    std::string Attackmessage() { return "양손검 휘두르기!"; }
    
    int Getrequiredexp() override
    {
        return 5 + level * level * level * 9;
    }

    void Applylevelupstats() override
    {
        maxhp += 30;
        hp = maxhp;
        maxmp += 5;
        mp = maxmp;
        attack += 7;
    }

};

class Mage : public Character
{
public:
    Mage(std::string name) : Character(name)
    {
        job = "마법사";
    }

    std::string Attackmessage() { return "파이어 볼!"; }

    int Getrequiredexp() override
    {
        return 20 + level * level * level * 3;
    }

    void Applylevelupstats() override
    {
        maxhp += 10;
        hp = maxhp;
        maxmp += 30;
        mp = maxmp;
        attack += 9;
    }
};

class Thief : public Character
{
public:
    Thief(std::string name) : Character(name)
    {
        job = "도적";
    }

    std::string Attackmessage() { return "수리검 던지기!"; }

    int Getrequiredexp() override
    {
        return 10 + level * level * level * 6;
    }

    void Applylevelupstats() override
    {
        maxhp += 20;
        hp = maxhp;
        maxmp += 10;
        mp = maxmp;
        attack += 15;
    }
};

class Archer : public Character
{
public:
    Archer(std::string name) : Character(name)
    {
        job = "궁수";
    }

    std::string Attackmessage() { return "더블 샷!"; }

    int Getrequiredexp() override
    {
        return 15 + level * level * level * 4;
    }

    void Applylevelupstats() override
    {
        maxhp += 15;
        hp = maxhp;
        maxmp += 12;
        mp = maxmp;
        attack += 10;
    }
};

void Character::Displaystatus()
{
    cout << "---------------------------------" << endl;
    cout << "이름: " << name << "  |  " << "직업: " << job << "  |  " << "Lv." << level << endl;
    cout << "HP: " << hp << "  |  " << "공격력: " << attack << "  |  " << "경험치: " << exp << "/" <<Getrequiredexp() << endl;

}

void Character::Basicattack(Monster* monster)
{
    int hitcount = 1;
    int damage = attack;
    int totaldamage = hitcount * damage;
    
    Attackmessage();
    monster->Takedamage(totaldamage);
}
}

void Character::Takedamage(int monsterattack)
{
    //대미지 공식
    int damage = monsterattack;
    if (damage < 0) damage = 1;
    cout << name << "에게 " << damage << " 대미지!" << endl;

    //실제 체력 소모
    int beforehp = currenthp;
    currenthp -= damage;
    if (currenthp < 0) {
        cout << name << "HP : " << beforehp << " -> " << currenthp << "(사망)" << endl;
        cout << endl;
    }
}
}

void Character::Gainexp(int amount)
{   
    cout << amount << " EXP 획득!" << endl;
    exp += amount;
    Printexpbar();

    while (exp >= Getrequiredexp())
    {
        exp -= Getrequiredexp();
        level++;

        Applylevelupstats();

        cout << " 레벨 업! 현재 레벨: " << level << endl;
        Printexpbar();

    }
}

void Character::Printexpbar()
{
    int requiredExp = Getrequiredexp();

    float ratio = (float)exp / requiredExp;

    int barWidth = 20;
    int filled = ratio * barWidth;

    cout << "EXP [";

    for (int i = 0; i < barWidth; i++)
    {
        if (i < filled)
            cout << "■";
        else
            cout << "-";
    }

    cout << "] ";

    cout << exp << " / " << requiredExp;
    cout << " (" << (int)(ratio * 100) << "%)" << endl;
}