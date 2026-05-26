#include "Monster.h"
#include "Character.h"

using namespace std;

void Monster::Takedamage(int playerattack)
{
	//대미지 공식
	int damage = playerattack;
	if (damage < 0) damage = 1;
	cout << name << "에게 " << damage << " 대미지!" << endl;

	//실제 체력 소모
	int beforehp = currenthp;
	currenthp -= damage;
	if (currenthp < 0) {
		cout << name << "HP : " << beforehp << " -> " << currenthp << "(사망)" << endl;
		cout << endl;
	}
}