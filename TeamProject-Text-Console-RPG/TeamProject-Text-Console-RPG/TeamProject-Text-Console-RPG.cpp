#include <iostream>
#include "Character.h"
#include "UIManager.h"
#include "AchievementManager.h"

// 팀원들의 전투 함수가 있는 GameManager.h 등을 인클루드했다고 가정
// #include "GameManager.h" 

int main()
{
    // 업적 매니저는 게임 시작 전(메인 타이틀)부터 존재해야 하므로 루프 밖으로 뺍니다.
    AchievementManager achManager;

    while (true)
    {
        // 텍스트 RPG 감성의 시작 화면을 띄우고 입력을 받습니다.
        int startMenuChoice = UIManager::ShowTitleScreen();

        if (startMenuChoice == 1)
        {
            // 1번: 게임 루프 진입 (while문 탈출)
            break;
        }
        else if (startMenuChoice == 2)
        {
            // 2번: 세이브/로드 기능 (나중에 추가할 기능)
            UIManager::PrintMessage("아직 구현되지 않은 기능입니다.");
        }
        else if (startMenuChoice == 3)
        {
            // 3번: 우리가 만든 업적 시스템 연동! 언제든 통계를 볼 수 있습니다.
            achManager.DisplayStatsAndTitles();
        }
        else if (startMenuChoice == 4)
        {
            // 4번: 게임 종료
            std::cout << "\n게임을 종료합니다. 안녕히 가세요!\n";
            return 0; // 프로그램 완전히 종료
        }
        else
        {
            // 잘못된 입력 처리
            UIManager::PrintWrongInput();
        }
    }

    // ---------------------------------------------------------
    // 여기서부터 본격적인 게임 진행 코드 (1번을 눌러 탈출한 후)
    // ---------------------------------------------------------
    system("cls");
    std::cout << "캐릭터의 이름을 입력하세요: ";
    std::string playerName;
    std::cin >> playerName;

    // 플레이어 객체 생성
    Character* player = new Character(playerName);

    // 오프닝 메시지
    UIManager::PrintMessage(playerName + " 용사여, 모험을 시작합니다!");

    // 이후 팀원이 만든 게임 로직으로 연결 (아래는 예시)
    // GameManager gameManager;
    // gameManager.battle(player); 

    delete player;
    return 0;
}