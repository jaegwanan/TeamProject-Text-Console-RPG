#include "Monster.h"
#include <Windows.h>
#include "Character.h"

using namespace std;

string Zombie::Basicattack(Character* player)
{
	int hitcount = 1;
	int damage = Getattack();
	int totaldamage = hitcount * damage;

	player->Takedamage(totaldamage);
	string message = "좀비가 할퀴었다! " + to_string(damage) + "대미지\n";

	return message;
}

string Zombie::Specialattack(Character* player)
{
	int damage = Getattack() * 2;

	player->Takedamage(damage);
	player->Setpoisoned(true);

	string message = "좀비가 깨물었다! " + player->Getname() + "에게 " + to_string(damage) + " 대미지!";

	return message;
}

vector<string> Zombie::GetAsciiArt()
{
	return {
"  \\\\  ___  // ",
"   \\\\[●W●]//  ",
"    |     |   ",
"    |_____|   "
	};
}

void Zombie::Takedamage(int playerattack)
{
	Monster::Takedamage(playerattack);

	if (this->hp <= 0 && !this->isrevived)
	{
		hp = 0;
		isrevived = true;
		reviveReady = true;
	}
}

string Zombie::Getrevivemessage()
{
	if (reviveReady)
	{
		return "좀비가 쓰러졌다... 그러나 무언가 이상하다..";
	}

	return "";
}

void Zombie::Revive()
{
	hp = maxhp / 2;
	reviveReady = false;
}