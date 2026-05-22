#pragma once

#include <string>
#include <vector>
#include <map>

// 개별 업적
struct Achievement {
    std::string titleName;     // 획득할 칭호 (예: "슬라임 학살자")
    std::string targetMonster; // 목표 몬스터 (예: "Slime")
    int targetCount;           // 목표 처치 수 (예: 3)
    bool isUnlocked;           // 달성 여부
};

class AchievementManager {
private:
    std::map<std::string, int> killStats; // 몬스터별 처치 횟수 저장소
    std::vector<Achievement> achievementList; // 전체 업적 목록

public:
    // 생성자에서 전체 업적 리스트를 초기화합니다.
    AchievementManager();

    // 몬스터 처치 시 호출할 함수 (핵심)
    void AddKillLog(std::string monsterName);

    // 사냥 통계 및 달성한 칭호를 보여주는 UI 함수
    void DisplayStatsAndTitles();
};