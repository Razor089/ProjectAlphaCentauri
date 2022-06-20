#pragma once
#ifndef ACTIONNEWGAME_H
#define ACTIONNEWGAME_H
#include "Action.hpp"
#include "Engine.hpp"
#include "PlayState.hpp"

class ActionNewGame : public Action
{
public:
    ActionNewGame() {}
    void FireAction()
    {
        Engine::Instance()->GetStateMachine()->ChangeState(new PlayState());
    }
};

#endif