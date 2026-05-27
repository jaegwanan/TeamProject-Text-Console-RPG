#pragma once
#include <string>
#include <vector>
#include <map>  

class Character; // ★ 핵심: Character 클래스가 있다고 미리 알려줌 (전방 선언)

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