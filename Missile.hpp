#pragma once
#ifndef MISSILE_H
#define MISSILE_H
#include "Entity.hpp"
#include "Vector.hpp"

class Missile : public Entity
{
private:
    Vector m_target;

    int m_time_to_live;
public:
    Missile() : Entity(), m_target(), m_time_to_live(300) 
    {
        m_tag = "Missile";
    }

    Missile(std::string texture, Vector target) : Entity(texture), m_target(target), m_time_to_live(300) 
    {
        m_tag = "Missile";
    }

    void SetTarget(Vector target) { m_target = target; }
    Vector GetTarget() { return m_target; }

    void Update();
    void Draw();
};

#endif