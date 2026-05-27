#pragma once

#include <string>
#include "Character.h" 
#include "Monster.h"

class UIManager
{
public:
    // 콘솔 커서를 특정 X, Y 좌표로 이동시키는 함수 (화면 분할용)
    static void gotoxy(int x, int y);

    static std::string GetGaugeBar(int current, int max, int width = 15);

    static void PrintMessage(std::string message);

    static void PrintMonsterAppear(std::string monsterName);

    static void DrawMonsterStatus(Monster* monster);

    static void DrawPlayerStatus(Character* player);

    static void DrawBattleMenu();

    static void PrintRunSuccess();

    static void PrintRunFail();

    static void PrintWrongInput();

    int ShowTitleScreen();
};