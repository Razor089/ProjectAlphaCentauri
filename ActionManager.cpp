#include "ActionManager.hpp"

ActionManager *ActionManager::m_instance = 0;

ActionManager *ActionManager::Instance()
{
    if(m_instance == 0) m_instance = new ActionManager();
    return m_instance;
}

void ActionManager::RegisterAction(std::string key, Action *action)
{
    if(m_mappa_azioni.count(key) > 0) return;

    m_mappa_azioni[key] = action;
}