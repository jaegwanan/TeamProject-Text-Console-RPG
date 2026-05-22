#include "MainMenuState.h"
#include "../Console.h"
#include "../inputs/Keyboard.h"
#include "StateMachine.h"
#include "GameState.h" // 뉴 게임 선택 시 넘어갈 상태

using namespace std::placeholders;

MainMenuState::MainMenuState(Console& console, Keyboard& keyboard, StateMachine& stateMachine)
    : m_Console(console)
    , m_Keyboard(keyboard)
    , m_StateMachine(stateMachine)
    , m_MenuSelector{ console, keyboard, {L"Continue", L"New Game", L"Settings", L"Exit"}, SelectorParams{0, 25, 1, 0, 3, L"->" } }
{
    m_CenterScreenW = m_Console.GetHalfWidth();
    m_ScreenHeight = m_Console.GetScreenHeight();

    // 메뉴가 화면 중앙에 오도록 x 좌표 재조정 (임의로 중앙에서 약간 왼쪽으로)
    m_MenuSelector.GetData();
    m_MenuSelector.SetSelectionFunc(std::bind(&MainMenuState::OnMenuSelect, this, _1, _2));
}

void MainMenuState::OnEnter()
{
    m_Console.ClearBuffer();
}

void MainMenuState::OnExit()
{
    m_Console.ClearBuffer();
}

void MainMenuState::Update()
{
    // 메인 메뉴에서는 특별한 실시간 업데이트 로직이 필요 없을 수 있습니다.
}

void MainMenuState::DrawTitle()
{
    // 기준이 되는 X, Y 좌표 설정
    int startY = 5;

    // 검 손잡이 부분 (화면 정중앙)
    m_Console.Write(m_CenterScreenW - 2, startY++, L" (_)", YELLOW);
    m_Console.Write(m_CenterScreenW - 2, startY++, L" | |", BLUE);
    m_Console.Write(m_CenterScreenW - 2, startY++, L" | |", BLUE);
    m_Console.Write(m_CenterScreenW - 2, startY++, L" | |", BLUE);
    m_Console.Write(m_CenterScreenW - 4, startY++, L"o=======o", BLUE);

    // 검날 부분과 TEXT RPG 글자
    // TEXT (왼쪽)
    int textX = m_CenterScreenW - 35;
    // RPG (오른쪽)
    int rpgX = m_CenterScreenW + 5;
    int bladeY = startY;

    // 아스키 아트 한 줄씩 그리기 (실제 이미지와 비슷한 형태로 조정)
    m_Console.Write(textX, bladeY, L" _____  _____ __  __ ____ ", GREEN);
    m_Console.Write(rpgX, bladeY++, L" _____  ____   _____ ", GREEN);

    m_Console.Write(textX, bladeY, L"|_   _||  ___|\\ \\/ /|  _ \\", GREEN);
    m_Console.Write(m_CenterScreenW - 1, bladeY, L"| |", WHITE); // 검날
    m_Console.Write(rpgX, bladeY++, L"|  __ \\|  _ \\ / ____|", GREEN);

    m_Console.Write(textX, bladeY, L"  | |  | |__   \\  / | |_) |", GREEN);
    m_Console.Write(m_CenterScreenW - 1, bladeY, L"| |", WHITE);
    m_Console.Write(rpgX, bladeY++, L"| |__) | |_) | |  __ ", GREEN);

    m_Console.Write(textX, bladeY, L"  | |  |  __|  /  \\ |  __/ ", GREEN);
    m_Console.Write(m_CenterScreenW - 1, bladeY, L"| |", WHITE);
    m_Console.Write(rpgX, bladeY++, L"|  _  /|  __/| | |_ |", GREEN);

    m_Console.Write(textX, bladeY, L"  |_|  |____| /_/\\_\\|_|    ", GREEN);
    m_Console.Write(m_CenterScreenW - 1, bladeY, L"| |", WHITE);
    m_Console.Write(rpgX, bladeY++, L"| | \\ \\| |   | |__| |", GREEN);

    // 검 끝부분
    m_Console.Write(m_CenterScreenW - 1, bladeY++, L"\\ /", WHITE);
    m_Console.Write(m_CenterScreenW, bladeY++, L"V", WHITE);

    // 가로 장식 선
    m_Console.DrawPanelHorz(textX, startY + 5, 25, LIGHT_BLUE);
    m_Console.DrawPanelHorz(rpgX, startY + 5, 25, LIGHT_BLUE);
    m_Console.DrawPanelHorz(textX, startY + 6, 25, RED);
    m_Console.DrawPanelHorz(rpgX, startY + 6, 25, RED);
}

void MainMenuState::Draw()
{
    DrawTitle();

    // 셀렉터(메뉴)의 X 좌표를 동적으로 화면 중앙으로 맞추기 (가장 긴 글자 기준)
    // SelectorParams의 x값을 직접 수정하기 어렵다면, 생성자에서 중앙 좌표를 직접 계산하여 넣으시면 됩니다.
    m_MenuSelector.Draw();

    m_Console.Draw();
}

void MainMenuState::ProcessInputs()
{
    m_MenuSelector.ProcessInputs();
}

void MainMenuState::OnMenuSelect(int index, std::vector<std::wstring> data)
{
    switch (index)
    {
    case 0: // Continue
        // 저장된 게임 로드 로직 구현 위치
        break;
    case 1: // New Game
        // 상태 머신을 GameState로 교체 (PushState로 쌓거나 기존 스택을 비우고 추가)
        m_StateMachine.PushState(std::make_unique<GameState>(m_Console, m_Keyboard, m_StateMachine));
        break;
    case 2: // Settings
        // SettingsState 구현 후 연결
        break;
    case 3: // Exit
        // 게임 종료 플래그를 처리할 수 있도록 
        // Game 클래스에서 m_pStateMachine이 비어있으면 종료되도록 로직을 짜두었으므로,
        // 현재 상태를 Pop 해버리면 스택이 비어 게임이 자연스럽게 종료됩니다.
        m_StateMachine.PopState();
        break;
    default:
        break;
    }
}