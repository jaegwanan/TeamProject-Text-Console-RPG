#include "UIManager.h"
#include <iostream>
#include <conio.h>

using namespace std;

void UIManager::gotoxy(int x, int y)
{
    cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}

string UIManager::GetGaugeBar(int current, int max, int width)
{
    if (max <= 0) return "[ ERROR ]";

    string bar = "[";
    float percentage = static_cast<float>(current) / max;
    int filledWidth = static_cast<int>(percentage * width);

    if (current > 0 && filledWidth == 0) filledWidth = 1;

    for (int i = 0; i < width; ++i) {
        if (i < filledWidth) bar += "#";
        else bar += "-";
    }
    bar += "]";
    return bar;
}

void UIManager::PrintMessage(string message)
{
    gotoxy(0, 15);
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  " << message << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  (계속하려면 아무 키나 누르세요) ▼";
    _getch();
}

void UIManager::PrintMonsterAppear(string monsterName)
{
    cout << "\033[2J\033[1;1H"; // system("cls") 대체용 화면 지우기
    PrintMessage("앗! 야생의 " + monsterName + "이(가) 나타났다!");
}

void UIManager::DrawMonsterStatus(Monster* monster)
{
    gotoxy(45, 2);
    cout << monster->Getname() << " (Lv." << monster->Getlevel() << ")";

    gotoxy(45, 3);
    cout << "HP: " << GetGaugeBar(monster->Gethp(), monster->Getmaxhp(), 15)
        << " " << monster->Gethp() << "/" << monster->Getmaxhp();
}

void UIManager::DrawPlayerStatus(Character* player)
{
    gotoxy(5, 8);

    if (!player->getActiveTitle().empty()) {
        cout << player->getActiveTitle() << " ";
    }

    cout << player->Getname() << " (Lv." << player->Getlevel() << ")";

    gotoxy(5, 9);
    cout << "HP: " << GetGaugeBar(player->Gethp(), player->Getmaxhp(), 15)
        << " " << player->Gethp() << "/" << player->Getmaxhp();
}

void UIManager::DrawBattleMenu()
{
    gotoxy(0, 15);
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  [무엇을 할까?]" << endl;
    cout << "  1. 싸운다 (일반 공격)" << endl;
    cout << "  2. 스킬 사용" << endl;
    cout << "  3. 가방 (아이템 사용)" << endl;
    cout << "  4. 도망간다" << endl;
    cout << "  5. 자동 전투 (랜덤 행동)" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  >> 입력: ";
}

void UIManager::PrintRunSuccess()
{
    PrintMessage("무사히 도망쳤다!");
}

void UIManager::PrintRunFail()
{
    PrintMessage("도망칠 수 없었다...");
}

void UIManager::PrintWrongInput()
{
    PrintMessage("잘못된 입력입니다. 다시 선택해주세요.");
}

int UIManager::ShowTitleScreen()
{
    cout << "\033[2J\033[1;1H";

    cout << "================================================================================" << endl;
    cout << "                           [ 어둠의 숲과 잊혀진 용사 ]                          " << endl;
    cout << "================================================================================" << endl;
    cout << endl;
    cout << "                              1. 새로운 모험 떠나기                             " << endl;
    cout << "                              2. 모험 이어하기                                  " << endl;
    cout << "                              3. 명예의 전당 (업적 확인)                        " << endl;
    cout << "                              4. 게임 종료                                      " << endl;
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "  >> 용사여, 선택을 내리시게: ";

    int choice;
    cin >> choice;

    return choice;
}

void UIManager::DrawPlayerAscii(Character* player)
{
    vector<string> art = player->GetAsciiArt();

    for (int i = 0; i < art.size(); i++)
    {
        gotoxy(5, 13 + i);
        cout << art[i];
    }
}

void UIManager::DrawMonsterAscii(Monster* monster)
{
    vector<string> art = monster->GetAsciiArt();
    for (int i = 0; i < art.size(); i++)
    {
        gotoxy(55, 4 + i);
        cout << art[i];
    }
}

void UIManager::DrawBattleScreen(Character* player, Monster* monster, string message, bool showMenu)
{
    cout << "\033[2J\033[1;1H";

    DrawMonsterStatus(monster);
    DrawMonsterAscii(monster);

    DrawPlayerAscii(player);
    DrawPlayerStatus(player);

    gotoxy(0, 22);
    cout << "--------------------------------------------------------------------------------";
    gotoxy(2, 23);

    if (showMenu)
    {
        cout << "1. 공격   2. " << player->Getskillname()
            << "   3. 아이템   4. 도주   5. 자동사냥";
    }
    else
    {
        cout << message;
    }

    gotoxy(0, 24);
    cout << "--------------------------------------------------------------------------------";

    if (showMenu)
    {
        gotoxy(2, 25);
        cout << "선택: ";
    }
    else
    {
        gotoxy(2, 25);
        cout << "계속하려면 엔터...";
    }
}

void UIManager::UpdateBattleMessage(string message)
{
    gotoxy(0, 22);
    cout << "                                                                                ";

    gotoxy(0, 22);
    cout << "--------------------------------------------------------------------------------";

    gotoxy(2, 23);
    cout << "                                                                                ";

    gotoxy(2, 23);
    cout << message;

    gotoxy(0, 24);
    cout << "--------------------------------------------------------------------------------";
}