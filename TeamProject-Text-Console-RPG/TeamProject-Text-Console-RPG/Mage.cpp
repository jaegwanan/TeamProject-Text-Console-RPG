#include "Mage.h"
#include <iostream>
#include "string.h"

using namespace std;

Mage::Mage(std::string name) : Character(name)
{
    job = "마법사";
}

std::string Mage::Attackmessage()
{
    return "매직 미사일";
}

int Mage::Getrequiredexp()
{
    return 20 + level * level * level * 3;
}

void Mage::Applylevelupstats()
{
    maxhp += 10;
    maxmp += 30;
    attack += 9;
}

vector<string> Mage::Skill(Monster* monster)
{
    vector<string> messages;

    if (mp < 30)
    {
        messages.push_back("MP가 부족해 스킬을 사용할 수 없다.");
        return messages;
    }

    mp -= 30;

    int damage = attack * 4;
    monster->Takedamage(damage);

    messages.push_back(
        "파이어 볼! " +
        monster->Getname() +
        "에게 " +
        to_string(damage) +
        " 데미지!"
    );

    return messages;
}

string Mage::Getskillname()
{
    return "파이어 볼";
}

vector<string> Mage::GetAsciiArt()
{
    return {
"  <  \\        ",
"  |　 \\       &",
"  <====>     /",
" ( * _ * )  /"
    };
}
