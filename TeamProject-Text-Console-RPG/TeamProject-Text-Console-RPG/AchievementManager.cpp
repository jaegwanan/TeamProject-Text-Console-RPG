#include "AchievementManager.h"
#include <iostream>

using namespace std;

AchievementManager::AchievementManager() {
    achievementList.push_back({ "초보 모험가", "Goblin", 1, false });
    achievementList.push_back({ "슬라임 학살자", "Slime", 3, false });
    achievementList.push_back({ "오크의 악몽", "Orc", 5, false });
}

void AchievementManager::AddKillLog(string monsterName) {
    killStats[monsterName]++;

    for (auto& ach : achievementList) {
        if (!ach.isUnlocked && ach.targetMonster == monsterName && killStats[monsterName] >= ach.targetCount) {

            ach.isUnlocked = true;

            string message = "★업적 달성! [" + ach.titleName + "] 칭호를 획득했습니다!★";
            UIManager::PrintMessage(message);
        }
    }
}

void AchievementManager::DisplayStatsAndTitles() {
    system("cls");
    cout << "========================================" << endl;
    cout << "         [ 몬스터 사냥 통계 ]           " << endl;
    cout << "----------------------------------------" << endl;

    int totalKills = 0;
    for (const auto& pair : killStats) {
        cout << " - " << pair.first << " : " << pair.second << " 마리 처치" << endl;
        totalKills += pair.second;
    }

    cout << "----------------------------------------" << endl;
    cout << " 총 처치 수 : " << totalKills << " 마리" << endl;
    cout << "========================================" << endl;

    cout << "\n         [ 획득한 칭호 목록 ]           " << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& ach : achievementList) {
        if (ach.isUnlocked) {
            cout << " [" << ach.titleName << "]" << endl;
        }
    }
    cout << "========================================" << endl;
    UIManager::PrintMessage("통계 확인 완료.");
}