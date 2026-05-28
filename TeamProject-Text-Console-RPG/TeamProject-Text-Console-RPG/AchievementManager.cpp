#include "AchievementManager.h"
#include "UIManager.h"
#include "Character.h" // Character 객체 사용을 위해 추가
#include <iostream>
#include <conio.h>

using namespace std;

AchievementManager::AchievementManager() {
    achievementList.push_back({ "슬라임 학살자", AchType::KILL, "슬라임", 3, false });
    achievementList.push_back({ "견습 기사", AchType::LEVEL, "", 5, false });
    achievementList.push_back({ "소드 마스터", AchType::LEVEL, "", 10, false });
    achievementList.push_back({ "물약 중독자", AchType::ITEM_USE, "HP 포션", 5, false }); // HealthPotion에서 수정 완료
    achievementList.push_back({ "전략적 후퇴", AchType::RUN_AWAY, "", 3, false });
}

void AchievementManager::UpdateItem(string itemName) {
    itemStats[itemName]++;
    CheckAchievements();
}

void AchievementManager::UpdateLevel(int currentLevel) {
    for (auto& ach : achievementList) {
        if (!ach.isUnlocked && ach.type == AchType::LEVEL && currentLevel >= ach.targetValue) {
            ach.isUnlocked = true;
            UIManager::PrintMessage("★ 업적 달성! [" + ach.titleName + "] 칭호를 획득했습니다!★");
        }
    }
}

void AchievementManager::CheckAchievements() {
    for (auto& ach : achievementList) {
        if (ach.isUnlocked) continue;

        bool conditionMet = false;

        if (ach.type == AchType::KILL && killStats[ach.targetString] >= ach.targetValue) {
            conditionMet = true;
        }
        else if (ach.type == AchType::ITEM_USE && itemStats[ach.targetString] >= ach.targetValue) {
            conditionMet = true;
        }
        else if (ach.type == AchType::RUN_AWAY && runAwayCount >= ach.targetValue) {
            conditionMet = true;
        }

        if (conditionMet) {
            ach.isUnlocked = true;
            UIManager::PrintMessage("★ 업적 달성! [" + ach.titleName + "] 칭호를 획득했습니다!★");
        }
    }
}

void AchievementManager::DisplayStatsAndTitles() {
    system("cls");
    cout << "========================================" << endl;
    cout << "         [ 명예의 전당 (업적) ]         " << endl;
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

void AchievementManager::EquipTitleMenu(Character* player) {
    while (true) {
        system("cls");
        cout << "========================================" << endl;
        cout << "         [ 칭호 장착 메뉴 ]             " << endl;
        cout << "----------------------------------------" << endl;
        cout << " 현재 장착 중인 칭호: "
            << (player->getActiveTitle().empty() ? "없음" : player->getActiveTitle()) << endl;
        cout << "----------------------------------------" << endl;

        // ★ 번호 스위칭 적용 완료
        cout << " -1. 칭호 장착 해제" << endl;
        cout << "  0. 마을로 돌아가기" << endl;

        vector<Achievement*> unlockedList;
        int index = 1;
        for (auto& ach : achievementList) {
            if (ach.isUnlocked) {
                cout << "  " << index << ". [" << ach.titleName << "]" << endl;
                unlockedList.push_back(&ach);
                index++;
            }
        }
        cout << "========================================" << endl;

        if (unlockedList.empty()) {
            cout << " * 아직 획득한 칭호가 없습니다! 업적을 달성해 보세요." << endl;
        }
        cout << " 장착할 칭호 번호를 입력하세요: ";

        int choice;
        cin >> choice;

        // ★ 0번을 입력하면 마을로 나가기 (break)
        if (choice == 0) break;

        // ★ -1번을 입력하면 칭호 해제
        if (choice == -1) {
            player->setActiveTitle("");
            UIManager::PrintMessage("칭호를 해제했습니다.");
            continue;
        }

        if (choice > 0 && choice <= static_cast<int>(unlockedList.size())) {
            string newTitle = "[" + unlockedList[choice - 1]->titleName + "]";
            player->setActiveTitle(newTitle);
            UIManager::PrintMessage(newTitle + " 칭호를 장착했습니다!");
        }
        else {
            UIManager::PrintMessage("잘못된 번호입니다. 다시 선택해 주세요.");
        }
    }
}

void AchievementManager::UpdateKill(string monsterName) {
    killStats[monsterName]++;
    CheckAchievements();
}

void AchievementManager::UpdateRunAway() {
    runAwayCount++;
    CheckAchievements();
}