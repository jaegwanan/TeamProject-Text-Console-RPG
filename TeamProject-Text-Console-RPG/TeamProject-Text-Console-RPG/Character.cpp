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
    string result1, result2;
   
    std :: cout << "[ 전투시작! ]" << name << "(" << job << ") vs (" << monster->Getname() << endl;
    
    
    
    while (Gethp() > 0 && monster->Gethp() > 0)
    {   
        // 사용자의 턴
        if (monster->Gethp() - Getattack() > 0) { result1 = "생존"; }
        else { result1 = "사망"; }

        cout << "--- " << name << "의 턴" << " ---" << endl;
        cout << Attackmessage() << endl;
        cout << monster->Getname() << "에게 " << Getattack() << "의 데미지" << endl;
        cout << monster->Getname() << " HP: " << monster->Gethp() << "->" << monster->Gethp() - Getattack() << "(" << result1 << ")" << endl;
        cout << endl;
        monster->Sethp(monster->Gethp() - Getattack());

        if (monster->Gethp() <= 0)
        {
            cout << endl << " ★ 전투 승리!" << endl;
            
            break;
        }


        // 몬스터의 턴
        if (Gethp() - monster->Getattack() > 0) { result2 = "생존"; }
        else { result2 = "사망"; }

        cout << "--- " << monster->Getname() << "턴" << " --- " << endl;
        cout << name << "에게 " << monster->Getattack() << "의 데미지" << endl;
        cout << name << " HP: " << Gethp() << "->" << Gethp() - monster->Getattack() << "(" << result2 << ")" << endl;
        cout << endl;
        Sethp(Gethp() - monster->Getattack());

        if (Gethp() <= 0)
        {
            cout << endl << name << " 사망. 패배" << endl;

            break;
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