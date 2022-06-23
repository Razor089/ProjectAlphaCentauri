#include "Missile.hpp"
#include "ParticleManager.hpp"

void Missile::Update()
{
    ParticleManager::Instance()->GetParticle("MissileTrail")->SetOrigin(m_position);
    ParticleManager::Instance()->GetParticle("MissileTrail")->AddParticle();
    ParticleManager::Instance()->GetParticle("MissileTrail")->Update();
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
    ParticleManager::Instance()->GetParticle("MissileTrail")->Draw();
    Entity::Draw();
}