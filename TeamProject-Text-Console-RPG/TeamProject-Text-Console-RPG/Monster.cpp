#include "Monster.h"
#include "Character.h"
#include <Windows.h>

using namespace std;

void Monster::Takedamage(int playerattack)
{
    int damage = playerattack;
    if (damage < 0) damage = 1;
    cout << name << "에게 " << damage << " 대미지!" << endl;

    int beforehp = hp;
    hp -= damage;
    if (hp <= 0) {
        cout << name << "HP : " << beforehp << " -> " << hp << "(사망)" << endl;
        cout << endl;
    }
}

// ==========================================
// 오크, 트롤, 슬라임 공격 구현부 추가
// ==========================================

// --- 오크 ---
void Orc::Basicattack(Character* player)
{
    int hitcount = 1;
    int damage = Getattack();
    int totaldamage = hitcount * damage;

    cout << "오크가 몽둥이를 크게 휘두른다!\n" << damage << " 대미지" << endl;

    player->Takedamage(totaldamage);
    cin.get();
}

void Orc::Specialattack(Character* player)
{
    int hitcount = 2;
    int damage = Getattack() * 1.5;
    int totaldamage = hitcount * damage;

    cout << "오크가 " << hitcount << "연속 분노의 내려찍기를 한다!\n" << endl;

    for (int i = 0; i < hitcount; i++)
    {
        cout << damage << "의 대미지!" << endl;
        Sleep(150);
    }

    player->Takedamage(totaldamage);
    cin.get();
}

// --- 트롤 ---
void Troll::Basicattack(Character* player)
{
    int hitcount = 1;
    int damage = Getattack();
    int totaldamage = hitcount * damage;

    cout << "트롤이 돌을 던진다!\n" << damage << " 대미지" << endl;

    player->Takedamage(totaldamage);
    cin.get();
}

void Troll::Specialattack(Character* player)
{
    int hitcount = 5;
    int damage = Getattack() * 0.5; // 연타이므로 데미지 감소
    if (damage <= 0) damage = 1;
    int totaldamage = hitcount * damage;

    cout << "트롤이 " << hitcount << "연속 무자비한 난타를 한다!\n" << endl;

    for (int i = 0; i < hitcount; i++)
    {
        cout << damage << "의 대미지!" << endl;
        Sleep(150);
    }

    player->Takedamage(totaldamage);
    cin.get();
}

// --- 슬라임 ---
void Slime::Basicattack(Character* player)
{
    int hitcount = 1;
    int damage = Getattack();
    int totaldamage = hitcount * damage;

    cout << "슬라임이 몸통 박치기를 한다!\n" << damage << " 대미지" << endl;

    player->Takedamage(totaldamage);
    cin.get();
}

void Slime::Specialattack(Character* player)
{
    int hitcount = 3;
    int damage = Getattack();
    int totaldamage = hitcount * damage;

    cout << "슬라임이 " << hitcount << "연속 산성액을 뱉는다!\n" << endl;

    for (int i = 0; i < hitcount; i++)
    {
        cout << damage << "의 대미지!" << endl;
        Sleep(150);
    }

    player->Takedamage(totaldamage);
    cin.get();
}