#pragma once
#include <string>
#include <vector>
#include <map>  

enum class AchType {
    KILL,       
    LEVEL,      
    ITEM_USE,   
    RUN_AWAY  
};

// 2. 구조체를 확장합니다.
struct Achievement {
    std::string titleName;
    AchType type;          
    std::string targetString; 
    int targetValue;        
    bool isUnlocked;
};

class AchievementManager {
private:
    std::map<std::string, int> killStats;
    std::map<std::string, int> itemStats;
    int runAwayCount = 0;              

public:
    AchievementManager();

    void UpdateKill(std::string monsterName);
    void UpdateLevel(int currentLevel);
    void UpdateItem(std::string itemName);
    void UpdateRunAway();

    void CheckAchievements();
    void DisplayStatsAndTitles();

    void EquipTitleMenu(Character* player);
};