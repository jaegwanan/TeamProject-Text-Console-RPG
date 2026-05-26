#include "Monster.h"
#include <Windows.h>

using namespace std;

void Goblin::Basicattack(Character* player)
{
	int hitcount = 1;
	int damage = Getattack();
	int totaldamage = hitcount * damage;

	cout << "고블린이 주먹질을 한다!\n" << damage << " 대미지" << endl;

	player->Takedamage(totaldamage);
}

void Goblin::Specialattack(Character* player)
{
	int hitcount = 3;
	int damage = Getattack();
	int totaldamage = hitcount * damage;

	cout << "고블린이 3연속 공격을 한다!\n" << endl;

	for (int i = 0; i < hitcount; i++)
	{
		cout << damage << "의 대미지!" << endl;
		Sleep(500);
	}

	player->Takedamage(totaldamage);
	
}