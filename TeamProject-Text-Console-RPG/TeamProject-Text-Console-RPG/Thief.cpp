#include "Thief.h"
#include <iostream>
#include "string.h"

using namespace std;

Thief::Thief(std::string name) : Character(name)
{
    job = "도적";
}

std::string Thief::Attackmessage()
{
    return "수리검 던지기!";
}

int Thief::Getrequiredexp()
{
    return 10 + level * level * level * 6;
}

void Thief::Applylevelupstats()
{
    maxhp += 20;
    maxmp += 10;
    attack += 15;
}

vector<string> Thief::Skill(Monster* monster)
{
    vector<string> messages;

    if (mp < 25)
    {
        messages.push_back("MP가 부족해 스킬을 사용할 수 없다.");
        return messages;
    }

    mp -= 25;

    messages.push_back("연속베기!");

    for (int i = 0; i < 3; i++)
    {
        int damage = attack * 0.7;

        messages.push_back(
            to_string(i + 1) +
            "타! " +
            monster->Getname() +
            "에게 " +
            to_string(damage) +
            " 데미지!"
        );
    }

    return messages;
}

string Thief::Getskillname()
{
    return "연속베기";
}

vector<string> Thief::GetAsciiArt()
{
    return {
"   .--.    /\\\\",
"  |####|  /__\\\\",
" /|####|\\\\  ||",
"    /\\\\"
    };
}
