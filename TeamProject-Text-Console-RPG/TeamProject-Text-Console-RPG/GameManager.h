// GameManager.h

#pragma once

// 인클루드 기본
#include<string>

//인클루드 커스텀 헤더
#include "Monster.h"
#include "Character.h"

class GameManager
{
public:
    void Battle(Character* player);
    bool Bossbattle(Character* player);
};