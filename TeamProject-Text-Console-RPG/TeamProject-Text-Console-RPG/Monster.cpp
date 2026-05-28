#include "Monster.h"
#include "Character.h"

using namespace std;

void Monster::Takedamage(int playerattack)
{
	//대미지 공식
	int damage = playerattack;
	if (damage < 0) damage = 1;

	//실제 체력 소모
	int beforehp = hp;
	hp -= damage;
	if (hp <= 0) {
		cout << endl;
	}
}

vector<string> Orc::GetAsciiArt() { return { "   ,____.     ", "   | Ò_Ó|     ", "   /( | )\\    ", "  ========    " }; }
vector<string> Troll::GetAsciiArt() { return { "   .----.     ", "   | >_<|     ", "   \\( | )/    ", "  ========    " }; }
vector<string> Slime::GetAsciiArt() { return { "    ____      ", "   /O__O\\     ", "  |______|    ", "  ========    " }; }
vector<string> Boss::GetAsciiArt() { return { "  [CALAMITY]  ", "  (((o_o)))   ", "   \\/ | \\/    ", "  ========    " }; }