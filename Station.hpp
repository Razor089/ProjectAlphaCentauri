#pragma once
#ifndef STATION_H
#define STATION_H
#include "Entity.hpp"
#include <string>
#include <vector>

const int NUM_FIGHTERS = 5;

class Station : public Entity
{
public:
    Station() : Entity(),
                m_rotation_speed(0),
                m_spawn_defense(false),
                m_target(0)
    {}

    Station(std::string texture) : Entity(texture),
                                   m_rotation_speed(0),
                                   m_spawn_defense(false),
                                   m_target(0)
    {}

    void Update();
    void Draw();
    void Alert(Entity *target);

    void SetTarget(Entity *target) { m_target = target; }
    Entity *GetTarget() { return m_target; }

    std::vector<Entity *> GetListFighters() const { return m_fighters; }

    void SetRotationSpeed(float rotation) { m_rotation_speed = rotation; }
    void SetSpawnDefende(bool val) { m_spawn_defense = val; }

    bool IsSpawnDefense() { return m_spawn_defense; }
private:
    float m_rotation_speed;

    bool m_spawn_defense;

    void SpawnDefense();

    std::vector<Entity *> m_fighters;
    Entity *m_target;
};

#endif