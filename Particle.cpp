#include "Particle.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"

void Particle::Update()
{
    m_velocity.Add(m_acceleration);
    m_position.Add(m_velocity);
    m_ttl--;
}

void Particle::Draw()
{
    // Drawin in alpha mode
    TextureManager::Instance()->DrawParticle(m_texture, m_position.x, m_position.y, 0, 0, 135, 133, 20, 20, m_ttl, Engine::Instance()->GetRenderer(), true);
}

bool Particle::IsDead()
{
    if(m_ttl < 0.0)
    {
        return true;
    }
    return false;
}