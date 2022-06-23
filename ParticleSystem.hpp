#pragma once
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Particle.hpp"
#include "Vector.hpp"
#include <vector>
#include <string>

class ParticleSystem
{
private:
    Vector m_origin;

    std::string m_texture;

    std::vector<Particle *> m_particles;
public:
    ParticleSystem() : m_origin(0,0), m_texture("")
    {}

    ParticleSystem(Vector origin, std::string texture) : m_origin(origin), m_texture(texture)
    {}

    ParticleSystem(std::string texture) : m_texture(texture)
    {}

    void AddParticle() { m_particles.push_back(new Particle(m_origin, 255, m_texture)); }
    void SetOrigin(Vector origin) { m_origin = origin; }

    void Update();
    void Draw();
};

#endif