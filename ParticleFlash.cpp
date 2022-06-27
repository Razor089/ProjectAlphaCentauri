#include "ParticleFlash.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"

void ParticleFlash::Update()
{
    Particle::Update();
    m_ttl--;
}

void ParticleFlash::Draw()
{
    TextureManager::Instance()->DrawParticle(m_texture, m_position.x, m_position.y, 0, 0, 6000, 4365, 150, 109, 0, m_ttl, Engine::Instance()->GetRenderer(), true);
}