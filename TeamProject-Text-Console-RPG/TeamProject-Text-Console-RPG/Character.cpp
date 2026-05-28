#include "Character.h"
#include "Inventory.h"
#include <iostream>
#include <string>

using namespace std;

Character::Character(std::string name)
{
    this->name = name;
    m_inventory = new Inventory();
}

void Character::Displaystatus()
{
    system("cls");

    vector<string> art = GetAsciiArt();

    // 아스키 출력
    for (int i = 0; i < art.size(); i++)
    {
        cout << "                    " << art[i] << endl;
    }

    cout << endl;

    cout << "       ---------------------------------------------------------------" << endl;

    cout << "          이름: " << name
        << "  |  직업: " << job
        << "  |  Lv." << level
        << "  |  경험치: " << exp << "/" << Getrequiredexp()
        << endl;

    cout << "          HP: " << hp << "/" << maxhp
        << "  |  MP: " << mp << "/" << maxmp
        << "  |  공격력: " << attack
        << "  |  소유금액: " << gold
        << endl;

    cout << "       ---------------------------------------------------------------" << endl;


}

void Character::Basicattack(Monster* monster)
{
    int hitcount = 1;
    int damage = attack;
    int totaldamage = hitcount * damage;
    monster->Takedamage(totaldamage);
}


void Character::Takedamage(int monsterattack)
{
    //대미지 공식
    int damage = monsterattack;
    if (damage < 0) damage = 1;


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
    exp += amount;

    while (exp >= Getrequiredexp())
    {
        exp -= Getrequiredexp();
        level++;

        Applylevelupstats();

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

// setter
void Character::Setjob(std::string job)
{
    this->job = job;
}

void Character::Setlevel(int level)
{
    this->level = level;
}

void Character::Sethp(int hp)
{
    this->hp = min(hp, maxhp);

    if (this->hp < 0)
        this->hp = 0;
}

void Character::Setmaxhp(int maxhp)
{
    this->maxhp = maxhp;
}

void Character::Setmp(int mp)
{
    this->mp = min(mp, maxmp);

    if (this->mp < 0)
        this->mp = 0;
}

void Character::Setmaxmp(int maxmp)
{
    this->maxmp = maxmp;
}

void Character::Setattack(int attack)
{
    this->attack = attack;
}

void Character::Setexp(int exp)
{
    this->exp = exp;
}

void Character::Setgold(int gold)
{
    this->gold = gold;
}

void Character::Setpoisoned(bool poisoned)
{
    this->ispoisoned = poisoned;
}

// getter
std::string Character::Getjob()
{
    return job;
}

int Character::Getlevel()
{
    return level;
}

int Character::Gethp()
{
    return hp;
}

int Character::Getmaxhp()
{
    return maxhp;
}

int Character::Getmp()
{
    return mp;
}

int Character::Getmaxmp()
{
    return maxmp;
}

int Character::Getattack()
{
    return attack;
}

int Character::Getexp()
{
    return exp;
}

int Character::Getgold()
{
    return gold;
}

int Character::Getpoisoned()
{
    return ispoisoned;
}