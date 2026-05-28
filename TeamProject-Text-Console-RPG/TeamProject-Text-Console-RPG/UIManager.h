#pragma once

#include <string>
#include "Character.h" 
#include "Monster.h"

class UIManager
{
public:
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

    static int ShowTitleScreen();
};