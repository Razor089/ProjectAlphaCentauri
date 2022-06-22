#include "Missile.hpp"

void Missile::Update()
{
    if(m_velocity.Length() != 0)
    {
        m_last_angle = m_velocity.Heading();
    }
    if(m_time_to_live > 0)
    {
        if(m_delay == 0)
        {
            Seek(m_target);
        }
        --m_time_to_live;
    }
    Move();
    if(m_delay > 0)
    {
        m_delay--;
    }
}

void Missile::Draw()
{
    Entity::Draw();
}