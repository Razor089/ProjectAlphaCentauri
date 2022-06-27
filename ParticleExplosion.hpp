#pragma once
#ifndef PARTICLEEXPLOSION_H
#define PARTICLEEXPLOSION_H
#include "Particle.hpp"
#include <string>

class ParticleExplosion : public Particle
{
private:
    int m_red;
    int m_green;
    int m_blue;
public:
    ParticleExplosion() : Particle(), m_red(255), m_green(255), m_blue(255) 
    {}

    ParticleExplosion(Vector position, float angle, int ttl, std::string texture) : Particle(position, angle, ttl, texture),
                                                                                    m_red(255),
                                                                                    m_green(255),
                                                                                    m_blue(255)
    {}

    virtual void Update();
    virtual void Draw();
};

#endif