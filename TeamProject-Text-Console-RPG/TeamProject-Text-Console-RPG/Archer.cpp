#include "Archer.h"
#include <iostream>
#include "string.h"

using namespace std;

Archer::Archer(std::string name) : Character(name)
{
    job = "궁수";
}

std::string Archer::Attackmessage()
{
    return "더블 샷!";
}

int Archer::Getrequiredexp()
{
    return 15 + level * level * level * 4;
}

void Archer::Applylevelupstats()
{
    maxhp += 15;
    maxmp += 12;
    attack += 10;
}

vector<string> Archer::Skill(Monster* monster)
{
    vector<string> messages;

    if (mp < 20)
    {
        messages.push_back("MP가 부족해 스킬을 사용할 수 없다.");
        return messages;
    }

    mp -= 20;

    int damage = attack * 2;
    int critChance = rand() % 100 + 1;

    if (critChance <= 40)
    {
        damage *= 2;
        messages.push_back("집중 사격! 급소 적중! 치명타!");
    }
    else
    {
        messages.push_back("집중 사격!");
    }

    monster->Takedamage(damage);

    messages.push_back(
        monster->Getname() +
        "에게 " +
        to_string(damage) +
        " 데미지!"
    );

    return messages;
}

string Archer::Getskillname()
{
    return "집중 사격";
}

vector<string> Archer::GetAsciiArt()
{
    return {
" ,____        ",
" |&   \\    |\\",
" [======]  | |",
" ( > _ ' ) |/"
    };
}