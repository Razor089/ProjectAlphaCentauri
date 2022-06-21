#include "Missile.hpp"

void Missile::Update()
{
    if(m_time_to_live > 0)
    {
        Seek(m_target);
        Move();
        --m_time_to_live;
    }
}

void Missile::Draw()
{
    Entity::Draw();
}