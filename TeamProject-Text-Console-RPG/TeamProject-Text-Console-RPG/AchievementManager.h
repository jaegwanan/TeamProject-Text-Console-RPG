#pragma once
#include <string>
#include <vector>
#include <map>  

class Character;

enum class AchType {
    KILL,
    LEVEL,
    ITEM_USE,
    RUN_AWAY
};

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

    std::vector<Achievement> achievementList;

public:
    AchievementManager();

    void UpdateKill(std::string monsterName);
    void UpdateLevel(int currentLevel);
    void UpdateItem(std::string itemName);
    void UpdateRunAway();

    void CheckAchievements();
    void DisplayStatsAndTitles();

    void EquipTitleMenu(Character* player);

    std::map<std::string, int>& GetKillStats() { return killStats; }
    std::map<std::string, int>& GetItemStats() { return itemStats; }
    int& GetRunAwayCount() { return runAwayCount; }
    std::vector<Achievement>& GetAchievementList() { return achievementList; }
};