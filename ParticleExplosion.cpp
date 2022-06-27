#include "ParticleExplosion.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"
#include <iostream>

int t_live;

void ParticleExplosion::Update()
{
    Particle::Update();
    m_blue -= 3;
    m_green -= 2;
    m_red--;
    if(m_blue < 0) m_blue = 0;
    if(m_green < 0) m_green = 0;
    if(m_red < 0) m_red = 0;
    /*
    t_live = m_ttl - 20;
    if(t_live < 0) t_live = 0;
    */
}

void ParticleExplosion::Draw()
{
    std::cout << "Explosion!" << std::endl;
    TextureManager::Instance()->DrawParticleWithColor(m_texture, m_position.x, m_position.y, 0, 0, 629, 581, 100, 100, m_red, m_green, m_blue, m_angle, m_ttl, Engine::Instance()->GetRenderer(), true);
    //TextureManager::Instance()->DrawParticle("BlueEffect", m_position.x, m_position.y, 0, 0, 6000, 4365, 300, 180, 0, t_live, Engine::Instance()->GetRenderer(), true);
}