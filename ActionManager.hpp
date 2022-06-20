#pragma once
#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H
#include "Action.hpp"
#include <map>
#include <string>

class ActionManager
{
private:
    ActionManager() {}

    static ActionManager *m_instance;

    std::map<std::string, Action *> m_mappa_azioni;
public:
    static ActionManager *Instance();

    void RegisterAction(std::string key, Action *action);
    Action *GetAction(std::string key) { return m_mappa_azioni[key]; }
};

#endif