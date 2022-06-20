#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "State.hpp"
#include "StateMachine.hpp"
#include "Entity.hpp"
#include "Vector.hpp"
#include <vector>

class PlayState : public State<StateMachine>
{
public:
    PlayState() {}

    virtual void Enter(StateMachine *sm);
    virtual void Update(StateMachine *sm);
    virtual void Execute(StateMachine *sm);
    virtual void Exit(StateMachine *sm);

    std::vector<Entity *> m_list_entity;
private:
    Entity *GetEntityByTag(std::string tag);

    bool m_seeking;
    bool m_targeting;
    Vector m_seek_target;
    Vector m_selected_target;

    Entity *m_player;
};

#endif