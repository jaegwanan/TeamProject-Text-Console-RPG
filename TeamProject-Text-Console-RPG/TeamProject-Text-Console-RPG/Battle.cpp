// Battle.cpp

#include <iostream>
#include <string>

#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "AchievementManager.h"

using namespace std;

void Attack(Character* player, Monster* monster)
{
    int damage = player->getAttack();

    monster->takeDamage(damage);
}

bool Skill(Character* player, Monster* monster)
{

}

void GameManager::battle(Character* player)
{
    Monster* monster = nullptr; // 우선 주소 자리부터 비우고

    // ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ몬스터 생성 함수 협의 필요

    // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ몬스터 getName() 해서 출현하는 텍스트 함수 요구합니다.
}

while (player->getHealth() > 0 && monster->getHealth() > 0) // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ 플레이어 체력게터 몬스터 체력 게터 요구합니다.
// 와일문으로 반복, 내부에서 continue 사용시 여기로 다시 복귀
{
    int choice;// 함수 내에서 사용할 변수 선언

    // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ적 UI 함수요구합니다.


    // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ아군 UI 함수 요구합니다.

    // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ전투 선택지 텍스트 함수 요구합니다.

    cin >> choice;// 입력 받고

    switch (choice)
    {
    case 1: // 선택지 랜덤
    {
        int randomvalue = rand() % 100 + 1;

        if (randomvalue > 50)
        {
            attack(player, monster);
        }
        else
        {
            skill(player, monster);
        }

        break;
    }

    case 2:
        Attack(player, monster);// 일반 공격 함수
        break;

    case 3:
    {
        bool Casting = false; // 스킬 사용 여부 확인용 변수

        skill(player, monster);// 스킬 공격 함수

        if (Casting == true) // 스킬 사용 성공시 break로 턴 넘어감
        {
            break;
        }
        else// 스킬 사용 실패시 턴 소모 없이 continue으로 다시 선택
        {
            continue;
        }
    }
    case 4:
    {
        bool Used = false; // 아이템 사용 여부 확인용 변수

        // 아이템 사용 함수

        if (Used == true) // 아이템 사용 성공시 break로 턴 넘어감
        {
            break;
        }
        else // 아이템 사용 실패시 턴 소모 없이 continue으로 다시 선택
        {
            continue;
        }
    }

    case 5:
    {
        int playerLevel = player->getLevel(); // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ플레이어 레벨 게터 요구함니다.
        int monsterLevel = monster->getLevel(); // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ몬스터 레벨 변수 선언과 레벨 요구함니다.
        int PantieRunRate = 65 + (playerLevel - monsterLevel) * 5; // 빤스런 수치

        int randomValue2 = rand() % 100 + 1;

        if (randomValue2 <= PantieRunRate)
        {
            // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ도망 성공 메시지 요구합니다.
            return;
        }
        else
        {
            // ㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇㅇ도망 실패 메시지 요구합니다.
            break;
        }
    }

    default:
    {
        // 잘못된 입력입니다 메시지 함수 요구합니다.
        continue;
    }
    }
    delete monster;
}

