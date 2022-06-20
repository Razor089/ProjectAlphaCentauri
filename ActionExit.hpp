#pragma once
#ifndef ACTIONEXIT_H
#define ACTIONEXIT_H
#include "Action.hpp"
#include "Engine.hpp"

class ActionExit : public Action
{
public:
    ActionExit() {}
    void FireAction()
    {
        Engine::Instance()->IsRunning = false;
    }
};

#endif