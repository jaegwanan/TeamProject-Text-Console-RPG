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
    // 주의: Monster.h에 getName()과 getLevel() 게터가 선언되어 있어야 합니다.
    cout << monster->Getname() << " (Lv." << monster->Getlevel() << ")";

    gotoxy(45, 3);
    // 주의: Monster.h에 getHealth()와 getMaxHealth() 게터가 선언되어 있어야 합니다.
    cout << "HP: " << GetGaugeBar(max(0, monster->Gethp()), monster->Getmaxhp(), 15)
        << " " << max(0, monster->Gethp()) << "/" << monster->Getmaxhp();
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
    cout << "HP : " << GetGaugeBar(max(0, player->Gethp()), player->Getmaxhp(), 15)
        << " " << max(0, player->Gethp()) << "/" << player->Getmaxhp();

    gotoxy(5, 10);
    cout << "MP : " << GetGaugeBar(max(0, player->Getmp()), player->Getmaxmp(), 15)
        << " " << max(0, player->Getmp()) << "/" << player->Getmaxmp();

    gotoxy(5, 11);
    cout << "EXP: " << GetGaugeBar(player->Getexp(), player->Getrequiredexp(), 15)
        << " " << player->Getexp() << "/" << player->Getrequiredexp();
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

void story()
{
    system("cls");

    cout << "시골의 어느 한적한 마을 리트. 가장 가까운 도시마저도 마차를 타고 꼬박 하루를 가야하는 마을이다."; cin.ignore(); cin.get();
    cout << "이 마을의 지극히 평범한 소년 리암 케이시(Liam Caty)."; cin.get();
    cout << "그는 농부의 아들로 태어났지만 언젠가는 이 마을을 떠나 세상을 여행하는 모험자가 되겠다는 꿈이 있었다."; cin.get();
    cout << "그러나 모험가는 아무나 될 수가 없다."; cin.get();
    cout << "모험가로서의 재능이 개화해야만 정식적으로 모험가 등록이 가능했던 것이다."; cin.get();
    cout << "언젠가는 자신에게 모험가의 힘이 생길 것이라고 믿으며 리암은 오늘 하루도 열심히 살기로 했다."; cin.get();
    cout << endl;

    cout << "리암의 일과는 단순했다."; cin.get();
    cout << "아침 일찍 일어나 밭에 물과 거름을 주었고 마을 주변 몬스터가 들어오지 못하도록 울타리를 점검했다."; cin.get();
    cout << "그리고 남는 시간에 모험가가 되기 위해 검술 훈련을 하는 단순하고 평화로운 일상의 반복이었다."; cin.get();
    cout << "너무 단조롭고 반복되는 탓이었을까?"; cin.get();
    cout << endl;

    cout << "-----------------------------------------------------------------------" << endl;
    cout << "최근들어 리암은 잠을 많이 자도 피곤하고 몸이 무거운 느낌이 자주 들었다." << endl;
    cout << "-----------------------------------------------------------------------" << endl; cin.get();
    system("cls");

    cout << "그러던 어느 날, 리암의 인생을 바꾼 그 일은 갑작스럽게 일어났다."; cin.get();
    cout << "이른 아침 리암이 눈을 떴을 때, 리암은 평소와 달리 몸이 매우 상쾌함을 느꼈다."; cin.get();
    cout << "창문 밖은 아직 어둠에 쌓여있지만 새소리와 함께 아침이 조금씩 밝아오는 중이었다."; cin.get();
    cout << "그러나 평소와는 분위기가 사뭇 달랐다."; cin.get();
    cout << "새소리 말고도 들려와야할 소리들이 들려오지 않았다."; cin.get();
    cout << "아침을 깨우는 부모님의 소리, 이른 아침부터 농사를 짓는 마을 사람들의 웅성거리는 소리, 땅을 가는 소리 등"; cin.get();
    cout << "들려와야할 그 어떤 소리도 들려오지 않았다."; cin.get();
    cout << "어떻게 된 것인지 확인하기 위해 집 밖으로 나온 리암은 눈 앞에 펼쳐진 광경을 믿을 수 없었다."; cin.get();
    cout << "리암의 집을 제외한 마을 전체가 흔적도 없이 사라져있던 것이다."; cin.get();
    cout << endl;

    cout << "리암은 고개를 돌려 주변을 확인했다."; cin.get();
    cout << "그리고 아침해가 떠오르는 산 너머로 경쾌하게 웃으며 날아가고 있는 존재를 발견했다."; cin.get();
    cout << "필시 그가 이 마을을 파괴한 것이리라."; cin.get();
    cout << "아침 햇살 너머로 사라져가는 그 존재를 바라보며 리암은 참을 수 없는 분노를 느꼈다."; cin.get();
    cout << "그 분노 속에서 리암은 자신의 몸이 변화함을 느꼈다."; cin.get();
    cout << "모험가로서의 능력이 개화한 것이다."; cin.get();
    cout << "소중한 사람들이 다 없어지고 난 후, 이제서야 모험가로서 활동할 수 있다니 너무나 절망적이었다."; cin.get();
    cout << "그럼에도 리암의 목표는 정해졌다."; cin.get();
    cout << endl;
    cout << "                    마을 사람들을 죽인 녀석에게 복수한다"; cin.get();
    cout << endl;

    cout << "훗날 이 사건을 일으킨 존재에게는 칼라미티 <Calamity:재앙> 이라는 별명이 붙는다."; cin.get();
    cout << "마을을 멸망시킨 마왕 칼라미티를 무찌르기 위한 시골청년 리암의 모험담."; cin.get();
    cout << "그 모험담이 이제 시작된다."; cin.get();

    cin.get();
}

int UIManager::ShowTitleScreen()
{
    while (true)
    {
        system("cls"); // 화면 초기화

        // 정통 텍스트 RPG 느낌을 살린 아스키 아트와 UI
        cout << R"(
 ======================================================================================
                                                                                       
    //////      ///      //           ///      //     //  //// //////// //    //       
   //    //    // //     //          // //     ///   ///   //     //     //  //        
   //         //   //    //         //   //    //// ////   //     //      ////         
   //        //     //   //        //     //   // /// //   //     //       //          
   //        /////////   //        /////////   //  /  //   //     //       //          
   //    //  //     //   //        //     //   //     //   //     //       //          
    //////   //     //   ////////  //     //   //     //  ////    //       //          
                                                                                       
 ======================================================================================
                                  [ 1조 - Text RPG ]                                  
                             << 부제 - 시골청년 리암의 모험 >>                         
---------------------------------------------------------------------------------------

                               1. Calamity(재앙) 스토리 보기

                               2. 게임 바로 시작하기
                                
---------------------------------------------------------------------------------------
)";

        int choice;

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            story();
        }

        return choice;
    }
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