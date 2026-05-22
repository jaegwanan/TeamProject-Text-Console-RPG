#pragma once

#include <string>
#include <vector>
#include <map>

struct Achievement {
    std::string titleName;  
    std::string targetMonster; 
    int targetCount;        
    bool isUnlocked;      
};

class AchievementManager {
private:
    std::map<std::string, int> killStats; 
    std::vector<Achievement> achievementList; 

public:
    AchievementManager();

    void AddKillLog(std::string monsterName);

    void DisplayStatsAndTitles();
};