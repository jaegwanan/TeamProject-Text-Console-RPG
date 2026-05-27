#include "UIManager.h"
#include <iostream>
#include <windows.h>
#include <conio.h> // _getch() 사용을 위해 필요

using namespace std;

// 콘솔 커서를 특정 X, Y 좌표로 이동시키는 함수
void UIManager::gotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 체력 비율을 계산하여 텍스트 게이지 바([####---])로 반환하는 함수
string UIManager::GetGaugeBar(int current, int max, int width)
{
    if (max <= 0) return "[ ERROR ]";

    string bar = "[";
    float percentage = static_cast<float>(current) / max;
    int filledWidth = static_cast<int>(percentage * width);

    // 체력이 남아있다면 최소 1칸은 차게 보이도록 (실피 보정)
    if (current > 0 && filledWidth == 0) filledWidth = 1;

    for (int i = 0; i < width; ++i) {
        if (i < filledWidth) bar += "#";
        else bar += "-";
    }
    bar += "]";
    return bar;
}

// 화면 하단에 테두리와 함께 시스템 메시지를 출력하고 대기하는 함수
void UIManager::PrintMessage(string message)
{
    gotoxy(0, 15); // 하단 텍스트 영역 시작점
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  " << message << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  (계속하려면 아무 키나 누르세요) ▼";
    _getch(); // 플레이어가 텍스트를 읽을 수 있도록 대기
}

// 몬스터 첫 출현 시 화면을 지우고 메시지를 띄우는 함수
void UIManager::PrintMonsterAppear(string monsterName)
{
    system("cls"); // 화면 초기화
    PrintMessage("앗! 야생의 " + monsterName + "이(가) 나타났다!");
}

// 전투 화면 우측 상단에 몬스터의 상태창을 그리는 함수
void UIManager::DrawMonsterStatus(Monster* monster)
{
    gotoxy(45, 2);
    // 주의: Monster.h에 getName()과 getLevel() 게터가 선언되어 있어야 합니다.
    cout << monster->Getname() << " (Lv." << monster->Getlevel() << ")";

    gotoxy(45, 3);
    // 주의: Monster.h에 getHealth()와 getMaxHealth() 게터가 선언되어 있어야 합니다.
    cout << "HP: " << GetGaugeBar(monster->Gethp(), monster->Getmaxhp(), 15)
        << " " << monster->Gethp() << "/" << monster->Getmaxhp();
}

// 전투 화면 좌측 하단에 플레이어의 상태창을 그리는 함수
void UIManager::DrawPlayerStatus(Character* player)
{
    gotoxy(5, 8);

    // 1. 플레이어가 칭호를 장착하고 있다면 이름 앞에 먼저 출력
    // 주의: Character.h에 getActiveTitle() 게터가 선언되어 있어야 합니다.
    if (!player->getActiveTitle().empty()) {
        cout << player->getActiveTitle() << " ";
    }

    // 2. 이어서 이름과 레벨 출력
    // 주의: Character.h에 getName()과 getLevel() 게터가 선언되어 있어야 합니다.
    cout << player->Getname() << " (Lv." << player->Getlevel() << ")";

    gotoxy(5, 9);

    // 3. 체력 바와 수치 출력
    // 주의: Character.h에 getHealth()와 getMaxHealth() 게터가 선언되어 있어야 합니다.
    cout << "HP: " << GetGaugeBar(player->Gethp(), player->Getmaxhp(), 15)
        << " " << player->Gethp() << "/" << player->Getmaxhp();
}

// 매 턴마다 하단에 전투 선택지 메뉴를 띄우는 함수
void UIManager::DrawBattleMenu()
{
    gotoxy(0, 15);
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  [무엇을 할까?]" << endl;
    cout << "  1. 자동 전투 (랜덤 행동)" << endl;
    cout << "  2. 싸운다 (일반 공격)" << endl;
    cout << "  3. 스킬 사용" << endl;
    cout << "  4. 가방 (아이템)" << endl;
    cout << "  5. 도망간다" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  >> 입력: ";
}

// 도망 성공 시 출력 메시지
void UIManager::PrintRunSuccess()
{
    PrintMessage("무사히 도망쳤다!");
}

// 도망 실패 시 출력 메시지
void UIManager::PrintRunFail()
{
    PrintMessage("도망칠 수 없었다...");
}

// 메뉴에서 잘못된 번호를 입력했을 때 출력 메시지
void UIManager::PrintWrongInput()
{
    PrintMessage("잘못된 입력입니다. 다시 선택해주세요.");
}

int UIManager::ShowTitleScreen()
{
    system("cls"); // 화면 초기화

    // 정통 텍스트 RPG 느낌을 살린 아스키 아트와 UI
    cout << R"(
================================================================================

       _______  ______  __   __  _______    _____   _____    _____ 
      |__   __||  ____| \ \ / / |__   __|  |  __ \ |  __ \  / ____|
         | |   | |__     \ V /     | |     | |__) || |__) || |  __  
         | |   |  __|     > <      | |     |  _  / |  ___/ | | |_ | 
         | |   | |____   / . \     | |     | | \ \ | |     | |__| | 
         |_|   |______| /_/ \_\    |_|     |_|  \_\|_|      \_____| 
                                                            
================================================================================
                         [ 어둠의 숲과 잊혀진 용사 ]
--------------------------------------------------------------------------------

                            1. 새로운 모험 떠나기
                            2. 모험 이어하기
                            3. 명예의 전당 (업적 확인)
                            4. 게임 종료

--------------------------------------------------------------------------------
)" << endl;

    cout << "  >> 용사여, 선택을 내리시게: ";

    int choice;
    cin >> choice;

    return choice;
}

void UIManager::DrawPlayerAscii(Character* player)
{
    gotoxy(6, 8);
    cout << "   O";
    gotoxy(6, 9);
    cout << "  /|\\";
    gotoxy(6, 10);
    cout << "  / \\";
}

void UIManager::DrawMonsterAscii(Monster* monster)
{
    gotoxy(55, 4);
    cout << "  /\\_/\\";
    gotoxy(55, 5);
    cout << " ( o.o )";
    gotoxy(55, 6);
    cout << "  > ^ <";
}

void UIManager::DrawBattleScreen(Character* player, Monster* monster, string message, bool showMenu)
{
    system("cls");

    DrawMonsterStatus(monster);
    DrawMonsterAscii(monster);

    DrawPlayerAscii(player);
    DrawPlayerStatus(player);

    gotoxy(0, 15);
    cout << "--------------------------------------------------------------------------------";
    gotoxy(2, 16);

    if (showMenu)
    {
        cout << "1. 공격   2. " << player->Getskillname()
            << "   3. 아이템   4. 도주   5. 자동사냥";
    }
    else
    {
        cout << message;
    }

    gotoxy(0, 17);
    cout << "--------------------------------------------------------------------------------";

    if (showMenu)
    {
        gotoxy(2, 18);
        cout << "선택: ";
    }
    else
    {
        gotoxy(2, 18);
        cout << "계속하려면 엔터...";
    }
}

void UIManager::UpdateBattleMessage(string message)
{
    gotoxy(0, 15);

    cout << "                                                                                ";
    gotoxy(0, 15);

    cout << "--------------------------------------------------------------------------------";

    gotoxy(2, 16);

    cout << "                                                                                ";
    gotoxy(2, 16);

    cout << message;

    gotoxy(0, 17);

    cout << "--------------------------------------------------------------------------------";
}