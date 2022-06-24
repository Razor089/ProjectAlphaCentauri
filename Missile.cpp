#include "Missile.hpp"
#include "ParticleManager.hpp"

void Missile::Update()
{
    ParticleManager::Instance()->GetParticle("MissileTrail")->SetOrigin(m_position);
    if(m_particle_delay)
    {
        m_particle_delay = false;
        ParticleManager::Instance()->GetParticle("MissileTrail")->AddParticle();
    }
    else
    {
        m_particle_delay = true;
    }
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

    if(m_time_to_live <= 0)
    {
        m_dead = true;
    }
}

void Missile::Draw()
{
    Entity::Draw();
}