#pragma once

#include <string>
#include "Monster.h"
#include "Character.h"

class AchievementManager;

class GameManager
{
public:
    void Battle(Character* player, AchievementManager* achManager);
};