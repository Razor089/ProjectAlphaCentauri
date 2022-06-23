#include "ParticleSystem.hpp"

void ParticleSystem::Update()
{
    for(std::vector<Particle *>::iterator it = m_particles.begin(); it != m_particles.end(); ++it)
    {
        (*it)->Update();
        if((*it)->IsDead())
        {
            delete((*it));
            m_particles.erase(it);
            --it;
        }
    }
}

void ParticleSystem::Draw()
{
    for(std::vector<Particle *>::iterator it = m_particles.begin(); it != m_particles.end(); ++it)
    {
        (*it)->Draw();
    }
}