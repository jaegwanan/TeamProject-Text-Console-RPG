#include "Warrior.h"
#include <iostream>
#include "string.h"

using namespace std;

Warrior::Warrior(std::string name) : Character(name)
{
    job = "전사";
}

std::string Warrior::Attackmessage()
{
    return "양손검 휘두르기!";
}

int Warrior::Getrequiredexp()
{
    return 5 + level * level * level * 9;
}

void Warrior::Applylevelupstats()
{
    maxhp += 30;
    maxmp += 5;
    attack += 7;
}

vector<string> Warrior::Skill(Monster* monster)
{
    vector<string> messages;

    if (mp < 15)
    {
        messages.push_back("MP가 부족해 스킬을 사용할 수 없다.");
        return messages;
    }

    mp -= 15;

    int damage = attack * 3;
    monster->Takedamage(damage);

    messages.push_back(
        "파워 스트라이크! " +
        monster->Getname() +
        "에게 " +
        to_string(damage) +
        " 데미지!"
    );

    return messages;
}
string Warrior::Getskillname()
{
    return "파워 스트라이크";
}

vector<string> Warrior::GetAsciiArt()
{
    return {
  "   /^\\\\      /\\\\",
  "  |###| <==|==|",
  " /|###|\\\\    ||",
  "   / \\\\"
    };
}