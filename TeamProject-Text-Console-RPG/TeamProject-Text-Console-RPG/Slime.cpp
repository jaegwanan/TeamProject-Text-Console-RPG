#include "Monster.h"
#include <Windows.h>
#include "Character.h"

using namespace std;

string Slime::Basicattack(Character* player)
{
	int hitcount = 1;
	int damage = Getattack() * 0.8;
	int totaldamage = hitcount * damage;

	player->Takedamage(totaldamage);
	string message = "슬라임이 끈끈이를 날린다! " + to_string(damage) + "대미지\n";

	return message;
}

string Slime::Specialattack(Character* player)
{
	int damage = Getattack() * 0.8;

	player->Takedamage(damage);

	string message = "슬라임의 연속 공격!" + player->Getname() + "에게 " + to_string(damage) + " 데미지!";

	return message;
}

vector<string> Slime::GetAsciiArt()
{
	return {
"  .@@@@@@     ",
" .@##`   @   ",
" @##.   `@@    ",
"  @@@@@@@@`    "
	};
}