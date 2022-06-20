#pragma once
#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "State.hpp"
#include <iostream>

class StateMachine
{
public:
    StateMachine() : m_current(0) {}

    void ChangeState(State<StateMachine> *state);
    void Update();
    void Execute();

    State<StateMachine> *GetCurrentState() { return m_current; }
private:
    State<StateMachine> *m_current;
};

#endif