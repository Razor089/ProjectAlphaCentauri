#pragma once
#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "State.hpp"
#include "StateMachine.hpp"
#include "GUIEntity.hpp"
#include <vector>

class MainMenuState : public State<StateMachine>
{
public:
    void Enter(StateMachine *sm);
    void Update(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm);
private:
    std::vector<GUIEntity *> m_list_gui_objects;
};

#endif