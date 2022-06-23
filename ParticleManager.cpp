#include "ParticleManager.hpp"

ParticleManager *ParticleManager::m_instance = 0;

ParticleManager *ParticleManager::Instance()
{
    if(m_instance == 0) m_instance = new ParticleManager();
    return m_instance;
}

void ParticleManager::AddParticle(std::string key, ParticleSystem *particle)
{
    if(m_mappa_particelle.count(key) >= 1) return;
    m_mappa_particelle[key] = particle;
}

ParticleSystem *ParticleManager::GetParticle(std::string key)
{
    return m_mappa_particelle[key];
}