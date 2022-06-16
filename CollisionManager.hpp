#pragma once
#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include <vector>
#include "Entity.hpp"

class CollisionManager
{
private:
    CollisionManager()
    {}

    static CollisionManager *m_instance;
public:
    static CollisionManager *Instance() 
    {
        if(m_instance == 0)
        {
            m_instance = new CollisionManager();
        }
        return m_instance;
    }

    void CollisionBounds(std::vector<Entity *> entity_list);
    void CollisionShip(Entity *ship, std::vector<Entity *> entity_list);
};

#endif