#include "Monster.h"
#include <Windows.h>
#include "Character.h"

using namespace std;

string Boss::Basicattack(Character* player)
{
	int hitcount = 1;
	int damage = Getattack() * 2.2;
	int totaldamage = hitcount * damage;

	player->Takedamage(totaldamage);
	string message = "Calamity의 검이 당신을 관통한다. " + to_string(damage) + "대미지\n";

	return message;
}

string Boss::Specialattack(Character* player)
{
	int damage = Getattack() * 2.2;

	player->Takedamage(damage);

	string message = "오크의 연속 공격! " + player->Getname() + "에게 " + to_string(damage) + " 데미지!";

	return message;
}
vector<string> Boss::GetAsciiArt()
{
	return {
"       _--_      ",
"     _|●  ●|_    ",
"    /  \\__/  \\ ",
"   |          |  "
	};
}
