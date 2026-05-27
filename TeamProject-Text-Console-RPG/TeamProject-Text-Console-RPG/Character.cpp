#include "Character.h"
#include <iostream>
#include <string>

using namespace std;

Character::Character(std::string name)
{
    this->name = name;
}

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
    
    cout << Attackmessage() << endl;
    cin.get();
    monster->Takedamage(totaldamage);
}


void Character::Takedamage(int monsterattack)
{
    //대미지 공식
    int damage = monsterattack;
    if (damage < 0) damage = 1;
    cout << name << "에게 " << damage << " 대미지!" << endl;

    //실제 체력 소모
    int beforehp = hp;
    hp -= damage;
    if (hp < 0) {
        cout << name << "HP : " << beforehp << " -> " << hp << "(사망)" << endl;
        cout << endl;
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