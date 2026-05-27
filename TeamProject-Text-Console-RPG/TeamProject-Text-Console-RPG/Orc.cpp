#include "Monster.h"
#include <Windows.h>
#include "Character.h"

using namespace std;

void Orc::Basicattack(Character* player)
{
	int hitcount = 1;
	int damage = Getattack();
	int totaldamage = hitcount * damage;

	cout << "오크가 발길질을 한다!\n" << damage << " 대미지" << endl;

	player->Takedamage(totaldamage);
	cin.get();
}

void Orc::Specialattack(Character* player)
{
	int hitcount = 2;
	int damage = Getattack();
	int totaldamage = hitcount * damage;

	cout << "오크가 " << hitcount << "연속 공격을 한다!\n" << endl;

	for (int i = 0; i < hitcount; i++)
	{
		cout << damage << "의 대미지!" << endl;
		Sleep(150);
	}

	player->Takedamage(totaldamage);
	cin.get();
}