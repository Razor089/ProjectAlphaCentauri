#include "StateMachine.hpp"

void StateMachine::ChangeState(State<StateMachine> *state)
{
    if(m_current != 0) m_current->Exit(this);

    m_current = state;

    if(m_current != 0) m_current->Enter(this);
}

void StateMachine::Update()
{
    if(m_current != 0) m_current->Update(this);
}

void StateMachine::Execute()
{
    if(m_current != 0) m_current->Execute(this);
}
