#include "Station.hpp"
#include <iostream>

void Station::Update()
{
    m_last_angle = m_rotation_speed * ((float)SDL_GetTicks() / 1000);

    if(m_fighters.size() > 0)
    {
        for(std::vector<Entity *>::iterator it = m_fighters.begin(); it != m_fighters.end(); ++it)
        {
            (*it)->Seek(*m_target->GetPosition());
            (*it)->Separate(m_fighters);
            (*it)->Align(m_fighters);
            (*it)->Cohesion(m_fighters);
            (*it)->Update();
        }
    }
    
    if(m_fighters.size() == 0 && IsSpawnDefense())
    {
        SetSpawnDefende(false);
    }
    
}

void Station::Draw()
{
    Entity::Draw();
    if(m_fighters.size() > 0)
    {
        for(std::vector<Entity *>::iterator it = m_fighters.begin(); it != m_fighters.end(); ++it)
        {
            (*it)->Draw();
        }
    }
}

void Station::Alert(Entity *target)
{
    float dist = Vector::Distance(*target->GetPosition(), m_position);
    //std::cout << "Dist: " << dist << " IsSpanw: " << IsSpawnDefense() << std::endl;
    if(dist <= 210 && !IsSpawnDefense())
    {
        // Spawn Defense
        m_spawn_defense = true;
        m_target = target;
        SpawnDefense();
    }
}

void Station::SpawnDefense()
{
    for(int i = 0; i < NUM_FIGHTERS; ++i)
    {
        srand((int)time(0) * i * 30);
        int x = m_position.x + ((rand() % 50) - 50);
        int y = m_position.y + ((rand() % 50) - 50);
        Entity *fighter = new Entity("Fighter");
        fighter->SetPosition(Vector(x, y));
        fighter->SetSize(26,20);
        fighter->SetRadius(26);
        fighter->SetMaxSpeed(10);
        fighter->SetMass(5);
        m_fighters.push_back(fighter);
        std::cout << "Fighter [" << i << "]: " << x << " " << y << std::endl;
    }

    std::cout << "Fighters Size: " << m_fighters.size() << std::endl;
}
