#pragma once
#include "IState.h"
#include "../Selector.h"

class Console;
class Keyboard;
class StateMachine;

class MainMenuState : public IState
{
private:
    Console& m_Console;
    Keyboard& m_Keyboard;
    StateMachine& m_StateMachine;

    Selector<> m_MenuSelector;

    int m_CenterScreenW;
    int m_ScreenHeight;

    // 아스키 아트와 화면을 그리는 내부 함수
    void DrawTitle();

    // 메뉴 선택 시 호출될 콜백 함수
    void OnMenuSelect(int index, std::vector<std::wstring> data);

public:
    MainMenuState(Console& console, Keyboard& keyboard, StateMachine& stateMachine);
    ~MainMenuState() = default;

    virtual void OnEnter() override;
    virtual void OnExit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void ProcessInputs() override;

    virtual bool Exit() override { return false; }
};