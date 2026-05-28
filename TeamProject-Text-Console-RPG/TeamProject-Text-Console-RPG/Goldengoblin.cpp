#include "Monster.h"
#include <Windows.h>
#include "Character.h"

using namespace std;

string Goldengoblin::Basicattack(Character* player) // 정찰
{
	/*
	int hitcount = 1;
	int damage = Getattack();
	int totaldamage = hitcount * damage;
	
	player->Takedamage(totaldamage);
	*/

	string message = "황금 고블린이 상황을 살핀다.. ";

	return message;
}

string Goldengoblin::Specialattack(Character* player) // 도망
{
	int damage = Getattack();
	
	string message = "황금 고블린이 도망쳤다! ";

	Takedamage(1); // 도망치는 행동을 따로 구현 힘들 것 같아 로직은 일단 자살로

	return message;
}

vector<string> Goldengoblin::GetAsciiArt()
{
	return {
"    /l__/l     ",
"   (○ W ○ )-┐  ",
"  E_)    E_)|  ",
"    l_/ l_)-┘  "
	};
}