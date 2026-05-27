#include "AchievementManager.h"
#include "UIManager.h"
#include <iostream>
#include <conio.h>

using namespace std;

AchievementManager::AchievementManager() {
    // 킬 관련 업적
    achievementList.push_back({ "슬라임 학살자", AchType::KILL, "Slime", 3, false });
    // 레벨 관련 업적
    achievementList.push_back({ "견습 기사", AchType::LEVEL, "", 5, false });
    achievementList.push_back({ "소드 마스터", AchType::LEVEL, "", 10, false });
    // 아이템 관련 업적
    achievementList.push_back({ "물약 중독자", AchType::ITEM_USE, "HealthPotion", 5, false });
    // 도망 관련 업적
    achievementList.push_back({ "전략적 후퇴", AchType::RUN_AWAY, "", 3, false });
}

// 아이템 사용 시 호출될 함수
void AchievementManager::UpdateItem(string itemName) {
    itemStats[itemName]++;
    CheckAchievements(); // 통계가 올랐으니 업적 검사 실행
}

// 레벨 업 시 호출될 함수
void AchievementManager::UpdateLevel(int currentLevel) {
    for (auto& ach : achievementList) {
        if (!ach.isUnlocked && ach.type == AchType::LEVEL && currentLevel >= ach.targetValue) {
            ach.isUnlocked = true;
            UIManager::PrintMessage("★업적 달성! [" + ach.titleName + "] 칭호를 획득했습니다!★");
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
            UIManager::PrintMessage("★업적 달성! [" + ach.titleName + "] 칭호를 획득했습니다!★");
        }
    }
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
        cout << " 0. 칭호 장착 해제" << endl;

        // 달성(Unlock)된 칭호만 따로 모아서 리스트로 보여줍니다.
        vector<Achievement*> unlockedList;
        int index = 1;
        for (auto& ach : achievementList) {
            if (ach.isUnlocked) {
                cout << " " << index << ". [" << ach.titleName << "]" << endl;
                unlockedList.push_back(&ach);
                index++;
            }
        }
        cout << "========================================" << endl;

        if (unlockedList.empty()) {
            cout << " * 아직 획득한 칭호가 없습니다! 업적을 달성해 보세요." << endl;
        }
        cout << " 장착할 칭호 번호를 입력하세요 (나가기: -1): ";

        int choice;
        cin >> choice;

        if (choice == -1) {
            break; // 메뉴 나가기
        }

        if (choice == 0) {
            player->setActiveTitle(""); // 비우기
            UIManager::PrintMessage("칭호를 해제했습니다.");
            continue;
        }

        // 유효한 번호를 선택한 경우
        if (choice > 0 && choice <= static_cast<int>(unlockedList.size())) {
            // 선택한 칭호를 플레이어에게 장착 ([칭호명] 형태로 저장)
            string newTitle = "[" + unlockedList[choice - 1]->titleName + "]";
            player->setActiveTitle(newTitle);
            UIManager::PrintMessage(newTitle + " 칭호를 장착했습니다!");
        }
        else {
            UIManager::PrintMessage("잘못된 번호입니다. 다시 선택해 주세요.");
        }
    }
}