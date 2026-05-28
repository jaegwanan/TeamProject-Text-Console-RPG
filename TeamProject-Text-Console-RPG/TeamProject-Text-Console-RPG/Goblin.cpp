#include "Monster.h"
#include <Windows.h>
#include "Character.h"

using namespace std;

string Goblin::Basicattack(Character* player)
{
	int hitcount = 1;
	int damage = Getattack();
	int totaldamage = hitcount * damage;

	player->Takedamage(totaldamage);
	string message = "고블린이 주먹질을 한다! " + to_string(damage) + "대미지\n";

	return message;
}

string Goblin::Specialattack(Character* player)
{
	int damage = Getattack();

	player->Takedamage(damage);

	string message = "고블린의 연속 공격! " + player->Getname() + "에게 " + to_string(damage) + " 데미지!";

	return message;
}