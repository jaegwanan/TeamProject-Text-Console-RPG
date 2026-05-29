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

	int mpdamage = 10;
	int currentmp = player->Getmp();

	if (currentmp >= mpdamage)
	{
		player->Setmp(currentmp - mpdamage);
	}
	else
	{
		player->Setmp(0);
	}

	string message = "트롤이 신비한 힘으로 마나를 강탈한다! " + player->Getname() + "에게 " + to_string(damage) + " 대미지! (mp " + to_string(mpdamage) + " 감소)";

	return message;
}

vector<string> Troll::GetAsciiArt()
{
	return {
"\\@\\  ┌△-_-△┐  /@/",
" \\ \\_[◎ U ◎]_/ / ",
"  \\   \\_W_/   /  ",
"  /___________\\  "
	};
}