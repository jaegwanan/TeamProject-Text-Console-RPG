#include "Monster.h"
#include <Windows.h>
#include "Character.h"

using namespace std;

void Slime::Basicattack(Character* player)
{
	int hitcount = 1;
	int damage = Getattack();
	int totaldamage = hitcount * damage;

	cout << "슬라임이 끈끈이를 날린다!\n" << damage << " 대미지" << endl;

	player->Takedamage(totaldamage);
	cin.get();
}

void Slime::Specialattack(Character* player)
{
	int hitcount = 3;
	int damage = Getattack();
	int totaldamage = hitcount * damage;

	cout << "슬라임이 " << hitcount << "연속 공격을 한다!\n" << endl;

	for (int i = 0; i < hitcount; i++)
	{
		cout << damage << "의 대미지!" << endl;
		Sleep(150);
	}

	player->Takedamage(totaldamage);
	cin.get();
}