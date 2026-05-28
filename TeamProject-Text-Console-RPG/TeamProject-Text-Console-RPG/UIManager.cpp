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

void UIManager::ShowTitleScreen()
{
    while(true)
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
        
        if (!(cin >> choice)) // 여기서 입력 받고
        {
            system("cls");
            cout << "잘못된 입력입니다.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();

            continue;
        }

        switch (choice)
        {
        case 1:
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
            break;

        case 2:
            
            return;
       
        default:
            system("cls");
            cout << " 잘못된 입력입니다." << endl;
            cin.ignore();
            cin.get();
            continue;
        }
    }
}

void UIManager::ShowEnding()
{
    while (true)
    {
        system("cls"); // 화면 초기화

        // 정통 텍스트 RPG 느낌을 살린 아스키 아트와 UI
        cout << R"(
 ======================================================================================
                  //////  //    // ////////  //// //    //   //////  
                 //      ///   // //     //  //  ///   //  //    // 
                 //      ////  // //     //  //  ////  //  //       
                 //////  // // // //     //  //  // // //  //   /// 
                 //      //  //// //     //  //  //  ////  //    // 
                 //      //   /// //     //  //  //   ///  //    // 
                  //////  //    // ////////  //// //    //   ////// 
 ======================================================================================
                                     [ Ending1 ]                                      
                                   << 밝혀진 진실 >>                                  
---------------------------------------------------------------------------------------

                               1. Calamity(재앙) 엔딩 보기

                               2. 제작자 소개

                               3. 게임 종료
                                
---------------------------------------------------------------------------------------
)";

        int choice;

        if (!(cin >> choice)) // 여기서 입력 받고
        {
            system("cls");
            cout << "잘못된 입력입니다.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cin.get();

            continue;
        }

        switch (choice)
        {
        case 1:
            system("cls");

            //cout << ""; cin.get();

            cout << "리암 : 하아... 하아...."; cin.ignore(); cin.get();
            cout << endl;
            cout << "리암은 우여곡절 끝에 마왕 칼라미티를 쓰러뜨렸다."; cin.get();
            cout << "가족과 마을 사람들의 원수를 드디어 물리친 것이다."; cin.get();
            cout << "최후의 순간에 마왕은 어떤 표정을 짓고 있을까."; cin.get();
            cout << "자신의 마을을 덮친 것을 후회하고 있을까?  아니면 죽기를 두려워하며 울고 있을까?"; cin.get();
            cout << "리암은 마왕의 얼굴을 확인하기 위해 마왕의 투구를 벗겼다."; cin.get();
            cout << endl; cin.get();
            cout << "리암 : 이..이럴수가? 이게 어떻게 된거지?";
            cout << endl; cin.get();
            cout << "투구 속에서 등장한 얼굴은 그 어떤 표정보다도 놀라웠다."; cin.get();
            cout << "투구를 벗은 마왕 칼라미티의 얼굴은 놀랍게도 리암의 얼굴과 쏙 빼닮아있었다."; cin.get();
            cout << endl; cin.get();
            cout << "리암 : 이건 나?"; cin.get();
            cout << endl; cin.get();
            cout << "리암은 당황을 금치 못했다."; cin.get();
            cout << "무슨 일이 일어나고 있는지 그는 알 수 없었다."; cin.get();
            system("cls");

            cout << "당황하고 있는 리암을 보며 마왕은 입을 열었다."; cin.get();
            cout << endl; cin.get();
            cout << "마왕 : 진실이 궁금한가?"; cin.get();
            cout << "리암 : ... ..."; cin.get();
            cout << endl; cin.get();
            cout << "리암은 태어날 때부터 모험가의 재능을 타고 났었다."; cin.get();
            cout << "리암의 부모님들은 이를 알았지만 리암이 성장하면 자연스럽게 해결되리라 생각하며 대수롭지 않게 생각했다."; cin.get();
            cout << "그러나 리암의 부모님들은 미처 깨닫지 못했다."; cin.get();
            cout << "리암의 능력이 너무나도 강력하다는 것을 말이다."; cin.get();
            cout << endl;
            cout << "리암은 자신 속에 있는 힘을 사용하지 못하고 나날히 그것을 억누르며 성장했다."; cin.get();
            cout << "단순한 훈련이나 휴식으로는 그 방대한 힘을 배출할 수 없었다."; cin.get();
            cout << "그 힘의 사용법을 더 빨리 터득했어야 했다."; cin.get();
            cout << "그리고 그 힘은 리암 안에서 쌓이고 쌓여 가득차게 되었던 것이다."; cin.get();
            cout << "문제의 그 날..."; cin.get();
            cout << endl;

            cout << "-----------------------------------------------------------------------" << endl;
            cout << "리암의 힘은 그 방대함을 견디지 못하고 폭발했다."; cin.get();
            cout << "-----------------------------------------------------------------------" << endl; cin.get();
            system("cls");

            cout << "그 날 아침, 리암의 몸이 묘하게 상쾌했던 이유는 그동안 축적되었던 힘이 개방되었기 때문이었다."; cin.get();
            cout << "마을사람들을 죽인 것은 그날 보았던 마왕 칼라미티가 아닌 리암 본인, 리암 안에 있던 강대한 힘이었던 것이다."; cin.get();
            cout << "그리고 그 얘기를 죽어가는 마왕으로 부터 듣게 되었다."; cin.get();
            cout << endl;
            cout << "리암 : 그.. 그럴리가 없어."; cin.get();
            cout << "마왕 : 마을사람들을 죽인건 리암. 바로 너다."; cin.get();
            cout << "마왕 : 내가 죽는 순간. 너는 '시간여행' 스킬을 획득하게 될 것이다. "; cin.get();
            cout << "마왕 : 그것으로 너의 힘이 폭발하던 시간으로 돌아가서 너를 죽여라."; cin.get();
            cout << "마왕 : 그것이 마을의 멸망을 막을 유일한 방법이다."; cin.get();
            cout << endl;
            cout << "이 말을 마지막으로 마왕은 숨을 거두었다."; cin.get();
            cout << endl;
            cout << "리암 : 물어볼게 더 많았는데... 난 어떻게 해야되는거지?"; cin.get();
            cout << endl;
            cout << "그 순간 리암은 '시간여행' 스킬을 획득했다."; cin.get();
            cout << "원하는 순간으로 돌아갈 수 있었다."; cin.get();
            cout << "리암은 흔들리는 마음을 붙잡고 다짐했다."; cin.get();
            cout << "리암은 결심한 듯이 바닥에 굴러다니던 마왕의 투구를 자신의 머리에 뒤집어 썼다."; cin.get();
            cout << "마왕의 망토까지 걸치니 영락없는 마왕 칼라미티의 모습이었다."; cin.get();
            system("cls");

            cout << "리암. 아니 이제 마왕으로 모습을 바꾼 칼라미티는 모든 사건의 시작점으로 돌아와 있었다."; cin.get();
            cout << "아직 해가뜨기 전 캄캄한 새벽."; cin.get();
            cout << "칼라미티는 수없이 고민을 계속했다."; cin.get();
            cout << "과거의 자신을 죽이기 위해 칼을 높이 들었다."; cin.get();
            cout << endl;
            cout << "칼라미티 : 죽일 수 없다...."; cin.get();
            cout << endl;
            cout << "자기자신을 죽인다니 불가능하다."; cin.get();
            cout << "도저히 할 수 없었다."; cin.get();
            cout << "자신은 이 선택을 내릴 수 없었다."; cin.get();
            cout << "그리고 그는 이 선택을 미래의 자신에게 떠넘겼다."; cin.get();
            cout << "칼라미티는 리암을 죽이지 못했다."; cin.get();
            cout << "리암의 힘이 폭발했고 마을은 사라졌다."; cin.get();
            system("cls");
           
            cout << "칼라미티 : 하하... 하하하하..."; cin.get();
            cout << endl;
            cout << "자신을 막지 못한 한심함에 웃음이 나온다."; cin.get();
            cout << "자신의 마을을 지키지 못한 슬픔, 자신을 죽이지 못하는 무력함."; cin.get();
            cout << "이 모든 것이 섞여 웃음 밖에 나오지 않는다."; cin.get();
            cout << "눈에 흐르는 눈물은 떠오르는 태양의 빛에 삼켜지고 깊게 눌러쓴 투구에 가려진다."; cin.get();
            cout << "이런 비참한 모습을 저 멀리 리암이 보고 있다."; cin.get();
            cout << "칼라미티를 바라보는 리암은 분노에 차있다."; cin.get();
            cout << "칼라미티는 그 분노가 자신을 향하기를 간절히 바란다."; cin.get();
            cout << "그리고 그 분노를 양식삼아 미래의 자신을 막아주기를 빌었다."; cin.get();
            cout << endl;
            cout << "칼라미티 : 재앙(Calamity), 그 자체로군...."; cin.get();
            cout << endl;
            cout << "마왕의 이름이 칼라미티가 되는 순간이었다."; cin.get();

            system("cls");
            cout << endl;
            cout << "C_______" << endl;
            cout << endl;
            cout << "____ C___" << endl; cin.get();

            system("cls");
            cout << endl;
            cout << "CA______" << endl;
            cout << endl;
            cout << "__A_ C___" << endl; cin.get();

            system("cls");
            cout << endl;
            cout << "CAL_____" << endl;
            cout << endl;
            cout << "L_A_ C___" << endl; cin.get();

            system("cls");
            cout << endl;
            cout << "CALA____" << endl;
            cout << endl;
            cout << "L_A_ CA__" << endl; cin.get();

            system("cls");
            cout << endl;
            cout << "CALAM___" << endl;
            cout << endl;
            cout << "L_AM CA__" << endl; cin.get();

            system("cls");
            cout << endl;
            cout << "CALAMI__" << endl;
            cout << endl;
            cout << "LIAM CA__" << endl; cin.get();

            system("cls");
            cout << endl;
            cout << "CALAMIT_" << endl;
            cout << endl;
            cout << "LIAM CAT_" << endl; cin.get();

            system("cls");
            cout << endl;
            cout << "CALAMITY" << endl;
            cout << endl;
            cout << "LIAM CATY" << endl; cin.get();
            cout << endl << endl << endl;
            cout << "칼라미티(Calamity)" << cin.get() << "-> 리암 케이시(Liam Caty)" << endl; cin.get();
            cout << endl;
            cout << "재앙은 반복된다."; cin.get();
            cout << "주인공 : 리암 케이시(Liam Caty)"; cin.get();
            cout << "마왕 : 칼라미티(Calamity)"; cin.get();
            cout << "마을이름 : 리트(Retry)"; cin.get();
            cout << "-The end-";
                     
            cin.get();
            break;

        case 2: //제작자 소개
            cout << endl;
            cout << "============================================================================" << endl;
            cout << "                                  제작자들                                  " << endl;
            cout << "============================================================================" << endl;
            cout << endl;
            cout << "                                [ 1조 - 1티어 ]                             " << endl;
            cout << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << endl;
            cout << "            ■ 플레이어 캐릭터 생성 (Player Character Creator)" << endl;
            cout << "               - 홍종우" << endl;
            cout << endl;
            cout << "            ■ 아이템 (Item System Developer)" << endl;
            cout << "               - 김로운" << endl;
            cout << endl;
            cout << "            ■ 게임 로그 확인 (Game Log System)" << endl;
            cout << "               - 김경수" << endl;
            cout << endl;
            cout << "            ■ 전투 시스템 (Combat System Developer)" << endl;
            cout << "               - 김현준" << endl;
            cout << endl;
            cout << "            ■ 레벨업 (Level-Up System Developer)" << endl;
            cout << "               - 안재관" << endl;
            cout << endl;
            cout << "            ■ _____________________________________" << endl;
            cout << "               - 양경환" << endl;
            cout << endl;
            cout << "----------------------------------------------------------------------------" << endl;
            cout << "                  Copyright 2026. 1조 - 1티어. All rights reserved.          " << endl;
            cout << "============================================================================" << endl;
            cout << endl;
            break;

        case 3:
        {
            return ;
        }

        default:
            system("cls");
            cout << " 잘못된 입력입니다." << endl;
            cin.ignore();
            cin.get();
            continue;
        }
    }
}