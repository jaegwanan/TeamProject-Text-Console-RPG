#pragma once

#include <string>
#include "Monster.h"
#include "Character.h"

class AchievementManager;

class GameManager
{
public:
    int Battle(Character* player, int Num, AchievementManager* achManager);
};