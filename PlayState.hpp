#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "State.hpp"
#include "StateMachine.hpp"
#include "Entity.hpp"
#include "GUIEntity.hpp"
#include "Vector.hpp"
#include "QuadTree.hpp"
#include <vector>

class PlayState : public State<StateMachine>
{
public:
    PlayState() {}

    virtual void Enter(StateMachine *sm);
    virtual void Update(StateMachine *sm);
    virtual void Execute(StateMachine *sm);
    virtual void Exit(StateMachine *sm);
    
    std::vector<Entity *> *GetListEntities() { return &m_list_entity; }
    Vector GetSelectedTarget() { return m_selected_target; }

    std::vector<Entity *> m_list_entity;
    std::vector<GUIEntity *> m_list_gui;
private:
    Entity *GetEntityByTag(std::string tag);

    bool m_seeking;
    bool m_targeting;
    Vector m_seek_target;
    Vector m_selected_target;

    int m_fire_delay;

    Entity *m_player;
    QuadTree *quadTree;
    QuadTreeData *player_data;
    QuadTreeData *station_data;
};

#endif