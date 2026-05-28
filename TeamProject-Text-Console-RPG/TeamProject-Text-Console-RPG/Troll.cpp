#include "Monster.h"
#include <Windows.h>
#include "Character.h"

using namespace std;

string Troll::Basicattack(Character* player)
{
	int hitcount = 1;
	int damage = Getattack() * 2;
	int totaldamage = hitcount * damage;

	player->Takedamage(totaldamage); 
	string message = "트롤이 몽둥이를 휘두른다! " + to_string(damage) + "대미지\n";

	return message;
}

string Troll::Specialattack(Character* player)
{
	int damage = Getattack() * 2;

	player->Takedamage(damage);

	string message = "트롤의 연속 공격! " + player->Getname() + "에게 " + to_string(damage) + " 데미지!";

	return message;
}

vector<string> Troll::GetAsciiArt()
{
	return {
"   .--._      ",
"  /     \\    ",
" [===##==]  A ",
" ( ^ o ^ )  Y "
	};
}