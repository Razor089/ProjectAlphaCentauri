#pragma once
#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "State.hpp"

class StateMachine
{
public:
    StateMachine() {}

    void ChangeState(State<StateMachine> *state);
    void Update();
    void Execute();

    State<StateMachine> *GetCurrentState() { return m_current; }
private:
    State<StateMachine> *m_current;
};

#endif